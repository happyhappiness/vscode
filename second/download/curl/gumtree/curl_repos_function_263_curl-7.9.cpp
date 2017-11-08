static void * DynaGetFunction(const char *name)
{
  void *func = NULL;

#if defined(HAVE_DLOPEN) || defined(HAVE_LIBDL)
  if (libldap) {
    func = dlsym(libldap, name);
  }
#endif
  
  return func;
}