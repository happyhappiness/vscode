static int
lt_argz_insert (pargz, pargz_len, before, entry)
     char **pargz;
     size_t *pargz_len;
     char *before;
     const char *entry;
{
  error_t error;

  /* Prior to Sep 8, 2005, newlib had a bug where argz_insert(pargz,
     pargz_len, NULL, entry) failed with EINVAL.  */
  if (before)
    error = argz_insert (pargz, pargz_len, before, entry);
  else
    error = argz_append (pargz, pargz_len, entry, 1 + LT_STRLEN (entry));

  if (error)
    {
      switch (error)
	{
	case ENOMEM:
	  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (NO_MEMORY));
	  break;
	default:
	  LT_DLMUTEX_SETERROR (LT_DLSTRERROR (UNKNOWN));
	  break;
	}
      return 1;
    }

  return 0;
}