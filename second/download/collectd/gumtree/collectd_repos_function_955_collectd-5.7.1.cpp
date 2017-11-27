static int turbostat_config(const char *key, const char *value) {
  long unsigned int tmp_val;
  char *end;

  if (strcasecmp("CoreCstates", key) == 0) {
    tmp_val = strtoul(value, &end, 0);
    if (*end != '\0' || tmp_val > UINT_MAX) {
      ERROR("turbostat plugin: Invalid CoreCstates '%s'", value);
      return -1;
    }
    config_core_cstate = (unsigned int)tmp_val;
    apply_config_core_cstate = 1;
  } else if (strcasecmp("PackageCstates", key) == 0) {
    tmp_val = strtoul(value, &end, 0);
    if (*end != '\0' || tmp_val > UINT_MAX) {
      ERROR("turbostat plugin: Invalid PackageCstates '%s'", value);
      return -1;
    }
    config_pkg_cstate = (unsigned int)tmp_val;
    apply_config_pkg_cstate = 1;
  } else if (strcasecmp("SystemManagementInterrupt", key) == 0) {
    config_smi = IS_TRUE(value);
    apply_config_smi = 1;
  } else if (strcasecmp("DigitalTemperatureSensor", key) == 0) {
    config_dts = IS_TRUE(value);
    apply_config_dts = 1;
  } else if (strcasecmp("PackageThermalManagement", key) == 0) {
    config_ptm = IS_TRUE(value);
    apply_config_ptm = 1;
  } else if (strcasecmp("LogicalCoreNames", key) == 0) {
    config_lcn = IS_TRUE(value);
  } else if (strcasecmp("RunningAveragePowerLimit", key) == 0) {
    tmp_val = strtoul(value, &end, 0);
    if (*end != '\0' || tmp_val > UINT_MAX) {
      ERROR("turbostat plugin: Invalid RunningAveragePowerLimit '%s'", value);
      return -1;
    }
    config_rapl = (unsigned int)tmp_val;
    apply_config_rapl = 1;
  } else if (strcasecmp("TCCActivationTemp", key) == 0) {
    tmp_val = strtoul(value, &end, 0);
    if (*end != '\0' || tmp_val > UINT_MAX) {
      ERROR("turbostat plugin: Invalid TCCActivationTemp '%s'", value);
      return -1;
    }
    tcc_activation_temp = (unsigned int)tmp_val;
  } else {
    ERROR("turbostat plugin: Invalid configuration option '%s'", key);
    return -1;
  }
  return 0;
}