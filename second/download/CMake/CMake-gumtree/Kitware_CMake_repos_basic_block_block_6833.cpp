{
  SECMODModule *module = *pmod;
  if(!module)
    /* not loaded */
    return;

  if(SECMOD_UnloadUserModule(module) != SECSuccess)
    /* unload failed */
    return;

  SECMOD_DestroyModule(module);
  *pmod = NULL;
}