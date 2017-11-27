static int ut_config_type_hysteresis(threshold_t *th, oconfig_item_t *ci) {
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_NUMBER)) {
    WARNING("threshold values: The `%s' option needs exactly one "
            "number argument.",
            ci->key);
    return -1;
  }

  th->hysteresis = ci->values[0].value.number;

  return 0;
}