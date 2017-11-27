static void xs_init(pTHX) {
  HV *stash = NULL;
  SV *tmp = NULL;
  char *file = __FILE__;

  dXSUB_SYS;

  /* enable usage of Perl modules using shared libraries */
  newXS("DynaLoader::boot_DynaLoader", boot_DynaLoader, file);

  /* register API */
  for (int i = 0; NULL != api[i].f; ++i)
    newXS(api[i].name, api[i].f, file);

  stash = gv_stashpv("Collectd", 1);

  /* export "constants" */
  for (int i = 0; '\0' != constants[i].name[0]; ++i)
    newCONSTSUB(stash, constants[i].name, newSViv(constants[i].value));

  /* export global variables
   * by adding "magic" to the SV's representing the globale variables
   * perl is able to automagically call the get/set function when
   * accessing any such variable (this is basically the same as using
   * tie() in Perl) */
  /* global strings */
  struct {
    char name[64];
    char *var;
  } g_strings[] = {{"Collectd::hostname_g", hostname_g}, {"", NULL}};

  for (int i = 0; '\0' != g_strings[i].name[0]; ++i) {
    tmp = get_sv(g_strings[i].name, 1);
    sv_magicext(tmp, NULL, PERL_MAGIC_ext, &g_pv_vtbl, g_strings[i].var, 0);
  }

  tmp = get_sv("Collectd::interval_g", /* create = */ 1);
  sv_magicext(tmp, NULL, /* how = */ PERL_MAGIC_ext,
              /* vtbl = */ &g_interval_vtbl,
              /* name = */ NULL, /* namelen = */ 0);

  return;
}