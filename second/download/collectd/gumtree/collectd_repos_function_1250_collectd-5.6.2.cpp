static int tcsv_config_get_index(oconfig_item_t *ci, ssize_t *ret_index) {
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_NUMBER)) {
    WARNING("tail_csv plugin: The \"%s\" config option needs exactly one "
            "integer argument.",
            ci->key);
    return (-1);
  }

  if (ci->values[0].value.number < 0) {
    WARNING("tail_csv plugin: The \"%s\" config option must be positive "
            "(or zero).",
            ci->key);
    return (-1);
  }

  *ret_index = (ssize_t)ci->values[0].value.number;
  return (0);
}