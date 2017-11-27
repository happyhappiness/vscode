static int cx_config_add_values(const char *name, cx_xpath_t *xpath, /* {{{ */
                                oconfig_item_t *ci) {
  if (ci->values_num < 1) {
    WARNING("curl_xml plugin: `ValuesFrom' needs at least one argument.");
    return -1;
  }

  for (int i = 0; i < ci->values_num; i++)
    if (ci->values[i].type != OCONFIG_TYPE_STRING) {
      WARNING("curl_xml plugin: `ValuesFrom' needs only string argument.");
      return -1;
    }

  sfree(xpath->values);

  xpath->values_len = 0;
  xpath->values = malloc(sizeof(cx_values_t) * ci->values_num);
  if (xpath->values == NULL)
    return -1;
  xpath->values_len = (size_t)ci->values_num;

  /* populate cx_values_t structure */
  for (int i = 0; i < ci->values_num; i++) {
    xpath->values[i].path_len = sizeof(ci->values[i].value.string);
    sstrncpy(xpath->values[i].path, ci->values[i].value.string,
             sizeof(xpath->values[i].path));
  }

  return 0;
}