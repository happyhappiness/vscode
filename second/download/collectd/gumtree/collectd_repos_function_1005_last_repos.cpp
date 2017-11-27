static void _plugin_unregister_generic(pTHX, perl_unregister_function_t *unreg,
                                       const char *desc) {
  dXSARGS;

  if (1 != items) {
    log_err("Usage: Collectd::plugin_unregister_%s(pluginname)", desc);
    XSRETURN_EMPTY;
  }

  if (!SvOK(ST(0))) {
    log_err("Collectd::plugin_unregister_%s(pluginname): "
            "Invalid pluginname",
            desc);
    XSRETURN_EMPTY;
  }

  log_debug("Collectd::plugin_unregister_%s: plugin = \"%s\"", desc,
            SvPV_nolen(ST(0)));

  unreg(SvPV_nolen(ST(0)));

  XSRETURN_EMPTY;

  return;
}