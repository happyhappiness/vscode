static int varnish_config_instance(const oconfig_item_t *ci) /* {{{ */
{
  user_config_t *conf;
  user_data_t ud;
  char callback_name[DATA_MAX_NAME_LEN];

  conf = calloc(1, sizeof(*conf));
  if (conf == NULL)
    return (ENOMEM);
  conf->instance = NULL;

  varnish_config_apply_default(conf);

  if (ci->values_num == 1) {
    int status;

    status = cf_util_get_string(ci, &conf->instance);
    if (status != 0) {
      sfree(conf);
      return (status);
    }
    assert(conf->instance != NULL);

    if (strcmp("localhost", conf->instance) == 0) {
      sfree(conf->instance);
      conf->instance = NULL;
    }
  } else if (ci->values_num > 1) {
    WARNING("Varnish plugin: \"Instance\" blocks accept only "
            "one argument.");
    sfree(conf);
    return (EINVAL);
  }

  for (int i = 0; i < ci->children_num; i++) {
    oconfig_item_t *child = ci->children + i;

    if (strcasecmp("CollectCache", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_cache);
    else if (strcasecmp("CollectConnections", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_connections);
    else if (strcasecmp("CollectESI", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_esi);
    else if (strcasecmp("CollectDirectorDNS", child->key) == 0)
#ifdef HAVE_VARNISH_V3
      cf_util_get_boolean(child, &conf->collect_dirdns);
#else
      WARNING("Varnish plugin: \"%s\" is available for Varnish %s only.",
              child->key, "v3");
#endif
    else if (strcasecmp("CollectBackend", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_backend);
    else if (strcasecmp("CollectFetch", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_fetch);
    else if (strcasecmp("CollectHCB", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_hcb);
    else if (strcasecmp("CollectObjects", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_objects);
    else if (strcasecmp("CollectPurge", child->key) == 0)
#if HAVE_VARNISH_V2
      cf_util_get_boolean(child, &conf->collect_purge);
#else
      WARNING("Varnish plugin: \"%s\" is available for Varnish %s only.",
              child->key, "v2");
#endif
    else if (strcasecmp("CollectBan", child->key) == 0)
#if HAVE_VARNISH_V2
      WARNING("Varnish plugin: \"%s\" is not available for Varnish %s.",
              child->key, "v2");
#else
      cf_util_get_boolean(child, &conf->collect_ban);
#endif
    else if (strcasecmp("CollectSession", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_session);
    else if (strcasecmp("CollectSHM", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_shm);
    else if (strcasecmp("CollectSMS", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_sms);
    else if (strcasecmp("CollectSMA", child->key) == 0)
#if HAVE_VARNISH_V2
      cf_util_get_boolean(child, &conf->collect_sma);
#else
      WARNING("Varnish plugin: \"%s\" is available for Varnish %s only.",
              child->key, "v2");
#endif
    else if (strcasecmp("CollectSM", child->key) == 0)
#if HAVE_VARNISH_V2
      cf_util_get_boolean(child, &conf->collect_sm);
#else
      WARNING("Varnish plugin: \"%s\" is available for Varnish %s only.",
              child->key, "v2");
#endif
    else if (strcasecmp("CollectStruct", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_struct);
    else if (strcasecmp("CollectTotals", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_totals);
    else if (strcasecmp("CollectUptime", child->key) == 0)
#if HAVE_VARNISH_V3 || HAVE_VARNISH_V4
      cf_util_get_boolean(child, &conf->collect_uptime);
#else
      WARNING("Varnish plugin: \"%s\" is available for Varnish %s only.",
              child->key, "v3 and v4");
#endif
    else if (strcasecmp("CollectVCL", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_vcl);
    else if (strcasecmp("CollectWorkers", child->key) == 0)
      cf_util_get_boolean(child, &conf->collect_workers);
    else if (strcasecmp("CollectVSM", child->key) == 0)
#if HAVE_VARNISH_V4
      cf_util_get_boolean(child, &conf->collect_vsm);
#else
      WARNING("Varnish plugin: \"%s\" is available for Varnish %s only.",
              child->key, "v4");
#endif
    else {
      WARNING("Varnish plugin: Ignoring unknown "
              "configuration option: \"%s\". Did "
              "you forget to add an <Instance /> "
              "block around the configuration?",
              child->key);
    }
  }

  if (!conf->collect_cache && !conf->collect_connections &&
      !conf->collect_esi && !conf->collect_backend
#ifdef HAVE_VARNISH_V3
      && !conf->collect_dirdns
#endif
      && !conf->collect_fetch && !conf->collect_hcb && !conf->collect_objects
#if HAVE_VARNISH_V2
      && !conf->collect_purge
#else
      && !conf->collect_ban
#endif
      && !conf->collect_session && !conf->collect_shm && !conf->collect_sms
#if HAVE_VARNISH_V2
      && !conf->collect_sma && !conf->collect_sm
#endif
      && !conf->collect_struct && !conf->collect_totals
#if HAVE_VARNISH_V3 || HAVE_VARNISH_V4
      && !conf->collect_uptime
#endif
      && !conf->collect_vcl && !conf->collect_workers
#if HAVE_VARNISH_V4
      && !conf->collect_vsm
#endif
      ) {
    WARNING("Varnish plugin: No metric has been configured for "
            "instance \"%s\". Disabling this instance.",
            (conf->instance == NULL) ? "localhost" : conf->instance);
    sfree(conf);
    return (EINVAL);
  }

  ssnprintf(callback_name, sizeof(callback_name), "varnish/%s",
            (conf->instance == NULL) ? "localhost" : conf->instance);

  ud.data = conf;
  ud.free_func = varnish_config_free;

  plugin_register_complex_read(/* group = */ "varnish",
                               /* name      = */ callback_name,
                               /* callback  = */ varnish_read,
                               /* interval  = */ 0,
                               /* user data = */ &ud);

  have_instance = 1;

  return (0);
}