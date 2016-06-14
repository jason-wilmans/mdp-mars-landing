/* Include files */

#include "Landing_sfun.h"
#include "c2_Landing.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "Landing_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c_with_debugger(S, sfGlobalDebugInstanceStruct);

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization);
static void chart_debug_initialize_data_addresses(SimStruct *S);
static const mxArray* sf_opaque_get_hover_data_for_msg(void *chartInstance,
  int32_T msgSSID);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c2_debug_family_names[16] = { "mass", "thrust", "gravity",
  "airDrag", "nargin", "nargout", "rocketPower", "thrustSetting", "bruttoWeight",
  "tankLevel", "tankVolume", "rocketDiameter", "height", "speed", "acceleration",
  "density" };

static const char * c2_b_debug_family_names[6] = { "nargin", "nargout",
  "bruttoWeight", "tankLevel", "tankVolume", "mass" };

static const char * c2_c_debug_family_names[6] = { "nargin", "nargout",
  "throttle", "rocketPower", "mass", "thrust" };

static const char * c2_d_debug_family_names[4] = { "acceleration", "marsGravity",
  "nargin", "nargout" };

static const char * c2_e_debug_family_names[11] = { "groundTemperature",
  "gasConstant", "groundPressure", "temperatureGradient", "temperature", "a",
  "hPa", "nargin", "nargout", "height", "density" };

static const char * c2_f_debug_family_names[10] = { "area", "cw",
  "rocketDiameter", "nargin", "nargout", "speed", "mass", "height", "airDrag",
  "density" };

/* Function Declarations */
static void initialize_c2_Landing(SFc2_LandingInstanceStruct *chartInstance);
static void initialize_params_c2_Landing(SFc2_LandingInstanceStruct
  *chartInstance);
static void enable_c2_Landing(SFc2_LandingInstanceStruct *chartInstance);
static void disable_c2_Landing(SFc2_LandingInstanceStruct *chartInstance);
static void c2_update_debugger_state_c2_Landing(SFc2_LandingInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_Landing(SFc2_LandingInstanceStruct
  *chartInstance);
static void set_sim_state_c2_Landing(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void finalize_c2_Landing(SFc2_LandingInstanceStruct *chartInstance);
static void sf_gateway_c2_Landing(SFc2_LandingInstanceStruct *chartInstance);
static void mdl_start_c2_Landing(SFc2_LandingInstanceStruct *chartInstance);
static void c2_chartstep_c2_Landing(SFc2_LandingInstanceStruct *chartInstance);
static void initSimStructsc2_Landing(SFc2_LandingInstanceStruct *chartInstance);
static real_T c2_Density(SFc2_LandingInstanceStruct *chartInstance, real_T
  c2_b_height);
static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber);
static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData);
static real_T c2_emlrt_marshallIn(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_b_density, const char_T *c2_identifier);
static real_T c2_b_emlrt_marshallIn(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static void c2_scalarEg(SFc2_LandingInstanceStruct *chartInstance);
static void c2_dimagree(SFc2_LandingInstanceStruct *chartInstance);
static void c2_error(SFc2_LandingInstanceStruct *chartInstance);
static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData);
static int32_T c2_c_emlrt_marshallIn(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData);
static uint8_T c2_d_emlrt_marshallIn(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_Landing, const char_T *c2_identifier);
static uint8_T c2_e_emlrt_marshallIn(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void init_dsm_address_info(SFc2_LandingInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_LandingInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_Landing(SFc2_LandingInstanceStruct *chartInstance)
{
  if (sf_is_first_init_cond(chartInstance->S)) {
    initSimStructsc2_Landing(chartInstance);
    chart_debug_initialize_data_addresses(chartInstance->S);
  }

  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_Landing = 0U;
}

static void initialize_params_c2_Landing(SFc2_LandingInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void enable_c2_Landing(SFc2_LandingInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_Landing(SFc2_LandingInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c2_update_debugger_state_c2_Landing(SFc2_LandingInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c2_Landing(SFc2_LandingInstanceStruct
  *chartInstance)
{
  const mxArray *c2_st;
  const mxArray *c2_y = NULL;
  real_T c2_hoistedGlobal;
  real_T c2_u;
  const mxArray *c2_b_y = NULL;
  real_T c2_b_hoistedGlobal;
  real_T c2_b_u;
  const mxArray *c2_c_y = NULL;
  uint8_T c2_c_hoistedGlobal;
  uint8_T c2_c_u;
  const mxArray *c2_d_y = NULL;
  c2_st = NULL;
  c2_st = NULL;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_createcellmatrix(3, 1), false);
  c2_hoistedGlobal = *chartInstance->c2_acceleration;
  c2_u = c2_hoistedGlobal;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 0, c2_b_y);
  c2_b_hoistedGlobal = *chartInstance->c2_density;
  c2_b_u = c2_b_hoistedGlobal;
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", &c2_b_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 1, c2_c_y);
  c2_c_hoistedGlobal = chartInstance->c2_is_active_c2_Landing;
  c2_c_u = c2_c_hoistedGlobal;
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y", &c2_c_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_y, 2, c2_d_y);
  sf_mex_assign(&c2_st, c2_y, false);
  return c2_st;
}

static void set_sim_state_c2_Landing(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  *chartInstance->c2_acceleration = c2_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("acceleration", c2_u, 0)), "acceleration");
  *chartInstance->c2_density = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell("density", c2_u, 1)), "density");
  chartInstance->c2_is_active_c2_Landing = c2_d_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell("is_active_c2_Landing", c2_u, 2)),
    "is_active_c2_Landing");
  sf_mex_destroy(&c2_u);
  c2_update_debugger_state_c2_Landing(chartInstance);
  sf_mex_destroy(&c2_st);
}

