#ifndef __c2_landingSimulation_h__
#define __c2_landingSimulation_h__

/* Include files */
#include "sf_runtime/sfc_sf.h"
#include "sf_runtime/sfc_mex.h"
#include "rtwtypes.h"
#include "multiword_types.h"

/* Type Definitions */
#ifndef typedef_SFc2_landingSimulationInstanceStruct
#define typedef_SFc2_landingSimulationInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  uint32_T chartNumber;
  uint32_T instanceNumber;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_landingSimulation;
  real_T *c2_rocketPower;
  real_T *c2_thrustSetting;
  real_T *c2_bruttoWeight;
  real_T *c2_acceleration;
  real_T *c2_tankLevel;
  real_T *c2_tankVolume;
  real_T *c2_speed;
  real_T *c2_rocketDiameter;
} SFc2_landingSimulationInstanceStruct;

#endif                                 /*typedef_SFc2_landingSimulationInstanceStruct*/

/* Named Constants */

/* Variable Declarations */
extern struct SfDebugInstanceStruct *sfGlobalDebugInstanceStruct;

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_landingSimulation_get_eml_resolved_functions_info
  (void);

/* Function Definitions */
extern void sf_c2_landingSimulation_get_check_sum(mxArray *plhs[]);
extern void c2_landingSimulation_method_dispatcher(SimStruct *S, int_T method,
  void *data);

#endif
