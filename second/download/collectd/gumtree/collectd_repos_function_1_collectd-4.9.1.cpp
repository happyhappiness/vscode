error_t
argz_create_sep (const char *str, int delim, char **pargz, size_t *pargz_len)
{
  size_t argz_len;
  char *argz = 0;

  assert (str);
  assert (pargz);
  assert (pargz_len);

  /* Make a copy of STR, but replacing each occurrence of
     DELIM with '\0'.  */
  argz_len = 1+ strlen (str);
  if (argz_len)
    {
      const char *p;
      char *q;

      argz = (char *) malloc (argz_len);
      if (!argz)
	return ENOMEM;

      for (p = str, q = argz; *p != EOS_CHAR; ++p)
	{
	  if (*p == delim)
	    {
	      /* Ignore leading delimiters, and fold consecutive
		 delimiters in STR into a single '\0' in ARGZ.  */
	      if ((q > argz) && (q[-1] != EOS_CHAR))
		*q++ = EOS_CHAR;
	      else
		--argz_len;
	    }
	  else
	    *q++ = *p;
	}
      /* Copy terminating EOS_CHAR.  */
      *q = *p;
    }

  /* If ARGZ_LEN has shrunk to nothing, release ARGZ's memory.  */
  if (!argz_len)
    argz = (free (argz), (char *) 0);

  /* Assign new values.  */
  *pargz = argz;
  *pargz_len = argz_len;

  return 0;
}