static void idna_init (void)
{
#ifdef WIN32
  char buf[60];
  UINT cp = GetACP();

  if(!getenv("CHARSET") && cp > 0) {
    snprintf(buf, sizeof(buf), "CHARSET=cp%u", cp);
    putenv(buf);
  }
#else
  /* to do? */
#endif
}