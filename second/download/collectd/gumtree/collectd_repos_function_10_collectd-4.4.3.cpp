static error_t
argz_create_sep (str, delim, pargz, pargz_len)
     const char *str;
     int delim;
     char **pargz;
     size_t *pargz_len;
{
  size_t argz_len;
  char *argz = 0;

  assert (str);
  assert (pargz);
  assert (pargz_len);

  /* Make a copy of STR, but replacing each occurrence of
     DELIM with '\0'.  */
  argz_len = 1+ LT_STRLEN (str);
  if (argz_len)
    {
      const char *p;
      char *q;

      argz = LT_DLMALLOC (char, argz_len);
      if (!argz)
	return ENOMEM;

      for (p = str, q = argz; *p != LT_EOS_CHAR; ++p)
	{
	  if (*p == delim)
	    {
	      /* Ignore leading delimiters, and fold consecutive
		 delimiters in STR into a single '\0' in ARGZ.  */
	      if ((q > argz) && (q[-1] != LT_EOS_CHAR))
		*q++ = LT_EOS_CHAR;
	      else
		--argz_len;
	    }
	  else
	    *q++ = *p;
	}
      /* Copy terminating LT_EOS_CHAR.  */
      *q = *p;
    }

  /* If ARGZ_LEN has shrunk to nothing, release ARGZ's memory.  */
  if (!argz_len)
    LT_DLFREE (argz);

  /* Assign new values.  */
  *pargz = argz;
  *pargz_len = argz_len;

  return 0;
}