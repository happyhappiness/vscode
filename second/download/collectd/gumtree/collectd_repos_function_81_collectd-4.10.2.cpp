const char *
lt__error_string (int errorcode)
{
  assert (errorcode >= 0);
  assert (errorcode < LT_ERROR_MAX);

  return error_strings[errorcode];
}