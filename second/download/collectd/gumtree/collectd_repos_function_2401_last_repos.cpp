static int cj_config(oconfig_item_t *ci) /* {{{ */
{
  int success;
  int errors;
  int status;

  success = 0;
  errors = 0;

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Sock", child->key) == 0 ||
        strcasecmp("URL", child->key) == 0) {
      status = cj_config_add_url(child);
      if (status == 0)
        success++;
      else
        errors++;
    } else {
      WARNING("curl_json plugin: Option `%s' not allowed here.", child->key);
      errors++;
    }
  }

  if ((success == 0) && (errors > 0)) {
    ERROR("curl_json plugin: All statements failed.");
    return -1;
  }

  return 0;
}