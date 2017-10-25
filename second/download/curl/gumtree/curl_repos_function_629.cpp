static dynafunc DynaGetFunction(const char *name)
{
  dynafunc func = (dynafunc)NULL;

#if defined(HAVE_DLOPEN) || defined(HAVE_LIBDL)
  if (libldap) {
    /* This typecast magic below was brought by Joe Halpin. In ISO C, you
     * cannot typecast a data pointer to a function pointer, but that's
     * exactly what we need to do here to avoid compiler warnings on picky
     * compilers! */
    *(void**) (&func) = dlsym(libldap, name);
  }
#elif defined(WIN32)
  if (libldap) {
    func = (dynafunc)GetProcAddress((HINSTANCE)libldap, name);
  }
#else
  (void) name;
#endif
  return func;
}