const char *
lt_dlerror ()
{
  const char *error;

  LT_DLMUTEX_GETERROR (error);
  LT_DLMUTEX_SETERROR (0);

  return error ? error : NULL;
}