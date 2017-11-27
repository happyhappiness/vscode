static int perl_config(oconfig_item_t *ci) {
  int status = 0;

  dTHXa(NULL);

  for (int i = 0; i < ci->children_num; ++i) {
    oconfig_item_t *c = ci->children + i;
    int current_status = 0;

    if (NULL != perl_threads) {
      if ((aTHX = PERL_GET_CONTEXT) == NULL)
        return -1;
    }

    if (0 == strcasecmp(c->key, "LoadPlugin"))
      current_status = perl_config_loadplugin(aTHX_ c);
    else if (0 == strcasecmp(c->key, "BaseName"))
      current_status = perl_config_basename(aTHX_ c);
    else if (0 == strcasecmp(c->key, "EnableDebugger"))
      current_status = perl_config_enabledebugger(aTHX_ c);
    else if (0 == strcasecmp(c->key, "IncludeDir"))
      current_status = perl_config_includedir(aTHX_ c);
    else if (0 == strcasecmp(c->key, "Plugin"))
      current_status = perl_config_plugin(aTHX_ c);
    else if (0 == strcasecmp(c->key, "RegisterLegacyFlush"))
      cf_util_get_boolean(c, &register_legacy_flush);
    else {
      log_warn("Ignoring unknown config key \"%s\".", c->key);
      current_status = 0;
    }

    /* fatal error - it's up to perl_config_* to clean up */
    if (0 > current_status) {
      log_err("Configuration failed with a fatal error - "
              "plugin disabled!");
      return current_status;
    }

    status += current_status;
  }
  return status;
}