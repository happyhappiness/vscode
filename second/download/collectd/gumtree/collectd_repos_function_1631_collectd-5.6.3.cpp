static int cx_config_add_url(oconfig_item_t *ci) /* {{{ */
{
  cx_t *db;
  int status = 0;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("curl_xml plugin: The `URL' block "
            "needs exactly one string argument.");
    return (-1);
  }

  db = calloc(1, sizeof(*db));
  if (db == NULL) {
    ERROR("curl_xml plugin: calloc failed.");
    return (-1);
  }

  db->timeout = -1;

  if (strcasecmp("URL", ci->key) == 0) {
    status = cf_util_get_string(ci, &db->url);
    if (status != 0) {
      sfree(db);
      return (status);
    }
  } else {
    ERROR("curl_xml plugin: cx_config: "
          "Invalid key: %s",
          ci->key);
    cx_free(db);
    return (-1);
  }

  /* Fill the `cx_t' structure.. */
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Instance", child->key) == 0)
      status = cf_util_get_string(child, &db->instance);
    else if (strcasecmp("Host", child->key) == 0)
      status = cf_util_get_string(child, &db->host);
    else if (strcasecmp("User", child->key) == 0)
      status = cf_util_get_string(child, &db->user);
    else if (strcasecmp("Password", child->key) == 0)
      status = cf_util_get_string(child, &db->pass);
    else if (strcasecmp("Digest", child->key) == 0)
      status = cf_util_get_boolean(child, &db->digest);
    else if (strcasecmp("VerifyPeer", child->key) == 0)
      status = cf_util_get_boolean(child, &db->verify_peer);
    else if (strcasecmp("VerifyHost", child->key) == 0)
      status = cf_util_get_boolean(child, &db->verify_host);
    else if (strcasecmp("CACert", child->key) == 0)
      status = cf_util_get_string(child, &db->cacert);
    else if (strcasecmp("xpath", child->key) == 0)
      status = cx_config_add_xpath(db, child);
    else if (strcasecmp("Header", child->key) == 0)
      status = cx_config_append_string("Header", &db->headers, child);
    else if (strcasecmp("Post", child->key) == 0)
      status = cf_util_get_string(child, &db->post_body);
    else if (strcasecmp("Namespace", child->key) == 0)
      status = cx_config_add_namespace(db, child);
    else if (strcasecmp("Timeout", child->key) == 0)
      status = cf_util_get_int(child, &db->timeout);
    else if (strcasecmp("Statistics", child->key) == 0) {
      db->stats = curl_stats_from_config(child);
      if (db->stats == NULL)
        status = -1;
    } else {
      WARNING("curl_xml plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  if (status == 0) {
    if (db->list == NULL) {
      WARNING("curl_xml plugin: No (valid) `Key' block "
              "within `URL' block `%s'.",
              db->url);
      status = -1;
    }
    if (status == 0)
      status = cx_init_curl(db);
  }

  /* If all went well, register this database for reading */
  if (status == 0) {
    char *cb_name;

    if (db->instance == NULL)
      db->instance = strdup("default");

    DEBUG("curl_xml plugin: Registering new read callback: %s", db->instance);

    cb_name = ssnprintf_alloc("curl_xml-%s-%s", db->instance, db->url);

    user_data_t ud = {.data = db, .free_func = cx_free};

    plugin_register_complex_read(/* group = */ "curl_xml", cb_name, cx_read,
                                 /* interval = */ 0, &ud);
    sfree(cb_name);
  } else {
    cx_free(db);
    return (-1);
  }

  return (0);
}