static void finalize_c2_Landing(SFc2_LandingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c2_Landing(SFc2_LandingInstanceStruct *chartInstance)
{
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_speed, 7U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_height, 6U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_rocketDiameter, 5U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_tankVolume, 4U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_tankLevel, 3U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_bruttoWeight, 2U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_thrustSetting, 1U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_rocketPower, 0U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_chartstep_c2_Landing(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_LandingMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_acceleration, 8U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
  _SFD_DATA_RANGE_CHECK(*chartInstance->c2_density, 9U, 1U, 0U,
                        chartInstance->c2_sfEvent, false);
}

static void mdl_start_c2_Landing(SFc2_LandingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_chartstep_c2_Landing(SFc2_LandingInstanceStruct *chartInstance)
{
  real_T c2_hoistedGlobal;
  real_T c2_b_hoistedGlobal;
  real_T c2_c_hoistedGlobal;
  real_T c2_d_hoistedGlobal;
  real_T c2_e_hoistedGlobal;
  real_T c2_f_hoistedGlobal;
  real_T c2_g_hoistedGlobal;
  real_T c2_h_hoistedGlobal;
  real_T c2_b_rocketPower;
  real_T c2_b_thrustSetting;
  real_T c2_b_bruttoWeight;
  real_T c2_b_tankLevel;
  real_T c2_b_tankVolume;
  real_T c2_b_rocketDiameter;
  real_T c2_b_height;
  real_T c2_b_speed;
  uint32_T c2_debug_family_var_map[16];
  real_T c2_mass;
  real_T c2_thrust;
  real_T c2_gravity;
  real_T c2_airDrag;
  real_T c2_nargin = 8.0;
  real_T c2_nargout = 2.0;
  real_T c2_b_acceleration;
  real_T c2_b_density;
  real_T c2_c_bruttoWeight;
  real_T c2_c_tankLevel;
  real_T c2_c_tankVolume;
  uint32_T c2_b_debug_family_var_map[6];
  real_T c2_b_nargin = 3.0;
  real_T c2_b_nargout = 1.0;
  real_T c2_throttle;
  real_T c2_c_rocketPower;
  real_T c2_b_mass;
  real_T c2_c_nargin = 3.0;
  real_T c2_c_nargout = 1.0;
  real_T c2_A;
  real_T c2_B;
  real_T c2_x;
  real_T c2_y;
  real_T c2_b_x;
  real_T c2_b_y;
  uint32_T c2_c_debug_family_var_map[4];
  real_T c2_c_acceleration;
  real_T c2_marsGravity;
  real_T c2_d_nargin = 0.0;
  real_T c2_d_nargout = 1.0;
  real_T c2_c_speed;
  real_T c2_c_mass;
  real_T c2_c_height;
  uint32_T c2_d_debug_family_var_map[10];
  real_T c2_area;
  real_T c2_cw;
  real_T c2_c_rocketDiameter;
  real_T c2_e_nargin = 4.0;
  real_T c2_e_nargout = 2.0;
  real_T c2_b_airDrag;
  real_T c2_c_density;
  real_T c2_b_A;
  real_T c2_c_A;
  real_T c2_b_B;
  real_T c2_c_B;
  real_T c2_c_x;
  real_T c2_d_x;
  real_T c2_c_y;
  real_T c2_d_y;
  real_T c2_e_x;
  real_T c2_f_x;
  real_T c2_e_y;
  real_T c2_f_y;
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
  c2_hoistedGlobal = *chartInstance->c2_rocketPower;
  c2_b_hoistedGlobal = *chartInstance->c2_thrustSetting;
  c2_c_hoistedGlobal = *chartInstance->c2_bruttoWeight;
  c2_d_hoistedGlobal = *chartInstance->c2_tankLevel;
  c2_e_hoistedGlobal = *chartInstance->c2_tankVolume;
  c2_f_hoistedGlobal = *chartInstance->c2_rocketDiameter;
  c2_g_hoistedGlobal = *chartInstance->c2_height;
  c2_h_hoistedGlobal = *chartInstance->c2_speed;
  c2_b_rocketPower = c2_hoistedGlobal;
  c2_b_thrustSetting = c2_b_hoistedGlobal;
  c2_b_bruttoWeight = c2_c_hoistedGlobal;
  c2_b_tankLevel = c2_d_hoistedGlobal;
  c2_b_tankVolume = c2_e_hoistedGlobal;
  c2_b_rocketDiameter = c2_f_hoistedGlobal;
  c2_b_height = c2_g_hoistedGlobal;
  c2_b_speed = c2_h_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 16U, 16U, c2_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_mass, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_thrust, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_gravity, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_airDrag, 3U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 4U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 5U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_rocketPower, 6U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_thrustSetting, 7U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_bruttoWeight, 8U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_tankLevel, 9U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_tankVolume, 10U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_rocketDiameter, 11U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_height, 12U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_b_speed, 13U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_acceleration, 14U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_density, 15U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 2);
  c2_c_bruttoWeight = c2_b_bruttoWeight;
  c2_c_tankLevel = c2_b_tankLevel;
  c2_c_tankVolume = c2_b_tankVolume;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c2_b_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargin, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_nargout, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_bruttoWeight, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_tankLevel, 3U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_tankVolume, 4U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_mass, 5U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_SCRIPT_FCN(0, 0);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_mass = 1000.0 * (c2_c_bruttoWeight + c2_c_tankLevel * c2_c_tankVolume);
  _SFD_SCRIPT_CALL(0U, chartInstance->c2_sfEvent, -6);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 4);
  c2_throttle = c2_b_thrustSetting;
  c2_c_rocketPower = c2_b_rocketPower;
  c2_b_mass = c2_mass;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 6U, 6U, c2_c_debug_family_names,
    c2_b_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargin, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_nargout, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_throttle, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_rocketPower, 3U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_mass, 4U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_thrust, 5U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_SCRIPT_FCN(1, 0);
  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, 3);
  c2_A = c2_throttle * c2_c_rocketPower * 1000.0;
  c2_B = c2_b_mass;
  c2_x = c2_A;
  c2_y = c2_B;
  c2_b_x = c2_x;
  c2_b_y = c2_y;
  c2_thrust = c2_b_x / c2_b_y;
  _SFD_SCRIPT_CALL(1U, chartInstance->c2_sfEvent, -3);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 5);
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 4U, 4U, c2_d_debug_family_names,
    c2_c_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_acceleration, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_marsGravity, 1U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_d_nargin, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_d_nargout, 3U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_SCRIPT_FCN(2, 0);
  _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 6);
  c2_marsGravity = 3.69;
  _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, 8);
  c2_c_acceleration = 3.69;
  _SFD_SCRIPT_CALL(2U, chartInstance->c2_sfEvent, -8);
  _SFD_SYMBOL_SCOPE_POP();
  c2_gravity = 3.69;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 6);
  c2_c_speed = c2_b_speed;
  c2_c_mass = c2_mass;
  c2_c_height = c2_b_height;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 10U, 10U, c2_f_debug_family_names,
    c2_d_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_area, 0U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_cw, 1U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_c_rocketDiameter, 2U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_e_nargin, 3U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_e_nargout, 4U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_speed, 5U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_mass, 6U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_height, 7U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_airDrag, 8U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_c_density, 9U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_SCRIPT_FCN(3, 0);
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 2);
  c2_c_density = c2_Density(chartInstance, c2_c_height);
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 4);
  c2_c_rocketDiameter = 33.528;
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 5);
  c2_area = 882.9875372472;
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 7);
  if (CV_SCRIPT_IF(3, 0, CV_RELATIONAL_EVAL(14U, 3U, 0, c2_c_speed, 0.0, -1, 5U,
        c2_c_speed >= 0.0))) {
    _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 8);
    c2_cw = 0.1;
    _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 9);
    c2_c_A = -(0.5 * c2_cw * c2_area * c2_c_density * c2_c_speed * c2_c_speed);
    c2_c_B = c2_c_mass;
    c2_d_x = c2_c_A;
    c2_d_y = c2_c_B;
    c2_f_x = c2_d_x;
    c2_f_y = c2_d_y;
    c2_b_airDrag = c2_f_x / c2_f_y;
  } else {
    _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 11);
    c2_cw = 1.33;
    _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 12);
    c2_b_A = 0.5 * c2_cw * c2_area * c2_c_density * c2_c_speed * c2_c_speed;
    c2_b_B = c2_c_mass;
    c2_c_x = c2_b_A;
    c2_c_y = c2_b_B;
    c2_e_x = c2_c_x;
    c2_e_y = c2_c_y;
    c2_b_airDrag = c2_e_x / c2_e_y;
  }

  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, -12);
  _SFD_SYMBOL_SCOPE_POP();
  c2_airDrag = c2_b_airDrag;
  c2_b_density = c2_c_density;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, 8);
  c2_b_acceleration = (c2_thrust - c2_gravity) + c2_airDrag;
  _SFD_EML_CALL(0U, chartInstance->c2_sfEvent, -8);
  _SFD_SYMBOL_SCOPE_POP();
  *chartInstance->c2_acceleration = c2_b_acceleration;
  *chartInstance->c2_density = c2_b_density;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c2_sfEvent);
}

