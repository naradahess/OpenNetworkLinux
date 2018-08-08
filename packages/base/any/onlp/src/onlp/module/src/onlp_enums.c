/************************************************************
 * <bsn.cl fy=2014 v=onl>
 *
 *        Copyright 2014, 2015 Big Switch Networks, Inc.
 *
 * Licensed under the Eclipse Public License, Version 1.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *        http://www.eclipse.org/legal/epl-v10.html
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the
 * License.
 *
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/

#include <onlp/onlp_config.h>
#include <onlp/onlp.h>
#include <onlp/sfp.h>
#include <onlp/oids.h>
#include <onlp/thermal.h>
#include <onlp/fan.h>
#include <onlp/psu.h>
#include <onlp/led.h>

#include "onlp_log.h"

/* <auto.start.enum(ALL).source> */
aim_map_si_t onlp_fan_caps_map[] =
{
    { "SET_DIR", ONLP_FAN_CAPS_SET_DIR },
    { "GET_DIR", ONLP_FAN_CAPS_GET_DIR },
    { "SET_RPM", ONLP_FAN_CAPS_SET_RPM },
    { "SET_PERCENTAGE", ONLP_FAN_CAPS_SET_PERCENTAGE },
    { "GET_RPM", ONLP_FAN_CAPS_GET_RPM },
    { "GET_PERCENTAGE", ONLP_FAN_CAPS_GET_PERCENTAGE },
    { NULL, 0 }
};

aim_map_si_t onlp_fan_caps_desc_map[] =
{
    { "None", ONLP_FAN_CAPS_SET_DIR },
    { "None", ONLP_FAN_CAPS_GET_DIR },
    { "None", ONLP_FAN_CAPS_SET_RPM },
    { "None", ONLP_FAN_CAPS_SET_PERCENTAGE },
    { "None", ONLP_FAN_CAPS_GET_RPM },
    { "None", ONLP_FAN_CAPS_GET_PERCENTAGE },
    { NULL, 0 }
};

const char*
onlp_fan_caps_name(onlp_fan_caps_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_fan_caps_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_fan_caps'";
    }
}

int
onlp_fan_caps_value(const char* str, onlp_fan_caps_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_fan_caps_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_fan_caps_desc(onlp_fan_caps_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_fan_caps_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_fan_caps'";
    }
}

int
onlp_fan_caps_valid(onlp_fan_caps_t e)
{
    return aim_map_si_i(NULL, e, onlp_fan_caps_map, 0) ? 1 : 0;
}


aim_map_si_t onlp_fan_dir_map[] =
{
    { "UNKNOWN", ONLP_FAN_DIR_UNKNOWN },
    { "B2F", ONLP_FAN_DIR_B2F },
    { "F2B", ONLP_FAN_DIR_F2B },
    { NULL, 0 }
};

aim_map_si_t onlp_fan_dir_desc_map[] =
{
    { "None", ONLP_FAN_DIR_UNKNOWN },
    { "None", ONLP_FAN_DIR_B2F },
    { "None", ONLP_FAN_DIR_F2B },
    { NULL, 0 }
};

const char*
onlp_fan_dir_name(onlp_fan_dir_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_fan_dir_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_fan_dir'";
    }
}

int
onlp_fan_dir_value(const char* str, onlp_fan_dir_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_fan_dir_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_fan_dir_desc(onlp_fan_dir_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_fan_dir_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_fan_dir'";
    }
}


aim_map_si_t onlp_led_caps_map[] =
{
    { "OFF", ONLP_LED_CAPS_OFF },
    { "AUTO", ONLP_LED_CAPS_AUTO },
    { "AUTO_BLINKING", ONLP_LED_CAPS_AUTO_BLINKING },
    { "CHAR", ONLP_LED_CAPS_CHAR },
    { "RED", ONLP_LED_CAPS_RED },
    { "RED_BLINKING", ONLP_LED_CAPS_RED_BLINKING },
    { "ORANGE", ONLP_LED_CAPS_ORANGE },
    { "ORANGE_BLINKING", ONLP_LED_CAPS_ORANGE_BLINKING },
    { "YELLOW", ONLP_LED_CAPS_YELLOW },
    { "YELLOW_BLINKING", ONLP_LED_CAPS_YELLOW_BLINKING },
    { "GREEN", ONLP_LED_CAPS_GREEN },
    { "GREEN_BLINKING", ONLP_LED_CAPS_GREEN_BLINKING },
    { "BLUE", ONLP_LED_CAPS_BLUE },
    { "BLUE_BLINKING", ONLP_LED_CAPS_BLUE_BLINKING },
    { "PURPLE", ONLP_LED_CAPS_PURPLE },
    { "PURPLE_BLINKING", ONLP_LED_CAPS_PURPLE_BLINKING },
    { NULL, 0 }
};

