#ifndef _DRV_LED_PWM_H_
#define _DRV_LED_PWM_H_


#define VI_DEBUG_MODE

#ifdef VI_DEBUG_MODE
#define VI_DEBUG(...) \
    do \
    { \
        fprintf(stderr, " DEBUG (%s|%s|%d): ", \
                __FILE__, __func__, __LINE__); \
        fprintf(stderr, __VA_ARGS__); \
    } \
    while(0)

#else
#define VI_DEBUG(...)
#endif


#define	PWMIOC_SET_MODE			0x01
#define	PWMIOC_SET_PERIOD		0x09
#define	PWMIOC_SET_DURATION		0x03
#define	PWMIOC_SET_RPT_VAL		0x04
#define	PWMIOC_START			0x05
#define	PWMIOC_STOP			0x06
#define	PWMIOC_SET_FIRST_PHASE_STATE	0x07
#define	PWMIOC_SET_INACT_OUT_STATE	0x08

#define	PWM_ONESHOT_MODE	0
#define	PWM_CONTINUOUS_MODE	1


#define PWM0_BASE_ADDR (0x01c22000)
#define PWM1_BASE_ADDR (0x01c22400)
#define PWM2_BASE_ADDR (0x01c22800)
#define PWM3_BASE_ADDR (0x01c22c00)

#define PWM_REG_SIZE (0x400)

#define PWM_PID_OFFSET (0x00)
#define PWM_PCR_OFFSET (0x04)
#define PWM_CFG_OFFSET (0x08)
#define PWM_START_OFFSET (0x0c)
#define PWM_RPT_OFFSET (0x10)
#define PWM_PER_OFFSET (0x14)
#define PWM_PH1D_OFFSET (0x18)

#define PWM_CFG_OPST_OFFSET (17)
#define PWM_CFG_CURLEV_OFFSET (16)
#define PWM_CFG_INTEN_OFFSET (6)
#define PWM_CFG_INACTOUT_OFFSET (5)
#define PWM_CFG_P1OUT_OFFSET (4)
#define PWM_CFG_EVTRIG_OFFSET (2)
#define PWM_CFG_MODE_OFFSET (0)

#define PWM_CFG_P1OUT_LOW (0)
#define PWM_CFG_P1OUT_HIGH (1)

#define PWM_CFG_INACTOUT_LOW (0)
#define PWM_CFG_INACTOUT_HIGH (1)

#define PWM_CFG_OPST_IDLE (0)
#define PWM_CFG_OPST_RUN (1)

#define PWM_CFG_INTEN_DISABLE (0)
#define PWM_CFG_INTEN_ENABLE (1)

#define PWM_CFG_MODE_ONESHOT (1)
#define PWM_CFG_MODE_CONTINUOUS (2)



int PWM_init();
int PWM_exit();

#endif
