static int tn_config_add_severity(tn_data_t *data, /* {{{ */
                                  const oconfig_item_t *ci) {
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    ERROR("Target `notification': The `%s' option requires exactly one string "
          "argument.",
          ci->key);
    return -1;
  }

  if ((strcasecmp("FAILURE", ci->values[0].value.string) == 0) ||
      (strcasecmp("CRITICAL", ci->values[0].value.string) == 0))
    data->severity = NOTIF_FAILURE;
  else if ((strcasecmp("WARNING", ci->values[0].value.string) == 0) ||
           (strcasecmp("WARN", ci->values[0].value.string) == 0))
    data->severity = NOTIF_WARNING;
  else if (strcasecmp("OKAY", ci->values[0].value.string) == 0)
    data->severity = NOTIF_OKAY;
  else {
    WARNING("Target `notification': Unknown severity `%s'. "
            "Will use `FAILURE' instead.",
            ci->values[0].value.string);
    data->severity = NOTIF_FAILURE;
  }

  return 0;
}