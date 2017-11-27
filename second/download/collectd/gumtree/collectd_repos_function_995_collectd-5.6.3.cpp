static int g_interval_get(pTHX_ SV *var, MAGIC *mg) {
  log_warn("Accessing $interval_g is deprecated (and might not "
           "give the desired results) - plugin_get_interval() should "
           "be used instead.");
  sv_setnv(var, CDTIME_T_TO_DOUBLE(interval_g));
  return 0;
}