static void initSimStructsc2_Landing(SFc2_LandingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static real_T c2_Density(SFc2_LandingInstanceStruct *chartInstance, real_T
  c2_b_height)
{
  real_T c2_b_density;
  uint32_T c2_debug_family_var_map[11];
  real_T c2_groundTemperature;
  real_T c2_gasConstant;
  real_T c2_groundPressure;
  real_T c2_temperatureGradient;
  real_T c2_temperature;
  real_T c2_a;
  real_T c2_hPa;
  real_T c2_nargin = 1.0;
  real_T c2_nargout = 1.0;
  real_T c2_A;
  real_T c2_x;
  real_T c2_b_x;
  real_T c2_y;
  real_T c2_b_a;
  real_T c2_c_a;
  real_T c2_c_x;
  real_T c2_d_a;
  real_T c2_ar;
  real_T c2_e_a;
  boolean_T c2_p;
  real_T c2_b_A;
  real_T c2_d_x;
  real_T c2_e_x;
  real_T c2_b_y;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 11U, 11U, c2_e_debug_family_names,
    c2_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_groundTemperature, 0U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c2_gasConstant, 1U, c2_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_groundPressure, 2U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_temperatureGradient, 3U,
    c2_sf_marshallOut, c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_temperature, 4U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_a, 5U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_hPa, 6U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargin, 7U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_nargout, 8U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_height, 9U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c2_b_density, 10U, c2_sf_marshallOut,
    c2_sf_marshallIn);
  CV_SCRIPT_FCN(3, 2);
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 32);
  c2_groundTemperature = 218.0;
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 34);
  c2_gasConstant = 191.5204402;
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 36);
  c2_groundPressure = 6.36;
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 37);
  c2_temperatureGradient = 0.0043;
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 39);
  c2_temperature = c2_temperatureGradient * c2_b_height;
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 40);
  c2_A = c2_temperature;
  c2_x = c2_A;
  c2_b_x = c2_x;
  c2_y = c2_b_x / 218.0;
  c2_a = 1.0 - c2_y;
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 41);
  c2_b_a = c2_a;
  c2_c_a = c2_b_a;
  c2_c_x = c2_c_a;
  c2_d_a = c2_c_x;
  c2_ar = c2_d_a;
  c2_a = muDoubleScalarPower(c2_ar, 5.255);
  c2_e_a = c2_c_a;
  c2_p = false;
  if (c2_e_a < 0.0) {
    c2_p = true;
  }

  if (c2_p) {
    c2_error(chartInstance);
  }

  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 42);
  c2_hPa = c2_groundPressure * c2_a;
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, 43);
  c2_b_A = c2_hPa;
  c2_d_x = c2_b_A;
  c2_e_x = c2_d_x;
  c2_b_y = c2_e_x / 41751.4559636;
  c2_b_density = c2_b_y * 100.0;
  _SFD_SCRIPT_CALL(3U, chartInstance->c2_sfEvent, -43);
  _SFD_SYMBOL_SCOPE_POP();
  return c2_b_density;
}

