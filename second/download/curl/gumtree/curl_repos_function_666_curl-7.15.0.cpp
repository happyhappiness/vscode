static void DynaClose(void)
{
#if defined(HAVE_DLOPEN) || defined(HAVE_LIBDL)
  if (libldap) {
    dlclose(libldap);
    libldap=NULL;
  }
#ifdef DL_LBER_FILE
  if (liblber) {
    dlclose(liblber);
    liblber=NULL;
  }
#endif
#elif defined(WIN32)
  if (libldap) {
    FreeLibrary ((HMODULE)libldap);
    libldap = NULL;
  }
#endif
}