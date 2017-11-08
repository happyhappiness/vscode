static void DynaClose(void)
{
#if defined(HAVE_DLOPEN) || defined(HAVE_LIBDL)
  if (libldap) {
    dlclose(libldap);
    libldap=NULL;
  }
  if (liblber) {
    dlclose(liblber);
    liblber=NULL;
  }
#endif
}