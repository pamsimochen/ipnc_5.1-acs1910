#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <drv_csl.h>
#include <drv_gpio.h>
#include "drv.h"
#include "drv_ACS1910.h"
#include "cmd_server.h"
#include "VIM_API_Release.h"
#include "drv_roi.h"
#include <sys/time.h>

unsigned int shutter_max_g[16] = {200001, 99841, 40001, 33281, 29974, 24996, 19983, 16641, 9992, 8321, 3983, 1992, 996, 178, 72, 0};

 
int ROI_SetVIMAEMode(pVF_AE_MODE_S pAEMode)
{
    int ret = OSA_SOK;
    AE_MODE_S VIMAEMode;

    sem_wait(&vim_aemode_sem);
    VIMAEMode.AE_Shutter_Mode = (AE_SHUTTER_MODE_E)AE_MANUAL_VIM;
    VIMAEMode.Exposuretime = pAEMode->Exposuretime;
    VIMAEMode.DGain = pAEMode->Gain;;
    VIMAEMode.DGainDeci = pAEMode->GainDeci;    
    VIMAEMode.AE_MaxET_Mode = (AE_MAXET_MODE_E)pAEMode->AE_MaxET_Mode;
    VIMAEMode.MaxET = pAEMode->MaxET;
    VIMAEMode.MaxDGain = pAEMode->MaxGain;
    //ROI_DEBUG("AE_Shutter_Mode= %d\n", VIMAEMode.AE_Shutter_Mode);
    //ROI_DEBUG("AE_MaxET_Mode = %d\n", VIMAEMode.AE_MaxET_Mode);
    ROI_DEBUG("Exposuretime = %d\n", VIMAEMode.Exposuretime);
    ROI_DEBUG("DGain = %d\n", VIMAEMode.DGain);
    //ROI_DEBUG("MaxDGain = %d\n", VIMAEMode.MaxDGain);
    ROI_DEBUG("DGainDeci = %d\n", VIMAEMode.DGainDeci);
    sem_wait(&vim_sem);
    ret = VIM_ISP_SetAEMode(VIMAEMode);
    sem_post(&vim_sem);
    if(ret != VIM_SUCCEED)
    {
        OSA_ERROR("VIM Set AEMode error = %d\n", ret);
        sem_post(&vim_aemode_sem);
        return ret;
    }
    sem_post(&vim_aemode_sem);
    return ret;
}

unsigned int VIM_roi_factor(avg_target, avg_current, shutter_gain)
{
    float factor;
    unsigned int shutter_gain_factor;
    factor = ((float)avg_target) / (float)avg_current;
    //ROI_DEBUG("factor = %f\n", factor);
    shutter_gain_factor = (unsigned int)(((float)shutter_gain) * factor + 0.5); 
    return shutter_gain_factor;
}


unsigned int VIM_shutter_calc(unsigned int shutter)
{
    unsigned int shutter_set;

    shutter_set = ((unsigned int)((float)shutter * 69.3))/2464;
    //printf("b = %d ", shutter_set);
    shutter_set = shutter_set * 2464/69.3 + 1;
    //printf("c = %d ", shutter_set);
    //printf("\n");

    return shutter_set; 
}

