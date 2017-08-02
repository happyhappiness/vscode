{
  char *config_string;
  SECMODModule *module = *pmod;
  if(module)
    /* already loaded */
    return CURLE_OK;

  config_string = aprintf("library=%s name=%s", library, name);
  if(!config_string)
    return CURLE_OUT_OF_MEMORY;

  module = SECMOD_LoadUserModule(config_string, NULL, PR_FALSE);
  free(config_string);

  if(module && module->loaded) {
    /* loaded successfully */
    *pmod = module;
    return CURLE_OK;
  }

  if(module)
    SECMOD_DestroyModule(module);
  return CURLE_FAILED_INIT;
}