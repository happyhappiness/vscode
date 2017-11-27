static int cj_config_add_key(cj_t *db, /* {{{ */
                             oconfig_item_t *ci) {
  cj_key_t *key;
  int status;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("curl_json plugin: The `Key' block "
            "needs exactly one string argument.");
    return -1;
  }

  key = calloc(1, sizeof(*key));
  if (key == NULL) {
    ERROR("curl_json plugin: calloc failed.");
    return -1;
  }

  if (strcasecmp("Key", ci->key) == 0) {
    status = cf_util_get_string(ci, &key->path);
    if (status != 0) {
      sfree(key);
      return status;
    }
  } else {
    ERROR("curl_json plugin: cj_config: "
          "Invalid key: %s",
          ci->key);
    cj_key_free(key);
    return -1;
  }

  status = 0;
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Type", child->key) == 0)
      status = cf_util_get_string(child, &key->type);
    else if (strcasecmp("Instance", child->key) == 0)
      status = cf_util_get_string(child, &key->instance);
    else {
      WARNING("curl_json plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  } /* for (i = 0; i < ci->children_num; i++) */

  if (status != 0) {
    cj_key_free(key);
    return -1;
  }

  if (key->type == NULL) {
    WARNING("curl_json plugin: `Type' missing in `Key' block.");
    cj_key_free(key);
    return -1;
  }

  status = cj_append_key(db, key);
  if (status != 0) {
    cj_key_free(key);
    return -1;
  }

  return 0;
}