unsigned char VIM_roi_calc_histogram_avg(unsigned int *shutter, unsigned short *gain)
{
    unsigned short roi0_his_avg, roi1_his_avg, roi2_his_avg;
    unsigned short roi0_height, roi0_width;
    unsigned short roi1_height, roi1_width;
    unsigned short roi2_height, roi2_width;
    unsigned int roi_his_sum, roi1_his_sum, roi2_his_sum;
    unsigned int roi_pix_sum, roi1_pix_sum, roi2_pix_sum;
    unsigned int roi_his_avg; 
    float gaindeci;

    VF_AE_ETGain_S ETGain; 
    ptACS1910ISPAllCfg pISPAllCfg = &(gACS1910_current_cfg.ISPAllCfg);

    DRV_GetVIMETGain(&ETGain);
    *shutter = (ETGain.etus + 1);
    gaindeci = (float)(ETGain.gainValue & 0x003f);
    gaindeci = (gaindeci / 64) * 10 + 0.5;
    *gain = (ETGain.gainValue >> 6) * 10 + (unsigned short)gaindeci;
    //ROI_DEBUG("shutter = %d, gain == %d\n", *shutter, *gain);

    DRV_FPGASPIRead(ROI0_WIDTH_FPGA_REG_ADDR, &roi0_width);
    DRV_FPGASPIRead(ROI0_HEIGHT_FPGA_REG_ADDR, &roi0_height);
    DRV_FPGASPIRead(ROI0_HISTOGRAM_FPGA_REG_ADDR, &roi0_his_avg);
    roi_his_avg = roi0_his_avg & 0xff; 
    roi_pix_sum = roi0_width * roi0_height;
    roi_his_sum = roi_his_avg * roi_pix_sum;
    //ROI_DEBUG("roi0_width = %d, roi0_height = %d\n", roi0_width, roi0_height);
    //ROI_DEBUG("roi0_his_avg = %d, roi0_pix_sum = %d, roi0_his_sum = %d\n", roi_his_avg, roi_pix_sum, roi_his_sum);

    if(pISPAllCfg->AERoi[1].onoff == 1)
    {
        DRV_FPGASPIRead(ROI1_WIDTH_FPGA_REG_ADDR, &roi1_width);
        DRV_FPGASPIRead(ROI1_HEIGHT_FPGA_REG_ADDR, &roi1_height);
        DRV_FPGASPIRead(ROI1_HISTOGRAM_FPGA_REG_ADDR, &roi1_his_avg);
        roi1_his_avg = roi1_his_avg & 0xff; 
        roi_pix_sum = roi_pix_sum + roi1_width * roi1_height;
        roi_his_sum = roi_his_sum + roi1_his_avg * roi1_width * roi1_height;
        roi_his_avg = roi_his_sum / roi_pix_sum; 
        //ROI_DEBUG("roi1_width = %d, roi1_height = %d\n", roi1_width, roi1_height);
        //ROI_DEBUG("roi1_his_avg = %d, roi1+roi0_pix_sum = %d, roi1+roi0_his_sum = %d\n", roi1_his_avg, roi_pix_sum, roi_his_sum);
        //ROI_DEBUG("roi1+0_his_avg = %d\n", roi_his_avg);
    }

    if(pISPAllCfg->AERoi[2].onoff == 1)
    {
        DRV_FPGASPIRead(ROI2_WIDTH_FPGA_REG_ADDR, &roi2_width);
        DRV_FPGASPIRead(ROI2_HEIGHT_FPGA_REG_ADDR, &roi2_height);
        DRV_FPGASPIRead(ROI2_HISTOGRAM_FPGA_REG_ADDR, &roi2_his_avg);
        roi2_his_avg = roi2_his_avg & 0xff; 
        roi_pix_sum = roi_pix_sum + roi2_width * roi2_height;
        roi_his_sum = roi_his_sum + roi2_his_avg * roi2_width * roi2_height;
        roi_his_avg = roi_his_sum / roi_pix_sum;
        //ROI_DEBUG("roi2_width = %d, roi2_height = %d\n", roi2_width, roi2_height);
        //ROI_DEBUG("roi2_his_avg = %d, roi2+roi1+roi0_pix_sum = %d, roi2+roi1+roi0_his_sum = %d\n", roi2_his_avg, roi_pix_sum, roi_his_sum);
        //ROI_DEBUG("roi2+1+0_his_avg = %d\n", roi_his_avg);
    }

    ROI_DEBUG("roi_his_avg = %d\n", roi_his_avg);

    return (unsigned char)roi_his_avg;
}