static void init_script_number_translation(uint32_T c2_machineNumber, uint32_T
  c2_chartNumber, uint32_T c2_instanceNumber)
{
  (void)c2_machineNumber;
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, c2_instanceNumber, 0U,
    sf_debug_get_script_id(
    "C:\\Users\\jason\\Documents\\Work\\Uni\\mdp\\experiment\\Mass.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, c2_instanceNumber, 1U,
    sf_debug_get_script_id(
    "C:\\Users\\jason\\Documents\\Work\\Uni\\mdp\\experiment\\Thrust.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, c2_instanceNumber, 2U,
    sf_debug_get_script_id(
    "C:\\Users\\jason\\Documents\\Work\\Uni\\mdp\\experiment\\Gravity.m"));
  _SFD_SCRIPT_TRANSLATION(c2_chartNumber, c2_instanceNumber, 3U,
    sf_debug_get_script_id(
    "C:\\Users\\jason\\Documents\\Work\\Uni\\mdp\\experiment\\AirDrag.m"));
}

static const mxArray *c2_sf_marshallOut(void *chartInstanceVoid, void *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  real_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_LandingInstanceStruct *chartInstance;
  chartInstance = (SFc2_LandingInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(real_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static real_T c2_emlrt_marshallIn(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_b_density, const char_T *c2_identifier)
{
  real_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_density),
    &c2_thisId);
  sf_mex_destroy(&c2_b_density);
  return c2_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_y;
  real_T c2_d0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d0, 1, 0, 0U, 0, 0U, 0);
  c2_y = c2_d0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_density;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  real_T c2_y;
  SFc2_LandingInstanceStruct *chartInstance;
  chartInstance = (SFc2_LandingInstanceStruct *)chartInstanceVoid;
  c2_b_density = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_density),
    &c2_thisId);
  sf_mex_destroy(&c2_b_density);
  *(real_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

const mxArray *sf_c2_Landing_get_eml_resolved_functions_info(void)
{
  const mxArray *c2_nameCaptureInfo = NULL;
  const char * c2_data[4] = {
    "789ced94df4ac33014c653a9d5098e3d8657c64b197a319cffc0dd757831bca85b74d126a94937b65bc15b9fa90fa1f81a3e82c9d26e210caae9502f762084af"
    "275fcf39e98f02efb20364d4e5fadc012090fbb65c1b40c766ae3db9fc7cd7cf7db09beb67b9fa8ca66892ea248d0802450c18c134a269384d10e048b0788c06",
    "b3cc1d8e518809ba6286b8c05290332335172ac58762fe66109b42879ae3002ce6f0ad398a28e6687cd367cfdf90aa1309a17c8725bec0aa17cc6e65741b235d"
    "3729f1372dbfd2bdd39b9326ec0ac4057c8804a3b0cdfa2382682ae035e38fb04b31248304a24982385609a8fadd278b79cdbe8325753da36e6d7e7f59ede9ed",
    "bde5eeaf5a7f75fe3dc3ef2df103637739efcaa10b4fe1908f44eaeeff098f47965f69171e75cf9ac80a3cbeac79fc5b1eb72c9fd2e73c1ae3745aa96e1987c7"
    "964f69170ef35e672056f88ebdfac79ac3ffc6610bf3368fee7fe5bfb82a1ef39e2bf298bd666b1e4bcf7f019ba6ad79",
    "" };

  c2_nameCaptureInfo = NULL;
  emlrtNameCaptureMxArrayR2016a(c2_data, 2816U, &c2_nameCaptureInfo);
  return c2_nameCaptureInfo;
}

static void c2_scalarEg(SFc2_LandingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_dimagree(SFc2_LandingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c2_error(SFc2_LandingInstanceStruct *chartInstance)
{
  const mxArray *c2_y = NULL;
  static char_T c2_u[31] = { 'C', 'o', 'd', 'e', 'r', ':', 't', 'o', 'o', 'l',
    'b', 'o', 'x', ':', 'p', 'o', 'w', 'e', 'r', '_', 'd', 'o', 'm', 'a', 'i',
    'n', 'E', 'r', 'r', 'o', 'r' };

  (void)chartInstance;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", c2_u, 10, 0U, 1U, 0U, 2, 1, 31), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "error", 0U, 1U, 14,
                    sf_mex_call_debug(sfGlobalDebugInstanceStruct, "message", 1U,
    1U, 14, c2_y));
}

static const mxArray *c2_b_sf_marshallOut(void *chartInstanceVoid, void
  *c2_inData)
{
  const mxArray *c2_mxArrayOutData = NULL;
  int32_T c2_u;
  const mxArray *c2_y = NULL;
  SFc2_LandingInstanceStruct *chartInstance;
  chartInstance = (SFc2_LandingInstanceStruct *)chartInstanceVoid;
  c2_mxArrayOutData = NULL;
  c2_u = *(int32_T *)c2_inData;
  c2_y = NULL;
  sf_mex_assign(&c2_y, sf_mex_create("y", &c2_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c2_mxArrayOutData, c2_y, false);
  return c2_mxArrayOutData;
}

static int32_T c2_c_emlrt_marshallIn(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  int32_T c2_y;
  int32_T c2_i0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_i0, 1, 6, 0U, 0, 0U, 0);
  c2_y = c2_i0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void c2_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c2_mxArrayInData, const char_T *c2_varName, void *c2_outData)
{
  const mxArray *c2_b_sfEvent;
  const char_T *c2_identifier;
  emlrtMsgIdentifier c2_thisId;
  int32_T c2_y;
  SFc2_LandingInstanceStruct *chartInstance;
  chartInstance = (SFc2_LandingInstanceStruct *)chartInstanceVoid;
  c2_b_sfEvent = sf_mex_dup(c2_mxArrayInData);
  c2_identifier = c2_varName;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_sfEvent),
    &c2_thisId);
  sf_mex_destroy(&c2_b_sfEvent);
  *(int32_T *)c2_outData = c2_y;
  sf_mex_destroy(&c2_mxArrayInData);
}

