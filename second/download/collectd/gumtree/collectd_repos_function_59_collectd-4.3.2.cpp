static int
argzize_path (path, pargz, pargz_len)
     const char *path;
     char **pargz;
     size_t *pargz_len;
{
  error_t error;

  assert (path);
  assert (pargz);
  assert (pargz_len);

  if ((error = argz_create_sep (path, LT_PATHSEP_CHAR, pargz, pargz_len)))
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