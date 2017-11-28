int
lt_dladderror (const char *diagnostic)
{
  int		errindex = 0;
  int		result	 = -1;
  const char  **temp     = (const char **) 0;

  assert (diagnostic);

  errindex = errorcount - LT_ERROR_MAX;
  temp = REALLOC (const char *, user_error_strings, 1 + errindex);
  if (temp)
    {
      user_error_strings		= temp;
      user_error_strings[errindex]	= diagnostic;
      result				= errorcount++;
    }

  return result;
}