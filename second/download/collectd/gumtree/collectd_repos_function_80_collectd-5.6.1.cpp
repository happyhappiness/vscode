int
lt_dlseterror (int errindex)
{
  int		errors	 = 0;

  if (errindex >= errorcount || errindex < 0)
    {
      /* Ack!  Error setting the error message! */
      LT__SETERROR (INVALID_ERRORCODE);
      ++errors;
    }
  else if (errindex < LT_ERROR_MAX)
    {
      /* No error setting the error message! */
      LT__SETERRORSTR (error_strings[errindex]);
    }
  else
    {
      /* No error setting the error message! */
      LT__SETERRORSTR (user_error_strings[errindex - LT_ERROR_MAX]);
    }

  return errors;
}