static const char *
dylderror (const char *errmsg)
{
  NSLinkEditErrors ler;
  int lerno;
  const char *file;
  const char *errstr;

  NSLinkEditError (&ler, &lerno, &file, &errstr);

  if (! (errstr && *errstr))
    {
      errstr = errmsg;
    }

  return errstr;
}