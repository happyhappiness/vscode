int
lt_dlseterror (errindex)
     int errindex;
{
  int		errors	 = 0;

  LT_DLMUTEX_LOCK ();

  if (errindex >= errorcount || errindex < 0)
    {
      /* Ack!  Error setting the error message! */
      LT_DLMUTEX_SETERROR (LT_DLSTRERROR (INVALID_ERRORCODE));
      ++errors;
    }
  else if (errindex < LT_ERROR_MAX)
    {
      /* No error setting the error message! */
      LT_DLMUTEX_SETERROR (lt_dlerror_strings[errindex]);
    }
  else
    {
      /* No error setting the error message! */
      LT_DLMUTEX_SETERROR (user_error_strings[errindex - LT_ERROR_MAX]);
    }

  LT_DLMUTEX_UNLOCK ();

  return errors;
}