aim_map_si_t onlp_led_caps_desc_map[] =
{
    { "None", ONLP_LED_CAPS_OFF },
    { "None", ONLP_LED_CAPS_AUTO },
    { "None", ONLP_LED_CAPS_AUTO_BLINKING },
    { "None", ONLP_LED_CAPS_CHAR },
    { "None", ONLP_LED_CAPS_RED },
    { "None", ONLP_LED_CAPS_RED_BLINKING },
    { "None", ONLP_LED_CAPS_ORANGE },
    { "None", ONLP_LED_CAPS_ORANGE_BLINKING },
    { "None", ONLP_LED_CAPS_YELLOW },
    { "None", ONLP_LED_CAPS_YELLOW_BLINKING },
    { "None", ONLP_LED_CAPS_GREEN },
    { "None", ONLP_LED_CAPS_GREEN_BLINKING },
    { "None", ONLP_LED_CAPS_BLUE },
    { "None", ONLP_LED_CAPS_BLUE_BLINKING },
    { "None", ONLP_LED_CAPS_PURPLE },
    { "None", ONLP_LED_CAPS_PURPLE_BLINKING },
    { NULL, 0 }
};

const char*
onlp_led_caps_name(onlp_led_caps_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_led_caps_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_led_caps'";
    }
}

int
onlp_led_caps_value(const char* str, onlp_led_caps_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_led_caps_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_led_caps_desc(onlp_led_caps_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_led_caps_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_led_caps'";
    }
}

int
onlp_led_caps_valid(onlp_led_caps_t e)
{
    return aim_map_si_i(NULL, e, onlp_led_caps_map, 0) ? 1 : 0;
}


aim_map_si_t onlp_led_mode_map[] =
{
    { "OFF", ONLP_LED_MODE_OFF },
    { "AUTO", ONLP_LED_MODE_AUTO },
    { "AUTO_BLINKING", ONLP_LED_MODE_AUTO_BLINKING },
    { "CHAR", ONLP_LED_MODE_CHAR },
    { "RED", ONLP_LED_MODE_RED },
    { "RED_BLINKING", ONLP_LED_MODE_RED_BLINKING },
    { "ORANGE", ONLP_LED_MODE_ORANGE },
    { "ORANGE_BLINKING", ONLP_LED_MODE_ORANGE_BLINKING },
    { "YELLOW", ONLP_LED_MODE_YELLOW },
    { "YELLOW_BLINKING", ONLP_LED_MODE_YELLOW_BLINKING },
    { "GREEN", ONLP_LED_MODE_GREEN },
    { "GREEN_BLINKING", ONLP_LED_MODE_GREEN_BLINKING },
    { "BLUE", ONLP_LED_MODE_BLUE },
    { "BLUE_BLINKING", ONLP_LED_MODE_BLUE_BLINKING },
    { "PURPLE", ONLP_LED_MODE_PURPLE },
    { "PURPLE_BLINKING", ONLP_LED_MODE_PURPLE_BLINKING },
    { NULL, 0 }
};

