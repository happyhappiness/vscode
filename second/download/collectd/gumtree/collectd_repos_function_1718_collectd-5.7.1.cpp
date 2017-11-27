static int cx_config_append_string(const char *name,
                                   struct curl_slist **dest, /* {{{ */
                                   oconfig_item_t *ci) {
  struct curl_slist *temp = NULL;
  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("curl_xml plugin: `%s' needs exactly one string argument.", name);
    return (-1);
  }

  temp = curl_slist_append(*dest, ci->values[0].value.string);
  if (temp == NULL)
    return (-1);

  *dest = temp;

  return (0);
}