#include "__cf_PV_fed_VCIMD_updated.h"
#include <math.h>
#include "PV_fed_VCIMD_updated_acc.h"
#include "PV_fed_VCIMD_updated_acc_private.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T PV_fed_VCIMD_updated_acc_rt_TDelayUpdateTailOrGrowBuf ( int_T *
bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr , real_T
tMinusDelay , real_T * * tBufPtr , real_T * * uBufPtr , real_T * * xBufPtr ,
boolean_T isfixedbuf , boolean_T istransportdelay , int_T * maxNewBufSzPtr )
{ int_T testIdx ; int_T tail = * tailPtr ; int_T bufSz = * bufSzPtr ; real_T
* tBuf = * tBufPtr ; real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if (
istransportdelay ) { numBuffer = 3 ; xBuf = * xBufPtr ; } testIdx = ( tail <
( bufSz - 1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] )
&& ! isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T *
tempX = ( NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024
; if ( newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU
= ( real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if (
tempU == ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * tBufPtr = tempT ; * uBufPtr = tempU ; if (
istransportdelay ) * xBufPtr = tempX ; } else { * tailPtr = testIdx ; }
return ( true ) ; } real_T PV_fed_VCIMD_updated_acc_rt_TDelayInterpolate (
real_T tMinusDelay , real_T tStart , real_T * tBuf , real_T * uBuf , int_T
bufSz , int_T * lastIdx , int_T oldestIdx , int_T newIdx , real_T initOutput
, boolean_T discrete , boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ;
real_T yout , t1 , t2 , u1 , u2 ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } real_T look1_pbinlxpw ( real_T
u0 , const real_T bp0 [ ] , const real_T table [ ] , uint32_T prevIndex [ ] ,
uint32_T maxIndex ) { real_T frac ; uint32_T iRght ; uint32_T iLeft ;
uint32_T bpIdx ; uint32_T found ; if ( u0 <= bp0 [ 0U ] ) { bpIdx = 0U ; frac
= ( u0 - bp0 [ 0U ] ) / ( bp0 [ 1U ] - bp0 [ 0U ] ) ; } else if ( u0 < bp0 [
maxIndex ] ) { bpIdx = prevIndex [ 0U ] ; iLeft = 0U ; iRght = maxIndex ;
found = 0U ; while ( found == 0U ) { if ( u0 < bp0 [ bpIdx ] ) { iRght =
bpIdx - 1U ; bpIdx = ( iRght + iLeft ) >> 1U ; } else if ( u0 < bp0 [ bpIdx +
1U ] ) { found = 1U ; } else { iLeft = bpIdx + 1U ; bpIdx = ( iRght + iLeft )
>> 1U ; } } frac = ( u0 - bp0 [ bpIdx ] ) / ( bp0 [ bpIdx + 1U ] - bp0 [
bpIdx ] ) ; } else { bpIdx = maxIndex - 1U ; frac = ( u0 - bp0 [ maxIndex -
1U ] ) / ( bp0 [ maxIndex ] - bp0 [ maxIndex - 1U ] ) ; } prevIndex [ 0U ] =
bpIdx ; return ( table [ bpIdx + 1U ] - table [ bpIdx ] ) * frac + table [
bpIdx ] ; } void rt_ssGetBlockPath ( SimStruct * S , int_T sysIdx , int_T
blkIdx , char_T * * path ) { _ssGetBlockPath ( S , sysIdx , blkIdx , path ) ;
} void rt_ssSet_slErrMsg ( SimStruct * S , void * diag ) { if ( !
_ssIsErrorStatusAslErrMsg ( S ) ) { _ssSet_slErrMsg ( S , diag ) ; } else {
_ssDiscardDiagnostic ( S , diag ) ; } } void rt_ssReportDiagnosticAsWarning (
SimStruct * S , void * diag ) { _ssReportDiagnosticAsWarning ( S , diag ) ; }
void PV_fed_VCIMD_updated_RMS_Init ( SimStruct * S ,
B_RMS_PV_fed_VCIMD_updated_T * localB , DW_RMS_PV_fed_VCIMD_updated_T *
localDW , P_RMS_PV_fed_VCIMD_updated_T * localP ,
X_RMS_PV_fed_VCIMD_updated_T * localX ) { localX -> integrator_CSTATE_o =
localP -> P_3 ; localDW -> Memory_PreviousInput = localP -> P_7 ; localX ->
integrator_CSTATE_i = localP -> P_8 ; localDW -> Memory_PreviousInput_a =
localP -> P_12 ; localB -> B_18_22_0 = localP -> P_2 ; } void
PV_fed_VCIMD_updated_RMS_Disable ( SimStruct * S ,
DW_RMS_PV_fed_VCIMD_updated_T * localDW ) { localDW -> RMS_MODE = false ; }
void PV_fed_VCIMD_updated_RMS ( SimStruct * S , boolean_T rtu_Enable , real_T
rtu_In , B_RMS_PV_fed_VCIMD_updated_T * localB ,
DW_RMS_PV_fed_VCIMD_updated_T * localDW , P_RMS_PV_fed_VCIMD_updated_T *
localP , X_RMS_PV_fed_VCIMD_updated_T * localX ) { real_T B_18_1_0 ; real_T
B_18_9_0 ; boolean_T rtb_B_18_4_0 ; int32_T isHit ; isHit = ssIsSampleHit ( S
, 1 , 0 ) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S ) != 0 ) ) { if (
rtu_Enable ) { if ( ! localDW -> RMS_MODE ) { if ( ssGetTaskTime ( S , 1 ) !=
ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
localDW -> RMS_MODE = true ; } } else { if ( localDW -> RMS_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
PV_fed_VCIMD_updated_RMS_Disable ( S , localDW ) ; } } } if ( localDW ->
RMS_MODE ) { localB -> B_18_0_0 = localX -> integrator_CSTATE_o ; { real_T *
* uBuffer = ( real_T * * ) & localDW -> TransportDelay_PWORK . TUbufferPtrs [
0 ] ; real_T * * tBuffer = ( real_T * * ) & localDW -> TransportDelay_PWORK .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - localP -> P_4 ; B_18_1_0 =
PV_fed_VCIMD_updated_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer
, * uBuffer , localDW -> TransportDelay_IWORK . CircularBufSize , & localDW
-> TransportDelay_IWORK . Last , localDW -> TransportDelay_IWORK . Tail ,
localDW -> TransportDelay_IWORK . Head , localP -> P_5 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localB ->
B_18_3_0 = localP -> P_6 ; } rtb_B_18_4_0 = ( ssGetT ( S ) >= localB ->
B_18_3_0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localB
-> B_18_5_0 = localDW -> Memory_PreviousInput ; } if ( rtb_B_18_4_0 ) {
localB -> B_18_7_0 = ( localB -> B_18_0_0 - B_18_1_0 ) * localP -> P_1 ; }
else { localB -> B_18_7_0 = localB -> B_18_5_0 ; } localB -> B_18_8_0 =
localX -> integrator_CSTATE_i ; { real_T * * uBuffer = ( real_T * * ) &
localDW -> TransportDelay_PWORK_j . TUbufferPtrs [ 0 ] ; real_T * * tBuffer =
( real_T * * ) & localDW -> TransportDelay_PWORK_j . TUbufferPtrs [ 1 ] ;
real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - localP -> P_9
; B_18_9_0 = PV_fed_VCIMD_updated_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * tBuffer , * uBuffer , localDW -> TransportDelay_IWORK_g .
CircularBufSize , & localDW -> TransportDelay_IWORK_g . Last , localDW ->
TransportDelay_IWORK_g . Tail , localDW -> TransportDelay_IWORK_g . Head ,
localP -> P_10 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && (
ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) ) ) ; } isHit = ssIsSampleHit (
S , 1 , 0 ) ; if ( isHit != 0 ) { localB -> B_18_11_0 = localP -> P_11 ; }
rtb_B_18_4_0 = ( ssGetT ( S ) >= localB -> B_18_11_0 ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localB -> B_18_13_0 =
localDW -> Memory_PreviousInput_a ; } if ( rtb_B_18_4_0 ) { localB ->
B_18_15_0 = ( localB -> B_18_8_0 - B_18_9_0 ) * localP -> P_0 ; } else {
localB -> B_18_15_0 = localB -> B_18_13_0 ; } localB -> B_18_19_0 = (
muDoubleScalarSin ( localP -> P_15 * ssGetTaskTime ( S , 0 ) + localP -> P_16
) * localP -> P_13 + localP -> P_14 ) * rtu_In ; localB -> B_18_21_0 = (
muDoubleScalarSin ( localP -> P_19 * ssGetTaskTime ( S , 0 ) + localP -> P_20
) * localP -> P_17 + localP -> P_18 ) * rtu_In ; localB -> B_18_22_0 = localP
-> P_21 * muDoubleScalarHypot ( localB -> B_18_7_0 , localB -> B_18_15_0 ) ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( localDW -> RMS_SubsysRanBC
) ; } } } void PV_fed_VCIMD_updated_RMS_Update ( SimStruct * S ,
B_RMS_PV_fed_VCIMD_updated_T * localB , DW_RMS_PV_fed_VCIMD_updated_T *
localDW , P_RMS_PV_fed_VCIMD_updated_T * localP ) { int32_T isHit ; if (
localDW -> RMS_MODE ) { { real_T * * uBuffer = ( real_T * * ) & localDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & localDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; localDW -> TransportDelay_IWORK . Head = ( ( localDW ->
TransportDelay_IWORK . Head < ( localDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( localDW -> TransportDelay_IWORK . Head + 1 ) : 0
) ; if ( localDW -> TransportDelay_IWORK . Head == localDW ->
TransportDelay_IWORK . Tail ) { if ( !
PV_fed_VCIMD_updated_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK . CircularBufSize , & localDW -> TransportDelay_IWORK .
Tail , & localDW -> TransportDelay_IWORK . Head , & localDW ->
TransportDelay_IWORK . Last , simTime - localP -> P_4 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & localDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ localDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ localDW -> TransportDelay_IWORK . Head ] = localB
-> B_18_0_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
localDW -> Memory_PreviousInput = localB -> B_18_7_0 ; } { real_T * * uBuffer
= ( real_T * * ) & localDW -> TransportDelay_PWORK_j . TUbufferPtrs [ 0 ] ;
real_T * * tBuffer = ( real_T * * ) & localDW -> TransportDelay_PWORK_j .
TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; localDW ->
TransportDelay_IWORK_g . Head = ( ( localDW -> TransportDelay_IWORK_g . Head
< ( localDW -> TransportDelay_IWORK_g . CircularBufSize - 1 ) ) ? ( localDW
-> TransportDelay_IWORK_g . Head + 1 ) : 0 ) ; if ( localDW ->
TransportDelay_IWORK_g . Head == localDW -> TransportDelay_IWORK_g . Tail ) {
if ( ! PV_fed_VCIMD_updated_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK_g . CircularBufSize , & localDW ->
TransportDelay_IWORK_g . Tail , & localDW -> TransportDelay_IWORK_g . Head ,
& localDW -> TransportDelay_IWORK_g . Last , simTime - localP -> P_9 ,
tBuffer , uBuffer , ( NULL ) , ( boolean_T ) 0 , false , & localDW ->
TransportDelay_IWORK_g . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * tBuffer ) [ localDW ->
TransportDelay_IWORK_g . Head ] = simTime ; ( * uBuffer ) [ localDW ->
TransportDelay_IWORK_g . Head ] = localB -> B_18_8_0 ; } isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localDW ->
Memory_PreviousInput_a = localB -> B_18_15_0 ; } } } void
PV_fed_VCIMD_updated_RMS_Deriv ( SimStruct * S , B_RMS_PV_fed_VCIMD_updated_T
* localB , DW_RMS_PV_fed_VCIMD_updated_T * localDW ,
XDot_RMS_PV_fed_VCIMD_updated_T * localXdot ) { if ( localDW -> RMS_MODE ) {
localXdot -> integrator_CSTATE_o = localB -> B_18_19_0 ; localXdot ->
integrator_CSTATE_i = localB -> B_18_21_0 ; } else { { real_T * dx ; int_T i
; dx = & ( localXdot -> integrator_CSTATE_o ) ; for ( i = 0 ; i < 2 ; i ++ )
{ dx [ i ] = 0.0 ; } } } } void PV_fed_VCIMD_updated_RMS_Term ( SimStruct *
const S ) { } void PV_fed_VCIMD_updated_TrueRMS_Init ( SimStruct * S ,
B_TrueRMS_PV_fed_VCIMD_updated_T * localB , DW_TrueRMS_PV_fed_VCIMD_updated_T
* localDW , P_TrueRMS_PV_fed_VCIMD_updated_T * localP ,
X_TrueRMS_PV_fed_VCIMD_updated_T * localX ) { localX -> integrator_CSTATE =
localP -> P_2 ; localDW -> Memory_PreviousInput = localP -> P_6 ; localB ->
B_20_10_0 = localP -> P_1 ; } void PV_fed_VCIMD_updated_TrueRMS_Disable (
SimStruct * S , DW_TrueRMS_PV_fed_VCIMD_updated_T * localDW ) { localDW ->
TrueRMS_MODE = false ; } void PV_fed_VCIMD_updated_TrueRMS ( SimStruct * S ,
boolean_T rtu_Enable , real_T rtu_In , B_TrueRMS_PV_fed_VCIMD_updated_T *
localB , DW_TrueRMS_PV_fed_VCIMD_updated_T * localDW ,
P_TrueRMS_PV_fed_VCIMD_updated_T * localP , X_TrueRMS_PV_fed_VCIMD_updated_T
* localX ) { real_T B_20_2_0 ; int32_T isHit ; real_T tmp ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( ( isHit != 0 ) && ( ssIsMajorTimeStep ( S
) != 0 ) ) { if ( rtu_Enable ) { if ( ! localDW -> TrueRMS_MODE ) { if (
ssGetTaskTime ( S , 1 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } localDW -> TrueRMS_MODE
= true ; } } else { if ( localDW -> TrueRMS_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ;
PV_fed_VCIMD_updated_TrueRMS_Disable ( S , localDW ) ; } } } if ( localDW ->
TrueRMS_MODE ) { localB -> B_20_1_0 = localX -> integrator_CSTATE ; { real_T
* * uBuffer = ( real_T * * ) & localDW -> TransportDelay_PWORK . TUbufferPtrs
[ 0 ] ; real_T * * tBuffer = ( real_T * * ) & localDW -> TransportDelay_PWORK
. TUbufferPtrs [ 1 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay =
simTime - localP -> P_3 ; B_20_2_0 =
PV_fed_VCIMD_updated_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 , * tBuffer
, * uBuffer , localDW -> TransportDelay_IWORK . CircularBufSize , & localDW
-> TransportDelay_IWORK . Last , localDW -> TransportDelay_IWORK . Tail ,
localDW -> TransportDelay_IWORK . Head , localP -> P_4 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ssGetTimeOfLastOutput ( S ) == ssGetT ( S ) ) )
) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { localB ->
B_20_3_0 = localP -> P_5 ; localB -> B_20_4_0 = localDW ->
Memory_PreviousInput ; } if ( ssGetT ( S ) >= localB -> B_20_3_0 ) { localB
-> B_20_7_0 = ( localB -> B_20_1_0 - B_20_2_0 ) * localP -> P_0 ; } else {
localB -> B_20_7_0 = localB -> B_20_4_0 ; } localB -> B_20_8_0 = rtu_In *
rtu_In ; if ( localB -> B_20_7_0 > localP -> P_7 ) { tmp = localP -> P_7 ; }
else if ( localB -> B_20_7_0 < localP -> P_8 ) { tmp = localP -> P_8 ; } else
{ tmp = localB -> B_20_7_0 ; } localB -> B_20_10_0 = muDoubleScalarSqrt ( tmp
) ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( localDW ->
TrueRMS_SubsysRanBC ) ; } } } void PV_fed_VCIMD_updated_TrueRMS_Update (
SimStruct * S , B_TrueRMS_PV_fed_VCIMD_updated_T * localB ,
DW_TrueRMS_PV_fed_VCIMD_updated_T * localDW ,
P_TrueRMS_PV_fed_VCIMD_updated_T * localP ) { int32_T isHit ; if ( localDW ->
TrueRMS_MODE ) { { real_T * * uBuffer = ( real_T * * ) & localDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T * * tBuffer = ( real_T * *
) & localDW -> TransportDelay_PWORK . TUbufferPtrs [ 1 ] ; real_T simTime =
ssGetT ( S ) ; localDW -> TransportDelay_IWORK . Head = ( ( localDW ->
TransportDelay_IWORK . Head < ( localDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( localDW -> TransportDelay_IWORK . Head + 1 ) : 0
) ; if ( localDW -> TransportDelay_IWORK . Head == localDW ->
TransportDelay_IWORK . Tail ) { if ( !
PV_fed_VCIMD_updated_acc_rt_TDelayUpdateTailOrGrowBuf ( & localDW ->
TransportDelay_IWORK . CircularBufSize , & localDW -> TransportDelay_IWORK .
Tail , & localDW -> TransportDelay_IWORK . Head , & localDW ->
TransportDelay_IWORK . Last , simTime - localP -> P_3 , tBuffer , uBuffer , (
NULL ) , ( boolean_T ) 0 , false , & localDW -> TransportDelay_IWORK .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * tBuffer ) [ localDW -> TransportDelay_IWORK . Head ] =
simTime ; ( * uBuffer ) [ localDW -> TransportDelay_IWORK . Head ] = localB
-> B_20_1_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
localDW -> Memory_PreviousInput = localB -> B_20_7_0 ; } } } void
PV_fed_VCIMD_updated_TrueRMS_Deriv ( SimStruct * S ,
B_TrueRMS_PV_fed_VCIMD_updated_T * localB , DW_TrueRMS_PV_fed_VCIMD_updated_T
* localDW , XDot_TrueRMS_PV_fed_VCIMD_updated_T * localXdot ) { if ( localDW
-> TrueRMS_MODE ) { localXdot -> integrator_CSTATE = localB -> B_20_8_0 ; }
else { localXdot -> integrator_CSTATE = 0.0 ; } } void
PV_fed_VCIMD_updated_TrueRMS_Term ( SimStruct * const S ) { } void
rt_invd4x4_snf ( const real_T u [ 16 ] , real_T y [ 16 ] ) { int8_T p [ 4 ] ;
real_T A [ 16 ] ; int8_T ipiv [ 4 ] ; int32_T jj ; int32_T jp1j ; int32_T
idxmax ; int32_T ix ; real_T smax ; real_T s ; int32_T iy ; int32_T jA ;
int32_T ijA ; int32_T pipk ; int32_T jBcol ; for ( iy = 0 ; iy < 16 ; iy ++ )
{ y [ iy ] = 0.0 ; A [ iy ] = u [ iy ] ; } ipiv [ 0 ] = 1 ; ipiv [ 1 ] = 2 ;
ipiv [ 2 ] = 3 ; for ( pipk = 0 ; pipk < 3 ; pipk ++ ) { jBcol = pipk * 5 + 1
; jj = pipk * 5 ; jp1j = jBcol + 1 ; iy = 4 - pipk ; idxmax = 1 ; ix = jBcol
- 1 ; smax = muDoubleScalarAbs ( A [ jj ] ) ; for ( jA = 2 ; jA <= iy ; jA ++
) { ix ++ ; s = muDoubleScalarAbs ( A [ ix ] ) ; if ( s > smax ) { idxmax =
jA ; smax = s ; } } if ( A [ ( jBcol + idxmax ) - 2 ] != 0.0 ) { if ( idxmax
- 1 != 0 ) { ipiv [ pipk ] = ( int8_T ) ( pipk + idxmax ) ; ix = pipk + 1 ;
iy = pipk + idxmax ; smax = A [ ix - 1 ] ; A [ ix - 1 ] = A [ iy - 1 ] ; A [
iy - 1 ] = smax ; ix += 4 ; iy += 4 ; smax = A [ ix - 1 ] ; A [ ix - 1 ] = A
[ iy - 1 ] ; A [ iy - 1 ] = smax ; ix += 4 ; iy += 4 ; smax = A [ ix - 1 ] ;
A [ ix - 1 ] = A [ iy - 1 ] ; A [ iy - 1 ] = smax ; ix += 4 ; iy += 4 ; smax
= A [ ix - 1 ] ; A [ ix - 1 ] = A [ iy - 1 ] ; A [ iy - 1 ] = smax ; } iy =
jp1j - pipk ; for ( ix = jp1j ; ix <= iy + 2 ; ix ++ ) { A [ ix - 1 ] /= A [
jj ] ; } } jBcol = 2 - pipk ; jA = jj ; jj += 4 ; for ( idxmax = 0 ; idxmax
<= jBcol ; idxmax ++ ) { if ( A [ jj ] != 0.0 ) { smax = - A [ jj ] ; ix =
jp1j ; iy = jA - pipk ; for ( ijA = jA + 6 ; ijA <= iy + 8 ; ijA ++ ) { A [
ijA - 1 ] += A [ ix - 1 ] * smax ; ix ++ ; } } jj += 4 ; jA += 4 ; } } p [ 0
] = 1 ; p [ 1 ] = 2 ; p [ 2 ] = 3 ; p [ 3 ] = 4 ; if ( ipiv [ 0 ] > 1 ) {
pipk = p [ ipiv [ 0 ] - 1 ] ; p [ ipiv [ 0 ] - 1 ] = 1 ; p [ 0 ] = ( int8_T )
pipk ; } if ( ipiv [ 1 ] > 2 ) { pipk = p [ ipiv [ 1 ] - 1 ] ; p [ ipiv [ 1 ]
- 1 ] = p [ 1 ] ; p [ 1 ] = ( int8_T ) pipk ; } if ( ipiv [ 2 ] > 3 ) { pipk
= p [ 3 ] ; p [ 3 ] = p [ 2 ] ; p [ 2 ] = ( int8_T ) pipk ; } jBcol = p [ 0 ]
; y [ ( p [ 0 ] - 1 ) << 2 ] = 1.0 ; for ( pipk = 1 ; pipk < 5 ; pipk ++ ) {
if ( y [ ( ( ( jBcol - 1 ) << 2 ) + pipk ) - 1 ] != 0.0 ) { for ( ix = pipk +
1 ; ix < 5 ; ix ++ ) { y [ ( ix + ( ( jBcol - 1 ) << 2 ) ) - 1 ] -= y [ ( ( (
jBcol - 1 ) << 2 ) + pipk ) - 1 ] * A [ ( ( ( pipk - 1 ) << 2 ) + ix ) - 1 ]
; } } } jBcol = p [ 1 ] ; y [ 1 + ( ( p [ 1 ] - 1 ) << 2 ) ] = 1.0 ; for (
pipk = 2 ; pipk < 5 ; pipk ++ ) { if ( y [ ( ( ( jBcol - 1 ) << 2 ) + pipk )
- 1 ] != 0.0 ) { for ( ix = pipk + 1 ; ix < 5 ; ix ++ ) { y [ ( ix + ( (
jBcol - 1 ) << 2 ) ) - 1 ] -= y [ ( ( ( jBcol - 1 ) << 2 ) + pipk ) - 1 ] * A
[ ( ( ( pipk - 1 ) << 2 ) + ix ) - 1 ] ; } } } jBcol = p [ 2 ] ; y [ 2 + ( (
p [ 2 ] - 1 ) << 2 ) ] = 1.0 ; for ( pipk = 3 ; pipk < 5 ; pipk ++ ) { if ( y
[ ( ( ( jBcol - 1 ) << 2 ) + pipk ) - 1 ] != 0.0 ) { for ( ix = pipk + 1 ; ix
< 5 ; ix ++ ) { y [ ( ( jBcol - 1 ) << 2 ) + 3 ] -= y [ ( ( ( jBcol - 1 ) <<
2 ) + pipk ) - 1 ] * A [ ( ( pipk - 1 ) << 2 ) + 3 ] ; } } } y [ 3 + ( ( p [
3 ] - 1 ) << 2 ) ] = 1.0 ; for ( pipk = 0 ; pipk < 4 ; pipk ++ ) { jBcol =
pipk << 2 ; if ( y [ jBcol + 3 ] != 0.0 ) { y [ jBcol + 3 ] /= A [ 15 ] ; for
( ix = 0 ; ix < 3 ; ix ++ ) { jp1j = 1 + ix ; y [ ( jp1j + jBcol ) - 1 ] -= y
[ jBcol + 3 ] * A [ jp1j + 11 ] ; } } if ( y [ jBcol + 2 ] != 0.0 ) { y [
jBcol + 2 ] /= A [ 10 ] ; for ( ix = 0 ; ix < 2 ; ix ++ ) { jp1j = 1 + ix ; y
[ ( jp1j + jBcol ) - 1 ] -= y [ jBcol + 2 ] * A [ jp1j + 7 ] ; } } if ( y [
jBcol + 1 ] != 0.0 ) { y [ jBcol + 1 ] /= A [ 5 ] ; for ( ix = 0 ; ix < 1 ;
ix ++ ) { y [ jBcol ] -= y [ jBcol + 1 ] * A [ 4 ] ; } } if ( y [ jBcol ] !=
0.0 ) { y [ jBcol ] /= A [ 0 ] ; } } } static void mdlOutputs ( SimStruct * S
, int_T tid ) { real_T B_46_236_0 ; real_T B_46_246_0 ; real_T B_46_256_0 ;
real_T B_46_268_0 ; real_T B_46_278_0 ; real_T B_46_288_0 ; boolean_T
B_46_19_0 ; boolean_T B_46_21_0 ; boolean_T B_46_26_0 ; boolean_T B_46_28_0 ;
boolean_T B_46_30_0 ; boolean_T B_46_202_0 ; boolean_T B_46_204_0 ; boolean_T
B_46_206_0 ; real_T rtb_B_46_14_0 ; real_T rtb_B_46_25_0 [ 4 ] ; real_T
rtb_B_46_84_0 ; real_T rtb_B_46_85_0 ; real_T rtb_B_46_103_0 ; boolean_T
rtb_B_46_110_0 ; real_T rtb_B_46_165_0 ; real_T rtb_B_46_201_0 [ 4 ] ; real_T
rtb_B_1_6_0 ; real_T rtb_B_1_11_0 ; real_T rtb_B_1_12_0 ; real_T rtb_B_9_4_0
; real_T rtb_B_46_6_0 [ 4 ] ; real_T rtb_B_1_19_0 [ 16 ] ; real_T rtb_B_2_1_0
[ 16 ] ; int32_T i ; real_T B_2_1_0 [ 16 ] ; real_T tmp [ 4 ] ; int32_T i_0 ;
real_T B_1_7_0_idx_0 ; real_T B_1_7_0_idx_1 ; real_T B_1_8_0_idx_0 ; real_T
B_1_8_0_idx_1 ; real_T B_46_133_0_idx_0 ; real_T B_46_133_0_idx_1 ;
B_PV_fed_VCIMD_updated_T * _rtB ; P_PV_fed_VCIMD_updated_T * _rtP ;
X_PV_fed_VCIMD_updated_T * _rtX ; DW_PV_fed_VCIMD_updated_T * _rtDW ; _rtDW =
( ( DW_PV_fed_VCIMD_updated_T * ) ssGetRootDWork ( S ) ) ; _rtX = ( (
X_PV_fed_VCIMD_updated_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_PV_fed_VCIMD_updated_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_PV_fed_VCIMD_updated_T * ) _ssGetModelBlockIO ( S ) ) ; i = ssIsSampleHit (
S , 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_46_3_0 [ 0 ] = _rtDW -> fluxes_DSTATE
[ 0 ] ; _rtB -> B_46_3_0 [ 1 ] = _rtDW -> fluxes_DSTATE [ 1 ] ; _rtB ->
B_46_3_0 [ 2 ] = _rtDW -> fluxes_DSTATE [ 2 ] ; _rtB -> B_46_3_0 [ 3 ] =
_rtDW -> fluxes_DSTATE [ 3 ] ; if ( _rtB -> B_46_7_0 > 0.0 ) { rtb_B_1_6_0 =
1.0 / ( ( 1.0 / _rtB -> B_1_1_0 [ 0 ] + 1.0 / _rtB -> B_1_1_0 [ 1 ] ) + 1.0 /
_rtDW -> Delay_DSTATE ) ; B_1_7_0_idx_0 = _rtB -> B_1_0_0 [ 0 ] * rtb_B_1_6_0
; B_1_7_0_idx_1 = _rtB -> B_1_0_0 [ 1 ] * rtb_B_1_6_0 ; rtb_B_1_12_0 =
muDoubleScalarHypot ( ( _rtP -> P_48 * _rtB -> B_46_3_0 [ 0 ] - _rtDW ->
fluxes_DSTATE_k [ 0 ] ) * B_1_7_0_idx_0 + ( _rtP -> P_48 * _rtB -> B_46_3_0 [
2 ] - _rtDW -> fluxes_DSTATE_k [ 2 ] ) * B_1_7_0_idx_1 , ( _rtP -> P_48 *
_rtB -> B_46_3_0 [ 1 ] - _rtDW -> fluxes_DSTATE_k [ 1 ] ) * B_1_7_0_idx_0 + (
_rtP -> P_48 * _rtB -> B_46_3_0 [ 3 ] - _rtDW -> fluxes_DSTATE_k [ 3 ] ) *
B_1_7_0_idx_1 ) ; rtb_B_1_11_0 = look1_pbinlxpw ( rtb_B_1_12_0 , _rtP -> P_7
, _rtP -> P_6 , & _rtDW -> m_bpIndex_j , 1U ) ; if ( rtb_B_1_11_0 != 0.0 ) {
_rtB -> B_1_17_0 = rtb_B_1_12_0 / rtb_B_1_11_0 ; } else { _rtB -> B_1_17_0 =
_rtB -> B_1_14_0 ; } memcpy ( & rtb_B_1_19_0 [ 0 ] , & _rtB -> B_1_15_0 [ 0 ]
, sizeof ( real_T ) << 4U ) ; rtb_B_1_19_0 [ 0 ] = _rtB -> B_1_17_0 ;
rtb_B_1_19_0 [ 5 ] = _rtB -> B_1_17_0 ; rtb_B_1_19_0 [ 2 ] = _rtB -> B_1_17_0
; rtb_B_1_19_0 [ 7 ] = _rtB -> B_1_17_0 ; rtb_B_1_19_0 [ 8 ] = _rtB ->
B_1_17_0 ; rtb_B_1_19_0 [ 13 ] = _rtB -> B_1_17_0 ; rtb_B_1_19_0 [ 10 ] =
_rtB -> B_1_17_0 ; rtb_B_1_19_0 [ 15 ] = _rtB -> B_1_17_0 ; for ( i = 0 ; i <
16 ; i ++ ) { rtb_B_2_1_0 [ i ] = rtb_B_1_19_0 [ i ] + _rtB -> B_1_20_0 [ i ]
; } rt_invd4x4_snf ( rtb_B_2_1_0 , _rtB -> B_1_23_0 ) ; for ( i = 0 ; i < 4 ;
i ++ ) { for ( i_0 = 0 ; i_0 < 4 ; i_0 ++ ) { _rtB -> B_1_24_0 [ i_0 + ( i <<
2 ) ] = 0.0 ; _rtB -> B_1_24_0 [ i_0 + ( i << 2 ) ] += _rtB -> B_1_23_0 [ i
<< 2 ] * _rtB -> B_1_22_0 [ i_0 ] ; _rtB -> B_1_24_0 [ i_0 + ( i << 2 ) ] +=
_rtB -> B_1_23_0 [ ( i << 2 ) + 1 ] * _rtB -> B_1_22_0 [ i_0 + 4 ] ; _rtB ->
B_1_24_0 [ i_0 + ( i << 2 ) ] += _rtB -> B_1_23_0 [ ( i << 2 ) + 2 ] * _rtB
-> B_1_22_0 [ i_0 + 8 ] ; _rtB -> B_1_24_0 [ i_0 + ( i << 2 ) ] += _rtB ->
B_1_23_0 [ ( i << 2 ) + 3 ] * _rtB -> B_1_22_0 [ i_0 + 12 ] ; } } if (
ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW -> Saturation_SubsysRanBC
) ; } } rtb_B_46_110_0 = ( _rtB -> B_46_9_0 >= _rtP -> P_53 ) ; for ( i = 0 ;
i < 16 ; i ++ ) { if ( rtb_B_46_110_0 ) { B_2_1_0 [ i ] = _rtB -> B_1_23_0 [
i ] ; } else { B_2_1_0 [ i ] = _rtB -> B_46_10_0 [ i ] ; } } for ( i = 0 ; i
< 4 ; i ++ ) { rtb_B_1_6_0 = B_2_1_0 [ i + 12 ] * _rtB -> B_46_3_0 [ 3 ] + (
B_2_1_0 [ i + 8 ] * _rtB -> B_46_3_0 [ 2 ] + ( B_2_1_0 [ i + 4 ] * _rtB ->
B_46_3_0 [ 1 ] + B_2_1_0 [ i ] * _rtB -> B_46_3_0 [ 0 ] ) ) ; rtb_B_46_201_0
[ i ] = rtb_B_1_6_0 ; } rtb_B_46_110_0 = ( _rtB -> B_46_9_0 >= _rtP -> P_53 )
; for ( i = 0 ; i < 16 ; i ++ ) { if ( rtb_B_46_110_0 ) { B_2_1_0 [ i ] =
_rtB -> B_1_23_0 [ i ] ; } else { B_2_1_0 [ i ] = _rtB -> B_46_10_0 [ i ] ; }
} for ( i = 0 ; i < 4 ; i ++ ) { rtb_B_1_6_0 = B_2_1_0 [ i + 12 ] * _rtB ->
B_46_3_0 [ 3 ] + ( B_2_1_0 [ i + 8 ] * _rtB -> B_46_3_0 [ 2 ] + ( B_2_1_0 [ i
+ 4 ] * _rtB -> B_46_3_0 [ 1 ] + B_2_1_0 [ i ] * _rtB -> B_46_3_0 [ 0 ] ) ) ;
rtb_B_46_6_0 [ i ] = rtb_B_1_6_0 ; } rtb_B_46_14_0 = _rtDW ->
Rotoranglethetam_DSTATE ; _rtB -> B_46_15_0 = _rtDW -> wm_delay_DSTATE ;
rtb_B_1_6_0 = _rtP -> P_58 * _rtB -> B_46_15_0 - _rtDW -> wm_predict_DSTATE ;
B_46_19_0 = _rtP -> P_233 ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( ( i != 0 )
&& ( ssIsMajorTimeStep ( S ) != 0 ) ) { if ( B_46_19_0 ) { if ( ! _rtDW ->
sinthrcosthr_MODE ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
sinthrcosthr_MODE = true ; } } else { if ( _rtDW -> sinthrcosthr_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtB -> B_10_2_0 = _rtP ->
P_33 ; _rtB -> B_10_2_1 = _rtP -> P_33 ; _rtB -> B_10_0_0 [ 0 ] = _rtP ->
P_33 ; _rtB -> B_10_0_0 [ 1 ] = _rtP -> P_33 ; for ( i = 0 ; i < 16 ; i ++ )
{ _rtB -> B_10_5_0 [ i ] = _rtP -> P_34 ; } _rtDW -> sinthrcosthr_MODE =
false ; } } } if ( _rtDW -> sinthrcosthr_MODE ) { _rtB -> B_10_0_0 [ 0 ] =
_rtP -> P_35 [ 0 ] ; _rtB -> B_10_0_0 [ 1 ] = _rtP -> P_35 [ 1 ] ;
rtb_B_1_12_0 = _rtP -> P_36 * rtb_B_1_6_0 ; muDoubleScalarSinCos (
rtb_B_46_14_0 , & _rtB -> B_10_2_0 , & _rtB -> B_10_2_1 ) ; memcpy ( & _rtB
-> B_10_5_0 [ 0 ] , & _rtB -> B_10_3_0 [ 0 ] , sizeof ( real_T ) << 4U ) ;
_rtB -> B_10_5_0 [ 4 ] = rtb_B_1_6_0 ; _rtB -> B_10_5_0 [ 1 ] = rtb_B_1_12_0
; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
sinthrcosthr_SubsysRanBC ) ; } } B_46_21_0 = _rtP -> P_234 ; i =
ssIsSampleHit ( S , 2 , 0 ) ; if ( ( i != 0 ) && ( ssIsMajorTimeStep ( S ) !=
0 ) ) { if ( B_46_21_0 ) { if ( ! _rtDW -> sinthrcosthr1_MODE ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
sinthrcosthr1_MODE = true ; } } else { if ( _rtDW -> sinthrcosthr1_MODE ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtB -> B_11_2_0 = _rtP ->
P_38 ; _rtB -> B_11_2_1 = _rtP -> P_38 ; _rtB -> B_11_0_0 [ 0 ] = _rtP ->
P_38 ; _rtB -> B_11_0_0 [ 1 ] = _rtP -> P_38 ; _rtDW -> sinthrcosthr1_MODE =
false ; } } } if ( _rtDW -> sinthrcosthr1_MODE ) { _rtB -> B_11_0_0 [ 0 ] =
_rtP -> P_40 [ 0 ] ; _rtB -> B_11_0_0 [ 1 ] = _rtP -> P_40 [ 1 ] ;
rtb_B_1_12_0 = _rtP -> P_41 * rtb_B_1_6_0 ; muDoubleScalarSinCos (
rtb_B_46_14_0 , & _rtB -> B_11_2_0 , & _rtB -> B_11_2_1 ) ; memcpy ( & _rtB
-> B_11_5_0 [ 0 ] , & _rtB -> B_11_3_0 [ 0 ] , sizeof ( real_T ) << 4U ) ;
_rtB -> B_11_5_0 [ 14 ] = rtb_B_1_12_0 ; _rtB -> B_11_5_0 [ 11 ] =
rtb_B_1_6_0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
sinthrcosthr1_SubsysRanBC ) ; } } _rtB -> B_46_23_0 = _rtP -> P_235 ; if (
_rtB -> B_46_23_0 ) { rtb_B_1_12_0 = _rtP -> P_29 - rtb_B_1_6_0 ;
rtb_B_1_11_0 = _rtP -> P_30 * rtb_B_1_12_0 ; rtb_B_9_4_0 = _rtP -> P_31 *
ssGetTaskTime ( S , 2 ) ; muDoubleScalarSinCos ( rtb_B_9_4_0 , & _rtB ->
B_9_6_0 , & _rtB -> B_9_6_1 ) ; muDoubleScalarSinCos ( rtb_B_9_4_0 -
rtb_B_46_14_0 , & _rtB -> B_9_7_0 , & _rtB -> B_9_7_1 ) ; memcpy ( & _rtB ->
B_9_10_0 [ 0 ] , & _rtB -> B_9_8_0 [ 0 ] , sizeof ( real_T ) << 4U ) ; _rtB
-> B_9_10_0 [ 14 ] = rtb_B_1_12_0 ; _rtB -> B_9_10_0 [ 11 ] = rtb_B_1_11_0 ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
sinbetacosbetasinthcosth_SubsysRanBC ) ; } } switch ( ( int32_T ) _rtB ->
B_46_13_0 ) { case 1 : rtb_B_46_25_0 [ 0 ] = _rtB -> B_10_2_0 ; rtb_B_46_25_0
[ 1 ] = _rtB -> B_10_2_1 ; rtb_B_46_25_0 [ 2 ] = _rtB -> B_10_0_0 [ 0 ] ;
rtb_B_46_25_0 [ 3 ] = _rtB -> B_10_0_0 [ 1 ] ; break ; case 2 : rtb_B_46_25_0
[ 0 ] = _rtB -> B_11_2_0 ; rtb_B_46_25_0 [ 1 ] = _rtB -> B_11_2_1 ;
rtb_B_46_25_0 [ 2 ] = _rtB -> B_11_0_0 [ 0 ] ; rtb_B_46_25_0 [ 3 ] = _rtB ->
B_11_0_0 [ 1 ] ; break ; default : rtb_B_46_25_0 [ 0 ] = _rtB -> B_9_7_0 ;
rtb_B_46_25_0 [ 1 ] = _rtB -> B_9_7_1 ; rtb_B_46_25_0 [ 2 ] = _rtB -> B_9_6_0
; rtb_B_46_25_0 [ 3 ] = _rtB -> B_9_6_1 ; break ; } B_46_26_0 = _rtP -> P_236
; if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( B_46_26_0 ) { if ( ! _rtDW ->
Rotorreferenceframe_MODE ) { if ( ssGetTaskTime ( S , 2 ) != ssGetTStart ( S
) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Rotorreferenceframe_MODE = true ; } } else { if ( _rtDW ->
Rotorreferenceframe_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep ( S )
; _rtB -> B_6_0_0 = _rtP -> P_21 ; _rtB -> B_6_1_0 = _rtP -> P_21 ; _rtB ->
B_6_2_0 = _rtP -> P_22 ; _rtB -> B_6_3_0 = _rtP -> P_22 ; _rtDW ->
Rotorreferenceframe_MODE = false ; } } } if ( _rtDW ->
Rotorreferenceframe_MODE ) { _rtB -> B_6_0_0 = rtb_B_46_201_0 [ 2 ] ; _rtB ->
B_6_1_0 = - ( 1.7320508075688772 * rtb_B_46_201_0 [ 3 ] + rtb_B_46_201_0 [ 2
] ) / 2.0 ; _rtB -> B_6_2_0 = rtb_B_46_25_0 [ 1 ] * rtb_B_46_201_0 [ 0 ] +
rtb_B_46_25_0 [ 0 ] * rtb_B_46_201_0 [ 1 ] ; _rtB -> B_6_3_0 = ( (
1.7320508075688772 * rtb_B_46_25_0 [ 0 ] + - rtb_B_46_25_0 [ 1 ] ) *
rtb_B_46_201_0 [ 0 ] + ( - 1.7320508075688772 * rtb_B_46_25_0 [ 1 ] -
rtb_B_46_25_0 [ 0 ] ) * rtb_B_46_201_0 [ 1 ] ) / 2.0 ; if ( ssIsMajorTimeStep
( S ) != 0 ) { srUpdateBC ( _rtDW -> Rotorreferenceframe_SubsysRanBC ) ; } }
B_46_28_0 = _rtP -> P_237 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { if (
B_46_28_0 ) { if ( ! _rtDW -> Stationaryreferenceframe_MODE ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Stationaryreferenceframe_MODE = true ; } } else { if ( _rtDW ->
Stationaryreferenceframe_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep
( S ) ; _rtB -> B_7_0_0 = _rtP -> P_23 ; _rtB -> B_7_1_0 = _rtP -> P_23 ;
_rtB -> B_7_2_0 = _rtP -> P_24 ; _rtB -> B_7_3_0 = _rtP -> P_24 ; _rtDW ->
Stationaryreferenceframe_MODE = false ; } } } if ( _rtDW ->
Stationaryreferenceframe_MODE ) { _rtB -> B_7_0_0 = rtb_B_46_25_0 [ 1 ] *
rtb_B_46_201_0 [ 2 ] - rtb_B_46_25_0 [ 0 ] * rtb_B_46_201_0 [ 3 ] ; _rtB ->
B_7_1_0 = ( ( - rtb_B_46_25_0 [ 1 ] - 1.7320508075688772 * rtb_B_46_25_0 [ 0
] ) * rtb_B_46_201_0 [ 2 ] + ( rtb_B_46_25_0 [ 0 ] - 1.7320508075688772 *
rtb_B_46_25_0 [ 1 ] ) * rtb_B_46_201_0 [ 3 ] ) / 2.0 ; _rtB -> B_7_2_0 =
rtb_B_46_201_0 [ 0 ] ; _rtB -> B_7_3_0 = - ( 1.7320508075688772 *
rtb_B_46_201_0 [ 1 ] + rtb_B_46_201_0 [ 0 ] ) / 2.0 ; if ( ssIsMajorTimeStep
( S ) != 0 ) { srUpdateBC ( _rtDW -> Stationaryreferenceframe_SubsysRanBC ) ;
} } B_46_30_0 = _rtP -> P_238 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { if (
B_46_30_0 ) { if ( ! _rtDW -> Synchronousreferenceframe_MODE ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Synchronousreferenceframe_MODE = true ; } } else { if ( _rtDW ->
Synchronousreferenceframe_MODE ) { ssSetBlockStateForSolverChangedAtMajorStep
( S ) ; _rtB -> B_8_0_0 = _rtP -> P_25 ; _rtB -> B_8_1_0 = _rtP -> P_25 ;
_rtB -> B_8_2_0 = _rtP -> P_26 ; _rtB -> B_8_3_0 = _rtP -> P_26 ; _rtDW ->
Synchronousreferenceframe_MODE = false ; } } } if ( _rtDW ->
Synchronousreferenceframe_MODE ) { _rtB -> B_8_0_0 = rtb_B_46_25_0 [ 1 ] *
rtb_B_46_201_0 [ 2 ] + rtb_B_46_25_0 [ 0 ] * rtb_B_46_201_0 [ 3 ] ; _rtB ->
B_8_1_0 = ( ( 1.7320508075688772 * rtb_B_46_25_0 [ 0 ] + - rtb_B_46_25_0 [ 1
] ) * rtb_B_46_201_0 [ 2 ] + ( - 1.7320508075688772 * rtb_B_46_25_0 [ 1 ] -
rtb_B_46_25_0 [ 0 ] ) * rtb_B_46_201_0 [ 3 ] ) / 2.0 ; _rtB -> B_8_2_0 =
rtb_B_46_25_0 [ 3 ] * rtb_B_46_201_0 [ 0 ] + rtb_B_46_25_0 [ 2 ] *
rtb_B_46_201_0 [ 1 ] ; _rtB -> B_8_3_0 = ( ( 1.7320508075688772 *
rtb_B_46_25_0 [ 2 ] + - rtb_B_46_25_0 [ 3 ] ) * rtb_B_46_201_0 [ 0 ] + ( -
1.7320508075688772 * rtb_B_46_25_0 [ 3 ] - rtb_B_46_25_0 [ 2 ] ) *
rtb_B_46_201_0 [ 1 ] ) / 2.0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) {
srUpdateBC ( _rtDW -> Synchronousreferenceframe_SubsysRanBC ) ; } } switch (
( int32_T ) _rtB -> B_46_2_0 ) { case 1 : B_1_7_0_idx_0 = _rtB -> B_6_0_0 ;
B_1_7_0_idx_1 = _rtB -> B_6_1_0 ; break ; case 2 : B_1_7_0_idx_0 = _rtB ->
B_7_0_0 ; B_1_7_0_idx_1 = _rtB -> B_7_1_0 ; break ; default : B_1_7_0_idx_0 =
_rtB -> B_8_0_0 ; B_1_7_0_idx_1 = _rtB -> B_8_1_0 ; break ; } switch ( (
int32_T ) _rtB -> B_46_33_0 ) { case 1 : B_1_8_0_idx_0 = _rtB -> B_6_2_0 ;
B_1_8_0_idx_1 = _rtB -> B_6_3_0 ; break ; case 2 : B_1_8_0_idx_0 = _rtB ->
B_7_2_0 ; B_1_8_0_idx_1 = _rtB -> B_7_3_0 ; break ; default : B_1_8_0_idx_0 =
_rtB -> B_8_2_0 ; B_1_8_0_idx_1 = _rtB -> B_8_3_0 ; break ; } _rtB ->
B_46_35_0 [ 0 ] = _rtP -> P_61 * B_1_7_0_idx_0 ; _rtB -> B_46_35_0 [ 2 ] =
_rtP -> P_61 * B_1_8_0_idx_0 ; _rtB -> B_46_35_0 [ 1 ] = _rtP -> P_61 *
B_1_7_0_idx_1 ; _rtB -> B_46_35_0 [ 3 ] = _rtP -> P_61 * B_1_8_0_idx_1 ; }
ssCallAccelRunBlock ( S , 46 , 36 , SS_CALL_MDL_OUTPUTS ) ; rtb_B_1_11_0 =
_rtB -> B_46_36_0 [ 1 ] + _rtB -> B_46_37_0 ; rtb_B_1_12_0 = _rtP -> P_67 *
_rtB -> B_46_36_0 [ 0 ] ; _rtB -> B_46_46_0 = ( ( rtb_B_1_11_0 - _rtB ->
B_46_39_0 ) * _rtP -> P_64 + _rtB -> B_46_42_0 ) * _rtP -> P_66 *
rtb_B_1_12_0 ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB ->
B_46_47_0 = _rtDW -> UnitDelay_DSTATE ; ssCallAccelRunBlock ( S , 46 , 48 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_46_49_0 [ 0 ] = _rtDW -> UnitDelay1_DSTATE
[ 0 ] ; _rtB -> B_46_49_0 [ 1 ] = _rtDW -> UnitDelay1_DSTATE [ 1 ] ; _rtB ->
B_46_49_0 [ 2 ] = _rtDW -> UnitDelay1_DSTATE [ 2 ] ; } if ( ssGetT ( S ) >=
_rtP -> P_83 ) { _rtB -> B_46_56_0 = _rtB -> B_46_50_0 ; } else if ( ssGetT (
S ) >= _rtP -> P_43 ) { _rtB -> B_46_56_0 = _rtB -> B_46_52_0 ; } else { _rtB
-> B_46_56_0 = _rtB -> B_46_54_0 ; } i = ssIsSampleHit ( S , 4 , 0 ) ; if ( i
!= 0 ) { _rtB -> B_46_57_0 = _rtDW -> UnitDelay_DSTATE_a ; } _rtB ->
B_46_58_0 = _rtB -> B_46_56_0 - _rtB -> B_46_57_0 ; i = ssIsSampleHit ( S , 4
, 0 ) ; if ( i != 0 ) { _rtB -> B_46_59_0 = _rtDW -> UnitDelay1_DSTATE_k ; }
i = ssIsSampleHit ( S , 4 , 0 ) ; if ( i != 0 ) { _rtB -> B_46_64_0 = _rtDW
-> UnitDelay_DSTATE_j ; } rtb_B_46_103_0 = ( ( _rtB -> B_46_58_0 - _rtB ->
B_46_59_0 ) * _rtP -> P_86 + _rtP -> P_87 * _rtB -> B_46_58_0 ) + _rtB ->
B_46_64_0 ; if ( rtb_B_46_103_0 > _rtP -> P_89 ) { _rtB -> B_46_66_0 = _rtP
-> P_89 ; } else if ( rtb_B_46_103_0 < _rtP -> P_90 ) { _rtB -> B_46_66_0 =
_rtP -> P_90 ; } else { _rtB -> B_46_66_0 = rtb_B_46_103_0 ; } i =
ssIsSampleHit ( S , 4 , 0 ) ; if ( i != 0 ) { _rtB -> B_46_68_0 =
muDoubleScalarAbs ( _rtB -> B_46_57_0 ) ; ssCallAccelRunBlock ( S , 15 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_46_70_0 = _rtB -> B_46_67_0 * _rtB ->
B_15_0_1 ; } _rtB -> B_46_71_0 = _rtB -> B_46_66_0 / _rtB -> B_46_70_0 ; if (
ssGetT ( S ) >= _rtP -> P_95 ) { rtb_B_46_103_0 = _rtB -> B_46_73_0 ; } else
{ rtb_B_46_103_0 = _rtB -> B_46_75_0 ; } _rtB -> B_46_79_0 = _rtB ->
B_46_71_0 / ( _rtB -> B_46_72_0 / rtb_B_46_103_0 * _rtB -> B_15_0_1 ) ; i =
ssIsSampleHit ( S , 4 , 0 ) ; if ( i != 0 ) { _rtB -> B_46_82_0 = _rtDW ->
UnitDelay_DSTATE_i ; } _rtB -> B_46_83_0 = ( _rtB -> B_46_79_0 + _rtB ->
B_46_57_0 ) * _rtP -> P_96 + _rtB -> B_46_82_0 ; rtb_B_46_84_0 =
muDoubleScalarCos ( _rtB -> B_46_83_0 ) ; rtb_B_46_85_0 = muDoubleScalarSin (
_rtB -> B_46_83_0 ) ; i = ssIsSampleHit ( S , 4 , 0 ) ; if ( i != 0 ) { _rtB
-> B_46_91_0 = ( _rtB -> B_15_0_1 - _rtDW -> UnitDelay3_DSTATE ) * _rtP ->
P_100 * _rtB -> B_46_86_0 + _rtB -> B_15_0_1 ; } rtb_B_9_4_0 = - _rtB ->
B_46_71_0 * rtb_B_46_85_0 + _rtB -> B_46_91_0 * rtb_B_46_84_0 ; _rtB ->
B_46_93_0 = _rtP -> P_101 * rtb_B_9_4_0 ; _rtB -> B_46_95_0 = ( _rtB ->
B_46_93_0 - _rtB -> B_46_49_0 [ 0 ] ) * _rtP -> P_102 ; i = ssIsSampleHit ( S
, 2 , 0 ) ; if ( i != 0 ) { rtb_B_46_103_0 = look1_pbinlxpw (
muDoubleScalarRem ( ssGetTaskTime ( S , 2 ) + _rtP -> P_104 , _rtP -> P_105 )
* _rtP -> P_106 , _rtP -> P_108 , _rtP -> P_107 , & _rtDW -> m_bpIndex , 2U )
; rtb_B_46_110_0 = ( _rtB -> B_46_95_0 >= ( ( rtb_B_46_103_0 - _rtP -> P_109
) * _rtB -> B_46_107_0 + _rtB -> B_46_96_0 [ 0 ] ) + _rtB -> B_46_107_0 ) ;
_rtB -> B_46_112_0 [ 0 ] = rtb_B_46_110_0 ; _rtB -> B_46_112_0 [ 1 ] = !
rtb_B_46_110_0 ; } rtb_B_46_84_0 = ( 1.7320508 * rtb_B_46_85_0 + -
rtb_B_46_84_0 ) * _rtB -> B_46_91_0 * 0.5 + ( 1.7320508 * rtb_B_46_84_0 +
rtb_B_46_85_0 ) * _rtB -> B_46_71_0 * 0.5 ; _rtB -> B_46_114_0 = _rtP ->
P_111 * rtb_B_46_84_0 ; _rtB -> B_46_116_0 = ( _rtB -> B_46_114_0 - _rtB ->
B_46_49_0 [ 1 ] ) * _rtP -> P_112 ; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i
!= 0 ) { rtb_B_46_85_0 = look1_pbinlxpw ( muDoubleScalarRem ( ssGetTaskTime (
S , 1 ) + _rtP -> P_114 , _rtP -> P_115 ) * _rtP -> P_116 , _rtP -> P_118 ,
_rtP -> P_117 , & _rtDW -> m_bpIndex_k , 2U ) ; rtb_B_46_110_0 = ( _rtB ->
B_46_116_0 >= ( ( rtb_B_46_85_0 - _rtP -> P_119 ) * _rtB -> B_46_128_0 + _rtB
-> B_46_117_0 [ 0 ] ) + _rtB -> B_46_128_0 ) ; B_46_133_0_idx_0 =
rtb_B_46_110_0 ; B_46_133_0_idx_1 = ! rtb_B_46_110_0 ; } _rtB -> B_46_135_0 =
( ( 0.0 - rtb_B_46_84_0 ) - rtb_B_9_4_0 ) * _rtP -> P_121 ; _rtB ->
B_46_137_0 = ( _rtB -> B_46_135_0 - _rtB -> B_46_49_0 [ 2 ] ) * _rtP -> P_122
; i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { rtb_B_9_4_0 =
look1_pbinlxpw ( muDoubleScalarRem ( ssGetTaskTime ( S , 1 ) + _rtP -> P_124
, _rtP -> P_125 ) * _rtP -> P_126 , _rtP -> P_128 , _rtP -> P_127 , & _rtDW
-> m_bpIndex_g , 2U ) ; rtb_B_46_110_0 = ( _rtB -> B_46_137_0 >= ( (
rtb_B_9_4_0 - _rtP -> P_129 ) * _rtB -> B_46_149_0 + _rtB -> B_46_138_0 [ 0 ]
) + _rtB -> B_46_149_0 ) ; _rtB -> B_46_155_0 [ 0 ] = _rtB -> B_46_112_0 [ 0
] ; _rtB -> B_46_155_0 [ 2 ] = B_46_133_0_idx_0 ; _rtB -> B_46_155_0 [ 1 ] =
_rtB -> B_46_112_0 [ 1 ] ; _rtB -> B_46_155_0 [ 3 ] = B_46_133_0_idx_1 ; _rtB
-> B_46_155_0 [ 4 ] = rtb_B_46_110_0 ; _rtB -> B_46_155_0 [ 5 ] = !
rtb_B_46_110_0 ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
rtb_B_46_165_0 = _rtP -> P_132 [ 0 ] * rtb_B_46_6_0 [ 0 ] * _rtB -> B_46_3_0
[ 1 ] + _rtP -> P_132 [ 1 ] * rtb_B_46_6_0 [ 1 ] * _rtB -> B_46_3_0 [ 0 ] ;
_rtB -> B_46_167_0 [ 0 ] = _rtP -> P_134 [ 0 ] * rtb_B_1_6_0 ; _rtB ->
B_46_167_0 [ 1 ] = _rtP -> P_134 [ 1 ] * rtb_B_46_165_0 ; _rtB -> B_46_167_0
[ 2 ] = _rtP -> P_133 * rtb_B_46_14_0 * _rtP -> P_134 [ 2 ] ; } rtb_B_46_14_0
= muDoubleScalarCos ( _rtB -> B_46_83_0 ) ; rtb_B_9_4_0 = muDoubleScalarSin (
_rtB -> B_46_83_0 ) ; i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB
-> B_46_170_0 = _rtB -> B_46_49_0 [ 0 ] ; _rtB -> B_46_171_0 = _rtB ->
B_46_49_0 [ 0 ] / 1.7320508075688772 + 1.1547005383792517 * _rtB -> B_46_49_0
[ 1 ] ; } _rtB -> B_46_172_0 = rtb_B_46_14_0 * _rtB -> B_46_170_0 +
rtb_B_9_4_0 * _rtB -> B_46_171_0 ; _rtB -> B_46_173_0 = - rtb_B_9_4_0 * _rtB
-> B_46_170_0 + rtb_B_46_14_0 * _rtB -> B_46_171_0 ; i = ssIsSampleHit ( S ,
1 , 0 ) ; if ( i != 0 ) { ssCallAccelRunBlock ( S , 46 , 174 ,
SS_CALL_MDL_OUTPUTS ) ; } i = ssIsSampleHit ( S , 4 , 0 ) ; if ( i != 0 ) {
_rtB -> B_46_175_0 [ 0 ] = _rtB -> B_46_56_0 ; _rtB -> B_46_175_0 [ 1 ] =
_rtB -> B_46_57_0 ; ssCallAccelRunBlock ( S , 46 , 176 , SS_CALL_MDL_OUTPUTS
) ; ssCallAccelRunBlock ( S , 46 , 177 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_46_178_0 [ 0 ] = _rtB -> B_46_93_0 ; _rtB -> B_46_178_0 [ 1 ] = _rtB ->
B_46_114_0 ; _rtB -> B_46_178_0 [ 2 ] = _rtB -> B_46_135_0 ;
ssCallAccelRunBlock ( S , 46 , 179 , SS_CALL_MDL_OUTPUTS ) ; } rtb_B_46_14_0
= _rtX -> Integrator_CSTATE ; _rtB -> B_46_183_0 = _rtP -> P_136 * _rtX ->
Integrator_CSTATE + _rtP -> P_137 * _rtB -> B_46_167_0 [ 1 ] ; i =
ssIsSampleHit ( S , 4 , 0 ) ; if ( i != 0 ) { ssCallAccelRunBlock ( S , 46 ,
184 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_46_185_0 [ 0 ] = _rtB -> B_46_172_0 ;
_rtB -> B_46_185_0 [ 1 ] = _rtB -> B_46_173_0 ; ssCallAccelRunBlock ( S , 46
, 186 , SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_46_187_0 [ 0 ] = _rtB -> B_46_91_0
; _rtB -> B_46_187_0 [ 1 ] = _rtB -> B_46_71_0 ; ssCallAccelRunBlock ( S , 46
, 188 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 46 , 189 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 46 , 190 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 46 , 191 ,
SS_CALL_MDL_OUTPUTS ) ; } i = ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) {
if ( _rtB -> B_46_194_0 >= _rtP -> P_143 ) { rtb_B_9_4_0 = _rtB -> B_1_17_0 ;
} else { rtb_B_9_4_0 = _rtB -> B_46_195_0 ; } rtb_B_46_201_0 [ 0 ] = _rtP ->
P_147 * _rtB -> B_46_200_0 [ 0 ] ; rtb_B_46_201_0 [ 2 ] = _rtP -> P_147 *
_rtB -> B_46_48_0 [ 10 ] ; rtb_B_46_201_0 [ 1 ] = _rtP -> P_147 * _rtB ->
B_46_200_0 [ 1 ] ; rtb_B_46_201_0 [ 3 ] = _rtP -> P_147 * _rtB -> B_46_48_0 [
11 ] ; B_46_202_0 = _rtP -> P_239 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { if
( B_46_202_0 ) { if ( ! _rtDW -> Rotorreferenceframe_MODE_d ) { if (
ssGetTaskTime ( S , 2 ) != ssGetTStart ( S ) ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; } _rtDW ->
Rotorreferenceframe_MODE_d = true ; } } else { if ( _rtDW ->
Rotorreferenceframe_MODE_d ) { ssSetBlockStateForSolverChangedAtMajorStep ( S
) ; _rtB -> B_3_2_0 = _rtP -> P_15 ; _rtB -> B_3_0_0 = _rtP -> P_15 ; _rtB ->
B_3_3_0 = _rtP -> P_16 ; _rtB -> B_3_1_0 = _rtP -> P_16 ; _rtDW ->
Rotorreferenceframe_MODE_d = false ; } } } if ( _rtDW ->
Rotorreferenceframe_MODE_d ) { _rtB -> B_3_0_0 = - 0.57735026918962573 *
rtb_B_46_201_0 [ 1 ] ; _rtB -> B_3_1_0 = ( ( rtb_B_46_25_0 [ 0 ] -
1.7320508075688772 * rtb_B_46_25_0 [ 1 ] ) * rtb_B_46_201_0 [ 3 ] + 2.0 *
rtb_B_46_25_0 [ 0 ] * rtb_B_46_201_0 [ 2 ] ) * 0.33333333333333331 ; _rtB ->
B_3_2_0 = ( 2.0 * rtb_B_46_201_0 [ 0 ] + rtb_B_46_201_0 [ 1 ] ) *
0.33333333333333331 ; _rtB -> B_3_3_0 = ( ( 1.7320508075688772 *
rtb_B_46_25_0 [ 0 ] + rtb_B_46_25_0 [ 1 ] ) * rtb_B_46_201_0 [ 3 ] + 2.0 *
rtb_B_46_25_0 [ 1 ] * rtb_B_46_201_0 [ 2 ] ) * 0.33333333333333331 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
Rotorreferenceframe_SubsysRanBC_n ) ; } } B_46_204_0 = _rtP -> P_240 ; if (
ssIsMajorTimeStep ( S ) != 0 ) { if ( B_46_204_0 ) { if ( ! _rtDW ->
Stationaryreferenceframe_MODE_p ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
_rtDW -> Stationaryreferenceframe_MODE_p = true ; } } else { if ( _rtDW ->
Stationaryreferenceframe_MODE_p ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtB -> B_4_2_0 = _rtP ->
P_17 ; _rtB -> B_4_0_0 = _rtP -> P_17 ; _rtB -> B_4_3_0 = _rtP -> P_18 ; _rtB
-> B_4_1_0 = _rtP -> P_18 ; _rtDW -> Stationaryreferenceframe_MODE_p = false
; } } } if ( _rtDW -> Stationaryreferenceframe_MODE_p ) { _rtB -> B_4_0_0 = (
( - rtb_B_46_25_0 [ 0 ] - 1.7320508075688772 * rtb_B_46_25_0 [ 1 ] ) *
rtb_B_46_201_0 [ 1 ] + - 2.0 * rtb_B_46_25_0 [ 0 ] * rtb_B_46_201_0 [ 0 ] ) *
0.33333333333333331 ; _rtB -> B_4_1_0 = - 0.57735026918962573 *
rtb_B_46_201_0 [ 3 ] ; _rtB -> B_4_2_0 = ( ( rtb_B_46_25_0 [ 1 ] -
1.7320508075688772 * rtb_B_46_25_0 [ 0 ] ) * rtb_B_46_201_0 [ 1 ] + 2.0 *
rtb_B_46_25_0 [ 1 ] * rtb_B_46_201_0 [ 0 ] ) * 0.33333333333333331 ; _rtB ->
B_4_3_0 = ( 2.0 * rtb_B_46_201_0 [ 2 ] + rtb_B_46_201_0 [ 3 ] ) *
0.33333333333333331 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC (
_rtDW -> Stationaryreferenceframe_SubsysRanBC_j ) ; } } B_46_206_0 = _rtP ->
P_241 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { if ( B_46_206_0 ) { if ( !
_rtDW -> Synchronousreferenceframe_MODE_d ) { if ( ssGetTaskTime ( S , 2 ) !=
ssGetTStart ( S ) ) { ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; }
_rtDW -> Synchronousreferenceframe_MODE_d = true ; } } else { if ( _rtDW ->
Synchronousreferenceframe_MODE_d ) {
ssSetBlockStateForSolverChangedAtMajorStep ( S ) ; _rtB -> B_5_2_0 = _rtP ->
P_19 ; _rtB -> B_5_0_0 = _rtP -> P_19 ; _rtB -> B_5_3_0 = _rtP -> P_20 ; _rtB
-> B_5_1_0 = _rtP -> P_20 ; _rtDW -> Synchronousreferenceframe_MODE_d = false
; } } } if ( _rtDW -> Synchronousreferenceframe_MODE_d ) { _rtB -> B_5_0_0 =
( ( rtb_B_46_25_0 [ 0 ] - 1.7320508075688772 * rtb_B_46_25_0 [ 1 ] ) *
rtb_B_46_201_0 [ 1 ] + 2.0 * rtb_B_46_25_0 [ 0 ] * rtb_B_46_201_0 [ 0 ] ) /
3.0 ; _rtB -> B_5_1_0 = ( ( rtb_B_46_25_0 [ 2 ] - 1.7320508075688772 *
rtb_B_46_25_0 [ 3 ] ) * rtb_B_46_201_0 [ 3 ] + 2.0 * rtb_B_46_25_0 [ 2 ] *
rtb_B_46_201_0 [ 2 ] ) / 3.0 ; _rtB -> B_5_2_0 = ( ( 1.7320508075688772 *
rtb_B_46_25_0 [ 0 ] + rtb_B_46_25_0 [ 1 ] ) * rtb_B_46_201_0 [ 1 ] + 2.0 *
rtb_B_46_25_0 [ 1 ] * rtb_B_46_201_0 [ 0 ] ) / 3.0 ; _rtB -> B_5_3_0 = ( (
1.7320508075688772 * rtb_B_46_25_0 [ 2 ] + rtb_B_46_25_0 [ 3 ] ) *
rtb_B_46_201_0 [ 3 ] + 2.0 * rtb_B_46_25_0 [ 3 ] * rtb_B_46_201_0 [ 2 ] ) /
3.0 ; if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
Synchronousreferenceframe_SubsysRanBC_i ) ; } } switch ( ( int32_T ) _rtB ->
B_46_199_0 ) { case 1 : _rtB -> B_46_208_0 [ 0 ] = _rtB -> B_3_3_0 ; _rtB ->
B_46_208_0 [ 1 ] = _rtB -> B_3_1_0 ; break ; case 2 : _rtB -> B_46_208_0 [ 0
] = _rtB -> B_4_3_0 ; _rtB -> B_46_208_0 [ 1 ] = _rtB -> B_4_1_0 ; break ;
default : _rtB -> B_46_208_0 [ 0 ] = _rtB -> B_5_3_0 ; _rtB -> B_46_208_0 [ 1
] = _rtB -> B_5_1_0 ; break ; } switch ( ( int32_T ) _rtB -> B_46_209_0 ) {
case 1 : _rtB -> B_46_210_0 [ 0 ] = _rtB -> B_3_2_0 ; _rtB -> B_46_210_0 [ 1
] = _rtB -> B_3_0_0 ; break ; case 2 : _rtB -> B_46_210_0 [ 0 ] = _rtB ->
B_4_2_0 ; _rtB -> B_46_210_0 [ 1 ] = _rtB -> B_4_0_0 ; break ; default : _rtB
-> B_46_210_0 [ 0 ] = _rtB -> B_5_2_0 ; _rtB -> B_46_210_0 [ 1 ] = _rtB ->
B_5_0_0 ; break ; } if ( ssGetTaskTime ( S , 2 ) >= _rtP -> P_150 ) {
rtb_B_46_25_0 [ 0 ] = _rtB -> B_46_208_0 [ 0 ] + _rtDW -> voltages_DSTATE [ 0
] ; rtb_B_46_25_0 [ 2 ] = _rtB -> B_46_210_0 [ 0 ] + _rtDW -> voltages_DSTATE
[ 2 ] ; rtb_B_46_25_0 [ 1 ] = _rtB -> B_46_208_0 [ 1 ] + _rtDW ->
voltages_DSTATE [ 1 ] ; rtb_B_46_25_0 [ 3 ] = _rtB -> B_46_210_0 [ 1 ] +
_rtDW -> voltages_DSTATE [ 3 ] ; switch ( ( int32_T ) _rtB -> B_46_196_0 ) {
case 1 : memcpy ( & rtb_B_1_19_0 [ 0 ] , & _rtB -> B_10_5_0 [ 0 ] , sizeof (
real_T ) << 4U ) ; break ; case 2 : memcpy ( & rtb_B_1_19_0 [ 0 ] , & _rtB ->
B_11_5_0 [ 0 ] , sizeof ( real_T ) << 4U ) ; break ; default : memcpy ( &
rtb_B_1_19_0 [ 0 ] , & _rtB -> B_9_10_0 [ 0 ] , sizeof ( real_T ) << 4U ) ;
break ; } rtb_B_46_110_0 = ( _rtB -> B_46_192_0 >= _rtP -> P_12 ) ; for ( i =
0 ; i < 16 ; i ++ ) { if ( rtb_B_46_110_0 ) { rtb_B_46_103_0 = _rtB ->
B_1_24_0 [ i ] ; } else { rtb_B_46_103_0 = _rtB -> B_46_193_0 [ i ] ; }
rtb_B_46_103_0 = ( ( 0.0 - rtb_B_1_19_0 [ i ] ) - rtb_B_46_103_0 ) * _rtP ->
P_13 ; B_2_1_0 [ i ] = _rtB -> B_46_198_0 [ i ] - rtb_B_46_103_0 ;
rtb_B_1_19_0 [ i ] = rtb_B_46_103_0 ; } rt_invd4x4_snf ( B_2_1_0 ,
rtb_B_2_1_0 ) ; for ( i = 0 ; i < 16 ; i ++ ) { rtb_B_1_19_0 [ i ] += _rtB ->
B_46_198_0 [ i ] ; } for ( i = 0 ; i < 4 ; i ++ ) { rtb_B_46_201_0 [ i ] =
0.0 ; tmp [ i ] = 0.0 ; for ( i_0 = 0 ; i_0 < 4 ; i_0 ++ ) { B_2_1_0 [ i + (
i_0 << 2 ) ] = 0.0 ; B_2_1_0 [ i + ( i_0 << 2 ) ] += rtb_B_1_19_0 [ i_0 << 2
] * rtb_B_2_1_0 [ i ] ; B_2_1_0 [ i + ( i_0 << 2 ) ] += rtb_B_1_19_0 [ ( i_0
<< 2 ) + 1 ] * rtb_B_2_1_0 [ i + 4 ] ; B_2_1_0 [ i + ( i_0 << 2 ) ] +=
rtb_B_1_19_0 [ ( i_0 << 2 ) + 2 ] * rtb_B_2_1_0 [ i + 8 ] ; B_2_1_0 [ i + (
i_0 << 2 ) ] += rtb_B_1_19_0 [ ( i_0 << 2 ) + 3 ] * rtb_B_2_1_0 [ i + 12 ] ;
rtb_B_46_201_0 [ i ] += B_2_1_0 [ ( i_0 << 2 ) + i ] * _rtB -> B_46_3_0 [ i_0
] ; tmp [ i ] += rtb_B_2_1_0 [ ( i_0 << 2 ) + i ] * _rtP -> P_14 *
rtb_B_46_25_0 [ i_0 ] ; } _rtB -> B_46_214_0 [ i ] = rtb_B_46_201_0 [ i ] +
tmp [ i ] ; } } else { _rtB -> B_46_214_0 [ 0 ] = _rtB -> B_46_3_0 [ 0 ] ;
_rtB -> B_46_214_0 [ 1 ] = _rtB -> B_46_3_0 [ 1 ] ; _rtB -> B_46_214_0 [ 2 ]
= _rtB -> B_46_3_0 [ 2 ] ; _rtB -> B_46_214_0 [ 3 ] = _rtB -> B_46_3_0 [ 3 ]
; } _rtB -> B_46_217_0 [ 2 ] = ( ( 0.0 - B_1_7_0_idx_0 ) - B_1_7_0_idx_1 ) *
_rtP -> P_151 [ 2 ] ; _rtB -> B_46_217_0 [ 0 ] = _rtP -> P_151 [ 0 ] *
B_1_7_0_idx_0 ; _rtB -> B_46_217_0 [ 3 ] = _rtP -> P_151 [ 3 ] * rtb_B_46_6_0
[ 2 ] ; _rtB -> B_46_217_0 [ 5 ] = _rtP -> P_151 [ 5 ] * _rtB -> B_46_3_0 [ 2
] ; _rtB -> B_46_217_0 [ 7 ] = _rtP -> P_151 [ 7 ] * _rtB -> B_46_210_0 [ 0 ]
; _rtB -> B_46_217_0 [ 9 ] = _rtP -> P_151 [ 9 ] * B_1_8_0_idx_0 ; _rtB ->
B_46_217_0 [ 12 ] = _rtP -> P_151 [ 12 ] * rtb_B_46_6_0 [ 0 ] ; _rtB ->
B_46_217_0 [ 14 ] = _rtP -> P_151 [ 14 ] * _rtB -> B_46_3_0 [ 0 ] ; _rtB ->
B_46_217_0 [ 16 ] = _rtP -> P_151 [ 16 ] * _rtB -> B_46_208_0 [ 0 ] ; _rtB ->
B_46_217_0 [ 1 ] = _rtP -> P_151 [ 1 ] * B_1_7_0_idx_1 ; _rtB -> B_46_217_0 [
4 ] = _rtP -> P_151 [ 4 ] * rtb_B_46_6_0 [ 3 ] ; _rtB -> B_46_217_0 [ 6 ] =
_rtP -> P_151 [ 6 ] * _rtB -> B_46_3_0 [ 3 ] ; _rtB -> B_46_217_0 [ 8 ] =
_rtP -> P_151 [ 8 ] * _rtB -> B_46_210_0 [ 1 ] ; _rtB -> B_46_217_0 [ 10 ] =
_rtP -> P_151 [ 10 ] * B_1_8_0_idx_1 ; _rtB -> B_46_217_0 [ 13 ] = _rtP ->
P_151 [ 13 ] * rtb_B_46_6_0 [ 1 ] ; _rtB -> B_46_217_0 [ 15 ] = _rtP -> P_151
[ 15 ] * _rtB -> B_46_3_0 [ 1 ] ; _rtB -> B_46_217_0 [ 17 ] = _rtP -> P_151 [
17 ] * _rtB -> B_46_208_0 [ 1 ] ; _rtB -> B_46_217_0 [ 11 ] = ( ( 0.0 -
B_1_8_0_idx_0 ) - B_1_8_0_idx_1 ) * _rtP -> P_151 [ 11 ] ; _rtB -> B_46_217_0
[ 18 ] = _rtP -> P_151 [ 18 ] * rtb_B_9_4_0 ; _rtB -> B_46_221_0 = ( (
rtb_B_46_165_0 - _rtB -> B_46_218_0 ) - _rtP -> P_153 * rtb_B_1_6_0 ) * _rtP
-> P_154 ; if ( _rtDW -> Rotorspeedwm_SYSTEM_ENABLE != 0 ) { _rtB ->
B_46_222_0 = _rtDW -> Rotorspeedwm_DSTATE ; } else { _rtB -> B_46_222_0 =
_rtP -> P_155 * _rtB -> B_46_221_0 + _rtDW -> Rotorspeedwm_DSTATE ; } _rtB ->
B_46_223_0 = _rtP -> P_157 * rtb_B_1_6_0 ; } _rtB -> B_46_231_0 = _rtP ->
P_159 * _rtB -> B_46_167_0 [ 1 ] + _rtP -> P_158 * rtb_B_46_14_0 ; i =
ssIsSampleHit ( S , 4 , 0 ) ; if ( i != 0 ) { ssCallAccelRunBlock ( S , 46 ,
232 , SS_CALL_MDL_OUTPUTS ) ; } rtb_B_46_165_0 = _rtX -> Integrator_CSTATE_m
; B_46_236_0 = _rtP -> P_161 * _rtX -> Integrator_CSTATE_m + _rtP -> P_162 *
_rtB -> B_46_49_0 [ 0 ] ; PV_fed_VCIMD_updated_TrueRMS ( S , _rtB ->
B_46_238_0 , B_46_236_0 , & _rtB -> TrueRMS , & _rtDW -> TrueRMS , & _rtP ->
TrueRMS , & _rtX -> TrueRMS ) ; PV_fed_VCIMD_updated_RMS ( S , _rtB ->
B_46_240_0 , B_46_236_0 , & _rtB -> RMS , & _rtDW -> RMS , & _rtP -> RMS , &
_rtX -> RMS ) ; if ( _rtB -> B_46_238_0 ) { rtb_B_1_6_0 = _rtB -> TrueRMS .
B_20_10_0 ; } else { rtb_B_1_6_0 = _rtB -> RMS . B_18_22_0 ; }
B_46_133_0_idx_0 = _rtX -> Integrator_CSTATE_n ; B_46_246_0 = _rtP -> P_165 *
_rtX -> Integrator_CSTATE_n + _rtP -> P_166 * _rtB -> B_46_49_0 [ 1 ] ;
PV_fed_VCIMD_updated_TrueRMS ( S , _rtB -> B_46_248_0 , B_46_246_0 , & _rtB
-> TrueRMS_f , & _rtDW -> TrueRMS_f , & _rtP -> TrueRMS_f , & _rtX ->
TrueRMS_f ) ; PV_fed_VCIMD_updated_RMS ( S , _rtB -> B_46_250_0 , B_46_246_0
, & _rtB -> RMS_f , & _rtDW -> RMS_f , & _rtP -> RMS_f , & _rtX -> RMS_f ) ;
if ( _rtB -> B_46_248_0 ) { rtb_B_46_14_0 = _rtB -> TrueRMS_f . B_20_10_0 ; }
else { rtb_B_46_14_0 = _rtB -> RMS_f . B_18_22_0 ; } B_46_133_0_idx_1 = _rtX
-> Integrator_CSTATE_i ; B_46_256_0 = _rtP -> P_169 * _rtX ->
Integrator_CSTATE_i + _rtP -> P_170 * _rtB -> B_46_49_0 [ 2 ] ;
PV_fed_VCIMD_updated_TrueRMS ( S , _rtB -> B_46_258_0 , B_46_256_0 , & _rtB
-> TrueRMS_h , & _rtDW -> TrueRMS_h , & _rtP -> TrueRMS_h , & _rtX ->
TrueRMS_h ) ; PV_fed_VCIMD_updated_RMS ( S , _rtB -> B_46_260_0 , B_46_256_0
, & _rtB -> RMS_fg , & _rtDW -> RMS_fg , & _rtP -> RMS_fg , & _rtX -> RMS_fg
) ; if ( _rtB -> B_46_258_0 ) { rtb_B_46_103_0 = _rtB -> TrueRMS_h .
B_20_10_0 ; } else { rtb_B_46_103_0 = _rtB -> RMS_fg . B_18_22_0 ; }
rtb_B_46_84_0 = ( muDoubleScalarPower ( rtb_B_1_6_0 , 2.0 ) +
muDoubleScalarPower ( rtb_B_46_14_0 , 2.0 ) ) + muDoubleScalarPower (
rtb_B_46_103_0 , 2.0 ) ; if ( rtb_B_46_84_0 < 0.0 ) { _rtB -> B_46_263_0 = -
muDoubleScalarSqrt ( - rtb_B_46_84_0 ) ; } else { _rtB -> B_46_263_0 =
muDoubleScalarSqrt ( rtb_B_46_84_0 ) ; } i = ssIsSampleHit ( S , 4 , 0 ) ; if
( i != 0 ) { ssCallAccelRunBlock ( S , 46 , 264 , SS_CALL_MDL_OUTPUTS ) ; }
rtb_B_1_6_0 = _rtX -> Integrator_CSTATE_o ; B_46_268_0 = _rtP -> P_173 * _rtX
-> Integrator_CSTATE_o + _rtP -> P_174 * _rtB -> B_46_93_0 ;
PV_fed_VCIMD_updated_TrueRMS ( S , _rtB -> B_46_270_0 , B_46_268_0 , & _rtB
-> TrueRMS_p , & _rtDW -> TrueRMS_p , & _rtP -> TrueRMS_p , & _rtX ->
TrueRMS_p ) ; PV_fed_VCIMD_updated_RMS ( S , _rtB -> B_46_272_0 , B_46_268_0
, & _rtB -> RMS_e , & _rtDW -> RMS_e , & _rtP -> RMS_e , & _rtX -> RMS_e ) ;
if ( _rtB -> B_46_270_0 ) { rtb_B_46_84_0 = _rtB -> TrueRMS_p . B_20_10_0 ; }
else { rtb_B_46_84_0 = _rtB -> RMS_e . B_18_22_0 ; } rtb_B_46_14_0 = _rtX ->
Integrator_CSTATE_d ; B_46_278_0 = _rtP -> P_177 * _rtX ->
Integrator_CSTATE_d + _rtP -> P_178 * _rtB -> B_46_114_0 ;
PV_fed_VCIMD_updated_TrueRMS ( S , _rtB -> B_46_280_0 , B_46_278_0 , & _rtB
-> TrueRMS_k , & _rtDW -> TrueRMS_k , & _rtP -> TrueRMS_k , & _rtX ->
TrueRMS_k ) ; PV_fed_VCIMD_updated_RMS ( S , _rtB -> B_46_282_0 , B_46_278_0
, & _rtB -> RMS_h , & _rtDW -> RMS_h , & _rtP -> RMS_h , & _rtX -> RMS_h ) ;
if ( _rtB -> B_46_280_0 ) { rtb_B_46_85_0 = _rtB -> TrueRMS_k . B_20_10_0 ; }
else { rtb_B_46_85_0 = _rtB -> RMS_h . B_18_22_0 ; } rtb_B_9_4_0 = _rtX ->
Integrator_CSTATE_a ; B_46_288_0 = _rtP -> P_181 * _rtX ->
Integrator_CSTATE_a + _rtP -> P_182 * _rtB -> B_46_135_0 ;
PV_fed_VCIMD_updated_TrueRMS ( S , _rtB -> B_46_290_0 , B_46_288_0 , & _rtB
-> TrueRMS_fi , & _rtDW -> TrueRMS_fi , & _rtP -> TrueRMS_fi , & _rtX ->
TrueRMS_fi ) ; PV_fed_VCIMD_updated_RMS ( S , _rtB -> B_46_292_0 , B_46_288_0
, & _rtB -> RMS_k , & _rtDW -> RMS_k , & _rtP -> RMS_k , & _rtX -> RMS_k ) ;
if ( _rtB -> B_46_290_0 ) { rtb_B_46_103_0 = _rtB -> TrueRMS_fi . B_20_10_0 ;
} else { rtb_B_46_103_0 = _rtB -> RMS_k . B_18_22_0 ; } rtb_B_46_84_0 = (
muDoubleScalarPower ( rtb_B_46_84_0 , 2.0 ) + muDoubleScalarPower (
rtb_B_46_85_0 , 2.0 ) ) + muDoubleScalarPower ( rtb_B_46_103_0 , 2.0 ) ; if (
rtb_B_46_84_0 < 0.0 ) { _rtB -> B_46_295_0 = - muDoubleScalarSqrt ( -
rtb_B_46_84_0 ) ; } else { _rtB -> B_46_295_0 = muDoubleScalarSqrt (
rtb_B_46_84_0 ) ; } i = ssIsSampleHit ( S , 4 , 0 ) ; if ( i != 0 ) {
ssCallAccelRunBlock ( S , 46 , 296 , SS_CALL_MDL_OUTPUTS ) ; } _rtB ->
B_46_299_0 = _rtP -> P_185 * _rtB -> B_46_49_0 [ 0 ] + _rtP -> P_184 *
rtb_B_46_165_0 ; _rtB -> B_46_302_0 = _rtP -> P_187 * _rtB -> B_46_49_0 [ 1 ]
+ _rtP -> P_186 * B_46_133_0_idx_0 ; _rtB -> B_46_305_0 = _rtP -> P_189 *
_rtB -> B_46_49_0 [ 2 ] + _rtP -> P_188 * B_46_133_0_idx_1 ; _rtB ->
B_46_308_0 = _rtP -> P_191 * _rtB -> B_46_93_0 + _rtP -> P_190 * rtb_B_1_6_0
; _rtB -> B_46_311_0 = _rtP -> P_193 * _rtB -> B_46_114_0 + _rtP -> P_192 *
rtb_B_46_14_0 ; _rtB -> B_46_314_0 = _rtP -> P_195 * _rtB -> B_46_135_0 +
_rtP -> P_194 * rtb_B_9_4_0 ; i = ssIsSampleHit ( S , 4 , 0 ) ; if ( i != 0 )
{ ssCallAccelRunBlock ( S , 46 , 315 , SS_CALL_MDL_OUTPUTS ) ; } i =
ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_46_316_0 = _rtP ->
P_196 * _rtB -> B_46_167_0 [ 0 ] ; _rtB -> B_46_318_0 = _rtP -> P_198 * _rtB
-> B_46_48_0 [ 12 ] ; _rtB -> B_46_319_0 = _rtP -> P_199 * _rtB -> B_46_48_0
[ 15 ] ; ssCallAccelRunBlock ( S , 12 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtB ->
B_46_323_0 = _rtP -> P_200 * _rtB -> B_12_0_1 - _rtP -> P_201 * _rtB ->
B_46_318_0 ; } rtb_B_46_103_0 = _rtB -> B_46_317_0 - ( _rtP -> P_203 * _rtX
-> TransferFcn_CSTATE + _rtP -> P_204 * _rtB -> B_46_323_0 ) ; if (
rtb_B_46_103_0 > _rtP -> P_205 ) { _rtB -> B_46_326_0 = _rtP -> P_205 ; }
else if ( rtb_B_46_103_0 < _rtP -> P_206 ) { _rtB -> B_46_326_0 = _rtP ->
P_206 ; } else { _rtB -> B_46_326_0 = rtb_B_46_103_0 ; } i = ssIsSampleHit (
S , 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_46_327_0 = _rtP -> P_207 * _rtB ->
B_46_48_0 [ 13 ] ; _rtB -> B_46_328_0 = _rtP -> P_208 * _rtB -> B_46_48_0 [
14 ] ; } _rtB -> B_46_329_0 = ssGetT ( S ) ; i = ssIsSampleHit ( S , 1 , 0 )
; if ( i != 0 ) { ssCallAccelRunBlock ( S , 13 , 0 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 46 , 332 , SS_CALL_MDL_OUTPUTS ) ; } i =
ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_46_333_0 = _rtB ->
B_46_318_0 * _rtB -> B_46_319_0 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i
!= 0 ) { ssCallAccelRunBlock ( S , 46 , 334 , SS_CALL_MDL_OUTPUTS ) ; } i =
ssIsSampleHit ( S , 2 , 0 ) ; if ( i != 0 ) { _rtB -> B_46_340_0 = _rtB ->
B_46_319_0 * _rtB -> B_46_338_0 + _rtB -> B_46_318_0 ; } rtb_B_46_165_0 =
rtb_B_1_11_0 / _rtB -> B_46_344_0 ; rtb_B_1_11_0 = muDoubleScalarExp ( _rtB
-> B_46_351_0 - ( ( rtb_B_1_11_0 - _rtB -> B_46_353_0 ) * _rtP -> P_217 +
_rtB -> B_46_352_0 ) * _rtP -> P_218 / ( _rtP -> P_219 * rtb_B_1_11_0 ) ) * (
_rtP -> P_220 * muDoubleScalarPower ( rtb_B_46_165_0 , 3.0 ) ) ; rtb_B_1_12_0
*= _rtB -> B_46_340_0 / _rtB -> B_46_366_0 ; i = ssIsSampleHit ( S , 2 , 0 )
; if ( i != 0 ) { _rtB -> B_46_369_0 = _rtB -> B_46_340_0 / _rtB ->
B_46_368_0 ; } _rtB -> B_46_370_0 = ( ( muDoubleScalarExp ( 1.0 / ( _rtP ->
P_212 * rtb_B_46_165_0 ) * _rtB -> B_46_340_0 ) - _rtB -> B_46_349_0 ) *
rtb_B_1_11_0 + rtb_B_1_12_0 ) - _rtB -> B_46_369_0 ; i = ssIsSampleHit ( S ,
1 , 0 ) ; if ( i != 0 ) { ssCallAccelRunBlock ( S , 46 , 383 ,
SS_CALL_MDL_OUTPUTS ) ; } rtb_B_46_165_0 = _rtP -> P_227 * ssGetT ( S ) ; if
( _rtB -> B_46_326_0 - ( _rtB -> B_46_389_0 - ( 1.0 - ( rtb_B_46_165_0 -
muDoubleScalarFloor ( rtb_B_46_165_0 ) ) * 2.0 ) * _rtP -> P_226 ) >= _rtP ->
P_228 ) { _rtB -> B_46_393_0 = _rtB -> B_46_387_0 ; } else { _rtB ->
B_46_393_0 = _rtB -> B_46_388_0 ; } i = ssIsSampleHit ( S , 1 , 0 ) ; if ( i
!= 0 ) { ssCallAccelRunBlock ( S , 46 , 394 , SS_CALL_MDL_OUTPUTS ) ; } i =
ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_46_401_0 = _rtP ->
P_230 ; } rtb_B_46_165_0 = ssGetT ( S ) + _rtB -> B_46_401_0 ; i =
ssIsSampleHit ( S , 1 , 0 ) ; if ( i != 0 ) { _rtB -> B_46_403_0 = _rtP ->
P_231 ; } _rtB -> B_46_410_0 = ( ( _rtB -> B_13_0_1 !=
PV_fed_VCIMD_updated_rtC ( S ) -> B_46_398_0 ) && ( _rtB -> B_13_0_1 >= ( (
_rtP -> P_232 * muDoubleScalarRem ( rtb_B_46_165_0 , _rtB -> B_46_403_0 ) *
2.0 - 1.0 ) + 1.0 ) * 0.5 ) ) ; UNUSED_PARAMETER ( tid ) ; } static void
mdlOutputsTID5 ( SimStruct * S , int_T tid ) { int32_T i ;
B_PV_fed_VCIMD_updated_T * _rtB ; P_PV_fed_VCIMD_updated_T * _rtP ;
DW_PV_fed_VCIMD_updated_T * _rtDW ; _rtDW = ( ( DW_PV_fed_VCIMD_updated_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_PV_fed_VCIMD_updated_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_PV_fed_VCIMD_updated_T * )
_ssGetModelBlockIO ( S ) ) ; _rtB -> B_46_0_0 [ 0 ] = _rtP -> P_44 [ 0 ] ;
_rtB -> B_46_0_0 [ 1 ] = _rtP -> P_44 [ 1 ] ; _rtB -> B_46_0_0 [ 2 ] = _rtP
-> P_44 [ 2 ] ; _rtB -> B_46_0_0 [ 3 ] = _rtP -> P_44 [ 3 ] ; for ( i = 0 ; i
< 6 ; i ++ ) { _rtB -> B_46_1_0 [ i ] = _rtP -> P_45 [ i ] ; } _rtB ->
B_46_2_0 = _rtP -> P_46 ; _rtB -> B_46_7_0 = _rtP -> P_50 ; _rtB -> B_1_0_0 [
0 ] = _rtP -> P_3 [ 0 ] ; _rtB -> B_1_1_0 [ 0 ] = _rtP -> P_4 [ 0 ] ; _rtB ->
B_1_0_0 [ 1 ] = _rtP -> P_3 [ 1 ] ; _rtB -> B_1_1_0 [ 1 ] = _rtP -> P_4 [ 1 ]
; _rtB -> B_1_14_0 = _rtP -> P_8 ; _rtB -> B_46_9_0 = _rtP -> P_51 ; _rtB ->
B_46_13_0 = _rtP -> P_54 ; memcpy ( & _rtB -> B_1_15_0 [ 0 ] , & _rtP -> P_9
[ 0 ] , sizeof ( real_T ) << 4U ) ; memcpy ( & _rtB -> B_1_20_0 [ 0 ] , &
_rtP -> P_10 [ 0 ] , sizeof ( real_T ) << 4U ) ; memcpy ( & _rtB -> B_1_22_0
[ 0 ] , & _rtP -> P_11 [ 0 ] , sizeof ( real_T ) << 4U ) ; memcpy ( & _rtB ->
B_46_10_0 [ 0 ] , & _rtP -> P_52 [ 0 ] , sizeof ( real_T ) << 4U ) ; memcpy (
& _rtB -> B_10_3_0 [ 0 ] , & _rtP -> P_37 [ 0 ] , sizeof ( real_T ) << 4U ) ;
if ( ssIsMajorTimeStep ( S ) != 0 ) { srUpdateBC ( _rtDW ->
sinthrcosthr_SubsysRanBC ) ; } memcpy ( & _rtB -> B_11_3_0 [ 0 ] , & _rtP ->
P_42 [ 0 ] , sizeof ( real_T ) << 4U ) ; if ( ssIsMajorTimeStep ( S ) != 0 )
{ srUpdateBC ( _rtDW -> sinthrcosthr1_SubsysRanBC ) ; } _rtB -> B_46_33_0 =
_rtP -> P_60 ; _rtB -> B_46_37_0 = _rtP -> P_62 ; _rtB -> B_46_39_0 = _rtP ->
P_63 ; _rtB -> B_46_42_0 = _rtP -> P_65 ; _rtB -> B_46_50_0 = _rtP -> P_80 ;
_rtB -> B_46_52_0 = _rtP -> P_81 ; _rtB -> B_46_54_0 = _rtP -> P_82 ; _rtB ->
B_46_67_0 = _rtP -> P_91 ; _rtB -> B_46_72_0 = _rtP -> P_92 ; _rtB ->
B_46_73_0 = _rtP -> P_93 ; _rtB -> B_46_75_0 = _rtP -> P_94 ; _rtB ->
B_46_86_0 = _rtP -> P_98 ; _rtB -> B_46_96_0 [ 0 ] = _rtP -> P_103 [ 0 ] ;
_rtB -> B_46_117_0 [ 0 ] = _rtP -> P_113 [ 0 ] ; _rtB -> B_46_138_0 [ 0 ] =
_rtP -> P_123 [ 0 ] ; _rtB -> B_46_96_0 [ 1 ] = _rtP -> P_103 [ 1 ] ; _rtB ->
B_46_117_0 [ 1 ] = _rtP -> P_113 [ 1 ] ; _rtB -> B_46_138_0 [ 1 ] = _rtP ->
P_123 [ 1 ] ; _rtB -> B_46_107_0 = ( _rtB -> B_46_96_0 [ 1 ] - _rtB ->
B_46_96_0 [ 0 ] ) * _rtP -> P_110 ; _rtB -> B_46_128_0 = ( _rtB -> B_46_117_0
[ 1 ] - _rtB -> B_46_117_0 [ 0 ] ) * _rtP -> P_120 ; _rtB -> B_46_149_0 = (
_rtB -> B_46_138_0 [ 1 ] - _rtB -> B_46_138_0 [ 0 ] ) * _rtP -> P_130 ; _rtB
-> B_46_162_0 = _rtP -> P_131 ; _rtB -> B_46_192_0 = _rtP -> P_138 ; _rtB ->
B_46_194_0 = _rtP -> P_140 ; _rtB -> B_46_195_0 = _rtP -> P_141 ; _rtB ->
B_46_196_0 = _rtP -> P_142 ; memcpy ( & _rtB -> B_9_8_0 [ 0 ] , & _rtP ->
P_32 [ 0 ] , sizeof ( real_T ) << 4U ) ; memcpy ( & _rtB -> B_46_193_0 [ 0 ]
, & _rtP -> P_139 [ 0 ] , sizeof ( real_T ) << 4U ) ; memcpy ( & _rtB ->
B_46_198_0 [ 0 ] , & _rtP -> P_144 [ 0 ] , sizeof ( real_T ) << 4U ) ; _rtB
-> B_46_199_0 = _rtP -> P_145 ; _rtB -> B_46_200_0 [ 0 ] = _rtP -> P_146 [ 0
] ; _rtB -> B_46_200_0 [ 1 ] = _rtP -> P_146 [ 1 ] ; _rtB -> B_46_209_0 =
_rtP -> P_148 ; _rtB -> B_46_218_0 = _rtP -> P_152 * _rtB -> B_46_162_0 ;
_rtB -> B_46_238_0 = ( _rtP -> P_163 != 0.0 ) ; _rtB -> B_46_240_0 = ! _rtB
-> B_46_238_0 ; _rtB -> B_46_248_0 = ( _rtP -> P_167 != 0.0 ) ; _rtB ->
B_46_250_0 = ! _rtB -> B_46_248_0 ; _rtB -> B_46_258_0 = ( _rtP -> P_171 !=
0.0 ) ; _rtB -> B_46_260_0 = ! _rtB -> B_46_258_0 ; _rtB -> B_46_270_0 = (
_rtP -> P_175 != 0.0 ) ; _rtB -> B_46_272_0 = ! _rtB -> B_46_270_0 ; _rtB ->
B_46_280_0 = ( _rtP -> P_179 != 0.0 ) ; _rtB -> B_46_282_0 = ! _rtB ->
B_46_280_0 ; _rtB -> B_46_290_0 = ( _rtP -> P_183 != 0.0 ) ; _rtB ->
B_46_292_0 = ! _rtB -> B_46_290_0 ; _rtB -> B_46_317_0 = _rtP -> P_197 ; _rtB
-> B_46_331_0 = _rtP -> P_209 ; _rtB -> B_46_338_0 = _rtP -> P_210 ; _rtB ->
B_46_344_0 = _rtP -> P_211 ; _rtB -> B_46_349_0 = _rtP -> P_213 ; _rtB ->
B_46_351_0 = _rtP -> P_214 ; _rtB -> B_46_352_0 = _rtP -> P_215 ; _rtB ->
B_46_353_0 = _rtP -> P_216 ; _rtB -> B_46_366_0 = _rtP -> P_221 ; _rtB ->
B_46_368_0 = _rtP -> P_222 ; _rtB -> B_46_387_0 = _rtP -> P_223 ; _rtB ->
B_46_388_0 = _rtP -> P_224 ; _rtB -> B_46_389_0 = _rtP -> P_225 ;
UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) { int32_T isHit ;
B_PV_fed_VCIMD_updated_T * _rtB ; P_PV_fed_VCIMD_updated_T * _rtP ;
DW_PV_fed_VCIMD_updated_T * _rtDW ; _rtDW = ( ( DW_PV_fed_VCIMD_updated_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_PV_fed_VCIMD_updated_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_PV_fed_VCIMD_updated_T * )
_ssGetModelBlockIO ( S ) ) ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit
!= 0 ) { _rtDW -> fluxes_DSTATE [ 0 ] = _rtB -> B_46_214_0 [ 0 ] ; _rtDW ->
fluxes_DSTATE_k [ 0 ] = _rtB -> B_46_3_0 [ 0 ] ; _rtDW -> fluxes_DSTATE [ 1 ]
= _rtB -> B_46_214_0 [ 1 ] ; _rtDW -> fluxes_DSTATE_k [ 1 ] = _rtB ->
B_46_3_0 [ 1 ] ; _rtDW -> fluxes_DSTATE [ 2 ] = _rtB -> B_46_214_0 [ 2 ] ;
_rtDW -> fluxes_DSTATE_k [ 2 ] = _rtB -> B_46_3_0 [ 2 ] ; _rtDW ->
fluxes_DSTATE [ 3 ] = _rtB -> B_46_214_0 [ 3 ] ; _rtDW -> fluxes_DSTATE_k [ 3
] = _rtB -> B_46_3_0 [ 3 ] ; if ( _rtB -> B_46_7_0 > 0.0 ) { _rtDW ->
Delay_DSTATE = _rtB -> B_1_17_0 ; } _rtDW -> Rotoranglethetam_DSTATE += _rtP
-> P_55 * _rtB -> B_46_223_0 ; _rtDW -> wm_delay_DSTATE = _rtB -> B_46_222_0
; _rtDW -> wm_predict_DSTATE = _rtB -> B_46_15_0 ; _rtDW -> UnitDelay_DSTATE
= _rtB -> B_46_370_0 ; ssCallAccelRunBlock ( S , 46 , 48 , SS_CALL_MDL_UPDATE
) ; _rtDW -> UnitDelay1_DSTATE [ 0 ] = _rtB -> B_46_217_0 [ 9 ] ; _rtDW ->
UnitDelay1_DSTATE [ 1 ] = _rtB -> B_46_217_0 [ 10 ] ; _rtDW ->
UnitDelay1_DSTATE [ 2 ] = _rtB -> B_46_217_0 [ 11 ] ; } isHit = ssIsSampleHit
( S , 4 , 0 ) ; if ( isHit != 0 ) { _rtDW -> UnitDelay_DSTATE_a = _rtB ->
B_46_316_0 ; _rtDW -> UnitDelay1_DSTATE_k = _rtB -> B_46_58_0 ; _rtDW ->
UnitDelay_DSTATE_j = _rtB -> B_46_66_0 ; _rtDW -> UnitDelay_DSTATE_i = _rtB
-> B_46_83_0 ; _rtDW -> UnitDelay3_DSTATE = _rtB -> B_15_0_1 ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> voltages_DSTATE [
0 ] = _rtB -> B_46_208_0 [ 0 ] ; _rtDW -> voltages_DSTATE [ 2 ] = _rtB ->
B_46_210_0 [ 0 ] ; _rtDW -> voltages_DSTATE [ 1 ] = _rtB -> B_46_208_0 [ 1 ]
; _rtDW -> voltages_DSTATE [ 3 ] = _rtB -> B_46_210_0 [ 1 ] ; _rtDW ->
Rotorspeedwm_SYSTEM_ENABLE = 0U ; _rtDW -> Rotorspeedwm_DSTATE = _rtP ->
P_155 * _rtB -> B_46_221_0 + _rtB -> B_46_222_0 ; }
PV_fed_VCIMD_updated_TrueRMS_Update ( S , & _rtB -> TrueRMS , & _rtDW ->
TrueRMS , & _rtP -> TrueRMS ) ; PV_fed_VCIMD_updated_RMS_Update ( S , & _rtB
-> RMS , & _rtDW -> RMS , & _rtP -> RMS ) ;
PV_fed_VCIMD_updated_TrueRMS_Update ( S , & _rtB -> TrueRMS_f , & _rtDW ->
TrueRMS_f , & _rtP -> TrueRMS_f ) ; PV_fed_VCIMD_updated_RMS_Update ( S , &
_rtB -> RMS_f , & _rtDW -> RMS_f , & _rtP -> RMS_f ) ;
PV_fed_VCIMD_updated_TrueRMS_Update ( S , & _rtB -> TrueRMS_h , & _rtDW ->
TrueRMS_h , & _rtP -> TrueRMS_h ) ; PV_fed_VCIMD_updated_RMS_Update ( S , &
_rtB -> RMS_fg , & _rtDW -> RMS_fg , & _rtP -> RMS_fg ) ;
PV_fed_VCIMD_updated_TrueRMS_Update ( S , & _rtB -> TrueRMS_p , & _rtDW ->
TrueRMS_p , & _rtP -> TrueRMS_p ) ; PV_fed_VCIMD_updated_RMS_Update ( S , &
_rtB -> RMS_e , & _rtDW -> RMS_e , & _rtP -> RMS_e ) ;
PV_fed_VCIMD_updated_TrueRMS_Update ( S , & _rtB -> TrueRMS_k , & _rtDW ->
TrueRMS_k , & _rtP -> TrueRMS_k ) ; PV_fed_VCIMD_updated_RMS_Update ( S , &
_rtB -> RMS_h , & _rtDW -> RMS_h , & _rtP -> RMS_h ) ;
PV_fed_VCIMD_updated_TrueRMS_Update ( S , & _rtB -> TrueRMS_fi , & _rtDW ->
TrueRMS_fi , & _rtP -> TrueRMS_fi ) ; PV_fed_VCIMD_updated_RMS_Update ( S , &
_rtB -> RMS_k , & _rtDW -> RMS_k , & _rtP -> RMS_k ) ; UNUSED_PARAMETER ( tid
) ; }
#define MDL_UPDATE
static void mdlUpdateTID5 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { B_PV_fed_VCIMD_updated_T *
_rtB ; P_PV_fed_VCIMD_updated_T * _rtP ; X_PV_fed_VCIMD_updated_T * _rtX ;
XDot_PV_fed_VCIMD_updated_T * _rtXdot ; DW_PV_fed_VCIMD_updated_T * _rtDW ;
_rtDW = ( ( DW_PV_fed_VCIMD_updated_T * ) ssGetRootDWork ( S ) ) ; _rtXdot =
( ( XDot_PV_fed_VCIMD_updated_T * ) ssGetdX ( S ) ) ; _rtX = ( (
X_PV_fed_VCIMD_updated_T * ) ssGetContStates ( S ) ) ; _rtP = ( (
P_PV_fed_VCIMD_updated_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_PV_fed_VCIMD_updated_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
Integrator_CSTATE = _rtB -> B_46_231_0 ; _rtXdot -> Integrator_CSTATE_m =
_rtB -> B_46_299_0 ; PV_fed_VCIMD_updated_TrueRMS_Deriv ( S , & _rtB ->
TrueRMS , & _rtDW -> TrueRMS , & _rtXdot -> TrueRMS ) ;
PV_fed_VCIMD_updated_RMS_Deriv ( S , & _rtB -> RMS , & _rtDW -> RMS , &
_rtXdot -> RMS ) ; _rtXdot -> Integrator_CSTATE_n = _rtB -> B_46_302_0 ;
PV_fed_VCIMD_updated_TrueRMS_Deriv ( S , & _rtB -> TrueRMS_f , & _rtDW ->
TrueRMS_f , & _rtXdot -> TrueRMS_f ) ; PV_fed_VCIMD_updated_RMS_Deriv ( S , &
_rtB -> RMS_f , & _rtDW -> RMS_f , & _rtXdot -> RMS_f ) ; _rtXdot ->
Integrator_CSTATE_i = _rtB -> B_46_305_0 ; PV_fed_VCIMD_updated_TrueRMS_Deriv
( S , & _rtB -> TrueRMS_h , & _rtDW -> TrueRMS_h , & _rtXdot -> TrueRMS_h ) ;
PV_fed_VCIMD_updated_RMS_Deriv ( S , & _rtB -> RMS_fg , & _rtDW -> RMS_fg , &
_rtXdot -> RMS_fg ) ; _rtXdot -> Integrator_CSTATE_o = _rtB -> B_46_308_0 ;
PV_fed_VCIMD_updated_TrueRMS_Deriv ( S , & _rtB -> TrueRMS_p , & _rtDW ->
TrueRMS_p , & _rtXdot -> TrueRMS_p ) ; PV_fed_VCIMD_updated_RMS_Deriv ( S , &
_rtB -> RMS_e , & _rtDW -> RMS_e , & _rtXdot -> RMS_e ) ; _rtXdot ->
Integrator_CSTATE_d = _rtB -> B_46_311_0 ; PV_fed_VCIMD_updated_TrueRMS_Deriv
( S , & _rtB -> TrueRMS_k , & _rtDW -> TrueRMS_k , & _rtXdot -> TrueRMS_k ) ;
PV_fed_VCIMD_updated_RMS_Deriv ( S , & _rtB -> RMS_h , & _rtDW -> RMS_h , &
_rtXdot -> RMS_h ) ; _rtXdot -> Integrator_CSTATE_a = _rtB -> B_46_314_0 ;
PV_fed_VCIMD_updated_TrueRMS_Deriv ( S , & _rtB -> TrueRMS_fi , & _rtDW ->
TrueRMS_fi , & _rtXdot -> TrueRMS_fi ) ; PV_fed_VCIMD_updated_RMS_Deriv ( S ,
& _rtB -> RMS_k , & _rtDW -> RMS_k , & _rtXdot -> RMS_k ) ; _rtXdot ->
TransferFcn_CSTATE = 0.0 ; _rtXdot -> TransferFcn_CSTATE += _rtP -> P_202 *
_rtX -> TransferFcn_CSTATE ; _rtXdot -> TransferFcn_CSTATE += _rtB ->
B_46_323_0 ; } static void mdlInitializeSizes ( SimStruct * S ) {
ssSetChecksumVal ( S , 0 , 2978093380U ) ; ssSetChecksumVal ( S , 1 ,
920741576U ) ; ssSetChecksumVal ( S , 2 , 3928500146U ) ; ssSetChecksumVal (
S , 3 , 3502847126U ) ; { mxArray * slVerStructMat = NULL ; mxArray *
slStrMat = mxCreateString ( "simulink" ) ; char slVerChar [ 10 ] ; int status
= mexCallMATLAB ( 1 , & slVerStructMat , 1 , & slStrMat , "ver" ) ; if (
status == 0 ) { mxArray * slVerMat = mxGetField ( slVerStructMat , 0 ,
"Version" ) ; if ( slVerMat == NULL ) { status = 1 ; } else { status =
mxGetString ( slVerMat , slVerChar , 10 ) ; } } mxDestroyArray ( slStrMat ) ;
mxDestroyArray ( slVerStructMat ) ; if ( ( status == 1 ) || ( strcmp (
slVerChar , "9.3" ) != 0 ) ) { return ; } } ssSetOptions ( S ,
SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork ( S ) != sizeof (
DW_PV_fed_VCIMD_updated_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file." ) ; } if ( ssGetSizeofGlobalBlockIO ( S
) != sizeof ( B_PV_fed_VCIMD_updated_T ) ) { ssSetErrorStatus ( S ,
"Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file." ) ; } { int ssSizeofParams ;
ssGetSizeofParams ( S , & ssSizeofParams ) ; if ( ssSizeofParams != sizeof (
P_PV_fed_VCIMD_updated_T ) ) { static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file." ) ; } } _ssSetModelRtp ( S , ( real_T *
) & PV_fed_VCIMD_updated_rtDefaultP ) ; _ssSetConstBlockIO ( S , &
PV_fed_VCIMD_updated_rtInvariant ) ; rt_InitInfAndNaN ( sizeof ( real_T ) ) ;
( ( P_PV_fed_VCIMD_updated_T * ) ssGetModelRtp ( S ) ) -> TrueRMS_fi . P_7 =
rtInf ; ( ( P_PV_fed_VCIMD_updated_T * ) ssGetModelRtp ( S ) ) -> TrueRMS_k .
P_7 = rtInf ; ( ( P_PV_fed_VCIMD_updated_T * ) ssGetModelRtp ( S ) ) ->
TrueRMS_p . P_7 = rtInf ; ( ( P_PV_fed_VCIMD_updated_T * ) ssGetModelRtp ( S
) ) -> TrueRMS_h . P_7 = rtInf ; ( ( P_PV_fed_VCIMD_updated_T * )
ssGetModelRtp ( S ) ) -> TrueRMS_f . P_7 = rtInf ; ( (
P_PV_fed_VCIMD_updated_T * ) ssGetModelRtp ( S ) ) -> TrueRMS . P_7 = rtInf ;
} static void mdlInitializeSampleTimes ( SimStruct * S ) { { SimStruct *
childS ; SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S , 0 ) ;
callSysFcns = ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ]
= ( SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 1 ) ; callSysFcns
= ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 2 ) ; callSysFcns =
ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; } slAccRegPrmChangeFcn ( S , mdlOutputsTID5 ) ; }
static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
