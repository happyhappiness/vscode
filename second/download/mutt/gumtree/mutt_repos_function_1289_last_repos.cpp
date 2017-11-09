static int get_toplevel_encoding (BODY *a)
{
  int e = ENC7BIT;

  for (; a; a = a->next)
  {
    if (a->encoding == ENCBINARY)
      return (ENCBINARY);
    else if (a->encoding == ENC8BIT)
      e = ENC8BIT;
  }

  return (e);
}