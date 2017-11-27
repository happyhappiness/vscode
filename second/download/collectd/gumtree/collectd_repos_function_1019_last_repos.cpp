static int perl_config_loadplugin(pTHX_ oconfig_item_t *ci) {
  char module_name[DATA_MAX_NAME_LEN];

  char *value = NULL;

  if ((0 != ci->children_num) || (1 != ci->values_num) ||
      (OCONFIG_TYPE_STRING != ci->values[0].type)) {
    log_err("LoadPlugin expects a single string argument.");
    return 1;
  }

  value = ci->values[0].value.string;

  if (NULL == get_module_name(module_name, sizeof(module_name), value)) {
    log_err("Invalid module name %s", value);
    return 1;
  }

  if (0 != init_pi(perl_argc, perl_argv))
    return -1;

  assert(NULL != perl_threads);
  assert(NULL != perl_threads->head);

  aTHX = perl_threads->head->interp;

  log_debug("perl_config: Loading Perl plugin \"%s\"", value);
  load_module(PERL_LOADMOD_NOIMPORT, newSVpv(module_name, strlen(module_name)),
              Nullsv);
  return 0;
}