aim_map_si_t onlp_led_mode_desc_map[] =
{
    { "None", ONLP_LED_MODE_OFF },
    { "None", ONLP_LED_MODE_AUTO },
    { "None", ONLP_LED_MODE_AUTO_BLINKING },
    { "None", ONLP_LED_MODE_CHAR },
    { "None", ONLP_LED_MODE_RED },
    { "None", ONLP_LED_MODE_RED_BLINKING },
    { "None", ONLP_LED_MODE_ORANGE },
    { "None", ONLP_LED_MODE_ORANGE_BLINKING },
    { "None", ONLP_LED_MODE_YELLOW },
    { "None", ONLP_LED_MODE_YELLOW_BLINKING },
    { "None", ONLP_LED_MODE_GREEN },
    { "None", ONLP_LED_MODE_GREEN_BLINKING },
    { "None", ONLP_LED_MODE_BLUE },
    { "None", ONLP_LED_MODE_BLUE_BLINKING },
    { "None", ONLP_LED_MODE_PURPLE },
    { "None", ONLP_LED_MODE_PURPLE_BLINKING },
    { NULL, 0 }
};

const char*
onlp_led_mode_name(onlp_led_mode_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_led_mode_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_led_mode'";
    }
}

int
onlp_led_mode_value(const char* str, onlp_led_mode_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_led_mode_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_led_mode_desc(onlp_led_mode_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_led_mode_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_led_mode'";
    }
}


aim_map_si_t onlp_log_flag_map[] =
{
    { "JSON", ONLP_LOG_FLAG_JSON },
    { NULL, 0 }
};

aim_map_si_t onlp_log_flag_desc_map[] =
{
    { "None", ONLP_LOG_FLAG_JSON },
    { NULL, 0 }
};

const char*
onlp_log_flag_name(onlp_log_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_log_flag_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_log_flag'";
    }
}

int
onlp_log_flag_value(const char* str, onlp_log_flag_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_log_flag_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_log_flag_desc(onlp_log_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_log_flag_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_log_flag'";
    }
}


aim_map_si_t onlp_oid_json_flag_map[] =
{
    { "RECURSIVE", ONLP_OID_JSON_FLAG_RECURSIVE },
    { "UNSUPPORTED_FIELDS", ONLP_OID_JSON_FLAG_UNSUPPORTED_FIELDS },
    { "TO_USER_JSON", ONLP_OID_JSON_FLAG_TO_USER_JSON },
    { NULL, 0 }
};

aim_map_si_t onlp_oid_json_flag_desc_map[] =
{
    { "None", ONLP_OID_JSON_FLAG_RECURSIVE },
    { "None", ONLP_OID_JSON_FLAG_UNSUPPORTED_FIELDS },
    { "None", ONLP_OID_JSON_FLAG_TO_USER_JSON },
    { NULL, 0 }
};

const char*
onlp_oid_json_flag_name(onlp_oid_json_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_oid_json_flag_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_oid_json_flag'";
    }
}

int
onlp_oid_json_flag_value(const char* str, onlp_oid_json_flag_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_oid_json_flag_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_oid_json_flag_desc(onlp_oid_json_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_oid_json_flag_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_oid_json_flag'";
    }
}

int
onlp_oid_json_flag_valid(onlp_oid_json_flag_t e)
{
    return aim_map_si_i(NULL, e, onlp_oid_json_flag_map, 0) ? 1 : 0;
}


aim_map_si_t onlp_oid_status_flag_map[] =
{
    { "PRESENT", ONLP_OID_STATUS_FLAG_PRESENT },
    { "FAILED", ONLP_OID_STATUS_FLAG_FAILED },
    { "OPERATIONAL", ONLP_OID_STATUS_FLAG_OPERATIONAL },
    { "UNPLUGGED", ONLP_OID_STATUS_FLAG_UNPLUGGED },
    { NULL, 0 }
};

aim_map_si_t onlp_oid_status_flag_desc_map[] =
{
    { "None", ONLP_OID_STATUS_FLAG_PRESENT },
    { "None", ONLP_OID_STATUS_FLAG_FAILED },
    { "None", ONLP_OID_STATUS_FLAG_OPERATIONAL },
    { "None", ONLP_OID_STATUS_FLAG_UNPLUGGED },
    { NULL, 0 }
};

const char*
onlp_oid_status_flag_name(onlp_oid_status_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_oid_status_flag_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_oid_status_flag'";
    }
}

int
onlp_oid_status_flag_value(const char* str, onlp_oid_status_flag_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_oid_status_flag_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_oid_status_flag_desc(onlp_oid_status_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_oid_status_flag_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_oid_status_flag'";
    }
}

