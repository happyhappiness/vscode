lt_dlhandle
lt_dlopenext (filename)
     const char *filename;
{
  lt_dlhandle	handle		= 0;
  char *	tmp		= 0;
  char *	ext		= 0;
  size_t	len;
  int		errors		= 0;

  if (!filename)
    {
      return lt_dlopen (filename);
    }

  assert (filename);

  len = LT_STRLEN (filename);
  ext = strrchr (filename, '.');

  /* If FILENAME already bears a suitable extension, there is no need
     to try appending additional extensions.  */
  if (ext && ((strcmp (ext, archive_ext) == 0)
#ifdef LTDL_SHLIB_EXT
	      || (strcmp (ext, shlib_ext) == 0)
#endif
      ))
    {
      return lt_dlopen (filename);
    }

  /* First try appending ARCHIVE_EXT.  */
  tmp = LT_EMALLOC (char, len + LT_STRLEN (archive_ext) + 1);
  if (!tmp)
    return 0;

  strcpy (tmp, filename);
  strcat (tmp, archive_ext);
  errors = try_dlopen (&handle, tmp);

  /* If we found FILENAME, stop searching -- whether we were able to
     load the file as a module or not.  If the file exists but loading
     failed, it is better to return an error message here than to
     report FILE_NOT_FOUND when the alternatives (foo.so etc) are not
     in the module search path.  */
  if (handle || ((errors > 0) && !file_not_found ()))
    {
      LT_DLFREE (tmp);
      return handle;
    }

#ifdef LTDL_SHLIB_EXT
  /* Try appending SHLIB_EXT.   */
  if (LT_STRLEN (shlib_ext) > LT_STRLEN (archive_ext))
    {
      LT_DLFREE (tmp);
      tmp = LT_EMALLOC (char, len + LT_STRLEN (shlib_ext) + 1);
      if (!tmp)
	return 0;

      strcpy (tmp, filename);
    }
  else
    {
      tmp[len] = LT_EOS_CHAR;
    }

  strcat(tmp, shlib_ext);
  errors = try_dlopen (&handle, tmp);

  /* As before, if the file was found but loading failed, return now
     with the current error message.  */
  if (handle || ((errors > 0) && !file_not_found ()))
    {
      LT_DLFREE (tmp);
      return handle;
    }
#endif

  /* Still here?  Then we really did fail to locate any of the file
     names we tried.  */
  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (FILE_NOT_FOUND));
  LT_DLFREE (tmp);
  return 0;
}