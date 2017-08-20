/***********************************************************
@file     drv_ACS1910.h
@brief    ACS1910相关数据
@version  V1.0
@date     2017-08-01
@author   pamsimochen
Copyright (c) 2017-2019 VIFOCUS
***********************************************************/

#ifndef _DRV_ACS1910_H_
#define _DRV_ACS1910_H_ 

#include "cmd_server.h"

#define FOCUS_PWM_IO    (92) 
#define FOCUS_PWM_NO    0
#define FOCUS_A_IO      (44)
#define FOCUS_B_IO      (26)
#define ZOOM_PWM_IO     (91)
#define ZOOM_PWM_NO     1
#define ZOOM_A_IO       (37)
#define ZOOM_B_IO       (45)
#define IRIS_PWM_IO     (87)
#define IRIS_PWM_NO     2
#define IRIS_A_IO       (82)
#define IRIS_B_IO       (81)
#define IRCUT_PWM_IO    (85)
#define IRCUT_PWM_IO    3
#define IRCUT_A_IO     (80)
#define IRCUT_B_IO     (79)

#define FOCUS_WIPPER_ADC_CH (3)
#define ZOOM_WIPPER_ADC_CH  (0)
#define IRIS_WIPPER_ADC_CH  (4)

#define FOCUS_FAR_LIMIT (1000)
#define FOCUS_NEAR_LIMIT (30)
#define ZOOM_WIDE_LIMIT (1000)
#define ZOOM_TELE_LIMIT (30)
#define IRIS_LARGE_LIMIT (1000)
#define IRIS_SMALL_LIMIT (30)

#define SPI0_SCS0_IO        (29)
#define SPI0_SOMI_IO        (23)
#define SPI0_SIMO_IO        (22)
#define SPI0_SCLK_IO        (24)

#define SPI2_SCS0_IO        (33)
#define SPI2_SOMI_IO        (31)
#define SPI2_SIMO_IO        (30)
#define SPI2_SCLK_IO        (32)

#define VIM_RESET_IO        (28)

//#pragma pack(1)
typedef struct 
{
    unsigned short reg_addr:15;
    unsigned short wr:1;
    unsigned short data;
}fpga_spi_data, *pfpga_spi_data;
//#pragma pack()
#define FPGA_SPI_WR_WRITE 0
#define FPGA_SPI_WR_READ 1

#define ROI_0_FPGA_REG_BASE (0x21)
#define ROI_0_X_FPGA_REG_OFFSET (0)
#define ROI_0_Y_FPGA_REG_OFFSET (1)
#define ROI_0_WIDTH_FPGA_REG_OFFSET (2)
#define ROI_0_HEIGHT_FPGA_REG_OFFSET (3)
#define ROI_0_X_FPGA_REG_ADDR (ROI_0_FPGA_REG_BASE + ROI_0_X_FPGA_REG_OFFSET)
#define ROI_0_Y_FPGA_REG_ADDR (ROI_0_FPGA_REG_BASE + ROI_0_Y_FPGA_REG_OFFSET)
#define ROI_0_WIDTH_FPGA_REG_ADDR (ROI_0_FPGA_REG_BASE + ROI_0_WIDTH_FPGA_REG_OFFSET)
#define ROI_0_HEIGHT_FPGA_REG_ADDR (ROI_0_FPGA_REG_BASE + ROI_0_HEIGHT_FPGA_REG_OFFSET)

#define ROI_0_HISTOGRAM_FPGA_REG_ADDR (0x25)

#define GRAD_HIGH_FPGA_REG_ADDR (114)
#define GRAD_LOW_FPGA_REG_ADDR (115)

#define ROI_1_FPGA_REG_BASE (127)
#define ROI_1_X_FPGA_REG_OFFSET (0)
#define ROI_1_Y_FPGA_REG_OFFSET (1)
#define ROI_1_WIDTH_FPGA_REG_OFFSET (2)
#define ROI_1_HEIGHT_FPGA_REG_OFFSET (3)
#define ROI_1_X_FPGA_REG_ADDR (ROI_1_FPGA_REG_BASE + ROI_1_X_FPGA_REG_OFFSET)
#define ROI_1_Y_FPGA_REG_ADDR (ROI_1_FPGA_REG_BASE + ROI_1_Y_FPGA_REG_OFFSET)
#define ROI_1_WIDTH_FPGA_REG_ADDR (ROI_1_FPGA_REG_BASE + ROI_1_WIDTH_FPGA_REG_OFFSET)
#define ROI_1_HEIGHT_FPGA_REG_ADDR (ROI_1_FPGA_REG_BASE + ROI_1_HEIGHT_FPGA_REG_OFFSET)