int
onlp_oid_status_flag_valid(onlp_oid_status_flag_t e)
{
    return aim_map_si_i(NULL, e, onlp_oid_status_flag_map, 0) ? 1 : 0;
}


aim_map_si_t onlp_oid_type_map[] =
{
    { "CHASSIS", ONLP_OID_TYPE_CHASSIS },
    { "MODULE", ONLP_OID_TYPE_MODULE },
    { "THERMAL", ONLP_OID_TYPE_THERMAL },
    { "FAN", ONLP_OID_TYPE_FAN },
    { "PSU", ONLP_OID_TYPE_PSU },
    { "LED", ONLP_OID_TYPE_LED },
    { "SFP", ONLP_OID_TYPE_SFP },
    { "GENERIC", ONLP_OID_TYPE_GENERIC },
    { NULL, 0 }
};

aim_map_si_t onlp_oid_type_desc_map[] =
{
    { "None", ONLP_OID_TYPE_CHASSIS },
    { "None", ONLP_OID_TYPE_MODULE },
    { "None", ONLP_OID_TYPE_THERMAL },
    { "None", ONLP_OID_TYPE_FAN },
    { "None", ONLP_OID_TYPE_PSU },
    { "None", ONLP_OID_TYPE_LED },
    { "None", ONLP_OID_TYPE_SFP },
    { "None", ONLP_OID_TYPE_GENERIC },
    { NULL, 0 }
};

const char*
onlp_oid_type_name(onlp_oid_type_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_oid_type_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_oid_type'";
    }
}

int
onlp_oid_type_value(const char* str, onlp_oid_type_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_oid_type_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_oid_type_desc(onlp_oid_type_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_oid_type_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_oid_type'";
    }
}

int
onlp_oid_type_valid(onlp_oid_type_t e)
{
    return aim_map_si_i(NULL, e, onlp_oid_type_map, 0) ? 1 : 0;
}


aim_map_si_t onlp_oid_type_flag_map[] =
{
    { "CHASSIS", ONLP_OID_TYPE_FLAG_CHASSIS },
    { "MODULE", ONLP_OID_TYPE_FLAG_MODULE },
    { "THERMAL", ONLP_OID_TYPE_FLAG_THERMAL },
    { "FAN", ONLP_OID_TYPE_FLAG_FAN },
    { "PSU", ONLP_OID_TYPE_FLAG_PSU },
    { "LED", ONLP_OID_TYPE_FLAG_LED },
    { "SFP", ONLP_OID_TYPE_FLAG_SFP },
    { "GENERIC", ONLP_OID_TYPE_FLAG_GENERIC },
    { NULL, 0 }
};

aim_map_si_t onlp_oid_type_flag_desc_map[] =
{
    { "None", ONLP_OID_TYPE_FLAG_CHASSIS },
    { "None", ONLP_OID_TYPE_FLAG_MODULE },
    { "None", ONLP_OID_TYPE_FLAG_THERMAL },
    { "None", ONLP_OID_TYPE_FLAG_FAN },
    { "None", ONLP_OID_TYPE_FLAG_PSU },
    { "None", ONLP_OID_TYPE_FLAG_LED },
    { "None", ONLP_OID_TYPE_FLAG_SFP },
    { "None", ONLP_OID_TYPE_FLAG_GENERIC },
    { NULL, 0 }
};

const char*
onlp_oid_type_flag_name(onlp_oid_type_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_oid_type_flag_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_oid_type_flag'";
    }
}

int
onlp_oid_type_flag_value(const char* str, onlp_oid_type_flag_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_oid_type_flag_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_oid_type_flag_desc(onlp_oid_type_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_oid_type_flag_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_oid_type_flag'";
    }
}

int
onlp_oid_type_flag_valid(onlp_oid_type_flag_t e)
{
    return aim_map_si_i(NULL, e, onlp_oid_type_flag_map, 0) ? 1 : 0;
}


