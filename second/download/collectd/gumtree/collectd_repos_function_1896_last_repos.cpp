static int ut_config_type_datasource(threshold_t *th, oconfig_item_t *ci) {
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("threshold values: The `DataSource' option needs exactly one "
            "string argument.");
    return -1;
  }

  sstrncpy(th->data_source, ci->values[0].value.string,
           sizeof(th->data_source));

  return 0;
}