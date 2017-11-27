static lt_module
vm_open (lt_user_data LT__UNUSED loader_data, const char *filename,
         lt_dladvise advise)
{
  int		module_flags = LT_LAZY_OR_NOW;
  lt_module	module;

  if (advise)
    {
#ifdef RTLD_GLOBAL
      /* If there is some means of asking for global symbol resolution,
         do so.  */
      if (advise->is_symglobal)
        module_flags |= RTLD_GLOBAL;
#else
      /* Otherwise, reset that bit so the caller can tell it wasn't
         acted on.  */
      advise->is_symglobal = 0;
#endif

/* And similarly for local only symbol resolution.  */
#ifdef RTLD_LOCAL
      if (advise->is_symlocal)
        module_flags |= RTLD_LOCAL;
#else
      advise->is_symlocal = 0;
#endif
    }

  module = dlopen (filename, module_flags);

  if (!module)
    {
      DL__SETERROR (CANNOT_OPEN);
    }

  return module;
}