aim_map_si_t onlp_psu_caps_map[] =
{
    { "GET_TYPE", ONLP_PSU_CAPS_GET_TYPE },
    { "GET_VIN", ONLP_PSU_CAPS_GET_VIN },
    { "GET_VOUT", ONLP_PSU_CAPS_GET_VOUT },
    { "GET_IIN", ONLP_PSU_CAPS_GET_IIN },
    { "GET_IOUT", ONLP_PSU_CAPS_GET_IOUT },
    { "GET_PIN", ONLP_PSU_CAPS_GET_PIN },
    { "GET_POUT", ONLP_PSU_CAPS_GET_POUT },
    { NULL, 0 }
};

aim_map_si_t onlp_psu_caps_desc_map[] =
{
    { "None", ONLP_PSU_CAPS_GET_TYPE },
    { "None", ONLP_PSU_CAPS_GET_VIN },
    { "None", ONLP_PSU_CAPS_GET_VOUT },
    { "None", ONLP_PSU_CAPS_GET_IIN },
    { "None", ONLP_PSU_CAPS_GET_IOUT },
    { "None", ONLP_PSU_CAPS_GET_PIN },
    { "None", ONLP_PSU_CAPS_GET_POUT },
    { NULL, 0 }
};

const char*
onlp_psu_caps_name(onlp_psu_caps_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_psu_caps_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_psu_caps'";
    }
}

int
onlp_psu_caps_value(const char* str, onlp_psu_caps_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_psu_caps_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_psu_caps_desc(onlp_psu_caps_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_psu_caps_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_psu_caps'";
    }
}

int
onlp_psu_caps_valid(onlp_psu_caps_t e)
{
    return aim_map_si_i(NULL, e, onlp_psu_caps_map, 0) ? 1 : 0;
}


aim_map_si_t onlp_psu_type_map[] =
{
    { "AC", ONLP_PSU_TYPE_AC },
    { "DC12", ONLP_PSU_TYPE_DC12 },
    { "DC48", ONLP_PSU_TYPE_DC48 },
    { NULL, 0 }
};

aim_map_si_t onlp_psu_type_desc_map[] =
{
    { "None", ONLP_PSU_TYPE_AC },
    { "None", ONLP_PSU_TYPE_DC12 },
    { "None", ONLP_PSU_TYPE_DC48 },
    { NULL, 0 }
};

const char*
onlp_psu_type_name(onlp_psu_type_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_psu_type_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_psu_type'";
    }
}

int
onlp_psu_type_value(const char* str, onlp_psu_type_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_psu_type_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_psu_type_desc(onlp_psu_type_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_psu_type_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_psu_type'";
    }
}


aim_map_si_t onlp_sfp_control_map[] =
{
    { "RESET", ONLP_SFP_CONTROL_RESET },
    { "RESET_STATE", ONLP_SFP_CONTROL_RESET_STATE },
    { "RX_LOS", ONLP_SFP_CONTROL_RX_LOS },
    { "TX_FAULT", ONLP_SFP_CONTROL_TX_FAULT },
    { "TX_DISABLE", ONLP_SFP_CONTROL_TX_DISABLE },
    { "TX_DISABLE_CHANNEL", ONLP_SFP_CONTROL_TX_DISABLE_CHANNEL },
    { "LP_MODE", ONLP_SFP_CONTROL_LP_MODE },
    { "POWER_OVERRIDE", ONLP_SFP_CONTROL_POWER_OVERRIDE },
    { NULL, 0 }
};

aim_map_si_t onlp_sfp_control_desc_map[] =
{
    { "None", ONLP_SFP_CONTROL_RESET },
    { "None", ONLP_SFP_CONTROL_RESET_STATE },
    { "None", ONLP_SFP_CONTROL_RX_LOS },
    { "None", ONLP_SFP_CONTROL_TX_FAULT },
    { "None", ONLP_SFP_CONTROL_TX_DISABLE },
    { "None", ONLP_SFP_CONTROL_TX_DISABLE_CHANNEL },
    { "None", ONLP_SFP_CONTROL_LP_MODE },
    { "None", ONLP_SFP_CONTROL_POWER_OVERRIDE },
    { NULL, 0 }
};

const char*
onlp_sfp_control_name(onlp_sfp_control_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_sfp_control_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_sfp_control'";
    }
}

