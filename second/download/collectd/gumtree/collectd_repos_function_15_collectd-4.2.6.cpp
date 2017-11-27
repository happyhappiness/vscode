int
lt_dladderror (diagnostic)
     const char *diagnostic;
{
  int		errindex = 0;
  int		result	 = -1;
  const char  **temp     = (const char **) 0;

  assert (diagnostic);

  LT_DLMUTEX_LOCK ();

  errindex = errorcount - LT_ERROR_MAX;
  temp = LT_EREALLOC (const char *, user_error_strings, 1 + errindex);
  if (temp)
    {
      user_error_strings		= temp;
      user_error_strings[errindex]	= diagnostic;
      result				= errorcount++;
    }

  LT_DLMUTEX_UNLOCK ();

  return result;
}