static const char *
internal_function
guess_category_value (category, categoryname)
     int category;
     const char *categoryname;
{
  const char *language;
  const char *retval;

  /* The highest priority value is the `LANGUAGE' environment
     variable.  But we don't use the value if the currently selected
     locale is the C locale.  This is a GNU extension.  */
  language = getenv ("LANGUAGE");
  if (language != NULL && language[0] == '\0')
    language = NULL;

  /* We have to proceed with the POSIX methods of looking to `LC_ALL',
     `LC_xxx', and `LANG'.  On some systems this can be done by the
     `setlocale' function itself.  */
#if defined _LIBC || (defined HAVE_SETLOCALE && defined HAVE_LC_MESSAGES && defined HAVE_LOCALE_NULL)
  retval = setlocale (category, NULL);
#else
  /* Setting of LC_ALL overwrites all other.  */
  retval = getenv ("LC_ALL");
  if (retval == NULL || retval[0] == '\0')
    {
      /* Next comes the name of the desired category.  */
      retval = getenv (categoryname);
      if (retval == NULL || retval[0] == '\0')
	{
	  /* Last possibility is the LANG environment variable.  */
	  retval = getenv ("LANG");
	  if (retval == NULL || retval[0] == '\0')
	    /* We use C as the default domain.  POSIX says this is
	       implementation defined.  */
	    return "C";
	}
    }
#endif

  return language != NULL && strcmp (retval, "C") != 0 ? language : retval;
}