int
onlp_sfp_control_value(const char* str, onlp_sfp_control_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_sfp_control_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_sfp_control_desc(onlp_sfp_control_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_sfp_control_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_sfp_control'";
    }
}


aim_map_si_t onlp_sfp_control_flag_map[] =
{
    { "RESET", ONLP_SFP_CONTROL_FLAG_RESET },
    { "RESET_STATE", ONLP_SFP_CONTROL_FLAG_RESET_STATE },
    { "RX_LOS", ONLP_SFP_CONTROL_FLAG_RX_LOS },
    { "TX_FAULT", ONLP_SFP_CONTROL_FLAG_TX_FAULT },
    { "TX_DISABLE", ONLP_SFP_CONTROL_FLAG_TX_DISABLE },
    { "TX_DISABLE_CHANNEL", ONLP_SFP_CONTROL_FLAG_TX_DISABLE_CHANNEL },
    { "LP_MODE", ONLP_SFP_CONTROL_FLAG_LP_MODE },
    { "POWER_OVERRIDE", ONLP_SFP_CONTROL_FLAG_POWER_OVERRIDE },
    { NULL, 0 }
};

aim_map_si_t onlp_sfp_control_flag_desc_map[] =
{
    { "None", ONLP_SFP_CONTROL_FLAG_RESET },
    { "None", ONLP_SFP_CONTROL_FLAG_RESET_STATE },
    { "None", ONLP_SFP_CONTROL_FLAG_RX_LOS },
    { "None", ONLP_SFP_CONTROL_FLAG_TX_FAULT },
    { "None", ONLP_SFP_CONTROL_FLAG_TX_DISABLE },
    { "None", ONLP_SFP_CONTROL_FLAG_TX_DISABLE_CHANNEL },
    { "None", ONLP_SFP_CONTROL_FLAG_LP_MODE },
    { "None", ONLP_SFP_CONTROL_FLAG_POWER_OVERRIDE },
    { NULL, 0 }
};

const char*
onlp_sfp_control_flag_name(onlp_sfp_control_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_sfp_control_flag_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_sfp_control_flag'";
    }
}

int
onlp_sfp_control_flag_value(const char* str, onlp_sfp_control_flag_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_sfp_control_flag_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_sfp_control_flag_desc(onlp_sfp_control_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_sfp_control_flag_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_sfp_control_flag'";
    }
}

int
onlp_sfp_control_flag_valid(onlp_sfp_control_flag_t e)
{
    return aim_map_si_i(NULL, e, onlp_sfp_control_flag_map, 0) ? 1 : 0;
}


aim_map_si_t onlp_sfp_type_map[] =
{
    { "SFP", ONLP_SFP_TYPE_SFP },
    { "QSFP", ONLP_SFP_TYPE_QSFP },
    { "SFP28", ONLP_SFP_TYPE_SFP28 },
    { "QSFP28", ONLP_SFP_TYPE_QSFP28 },
    { NULL, 0 }
};

aim_map_si_t onlp_sfp_type_desc_map[] =
{
    { "None", ONLP_SFP_TYPE_SFP },
    { "None", ONLP_SFP_TYPE_QSFP },
    { "None", ONLP_SFP_TYPE_SFP28 },
    { "None", ONLP_SFP_TYPE_QSFP28 },
    { NULL, 0 }
};

const char*
onlp_sfp_type_name(onlp_sfp_type_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_sfp_type_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_sfp_type'";
    }
}

int
onlp_sfp_type_value(const char* str, onlp_sfp_type_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_sfp_type_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_sfp_type_desc(onlp_sfp_type_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_sfp_type_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_sfp_type'";
    }
}


aim_map_si_t onlp_status_map[] =
{
    { "OK", ONLP_STATUS_OK },
    { "E_GENERIC", ONLP_STATUS_E_GENERIC },
    { "E_UNSUPPORTED", ONLP_STATUS_E_UNSUPPORTED },
    { "E_MISSING", ONLP_STATUS_E_MISSING },
    { "E_INVALID", ONLP_STATUS_E_INVALID },
    { "E_INTERNAL", ONLP_STATUS_E_INTERNAL },
    { "E_PARAM", ONLP_STATUS_E_PARAM },
    { "E_I2C", ONLP_STATUS_E_I2C },
    { NULL, 0 }
};

