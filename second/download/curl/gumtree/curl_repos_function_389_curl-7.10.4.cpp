static void DynaOpen(void)
{
#if defined(HAVE_DLOPEN) || defined(HAVE_LIBDL)
  if (libldap == NULL) {
    /*
     * libldap.so should be able to resolve its dependency on
     * liblber.so automatically, but since it does not we will
     * handle it here by opening liblber.so as global.
     */
    dlopen("liblber.so",
#ifdef RTLD_LAZY_GLOBAL /* It turns out some systems use this: */
           RTLD_LAZY_GLOBAL
#else
#ifdef RTLD_GLOBAL
           RTLD_LAZY | RTLD_GLOBAL
#else
           /* and some systems don't have the RTLD_GLOBAL symbol */
           RTLD_LAZY
#endif
#endif
           );
    libldap = dlopen("libldap.so", RTLD_LAZY);
  }
#endif
}