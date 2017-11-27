static int cj_config_add_url(oconfig_item_t *ci) /* {{{ */
{
  cj_t *db;
  int status = 0;

  if ((ci->values_num != 1) || (ci->values[0].type != OCONFIG_TYPE_STRING)) {
    WARNING("curl_json plugin: The `URL' block "
            "needs exactly one string argument.");
    return (-1);
  }

  db = calloc(1, sizeof(*db));
  if (db == NULL) {
    ERROR("curl_json plugin: calloc failed.");
    return (-1);
  }

  db->timeout = -1;

  if (strcasecmp("URL", ci->key) == 0)
    status = cf_util_get_string(ci, &db->url);
  else if (strcasecmp("Sock", ci->key) == 0)
    status = cf_util_get_string(ci, &db->sock);
  else {
    ERROR("curl_json plugin: cj_config: "
          "Invalid key: %s",
          ci->key);
    cj_free(db);
    return (-1);
  }
  if (status != 0) {
    sfree(db);
    return (status);
  }

  /* Fill the `cj_t' structure.. */
  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("Instance", child->key) == 0)
      status = cf_util_get_string(child, &db->instance);
    else if (strcasecmp("Host", child->key) == 0)
      status = cf_util_get_string(child, &db->host);
    else if (db->url && strcasecmp("User", child->key) == 0)
      status = cf_util_get_string(child, &db->user);
    else if (db->url && strcasecmp("Password", child->key) == 0)
      status = cf_util_get_string(child, &db->pass);
    else if (strcasecmp("Digest", child->key) == 0)
      status = cf_util_get_boolean(child, &db->digest);
    else if (db->url && strcasecmp("VerifyPeer", child->key) == 0)
      status = cf_util_get_boolean(child, &db->verify_peer);
    else if (db->url && strcasecmp("VerifyHost", child->key) == 0)
      status = cf_util_get_boolean(child, &db->verify_host);
    else if (db->url && strcasecmp("CACert", child->key) == 0)
      status = cf_util_get_string(child, &db->cacert);
    else if (db->url && strcasecmp("Header", child->key) == 0)
      status = cj_config_append_string("Header", &db->headers, child);
    else if (db->url && strcasecmp("Post", child->key) == 0)
      status = cf_util_get_string(child, &db->post_body);
    else if (strcasecmp("Key", child->key) == 0)
      status = cj_config_add_key(db, child);
    else if (strcasecmp("Interval", child->key) == 0)
      status = cf_util_get_cdtime(child, &db->interval);
    else if (strcasecmp("Timeout", child->key) == 0)
      status = cf_util_get_int(child, &db->timeout);
    else if (strcasecmp("Statistics", child->key) == 0) {
      db->stats = curl_stats_from_config(child);
      if (db->stats == NULL)
        status = -1;
    } else {
      WARNING("curl_json plugin: Option `%s' not allowed here.", child->key);
      status = -1;
    }

    if (status != 0)
      break;
  }

  if (status == 0) {
    if (db->tree == NULL) {
      WARNING("curl_json plugin: No (valid) `Key' block within `%s' \"`%s'\".",
              db->url ? "URL" : "Sock", db->url ? db->url : db->sock);
      status = -1;
    }
    if (status == 0 && db->url)
      status = cj_init_curl(db);
  }

  /* If all went well, register this database for reading */
  if (status == 0) {
    char *cb_name;

    if (db->instance == NULL)
      db->instance = strdup("default");

    DEBUG("curl_json plugin: Registering new read callback: %s", db->instance);

    cb_name = ssnprintf_alloc("curl_json-%s-%s", db->instance,
                              db->url ? db->url : db->sock);

    user_data_t ud = {.data = db, .free_func = cj_free};

    plugin_register_complex_read(/* group = */ NULL, cb_name, cj_read,
                                 /* interval = */ db->interval, &ud);
    sfree(cb_name);
  } else {
    cj_free(db);
    return (-1);
  }

  return (0);
}