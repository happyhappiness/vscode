static void DynaClose(void)
{
#if defined(HAVE_DLOPEN) || defined(HAVE_LIBDL)
  if (libldap) {
    dlclose(libldap);
  }
  if (liblber) {
    dlclose(liblber);
  }
#endif
}