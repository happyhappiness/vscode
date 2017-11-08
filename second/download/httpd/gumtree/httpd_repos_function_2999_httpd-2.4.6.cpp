static const char *am_allowmethods(cmd_parms *cmd, void *d, int argc, char *const argv[])
{
  int i;
  am_conf_t* conf = (am_conf_t*) d;
  if (argc == 0) {
      return "AllowMethods: No method or 'reset' keyword given";
  }
  if (argc == 1) {
    if (strcasecmp("reset", argv[0]) == 0) {
      conf->allowed = 0;
      conf->allowed_set = 1;
      return NULL;
    }
  }

  for (i = 0; i < argc; i++) {
    int m = 0;
    m = ap_method_number_of(argv[i]);
    if (m == M_INVALID) {
      return apr_pstrcat(cmd->pool, "AllowMethods: Invalid Method '", argv[i], "'", NULL);
    }

    conf->allowed |= (AP_METHOD_BIT << m);
  }
  conf->allowed_set = 1;
  return NULL;
}