static uint8_T c2_d_emlrt_marshallIn(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_Landing, const char_T *c2_identifier)
{
  uint8_T c2_y;
  emlrtMsgIdentifier c2_thisId;
  c2_thisId.fIdentifier = c2_identifier;
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_y = c2_e_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_Landing), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_Landing);
  return c2_y;
}

static uint8_T c2_e_emlrt_marshallIn(SFc2_LandingInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_y;
  uint8_T c2_u0;
  (void)chartInstance;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_u0, 1, 3, 0U, 0, 0U, 0);
  c2_y = c2_u0;
  sf_mex_destroy(&c2_u);
  return c2_y;
}

static void init_dsm_address_info(SFc2_LandingInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc2_LandingInstanceStruct *chartInstance)
{
  chartInstance->c2_rocketPower = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c2_thrustSetting = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_bruttoWeight = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c2_tankLevel = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 3);
  chartInstance->c2_tankVolume = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 4);
  chartInstance->c2_rocketDiameter = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 5);
  chartInstance->c2_height = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 6);
  chartInstance->c2_acceleration = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c2_speed = (real_T *)ssGetInputPortSignal_wrapper
    (chartInstance->S, 7);
  chartInstance->c2_density = (real_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c2_Landing_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(189531444U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(967069745U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1007661329U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(156187207U);
}

mxArray* sf_c2_Landing_get_post_codegen_info(void);
mxArray *sf_c2_Landing_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals", "postCodegenInfo" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1, 1, sizeof
    (autoinheritanceFields)/sizeof(autoinheritanceFields[0]),
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("XNOur7MbOMi6lc4r9GSi4C");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,8,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,0,mxREAL);
      double *pr = mxGetPr(mxSize);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt", "isFixedPointType" };

      mxArray *mxType = mxCreateStructMatrix(1,1,sizeof(typeFields)/sizeof
        (typeFields[0]),typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxType,0,"isFixedPointType",mxCreateDoubleScalar(0));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  {
    mxArray* mxPostCodegenInfo = sf_c2_Landing_get_post_codegen_info();
    mxSetField(mxAutoinheritanceInfo,0,"postCodegenInfo",mxPostCodegenInfo);
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c2_Landing_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_Landing_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("pre");
  mxArray *fallbackReason = mxCreateString("hasBreakpoints");
  mxArray *hiddenFallbackType = mxCreateString("none");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_Landing_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

mxArray* sf_c2_Landing_get_post_codegen_info(void)
{
  const char* fieldNames[] = { "exportedFunctionsUsedByThisChart",
    "exportedFunctionsChecksum" };

  mwSize dims[2] = { 1, 1 };

  mxArray* mxPostCodegenInfo = mxCreateStructArray(2, dims, sizeof(fieldNames)/
    sizeof(fieldNames[0]), fieldNames);

  {
    mxArray* mxExportedFunctionsChecksum = mxCreateString("");
    mwSize exp_dims[2] = { 0, 1 };

    mxArray* mxExportedFunctionsUsedByThisChart = mxCreateCellArray(2, exp_dims);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsUsedByThisChart",
               mxExportedFunctionsUsedByThisChart);
    mxSetField(mxPostCodegenInfo, 0, "exportedFunctionsChecksum",
               mxExportedFunctionsChecksum);
  }

  return mxPostCodegenInfo;
}

static const mxArray *sf_get_sim_state_info_c2_Landing(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x3'type','srcId','name','auxInfo'{{M[1],M[5],T\"acceleration\",},{M[1],M[15],T\"density\",},{M[8],M[0],T\"is_active_c2_Landing\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 3, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_Landing_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_LandingInstanceStruct *chartInstance = (SFc2_LandingInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _LandingMachineNumber_,
           2,
           1,
           1,
           0,
           10,
           0,
           0,
           0,
           0,
           4,
           &chartInstance->chartNumber,
           &chartInstance->instanceNumber,
           (void *)S);

        /* Each instance must initialize its own list of scripts */
        init_script_number_translation(_LandingMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_LandingMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _LandingMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"rocketPower");
          _SFD_SET_DATA_PROPS(1,1,1,0,"thrustSetting");
          _SFD_SET_DATA_PROPS(2,1,1,0,"bruttoWeight");
          _SFD_SET_DATA_PROPS(3,1,1,0,"tankLevel");
          _SFD_SET_DATA_PROPS(4,1,1,0,"tankVolume");
          _SFD_SET_DATA_PROPS(5,1,1,0,"rocketDiameter");
          _SFD_SET_DATA_PROPS(6,1,1,0,"height");
          _SFD_SET_DATA_PROPS(7,1,1,0,"speed");
          _SFD_SET_DATA_PROPS(8,2,0,1,"acceleration");
          _SFD_SET_DATA_PROPS(9,2,0,1,"density");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,416);
        _SFD_CV_INIT_SCRIPT(0,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(0,0,"Mass",0,-1,316);
        _SFD_CV_INIT_SCRIPT(1,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(1,0,"Thrust",0,-1,150);
        _SFD_CV_INIT_SCRIPT(2,1,0,0,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(2,0,"Gravity",0,-1,230);
        _SFD_CV_INIT_SCRIPT(3,3,0,1,0,0,0,0,0,0,0);
        _SFD_CV_INIT_SCRIPT_FCN(3,0,"AirDrag",0,-1,531);
        _SFD_CV_INIT_SCRIPT_FCN(3,1,"Area",533,-1,639);
        _SFD_CV_INIT_SCRIPT_FCN(3,2,"Density",641,-1,1586);
        _SFD_CV_INIT_SCRIPT_IF(3,0,192,205,366,527);
        _SFD_CV_INIT_SCRIPT_RELATIONAL(3,0,195,205,-1,5);
        _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(4,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c2_sf_marshallOut,(MexInFcnForType)c2_sf_marshallIn);
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _LandingMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static void chart_debug_initialize_data_addresses(SimStruct *S)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc2_LandingInstanceStruct *chartInstance = (SFc2_LandingInstanceStruct *)
      sf_get_chart_instance_ptr(S);
    if (ssIsFirstInitCond(S)) {
      /* do this only if simulation is starting and after we know the addresses of all data */
      {
        _SFD_SET_DATA_VALUE_PTR(0U, chartInstance->c2_rocketPower);
        _SFD_SET_DATA_VALUE_PTR(1U, chartInstance->c2_thrustSetting);
        _SFD_SET_DATA_VALUE_PTR(2U, chartInstance->c2_bruttoWeight);
        _SFD_SET_DATA_VALUE_PTR(3U, chartInstance->c2_tankLevel);
        _SFD_SET_DATA_VALUE_PTR(4U, chartInstance->c2_tankVolume);
        _SFD_SET_DATA_VALUE_PTR(5U, chartInstance->c2_rocketDiameter);
        _SFD_SET_DATA_VALUE_PTR(6U, chartInstance->c2_height);
        _SFD_SET_DATA_VALUE_PTR(8U, chartInstance->c2_acceleration);
        _SFD_SET_DATA_VALUE_PTR(7U, chartInstance->c2_speed);
        _SFD_SET_DATA_VALUE_PTR(9U, chartInstance->c2_density);
      }
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "sCwQO0jlJl5RsHQR45pmXcG";
}

static void sf_opaque_initialize_c2_Landing(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc2_LandingInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c2_Landing((SFc2_LandingInstanceStruct*) chartInstanceVar);
  initialize_c2_Landing((SFc2_LandingInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_Landing(void *chartInstanceVar)
{
  enable_c2_Landing((SFc2_LandingInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_Landing(void *chartInstanceVar)
{
  disable_c2_Landing((SFc2_LandingInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_Landing(void *chartInstanceVar)
{
  sf_gateway_c2_Landing((SFc2_LandingInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_Landing(SimStruct* S)
{
  return get_sim_state_c2_Landing((SFc2_LandingInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_Landing(SimStruct* S, const mxArray *st)
{
  set_sim_state_c2_Landing((SFc2_LandingInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_terminate_c2_Landing(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_LandingInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_Landing_optimization_info();
    }

    finalize_c2_Landing((SFc2_LandingInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_Landing((SFc2_LandingInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_Landing(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_Landing((SFc2_LandingInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

static void mdlSetWorkWidths_c2_Landing(SimStruct *S)
{
  /* Set overwritable ports for inplace optimization */
  ssMdlUpdateIsEmpty(S, 1);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_Landing_optimization_info(sim_mode_is_rtw_gen(S),
      sim_mode_is_modelref_sim(S), sim_mode_is_external(S));
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,2);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,1);
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,2,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_set_chart_accesses_machine_info(S, sf_get_instance_specialization(),
      infoStruct, 2);
    sf_update_buildInfo(S, sf_get_instance_specialization(),infoStruct,2);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,2,8);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,2,2);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=2; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 8; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,2);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(14778372U));
  ssSetChecksum1(S,(93122497U));
  ssSetChecksum2(S,(3013629719U));
  ssSetChecksum3(S,(477560660U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSetStateSemanticsClassicAndSynchronous(S, true);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c2_Landing(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c2_Landing(SimStruct *S)
{
  SFc2_LandingInstanceStruct *chartInstance;
  chartInstance = (SFc2_LandingInstanceStruct *)utMalloc(sizeof
    (SFc2_LandingInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_LandingInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_Landing;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_Landing;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c2_Landing;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_Landing;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_Landing;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_Landing;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_Landing;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_Landing;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_Landing;
  chartInstance->chartInfo.mdlStart = mdlStart_c2_Landing;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_Landing;
  chartInstance->chartInfo.callGetHoverDataForMsg = NULL;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  chart_debug_initialization(S,1);
  mdl_start_c2_Landing(chartInstance);
}

void c2_Landing_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c2_Landing(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_Landing(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_Landing(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_Landing_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
