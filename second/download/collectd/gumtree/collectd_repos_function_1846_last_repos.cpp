static int cx_config(oconfig_item_t *ci) /* {{{ */
{
  int success = 0;
  int errors = 0;

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("URL", child->key) == 0) {
      if (cx_config_add_url(child) == 0)
        success++;
      else
        errors++;
    } else {
      WARNING("curl_xml plugin: Option `%s' not allowed here.", child->key);
      errors++;
    }
  }

  if ((success == 0) && (errors > 0)) {
    ERROR("curl_xml plugin: All statements failed.");
    return -1;
  }

  return 0;
}