void VIM_roi_autoexp_thread()
{

    unsigned char roi_avg_current, roi_avg_last;
    float factor;
    VF_AE_ETGain_S ETGain;
    pVF_AE_MODE_S pAEMode = &(gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.AEMode);
    VF_AE_MODE_S AEMode_adj;
    ptACS1910ISPNormalCfg pISPNormalCfg = &(gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg); 
    unsigned int shutter_max;
    unsigned int shutter_min;
    unsigned int shutter = 40001;
    unsigned int shutter_temp;
    unsigned int shutter_max_bigger;
    unsigned short gain_max = 2559;
    unsigned short gain_min = 1;
    unsigned short gain = 10;
    unsigned char dgain = 1;
    unsigned char dgaindeci = 0;
    struct timeval t1, t2 ,t3, t4;
    VF_IRCUT_MODE_S IRCutMode;
    VF_COLORBLACK_MODE_E colorblack;

    unsigned char avg_max, avg_min, avg_target;

    ROI_DEBUG("Hello roi autoexp thread!\n");

    IRCutMode.Mode = gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Mode;
    colorblack = gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.ColorBlackMode;

    while(VIM_roi_autoexp_thread_run)
    {
        if(pAEMode->AE_Shutter_Mode == VF_AE_ROI)
        {
            ROI_DEBUG("=========================================\n");
            ROI_DEBUG("ROI autoexp\n");
            ROI_DEBUG("shutter = %d\n", shutter);
            ROI_DEBUG("dgain = %d\n", dgain);
            ROI_DEBUG("dgaindeci =  %d\n", dgaindeci);

            if(shutter > 40001)
                sleep(1);
            else 
                usleep(1000000);

            //gettimeofday(&t1, NULL);
            if(pAEMode->AE_Shutter_Mode != VF_AE_ROI)
            {
                continue;
            }
            if(pAEMode->AE_MaxET_Mode == AE_MAXET_MANUAL)
                shutter_max = VIM_shutter_calc(pAEMode->MaxET);
            else
                shutter_max = shutter_max_g[pAEMode->AE_MaxET_Mode];
            //ROI_DEBUG("shutter_max = %d\n", shutter_max);
            if(shutter_max > 40001)
                shutter_max_bigger = 1;
            else 
                shutter_max_bigger = 0;

            gain_max = pAEMode->MaxGain * 10;
            sem_wait(&bright_sem);
            avg_max = DEFAULT_AVG_MAX + ((pISPNormalCfg->BaseAttr.BrightnessCoeff - 50) * 2);
            avg_min = DEFAULT_AVG_MIN + ((pISPNormalCfg->BaseAttr.BrightnessCoeff - 50) * 2);
            sem_post(&bright_sem);
            avg_target = (avg_max + avg_min) >> 1; 
            ROI_DEBUG("avg_max = %d, avg_min = %d, avg_target = %d\n", avg_max, avg_min, avg_target);

            memcpy(&AEMode_adj, pAEMode, sizeof(VF_AE_MODE_S));
            //获取当前shutter、gain、roi灰度平均值
            roi_avg_current = VIM_roi_calc_histogram_avg(&shutter, &gain);

            if(shutter > shutter_max)
                shutter = shutter_max;
            if(gain > gain_max)
                gain = gain_max;

            if(roi_avg_current == 0)
                roi_avg_current = 1;
            if(roi_avg_current < avg_min)
            {//曝光不足
                ROI_DEBUG("it is dark\n");
                if(shutter_max_bigger == 0)
                {//最大积分时间小于或者等于帧间隔
                    ROI_DEBUG("shutter_max =< 40000\n");
                    if(shutter < shutter_max)
                    {
                        ROI_DEBUG("shutter is not max\n");
                        shutter = VIM_roi_factor(avg_target, roi_avg_current, shutter);
                        //ROI_DEBUG("shutter a = %d ", shutter);
                        shutter = VIM_shutter_calc(shutter);
                        if(shutter > shutter_max)
                            shutter = shutter_max;
                        dgain = 1;
                        dgaindeci = 0;
                    }
                    else 
                    {
                        ROI_DEBUG("shutter is max, adjust gain\n");
                        gain = VIM_roi_factor(avg_target, roi_avg_current, gain);
                        if(gain > gain_max)
                            gain = gain_max;
                        dgain = gain / 10; 
                        dgaindeci = gain % 10;
                        shutter = shutter_max;
                    }
                }//shutter_max_bigger == 0
                if(shutter_max_bigger == 1)
                {//最大积分时间大于帧间隔
                    ROI_DEBUG("shutter_max > 40000\n");
                    if(shutter < 40001)
                    {
                        ROI_DEBUG("shutter is not bigger than 40000\n");
                        shutter = VIM_roi_factor(avg_target, roi_avg_current, shutter);
                        //ROI_DEBUG("shutter a = %d ", shutter);
                        shutter = VIM_shutter_calc(shutter);
                        if(shutter > 40001)
                            shutter = 40001;
                        dgain = 1;
                        dgaindeci = 0;
                    }
                    else if((shutter == 40001) && (gain < gain_max))
                    {
                        ROI_DEBUG("shutter is 40000, adjust gain\n"); 
                        gain = VIM_roi_factor(avg_target, roi_avg_current, gain);
                        //ROI_DEBUG("gain = %d\n", gain);
                        if(gain > gain_max)
                            gain = gain_max;
                        dgain = gain/10;
                        dgaindeci = gain % 10;
                        shutter = 40001;
                        //ROI_DEBUG("gain = %d, dgain = %d, dgaindeci = %d\n", gain, gain/10, gain%10);
                    }
                    else if((shutter > 40001) && (gain < gain_max))
                    {
                        ROI_DEBUG("shutter > 40000, gain < gain_max");
                        shutter = 40001;
                        dgain = 1;
                        dgaindeci = 0;
                    }
                    else 
                    {
                        ROI_DEBUG("gain == gain_max, adjust shutter down the fps\n");
                        shutter = VIM_roi_factor(avg_target, roi_avg_current, shutter);
                        //ROI_DEBUG("shutter a = %d ", shutter);
                        shutter = VIM_shutter_calc(shutter);
                        if(shutter > shutter_max)
                            shutter = shutter_max;
                        dgain = gain_max/10;
                        dgaindeci = gain_max % 10;
                    }
                }//shutter_max_bigger == 1
                //ROI_DEBUG("gain = %d\n", gain);
                AEMode_adj.Exposuretime = shutter;
                AEMode_adj.Gain = dgain;
                AEMode_adj.GainDeci = dgaindeci;
                //ROI_DEBUG("shutter = %d, dgain = %d, dgaindeci = %d\n", AEMode_adj.Exposuretime, AEMode_adj.Gain, AEMode_adj.GainDeci);
                ROI_SetVIMAEMode(&AEMode_adj);
            }//(roi_avg_current < avg_min)
            else if(roi_avg_current > avg_max)
            {
                ROI_DEBUG("it is light\n");        
                if(shutter_max_bigger == 0)
                {
                    ROI_DEBUG("shutter_max <= 40000\n");
                    if(gain > 10)
                    {
                        ROI_DEBUG("gain > 1, down gain first\n");
                        gain = VIM_roi_factor(avg_target, roi_avg_current, gain);
                        //ROI_DEBUG("gain = %d\n", gain);
                        if(gain < 10)
                            gain = 10;
                        dgain = gain/10;
                        dgaindeci = gain % 10;
                        shutter = shutter_max;
                    }
                    else 
                    {
                        ROI_DEBUG("gain = 1, down shutter\n");
                        dgain = 1;
                        dgaindeci = 0;
                        shutter = VIM_roi_factor(avg_target, roi_avg_current, shutter);
                        //ROI_DEBUG("shutter a = %d ", shutter);
                        shutter = VIM_shutter_calc(shutter);
                        if(shutter < 36)
                            shutter = 36;
                    }
                }//shutter_max_bigger == 0
                if(shutter_max_bigger == 1)
                {
                    //ROI_DEBUG("shutter_max > 40000\n");
                    if(shutter > 40001)
                    {
                        ROI_DEBUG("fps is less than 25fps, should up fps\n");
                        dgain = gain_max / 10;
                        dgaindeci = gain_max % 10;
                        shutter = VIM_roi_factor(avg_target, roi_avg_current, shutter);
                        //ROI_DEBUG("shutter a = %d ", shutter);
                        shutter = VIM_shutter_calc(shutter);
                        if(shutter < 40001)
                            shutter = 40001;
                    }
                    else if((shutter == 40001) && (gain > 10))
                    {
                        ROI_DEBUG("fps is 25fps and gain > 10,  down gain\n");
                        gain = VIM_roi_factor(avg_target, roi_avg_current, gain);
                        //ROI_DEBUG("gain = %d\n", gain);
                        if(gain < 10)
                            gain = 10;
                        dgain = gain / 10;
                        dgaindeci = gain % 10;
                        shutter = 40001;
                    }
                    //else if((shutter < 40000) && (gain > 10))
                    //{
                    //    ROI_DEBUG("shutter < 4000 and gain > 10");
                    //    shutter = 40000 + 1;
                    //    dgain = 1;
                    //    dgaindeci = 0;
                    //}
                    else 
                    {
                        ROI_DEBUG("gain == 10, down shutter\n");
                        dgain = 1;
                        dgaindeci = 0;
                        shutter = VIM_roi_factor(avg_target, roi_avg_current, shutter);
                        //ROI_DEBUG("shutter a = %d ", shutter);
                        shutter = VIM_shutter_calc(shutter);
                        if(shutter < 36)
                            shutter = 36;
                    }
                }//shutter_max_bigger == 1
                AEMode_adj.Exposuretime = shutter;
                AEMode_adj.Gain = dgain;
                AEMode_adj.GainDeci = dgaindeci;
                //ROI_DEBUG("shutter = %d, dgain = %d, dgaindeci = %d\n", shutter, dgain, dgaindeci);
                ROI_SetVIMAEMode(&AEMode_adj);
            }//roi_avg_current > avg_max
            else 
            {//
                ROI_DEBUG("it is ok\n");
                if(shutter_max_bigger == 0)
                {
                    if((shutter < shutter_max) && (gain > 10))
                    {//
                        ROI_DEBUG("   ***************** \n");
                        //ROI_DEBUG("but shutter < shutter_max, and gain > 10\n");
                        shutter = shutter_max;
                        gain = 10;
                    }
                }
                if(shutter_max_bigger == 1)
                {
                    if((shutter < 40001) && (gain > 10))
                    {
                        ROI_DEBUG("   ################# \n");
                        //ROI_DEBUG("but shutter < shutter_max, and gain > 10\n");
                        shutter = 40001;
                        gain = 10;
                    }
                    if((shutter > 40001) && (gain < gain_max))
                    {
                        ROI_DEBUG("   ================= \n");
                        shutter = 40001;
                        gain = gain_max;
                    }
                }
                AEMode_adj.Exposuretime = shutter;
                AEMode_adj.Gain = gain / 10;
                AEMode_adj.GainDeci = gain % 10;
                ROI_SetVIMAEMode(&AEMode_adj);
            }
            //IR_CUT
#if 0
            if((shutter == (shutter_max)) && (dgain == gain_max/10) && (dgaindeci == gain_max%10))
            {
                    if(roi_avg_current < avg_min)
                    {
                        ROI_DEBUG("Night\n");
                        IRCutMode.Mode = VF_IRCUT_MANUAL_NIGHT;
                        IRCutMode.Th = gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Th;
                        colorblack = VF_COLORBLACK_MANUAL_BLACK;
                    }
            }
            else  
            {
                if(shutter_max_bigger == 1)
                {
                    ROI_DEBUG("shutter_max_bigger == 1  \n");
                    if(dgain < (gain_max / 10))
                    {
                        ROI_DEBUG("Day\n");
                        IRCutMode.Mode = VF_IRCUT_MANUAL_DAY;
                        IRCutMode.Th = gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Th;
                        colorblack = VF_COLORBLACK_MANUAL_COLOR;
                    }
                }
                if(shutter_max_bigger == 0)
                {
                    ROI_DEBUG("shutter_max_bigger == 0  \n");
                    if((dgain == 1) && (dgaindeci == 0))
                    {
                        ROI_DEBUG("Day\n");
                        IRCutMode.Mode = VF_IRCUT_MANUAL_DAY;
                        IRCutMode.Th = gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Th;
                        colorblack = VF_COLORBLACK_MANUAL_COLOR;
                    }
                }
            }
#else 
            if(shutter_max_bigger == 1)
            {
                if(shutter == shutter_max )
                {
                    if(roi_avg_current < avg_min)
                    {
                        ROI_DEBUG("Night 1\n");
                        IRCutMode.Mode = VF_IRCUT_MANUAL_NIGHT;
                        IRCutMode.Th = gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Th;
                        colorblack = VF_COLORBLACK_MANUAL_BLACK;
                    }
                }
                if(shutter < 40002)
                {
                    if(roi_avg_current > avg_max)
                    {
                        ROI_DEBUG("Day 1\n");
                        IRCutMode.Mode = VF_IRCUT_MANUAL_DAY;
                        IRCutMode.Th = gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Th;
                        colorblack = VF_COLORBLACK_MANUAL_COLOR;
                    }
                }
            }
            if(shutter_max_bigger == 0)
            {
                if(!(gain < gain_max))
                {
                    if(roi_avg_current < avg_min)
                    {
                        ROI_DEBUG("Night 2\n");
                        IRCutMode.Mode = VF_IRCUT_MANUAL_NIGHT;
                        IRCutMode.Th = gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Th;
                        colorblack = VF_COLORBLACK_MANUAL_BLACK;
                    }
                }
                VI_DEBUG("gain_max = %d\n", gain_max);
                if(gain_max > 100)
                {
                    VI_DEBUG("gain_max >> 1 = %d\n", gain_max >> 1);
                    if(gain < (gain_max >> 1))
                        if(roi_avg_current > avg_max)
                        {
                            ROI_DEBUG("Day 2.1\n");
                            IRCutMode.Mode = VF_IRCUT_MANUAL_DAY;
                            IRCutMode.Th = gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Th;
                            colorblack = VF_COLORBLACK_MANUAL_COLOR;
                        }
                }
                else
                {
                    VI_DEBUG("gain_max < 500\n");
                    switch(shutter_max) 
                    {
                        case 40001:
                            shutter_temp = 33281;
                        case 33281:
                        case 29974:
                        case 24996:
                        case 19983:
                        case 16641:
                            shutter_temp = shutter_max /10000 *10000;
                            break;
                        case 9992:
                        case 8321:
                        case 3983:
                        case 1992:
                            shutter_temp = shutter_max /1000 *1000;
                            break;
                        case 996:
                        case 178:
                            shutter_temp = shutter_max /100 *100;
                            break;
                        case 72:
                            shutter_temp = shutter_max;
                            break;
                        default:
                            shutter_temp = shutter_max;
                            break;
                    }
                    VI_DEBUG("shutter = %d, shutter_temp = %d\n", shutter, shutter_temp);
                    if(shutter < shutter_temp)
                    {
                        if(roi_avg_current > avg_max)
                        {
                            ROI_DEBUG("Day 2.2\n");
                            IRCutMode.Mode = VF_IRCUT_MANUAL_DAY;
                            IRCutMode.Th = gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Th;
                            colorblack = VF_COLORBLACK_MANUAL_COLOR;
                        }
                    }
                }
            }
#endif
            ROI_DEBUG("gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Mode = %d\n", gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Mode);
            if(gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Mode == VF_IRCUT_AUTO)
            {
                ROI_DEBUG("AUTO Change IRCUT\n");
                sem_wait(&vim_sem);
                VIM_ISP_SetIrCut(IRCutMode.Mode);
                VIM_ISP_SetIrCutTh(IRCutMode.Th);
                sem_post(&vim_sem);
            }
            if(gACS1910_current_cfg.ISPAllCfg.ISPNormalCfg.IRCutMode.Mode == VF_COLORBLACK_AUTO)
            {
                sem_wait(&vim_sem);
                VIM_ISP_SetColorBlack(colorblack);
                sem_post(&vim_sem);
            }
            //gettimeofday(&t2, NULL);
            //ROI_DEBUG("t2 - t1 = %d\n", ((t2.tv_sec*1000 + t2.tv_usec/1000) - (t1.tv_sec*1000 + t1.tv_usec/1000)));
        }//pAEMode->AE_Shutter_Mode == VF_AE_ROI
        else 
        {
            sleep(1);
        }
    }
}


int VIM_roi_autoexp_thread_init()
{
    int retVal = 0;
    VI_DEBUG("Initialize roi autoexp_thread\n");

    if((retVal = pthread_create(&VIM_roi_autoexp_thread_id, NULL, VIM_roi_autoexp_thread, NULL)) != 0)
    {
        perror("Create ROI autoexp thread\n");
    }
    else 
    {
        VIM_roi_autoexp_thread_run = 1;
        VI_DEBUG("Create roi autoexp thread done!\n\n");
    }
}



