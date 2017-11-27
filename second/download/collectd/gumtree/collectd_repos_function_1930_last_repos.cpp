static int config_set_format(wh_callback_t *cb, /* {{{ */
                             oconfig_item_t *ci) {
  char *string;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("write_http plugin: The `%s' config option "
            "needs exactly one string argument.",
            ci->key);
    return -1;
  }

  string = ci->values[0].value.string;
  if (strcasecmp("Command", string) == 0)
    cb->format = WH_FORMAT_COMMAND;
  else if (strcasecmp("JSON", string) == 0)
    cb->format = WH_FORMAT_JSON;
  else if (strcasecmp("KAIROSDB", string) == 0)
    cb->format = WH_FORMAT_KAIROSDB;
  else {
    ERROR("write_http plugin: Invalid format string: %s", string);
    return -1;
  }

  return 0;
}