static int cx_config_add_xpath(cx_t *db, oconfig_item_t *ci) /* {{{ */
{
  cx_xpath_t *xpath = calloc(1, sizeof(*xpath));
  if (xpath == NULL) {
    ERROR("curl_xml plugin: calloc failed.");
    return -1;
  }

  int status = cf_util_get_string(ci, &xpath->path);
  if (status != 0) {
    cx_xpath_free(xpath);
    return status;
  }

  /* error out if xpath->path is an empty string */
  if (strlen(xpath->path) == 0) {
    ERROR("curl_xml plugin: invalid xpath. "
          "xpath value can't be an empty string");
    cx_xpath_free(xpath);
    return -1;
  }

  status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Type", child->key) == 0)
      status = cf_util_get_string(child, &xpath->type);
    else if (strcasecmp("InstancePrefix", child->key) == 0)
      status = cf_util_get_string(child, &xpath->instance_prefix);
    else if (strcasecmp("InstanceFrom", child->key) == 0)
      status = cf_util_get_string(child, &xpath->instance);
    else if (strcasecmp("PluginInstanceFrom", child->key) == 0)
      status = cf_util_get_string(child, &xpath->plugin_instance_from);
    else if (strcasecmp("ValuesFrom", child->key) == 0)
      status = cx_config_add_values("ValuesFrom", xpath, child);
    else {
      WARNING("curl_xml plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  if (status != 0) {
    cx_xpath_free(xpath);
    return status;
  }

  if (xpath->type == NULL) {
    WARNING("curl_xml plugin: `Type' missing in `xpath' block.");
    cx_xpath_free(xpath);
    return -1;
  }

  if (xpath->values_len == 0) {
    WARNING("curl_xml plugin: `ValuesFrom' missing in `xpath' block.");
    cx_xpath_free(xpath);
    return -1;
  }

  llentry_t *le = llentry_create(xpath->path, xpath);
  if (le == NULL) {
    ERROR("curl_xml plugin: llentry_create failed.");
    cx_xpath_free(xpath);
    return -1;
  }

  llist_append(db->xpath_list, le);
  return 0;
}