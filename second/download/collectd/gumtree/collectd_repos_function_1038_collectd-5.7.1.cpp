static void _plugin_register_generic_userdata(pTHX, int type,
                                              const char *desc) {
  int ret = 0;
  user_data_t userdata;
  char *pluginname;

  dXSARGS;

  if (2 != items) {
    log_err("Usage: Collectd::plugin_register_%s(pluginname, subname)", desc);
    XSRETURN_EMPTY;
  }

  if (!SvOK(ST(0))) {
    log_err("Collectd::plugin_register_%s(pluginname, subname): "
            "Invalid pluginname",
            desc);
    XSRETURN_EMPTY;
  }
  if (!SvOK(ST(1))) {
    log_err("Collectd::plugin_register_%s(pluginname, subname): "
            "Invalid subname",
            desc);
    XSRETURN_EMPTY;
  }

  /* Use pluginname as-is to allow flush a single perl plugin */
  pluginname = SvPV_nolen(ST(0));

  log_debug("Collectd::plugin_register_%s: "
            "plugin = \"%s\", sub = \"%s\"",
            desc, pluginname, SvPV_nolen(ST(1)));

  memset(&userdata, 0, sizeof(userdata));
  userdata.data = strdup(SvPV_nolen(ST(1)));
  userdata.free_func = free;

  if (PLUGIN_READ == type) {
    ret = plugin_register_complex_read(
        "perl",                                       /* group */
        pluginname, perl_read, plugin_get_interval(), /* Default interval */
        &userdata);
  } else if (PLUGIN_WRITE == type) {
    ret = plugin_register_write(pluginname, perl_write, &userdata);
  } else if (PLUGIN_LOG == type) {
    ret = plugin_register_log(pluginname, perl_log, &userdata);
  } else if (PLUGIN_NOTIF == type) {
    ret = plugin_register_notification(pluginname, perl_notify, &userdata);
  } else if (PLUGIN_FLUSH == type) {
    if (1 == register_legacy_flush) { /* For collectd-5.7 only, #1731 */
      register_legacy_flush = 0;
      ret = plugin_register_flush("perl", perl_flush, /* user_data = */ NULL);
    }

    if (0 == ret)
      ret = plugin_register_flush(pluginname, perl_flush, &userdata);
  } else {
    ret = -1;
  }

  if (0 == ret)
    XSRETURN_YES;
  else {
    free(userdata.data);
    XSRETURN_EMPTY;
  }
}