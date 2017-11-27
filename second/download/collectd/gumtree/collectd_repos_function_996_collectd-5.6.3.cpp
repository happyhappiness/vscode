static int g_interval_set(pTHX_ SV *var, MAGIC *mg) {
  double nv = (double)SvNV(var);
  log_warn("Accessing $interval_g is deprecated (and might not "
           "give the desired results) - plugin_get_interval() should "
           "be used instead.");
  interval_g = DOUBLE_TO_CDTIME_T(nv);
  return 0;
}