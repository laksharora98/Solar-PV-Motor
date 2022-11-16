#include "__cf_PV_fed_VCIMD_updated.h"
#ifndef RTW_HEADER_PV_fed_VCIMD_updated_acc_h_
#define RTW_HEADER_PV_fed_VCIMD_updated_acc_h_
#include <stddef.h>
#include <float.h>
#include <string.h>
#ifndef PV_fed_VCIMD_updated_acc_COMMON_INCLUDES_
#define PV_fed_VCIMD_updated_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn 
#define S_FUNCTION_LEVEL 2
#define RTW_GENERATED_S_FUNCTION
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "PV_fed_VCIMD_updated_acc_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rtGetInf.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { real_T B_18_0_0 ; real_T B_18_3_0 ; real_T B_18_5_0 ; real_T
B_18_7_0 ; real_T B_18_8_0 ; real_T B_18_11_0 ; real_T B_18_13_0 ; real_T
B_18_15_0 ; real_T B_18_19_0 ; real_T B_18_21_0 ; real_T B_18_22_0 ; }
B_RMS_PV_fed_VCIMD_updated_T ; typedef struct { real_T Memory_PreviousInput ;
real_T Memory_PreviousInput_a ; struct { real_T modelTStart ; }
TransportDelay_RWORK ; struct { real_T modelTStart ; } TransportDelay_RWORK_c
; struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void
* TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK_j ; int32_T RMS_sysIdxToRun ;
int32_T TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun_n ; struct { int_T Tail ; int_T
Head ; int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK_g ; int8_T
RMS_SubsysRanBC ; boolean_T RMS_MODE ; char_T pad_RMS_MODE [ 2 ] ; }
DW_RMS_PV_fed_VCIMD_updated_T ; typedef struct { real_T integrator_CSTATE_o ;
real_T integrator_CSTATE_i ; } X_RMS_PV_fed_VCIMD_updated_T ; typedef struct
{ real_T integrator_CSTATE_o ; real_T integrator_CSTATE_i ; }
XDot_RMS_PV_fed_VCIMD_updated_T ; typedef struct { boolean_T
integrator_CSTATE_o ; boolean_T integrator_CSTATE_i ; }
XDis_RMS_PV_fed_VCIMD_updated_T ; typedef struct { real_T B_20_1_0 ; real_T
B_20_3_0 ; real_T B_20_4_0 ; real_T B_20_7_0 ; real_T B_20_8_0 ; real_T
B_20_10_0 ; } B_TrueRMS_PV_fed_VCIMD_updated_T ; typedef struct { real_T
Memory_PreviousInput ; struct { real_T modelTStart ; } TransportDelay_RWORK ;
struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; int32_T
TrueRMS_sysIdxToRun ; int32_T TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay_IWORK ; int8_T TrueRMS_SubsysRanBC ;
boolean_T TrueRMS_MODE ; char_T pad_TrueRMS_MODE [ 2 ] ; }
DW_TrueRMS_PV_fed_VCIMD_updated_T ; typedef struct { real_T integrator_CSTATE
; } X_TrueRMS_PV_fed_VCIMD_updated_T ; typedef struct { real_T
integrator_CSTATE ; } XDot_TrueRMS_PV_fed_VCIMD_updated_T ; typedef struct {
boolean_T integrator_CSTATE ; } XDis_TrueRMS_PV_fed_VCIMD_updated_T ; typedef
struct { real_T B_46_0_0 [ 4 ] ; real_T B_46_1_0 [ 6 ] ; real_T B_46_2_0 ;
real_T B_46_3_0 [ 4 ] ; real_T B_46_7_0 ; real_T B_46_9_0 ; real_T B_46_10_0
[ 16 ] ; real_T B_46_13_0 ; real_T B_46_15_0 ; real_T B_46_33_0 ; real_T
B_46_35_0 [ 4 ] ; real_T B_46_36_0 [ 2 ] ; real_T B_46_37_0 ; real_T
B_46_39_0 ; real_T B_46_42_0 ; real_T B_46_46_0 ; real_T B_46_47_0 ; real_T
B_46_48_0 [ 16 ] ; real_T B_46_48_1 [ 10 ] ; real_T B_46_49_0 [ 3 ] ; real_T
B_46_50_0 ; real_T B_46_52_0 ; real_T B_46_54_0 ; real_T B_46_56_0 ; real_T
B_46_57_0 ; real_T B_46_58_0 ; real_T B_46_59_0 ; real_T B_46_64_0 ; real_T
B_46_66_0 ; real_T B_46_67_0 ; real_T B_46_68_0 ; real_T B_46_70_0 ; real_T
B_46_71_0 ; real_T B_46_72_0 ; real_T B_46_73_0 ; real_T B_46_75_0 ; real_T
B_46_79_0 ; real_T B_46_82_0 ; real_T B_46_83_0 ; real_T B_46_86_0 ; real_T
B_46_91_0 ; real_T B_46_93_0 ; real_T B_46_95_0 ; real_T B_46_96_0 [ 2 ] ;
real_T B_46_107_0 ; real_T B_46_112_0 [ 2 ] ; real_T B_46_114_0 ; real_T
B_46_116_0 ; real_T B_46_117_0 [ 2 ] ; real_T B_46_128_0 ; real_T B_46_135_0
; real_T B_46_137_0 ; real_T B_46_138_0 [ 2 ] ; real_T B_46_149_0 ; real_T
B_46_155_0 [ 6 ] ; real_T B_46_162_0 ; real_T B_46_167_0 [ 3 ] ; real_T
B_46_170_0 ; real_T B_46_171_0 ; real_T B_46_172_0 ; real_T B_46_173_0 ;
real_T B_46_175_0 [ 2 ] ; real_T B_46_183_0 ; real_T B_46_185_0 [ 2 ] ;
real_T B_46_187_0 [ 2 ] ; real_T B_46_192_0 ; real_T B_46_193_0 [ 16 ] ;
real_T B_46_194_0 ; real_T B_46_195_0 ; real_T B_46_196_0 ; real_T B_46_198_0
[ 16 ] ; real_T B_46_199_0 ; real_T B_46_200_0 [ 2 ] ; real_T B_46_208_0 [ 2
] ; real_T B_46_209_0 ; real_T B_46_210_0 [ 2 ] ; real_T B_46_214_0 [ 4 ] ;
real_T B_46_217_0 [ 19 ] ; real_T B_46_218_0 ; real_T B_46_221_0 ; real_T
B_46_222_0 ; real_T B_46_223_0 ; real_T B_46_231_0 ; real_T B_46_263_0 ;
real_T B_46_295_0 ; real_T B_46_299_0 ; real_T B_46_302_0 ; real_T B_46_305_0
; real_T B_46_308_0 ; real_T B_46_311_0 ; real_T B_46_314_0 ; real_T
B_46_316_0 ; real_T B_46_317_0 ; real_T B_46_318_0 ; real_T B_46_319_0 ;
real_T B_46_323_0 ; real_T B_46_326_0 ; real_T B_46_327_0 ; real_T B_46_328_0
; real_T B_46_329_0 ; real_T B_46_331_0 ; real_T B_46_333_0 ; real_T
B_46_338_0 ; real_T B_46_340_0 ; real_T B_46_344_0 ; real_T B_46_349_0 ;
real_T B_46_351_0 ; real_T B_46_352_0 ; real_T B_46_353_0 ; real_T B_46_366_0
; real_T B_46_368_0 ; real_T B_46_369_0 ; real_T B_46_370_0 ; real_T
B_46_387_0 ; real_T B_46_388_0 ; real_T B_46_389_0 ; real_T B_46_393_0 ;
real_T B_46_401_0 ; real_T B_46_403_0 ; real_T B_46_410_0 ; real_T B_15_0_1 ;
real_T B_13_0_1 ; real_T B_12_0_1 ; real_T B_11_0_0 [ 2 ] ; real_T B_11_2_0 ;
real_T B_11_2_1 ; real_T B_11_3_0 [ 16 ] ; real_T B_11_5_0 [ 16 ] ; real_T
B_10_0_0 [ 2 ] ; real_T B_10_2_0 ; real_T B_10_2_1 ; real_T B_10_3_0 [ 16 ] ;
real_T B_10_5_0 [ 16 ] ; real_T B_9_6_0 ; real_T B_9_6_1 ; real_T B_9_7_0 ;
real_T B_9_7_1 ; real_T B_9_8_0 [ 16 ] ; real_T B_9_10_0 [ 16 ] ; real_T
B_8_0_0 ; real_T B_8_1_0 ; real_T B_8_2_0 ; real_T B_8_3_0 ; real_T B_7_0_0 ;
real_T B_7_1_0 ; real_T B_7_2_0 ; real_T B_7_3_0 ; real_T B_6_0_0 ; real_T
B_6_1_0 ; real_T B_6_2_0 ; real_T B_6_3_0 ; real_T B_5_0_0 ; real_T B_5_1_0 ;
real_T B_5_2_0 ; real_T B_5_3_0 ; real_T B_4_0_0 ; real_T B_4_1_0 ; real_T
B_4_2_0 ; real_T B_4_3_0 ; real_T B_3_0_0 ; real_T B_3_1_0 ; real_T B_3_2_0 ;
real_T B_3_3_0 ; real_T B_1_0_0 [ 2 ] ; real_T B_1_1_0 [ 2 ] ; real_T
B_1_14_0 ; real_T B_1_15_0 [ 16 ] ; real_T B_1_17_0 ; real_T B_1_20_0 [ 16 ]
; real_T B_1_22_0 [ 16 ] ; real_T B_1_23_0 [ 16 ] ; real_T B_1_24_0 [ 16 ] ;
real_T B_46_178_0 [ 3 ] ; boolean_T B_46_23_0 ; boolean_T B_46_238_0 ;
boolean_T B_46_240_0 ; boolean_T B_46_248_0 ; boolean_T B_46_250_0 ;
boolean_T B_46_258_0 ; boolean_T B_46_260_0 ; boolean_T B_46_270_0 ;
boolean_T B_46_272_0 ; boolean_T B_46_280_0 ; boolean_T B_46_282_0 ;
boolean_T B_46_290_0 ; boolean_T B_46_292_0 ; char_T pad_B_46_292_0 [ 3 ] ;
B_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_fi ; B_RMS_PV_fed_VCIMD_updated_T
RMS_k ; B_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_k ;
B_RMS_PV_fed_VCIMD_updated_T RMS_h ; B_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS_p ; B_RMS_PV_fed_VCIMD_updated_T RMS_e ;
B_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_h ; B_RMS_PV_fed_VCIMD_updated_T
RMS_fg ; B_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_f ;
B_RMS_PV_fed_VCIMD_updated_T RMS_f ; B_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS
; B_RMS_PV_fed_VCIMD_updated_T RMS ; } B_PV_fed_VCIMD_updated_T ; typedef
struct { real_T fluxes_DSTATE [ 4 ] ; real_T fluxes_DSTATE_k [ 4 ] ; real_T
Rotoranglethetam_DSTATE ; real_T wm_delay_DSTATE ; real_T wm_predict_DSTATE ;
real_T UnitDelay_DSTATE ; real_T StateSpace_DSTATE [ 5 ] ; real_T
UnitDelay1_DSTATE [ 3 ] ; real_T UnitDelay_DSTATE_a ; real_T
UnitDelay1_DSTATE_k ; real_T UnitDelay_DSTATE_j ; real_T UnitDelay_DSTATE_i ;
real_T UnitDelay3_DSTATE ; real_T voltages_DSTATE [ 4 ] ; real_T
Rotorspeedwm_DSTATE ; real_T Delay_DSTATE ; real_T inversion_DWORK1 [ 16 ] ;
real_T inversion_DWORK3 [ 16 ] ; real_T inversion_DWORK4 [ 16 ] ; real_T
inversion_DWORK4_g [ 16 ] ; void * FromWs_PWORK [ 3 ] ; struct { void * AS ;
void * BS ; void * CS ; void * DS ; void * DX_COL ; void * BD_COL ; void *
TMP1 ; void * TMP2 ; void * XTMP ; void * SWITCH_STATUS ; void *
SWITCH_STATUS_INIT ; void * SW_CHG ; void * G_STATE ; void * USWLAST ; void *
XKM12 ; void * XKP12 ; void * XLAST ; void * ULAST ; void * IDX_SW_CHG ; void
* Y_SWITCH ; void * SWITCH_TYPES ; void * IDX_OUT_SW ; void *
SWITCH_TOPO_SAVED_IDX ; void * SWITCH_MAP ; } StateSpace_PWORK ; void *
Scope1_PWORK [ 7 ] ; void * ToWorkspace_PWORK ; void * ToWorkspace1_PWORK ;
void * ToWorkspace2_PWORK ; void * ToWorkspace3_PWORK ; void *
ToWorkspace4_PWORK ; void * ToWorkspace5_PWORK ; void * ToWorkspace6_PWORK ;
void * ToWorkspace7_PWORK ; void * ToWorkspace8_PWORK ; void *
ToWorkspace_PWORK_o ; void * ToWorkspace1_PWORK_k ; void *
ToWorkspace2_PWORK_l ; void * ToWorkspace_PWORK_or ; void *
ControlScope_PWORK [ 4 ] ; void * PVScope_PWORK [ 5 ] ; int32_T
FEILDWEAKENING_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitch1Inport3_sysIdxToRun ; int32_T
VariableDCtoFixedDC_sysIdxToRun ; int32_T MPPT_sysIdxToRun ; int32_T
sinthrcosthr1_sysIdxToRun ; int32_T sinthrcosthr_sysIdxToRun ; int32_T
sinbetacosbetasinthcosth_sysIdxToRun ; int32_T
Synchronousreferenceframe_sysIdxToRun ; int32_T
Stationaryreferenceframe_sysIdxToRun ; int32_T
Rotorreferenceframe_sysIdxToRun ; int32_T
Synchronousreferenceframe_sysIdxToRun_l ; int32_T
Stationaryreferenceframe_sysIdxToRun_n ; int32_T
Rotorreferenceframe_sysIdxToRun_e ; int32_T
TmpAtomicSubsysAtICInport1_sysIdxToRun ; int32_T inversion_DWORK2 [ 4 ] ;
int32_T Saturation_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitchInport1_sysIdxToRun ; uint32_T m_bpIndex ; uint32_T
m_bpIndex_k ; uint32_T m_bpIndex_g ; uint32_T m_bpIndex_j ; int_T
FromWs_IWORK ; int_T StateSpace_IWORK [ 11 ] ; int8_T
sinthrcosthr1_SubsysRanBC ; int8_T sinthrcosthr_SubsysRanBC ; int8_T
sinbetacosbetasinthcosth_SubsysRanBC ; int8_T
Synchronousreferenceframe_SubsysRanBC ; int8_T
Stationaryreferenceframe_SubsysRanBC ; int8_T Rotorreferenceframe_SubsysRanBC
; int8_T Synchronousreferenceframe_SubsysRanBC_i ; int8_T
Stationaryreferenceframe_SubsysRanBC_j ; int8_T
Rotorreferenceframe_SubsysRanBC_n ; int8_T Saturation_SubsysRanBC ; uint8_T
Rotoranglethetam_NumInitCond ; uint8_T Rotorspeedwm_SYSTEM_ENABLE ; uint8_T
Rotorspeedwm_NumInitCond ; boolean_T sinthrcosthr1_MODE ; boolean_T
sinthrcosthr_MODE ; boolean_T Synchronousreferenceframe_MODE ; boolean_T
Stationaryreferenceframe_MODE ; boolean_T Rotorreferenceframe_MODE ;
boolean_T Synchronousreferenceframe_MODE_d ; boolean_T
Stationaryreferenceframe_MODE_p ; boolean_T Rotorreferenceframe_MODE_d ;
char_T pad_Rotorreferenceframe_MODE_d [ 3 ] ;
DW_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_fi ; DW_RMS_PV_fed_VCIMD_updated_T
RMS_k ; DW_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_k ;
DW_RMS_PV_fed_VCIMD_updated_T RMS_h ; DW_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS_p ; DW_RMS_PV_fed_VCIMD_updated_T RMS_e ;
DW_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_h ; DW_RMS_PV_fed_VCIMD_updated_T
RMS_fg ; DW_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_f ;
DW_RMS_PV_fed_VCIMD_updated_T RMS_f ; DW_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS ; DW_RMS_PV_fed_VCIMD_updated_T RMS ; } DW_PV_fed_VCIMD_updated_T ;
typedef struct { real_T Integrator_CSTATE ; real_T Integrator_CSTATE_m ;
real_T Integrator_CSTATE_n ; real_T Integrator_CSTATE_i ; real_T
Integrator_CSTATE_o ; real_T Integrator_CSTATE_d ; real_T Integrator_CSTATE_a
; real_T TransferFcn_CSTATE ; X_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_fi ;
X_RMS_PV_fed_VCIMD_updated_T RMS_k ; X_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS_k ; X_RMS_PV_fed_VCIMD_updated_T RMS_h ;
X_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_p ; X_RMS_PV_fed_VCIMD_updated_T
RMS_e ; X_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_h ;
X_RMS_PV_fed_VCIMD_updated_T RMS_fg ; X_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS_f ; X_RMS_PV_fed_VCIMD_updated_T RMS_f ;
X_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS ; X_RMS_PV_fed_VCIMD_updated_T RMS ;
} X_PV_fed_VCIMD_updated_T ; typedef struct { real_T Integrator_CSTATE ;
real_T Integrator_CSTATE_m ; real_T Integrator_CSTATE_n ; real_T
Integrator_CSTATE_i ; real_T Integrator_CSTATE_o ; real_T Integrator_CSTATE_d
; real_T Integrator_CSTATE_a ; real_T TransferFcn_CSTATE ;
XDot_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_fi ;
XDot_RMS_PV_fed_VCIMD_updated_T RMS_k ; XDot_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS_k ; XDot_RMS_PV_fed_VCIMD_updated_T RMS_h ;
XDot_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_p ;
XDot_RMS_PV_fed_VCIMD_updated_T RMS_e ; XDot_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS_h ; XDot_RMS_PV_fed_VCIMD_updated_T RMS_fg ;
XDot_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_f ;
XDot_RMS_PV_fed_VCIMD_updated_T RMS_f ; XDot_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS ; XDot_RMS_PV_fed_VCIMD_updated_T RMS ; } XDot_PV_fed_VCIMD_updated_T
; typedef struct { boolean_T Integrator_CSTATE ; boolean_T
Integrator_CSTATE_m ; boolean_T Integrator_CSTATE_n ; boolean_T
Integrator_CSTATE_i ; boolean_T Integrator_CSTATE_o ; boolean_T
Integrator_CSTATE_d ; boolean_T Integrator_CSTATE_a ; boolean_T
TransferFcn_CSTATE ; XDis_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_fi ;
XDis_RMS_PV_fed_VCIMD_updated_T RMS_k ; XDis_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS_k ; XDis_RMS_PV_fed_VCIMD_updated_T RMS_h ;
XDis_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_p ;
XDis_RMS_PV_fed_VCIMD_updated_T RMS_e ; XDis_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS_h ; XDis_RMS_PV_fed_VCIMD_updated_T RMS_fg ;
XDis_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_f ;
XDis_RMS_PV_fed_VCIMD_updated_T RMS_f ; XDis_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS ; XDis_RMS_PV_fed_VCIMD_updated_T RMS ; } XDis_PV_fed_VCIMD_updated_T
; typedef struct { const real_T B_46_398_0 ; } ConstB_PV_fed_VCIMD_updated_T
;
#define PV_fed_VCIMD_updated_rtC(S) ((ConstB_PV_fed_VCIMD_updated_T *) _ssGetConstBlockIO(S))
struct P_RMS_PV_fed_VCIMD_updated_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ;
real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ;
real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T
P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ;
real_T P_20 ; real_T P_21 ; } ; struct P_TrueRMS_PV_fed_VCIMD_updated_T_ {
real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ;
real_T P_6 ; real_T P_7 ; real_T P_8 ; } ; struct P_PV_fed_VCIMD_updated_T_ {
real_T P_0 ; real_T P_1 ; real_T P_2 ; real_T P_3 [ 2 ] ; real_T P_4 [ 2 ] ;
real_T P_5 ; real_T P_6 [ 2 ] ; real_T P_7 [ 2 ] ; real_T P_8 ; real_T P_9 [
16 ] ; real_T P_10 [ 16 ] ; real_T P_11 [ 16 ] ; real_T P_12 ; real_T P_13 ;
real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T
P_19 ; real_T P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T P_24 ;
real_T P_25 ; real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ; real_T
P_30 ; real_T P_31 ; real_T P_32 [ 16 ] ; real_T P_33 ; real_T P_34 ; real_T
P_35 [ 2 ] ; real_T P_36 ; real_T P_37 [ 16 ] ; real_T P_38 ; real_T P_39 ;
real_T P_40 [ 2 ] ; real_T P_41 ; real_T P_42 [ 16 ] ; real_T P_43 ; real_T
P_44 [ 4 ] ; real_T P_45 [ 6 ] ; real_T P_46 ; real_T P_47 [ 4 ] ; real_T
P_48 ; real_T P_49 [ 4 ] ; real_T P_50 ; real_T P_51 ; real_T P_52 [ 16 ] ;
real_T P_53 ; real_T P_54 ; real_T P_55 ; real_T P_56 ; real_T P_57 ; real_T
P_58 ; real_T P_59 ; real_T P_60 ; real_T P_61 ; real_T P_62 ; real_T P_63 ;
real_T P_64 ; real_T P_65 ; real_T P_66 ; real_T P_67 ; real_T P_68 ; real_T
P_69 [ 2 ] ; real_T P_70 [ 25 ] ; real_T P_71 [ 2 ] ; real_T P_72 [ 70 ] ;
real_T P_73 [ 2 ] ; real_T P_74 [ 80 ] ; real_T P_75 [ 2 ] ; real_T P_76 [
224 ] ; real_T P_77 [ 2 ] ; real_T P_78 [ 5 ] ; real_T P_79 ; real_T P_80 ;
real_T P_81 ; real_T P_82 ; real_T P_83 ; real_T P_84 ; real_T P_85 ; real_T
P_86 ; real_T P_87 ; real_T P_88 ; real_T P_89 ; real_T P_90 ; real_T P_91 ;
real_T P_92 ; real_T P_93 ; real_T P_94 ; real_T P_95 ; real_T P_96 ; real_T
P_97 ; real_T P_98 ; real_T P_99 ; real_T P_100 ; real_T P_101 ; real_T P_102
; real_T P_103 [ 2 ] ; real_T P_104 ; real_T P_105 ; real_T P_106 ; real_T
P_107 [ 3 ] ; real_T P_108 [ 3 ] ; real_T P_109 ; real_T P_110 ; real_T P_111
; real_T P_112 ; real_T P_113 [ 2 ] ; real_T P_114 ; real_T P_115 ; real_T
P_116 ; real_T P_117 [ 3 ] ; real_T P_118 [ 3 ] ; real_T P_119 ; real_T P_120
; real_T P_121 ; real_T P_122 ; real_T P_123 [ 2 ] ; real_T P_124 ; real_T
P_125 ; real_T P_126 ; real_T P_127 [ 3 ] ; real_T P_128 [ 3 ] ; real_T P_129
; real_T P_130 ; real_T P_131 ; real_T P_132 [ 2 ] ; real_T P_133 ; real_T
P_134 [ 3 ] ; real_T P_135 ; real_T P_136 ; real_T P_137 ; real_T P_138 ;
real_T P_139 [ 16 ] ; real_T P_140 ; real_T P_141 ; real_T P_142 ; real_T
P_143 ; real_T P_144 [ 16 ] ; real_T P_145 ; real_T P_146 [ 2 ] ; real_T
P_147 ; real_T P_148 ; real_T P_149 ; real_T P_150 ; real_T P_151 [ 19 ] ;
real_T P_152 ; real_T P_153 ; real_T P_154 ; real_T P_155 ; real_T P_156 ;
real_T P_157 ; real_T P_158 ; real_T P_159 ; real_T P_160 ; real_T P_161 ;
real_T P_162 ; real_T P_163 ; real_T P_164 ; real_T P_165 ; real_T P_166 ;
real_T P_167 ; real_T P_168 ; real_T P_169 ; real_T P_170 ; real_T P_171 ;
real_T P_172 ; real_T P_173 ; real_T P_174 ; real_T P_175 ; real_T P_176 ;
real_T P_177 ; real_T P_178 ; real_T P_179 ; real_T P_180 ; real_T P_181 ;
real_T P_182 ; real_T P_183 ; real_T P_184 ; real_T P_185 ; real_T P_186 ;
real_T P_187 ; real_T P_188 ; real_T P_189 ; real_T P_190 ; real_T P_191 ;
real_T P_192 ; real_T P_193 ; real_T P_194 ; real_T P_195 ; real_T P_196 ;
real_T P_197 ; real_T P_198 ; real_T P_199 ; real_T P_200 ; real_T P_201 ;
real_T P_202 ; real_T P_203 ; real_T P_204 ; real_T P_205 ; real_T P_206 ;
real_T P_207 ; real_T P_208 ; real_T P_209 ; real_T P_210 ; real_T P_211 ;
real_T P_212 ; real_T P_213 ; real_T P_214 ; real_T P_215 ; real_T P_216 ;
real_T P_217 ; real_T P_218 ; real_T P_219 ; real_T P_220 ; real_T P_221 ;
real_T P_222 ; real_T P_223 ; real_T P_224 ; real_T P_225 ; real_T P_226 ;
real_T P_227 ; real_T P_228 ; real_T P_229 ; real_T P_230 ; real_T P_231 ;
real_T P_232 ; boolean_T P_233 ; boolean_T P_234 ; boolean_T P_235 ;
boolean_T P_236 ; boolean_T P_237 ; boolean_T P_238 ; boolean_T P_239 ;
boolean_T P_240 ; boolean_T P_241 ; char_T pad_P_241 [ 7 ] ;
P_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_fi ; P_RMS_PV_fed_VCIMD_updated_T
RMS_k ; P_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_k ;
P_RMS_PV_fed_VCIMD_updated_T RMS_h ; P_TrueRMS_PV_fed_VCIMD_updated_T
TrueRMS_p ; P_RMS_PV_fed_VCIMD_updated_T RMS_e ;
P_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_h ; P_RMS_PV_fed_VCIMD_updated_T
RMS_fg ; P_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS_f ;
P_RMS_PV_fed_VCIMD_updated_T RMS_f ; P_TrueRMS_PV_fed_VCIMD_updated_T TrueRMS
; P_RMS_PV_fed_VCIMD_updated_T RMS ; } ; extern P_PV_fed_VCIMD_updated_T
PV_fed_VCIMD_updated_rtDefaultP ; extern const ConstB_PV_fed_VCIMD_updated_T
PV_fed_VCIMD_updated_rtInvariant ;
#endif
