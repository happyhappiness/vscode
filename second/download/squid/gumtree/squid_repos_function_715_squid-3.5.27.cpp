static lt_module
vm_open (lt_user_data loader_data LT__UNUSED, const char *filename,
         lt_dladvise advise)
{
  int		module_flags = LT_LAZY_OR_NOW;
  lt_module	module;
#ifdef RTLD_MEMBER
  int		len = LT_STRLEN (filename);
#endif

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

#ifdef RTLD_MEMBER /* AIX */
  if (len >= 4) /* at least "l(m)" */
    {
      /* Advise loading an archive member only if the filename really
	 contains both the opening and closing parent, and a member. */
      if (filename[len-1] == ')')
	{
	  const char *opening = strrchr(filename, '(');
	  if (opening && opening < (filename+len-2) && strchr(opening+1, '/') == NULL)
	    module_flags |= RTLD_MEMBER;
	}
    }
#endif

  module = dlopen (filename, module_flags);

#if defined RTLD_MEMBER && defined LT_SHARED_LIB_MEMBER
  if (!module && len && !(module_flags & RTLD_MEMBER) && errno == ENOEXEC)
    {
      /* Loading without a member specified failed with "Exec format error".
	 So the file is there, but either has wrong bitwidth, or is an
	 archive eventually containing the default shared archive member.
	 Retry with default member, getting same error in worst case. */
      const char *member = LT_SHARED_LIB_MEMBER;

      char *attempt = MALLOC (char, len + strlen (member) + 1);
      if (!attempt)
	{
	  LT__SETERROR (NO_MEMORY);
	  return module;
	}

      sprintf (attempt, "%s%s", filename, member);
      module = vm_open (loader_data, attempt, advise);
      FREE (attempt);
      return module;
    }
#endif

  if (!module)
    {
      DL__SETERROR (CANNOT_OPEN);
    }

  return module;
}