#define ROI_2_FPGA_REG_BASE (127)
#define ROI_2_X_FPGA_REG_OFFSET (0)
#define ROI_2_Y_FPGA_REG_OFFSET (1)
#define ROI_2_WIDTH_FPGA_REG_OFFSET (2)
#define ROI_2_HEIGHT_FPGA_REG_OFFSET (3)
#define ROI_2_X_FPGA_REG_ADDR (ROI_2_FPGA_REG_BASE + ROI_2_X_FPGA_REG_OFFSET)
#define ROI_2_Y_FPGA_REG_ADDR (ROI_2_FPGA_REG_BASE + ROI_2_Y_FPGA_REG_OFFSET)
#define ROI_2_WIDTH_FPGA_REG_ADDR (ROI_2_FPGA_REG_BASE + ROI_2_WIDTH_FPGA_REG_OFFSET)
#define ROI_2_HEIGHT_FPGA_REG_ADDR (ROI_2_FPGA_REG_BASE + ROI_2_HEIGHT_FPGA_REG_OFFSET)

#define ACS1910_DEFAULT_CFG "/mnt/nand/acs1910_default.cfg"
#define ACS1910_SAVED_CFG "/mnt/nand/acs1910_saved.cfg"

#define DEFAULT_EXPOSURE_TIME 9984

#define DEFAULT_ROI_ON 1
#define DEFAULT_ROI_OFF 0
#define DEFAULT_ROI1_X 0
#define DEFAULT_ROI1_Y 0
#define DEFAULT_ROI1_WIDTH 1919
#define DEFAULT_ROI1_HEIGHT 1079
#define DEFAULT_ROI2_X 0
#define DEFAULT_ROI2_Y 0
#define DEFAULT_ROI2_WIDTH 1919
#define DEFAULT_ROI2_HEIGHT 1079
#define DEFAULT_ROI3_X 0
#define DEFAULT_ROI3_Y 0
#define DEFAULT_ROI3_WIDTH 1919
#define DEFAULT_ROI3_HEIGHT 1079
#define ROI_NO 3
#define DEFAULT_ROI_1 {0, DEFAULT_ROI_OFF, DEFAULT_ROI1_X, DEFAULT_ROI1_Y, DEFAULT_ROI1_WIDTH, DEFAULT_ROI1_HEIGHT}
#define DEFAULT_ROI_2 {1, DEFAULT_ROI_OFF, DEFAULT_ROI2_X, DEFAULT_ROI2_Y, DEFAULT_ROI2_WIDTH, DEFAULT_ROI2_HEIGHT}
#define DEFAULT_ROI_3 {2, DEFAULT_ROI_OFF, DEFAULT_ROI3_X, DEFAULT_ROI3_Y, DEFAULT_ROI3_WIDTH, DEFAULT_ROI3_HEIGHT}
#define DEFAULT_AE_ROI {DEFAULT_ROI_1, DEFAULT_ROI_2, DEFAULT_ROI_3}

#define DEFAULT_AWB_INTERVAL 0
#define DEFAULT_AWB_SPEED 16
#define DEFAULT_AWB_AWBDELAY 10

#define DEFAULT_BRIGHTNESS 50 
#define DEFAULT_CONTRAST 50
#define DEFAULT_SATURATION 50
#define DEFAULT_HUE 50
#define DEFAULT_SHARPNESS 50

#define DEFAULT_IRCUT_TH 16

typedef struct ACS1910_ISP_NORMAL_CFG{
    VF_AE_MODE_S AEMode;
    VF_AWB_MODE_S AWBMode;
    VF_BASE_ATTRIBUTE_S BaseAttr;
    VF_IRCUT_MODE_S IRCutMode;
    VF_DR_MODE_S DRMode;
    VF_FLIP_MIRROR_MODE_E FlipMirrorMode;
    VF_IRIS_MODE_E IrisMode;
    VF_COLORBLACK_MODE_E ColorBlackMode;
    VF_DENOISE_MODE_S DeNoiseMode;
    VF_EIS_FLAG_E EISFlag;
    VF_DEFOG_MODE_E DefogMode;
    VF_MAXFRMRATE_E MaxFrmRate;
    //unsigned int AEDelay;
}tACS1910ISPNormalCfg, *ptACS1910ISPNormalCfg;

typedef struct ACS1910_ISP_ALL_CFG{
    VF_AE_ROI_S AERoi[ROI_NO];
    tACS1910ISPNormalCfg ISPNormalCfg;
}tACS1910ISPAllCfg, *ptACS1910ISPAllCfg;

typedef struct ACS1910_SYS_CFG{
    unsigned char reserved;
}tACS1910SYSCfg, *ptACS1910SYSCfg;

typedef struct ACS1910_LEN_CFG{
    unsigned char zoom_speed;
    unsigned char focus_speed;
    unsigned char iris_speed;
}tACS1910LenCfg, *ptACS1910LenCfg;

typedef struct ACS1910_CFG{
    tACS1910ISPAllCfg ISPAllCfg;
    tACS1910SYSCfg SYSCfg;
    tACS1910LenCfg LenCfg;
}tACS1910Cfg, *ptACS1910Cfg;



extern tACS1910Cfg gACS1910_default_cfg;
extern tACS1910Cfg gACS1910_saved_cfg;
extern tACS1910Cfg gACS1910_current_cfg;
int DRV_ACS1910Init();
int save_current_cfg();

#endif


