static int DynaOpen(const char **mod_name)
{
#if defined(HAVE_DLOPEN) || defined(HAVE_LIBDL)
  if (libldap == NULL) {
    /*
     * libldap.so can normally resolve its dependency on liblber.so
     * automatically, but in broken installation it does not so
     * handle it here by opening liblber.so as global.
     */
#ifdef DL_LBER_FILE
    *mod_name = DL_LBER_FILE;
    liblber = dlopen(*mod_name, DLOPEN_MODE);
    if (!liblber)
      return 0;
#endif

    /* Assume loading libldap.so will fail if loading of liblber.so failed
     */
    *mod_name = DL_LDAP_FILE;
    libldap = dlopen(*mod_name, RTLD_LAZY);
  }
  return (libldap != NULL);

#elif defined(WIN32)
  *mod_name = DL_LDAP_FILE;
  if (!libldap)
    libldap = (void*)LoadLibrary(*mod_name);
  return (libldap != NULL);

#else
  (void) mod_name;
  return (0);
#endif
}