aim_map_si_t onlp_status_desc_map[] =
{
    { "None", ONLP_STATUS_OK },
    { "None", ONLP_STATUS_E_GENERIC },
    { "None", ONLP_STATUS_E_UNSUPPORTED },
    { "None", ONLP_STATUS_E_MISSING },
    { "None", ONLP_STATUS_E_INVALID },
    { "None", ONLP_STATUS_E_INTERNAL },
    { "None", ONLP_STATUS_E_PARAM },
    { "None", ONLP_STATUS_E_I2C },
    { NULL, 0 }
};

const char*
onlp_status_name(onlp_status_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_status_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_status'";
    }
}

int
onlp_status_value(const char* str, onlp_status_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_status_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_status_desc(onlp_status_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_status_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_status'";
    }
}

int
onlp_status_valid(onlp_status_t e)
{
    return aim_map_si_i(NULL, e, onlp_status_map, 0) ? 1 : 0;
}


aim_map_si_t onlp_thermal_caps_map[] =
{
    { "GET_TEMPERATURE", ONLP_THERMAL_CAPS_GET_TEMPERATURE },
    { "GET_WARNING_THRESHOLD", ONLP_THERMAL_CAPS_GET_WARNING_THRESHOLD },
    { "GET_ERROR_THRESHOLD", ONLP_THERMAL_CAPS_GET_ERROR_THRESHOLD },
    { "GET_SHUTDOWN_THRESHOLD", ONLP_THERMAL_CAPS_GET_SHUTDOWN_THRESHOLD },
    { NULL, 0 }
};

aim_map_si_t onlp_thermal_caps_desc_map[] =
{
    { "None", ONLP_THERMAL_CAPS_GET_TEMPERATURE },
    { "None", ONLP_THERMAL_CAPS_GET_WARNING_THRESHOLD },
    { "None", ONLP_THERMAL_CAPS_GET_ERROR_THRESHOLD },
    { "None", ONLP_THERMAL_CAPS_GET_SHUTDOWN_THRESHOLD },
    { NULL, 0 }
};

const char*
onlp_thermal_caps_name(onlp_thermal_caps_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_thermal_caps_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_thermal_caps'";
    }
}

int
onlp_thermal_caps_value(const char* str, onlp_thermal_caps_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_thermal_caps_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_thermal_caps_desc(onlp_thermal_caps_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_thermal_caps_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_thermal_caps'";
    }
}

int
onlp_thermal_caps_valid(onlp_thermal_caps_t e)
{
    return aim_map_si_i(NULL, e, onlp_thermal_caps_map, 0) ? 1 : 0;
}


aim_map_si_t onlp_thermal_threshold_map[] =
{
    { "WARNING_DEFAULT", ONLP_THERMAL_THRESHOLD_WARNING_DEFAULT },
    { "ERROR_DEFAULT", ONLP_THERMAL_THRESHOLD_ERROR_DEFAULT },
    { "SHUTDOWN_DEFAULT", ONLP_THERMAL_THRESHOLD_SHUTDOWN_DEFAULT },
    { NULL, 0 }
};

aim_map_si_t onlp_thermal_threshold_desc_map[] =
{
    { "None", ONLP_THERMAL_THRESHOLD_WARNING_DEFAULT },
    { "None", ONLP_THERMAL_THRESHOLD_ERROR_DEFAULT },
    { "None", ONLP_THERMAL_THRESHOLD_SHUTDOWN_DEFAULT },
    { NULL, 0 }
};

const char*
onlp_thermal_threshold_name(onlp_thermal_threshold_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_thermal_threshold_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_thermal_threshold'";
    }
}

int
onlp_thermal_threshold_value(const char* str, onlp_thermal_threshold_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_thermal_threshold_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_thermal_threshold_desc(onlp_thermal_threshold_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_thermal_threshold_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_thermal_threshold'";
    }
}

int
onlp_thermal_threshold_valid(onlp_thermal_threshold_t e)
{
    return aim_map_si_i(NULL, e, onlp_thermal_threshold_map, 0) ? 1 : 0;
}

/* <auto.end.enum(ALL).source> */
