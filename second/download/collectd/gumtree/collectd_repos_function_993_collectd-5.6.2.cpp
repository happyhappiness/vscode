static int g_pv_get(pTHX_ SV *var, MAGIC *mg) {
  char *pv = mg->mg_ptr;
  sv_setpv(var, pv);
  return 0;
}