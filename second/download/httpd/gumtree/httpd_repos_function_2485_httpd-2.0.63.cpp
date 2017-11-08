int XML_SetBase(XML_Parser parser, const XML_Char *p)
{
  if (p) {
    p = poolCopyString(&dtd.pool, p);
    if (!p)
      return 0;
    curBase = p;
  }
  else
    curBase = 0;
  return 1;
}