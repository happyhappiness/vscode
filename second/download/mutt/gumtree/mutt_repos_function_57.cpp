char *
mutt_compile_help (char *buf, size_t buflen, int menu, const struct mapping_t *items)
{
  int i;
  size_t len;
  char *pbuf = buf;
  
  for (i = 0; items[i].name && buflen > 2; i++)
  {
    if (i)
    {
      *pbuf++ = ' ';
      *pbuf++ = ' ';
      buflen -= 2;
    }
    mutt_make_help (pbuf, buflen, _(items[i].name), menu, items[i].value);
    len = mutt_strlen (pbuf);
    pbuf += len;
    buflen -= len;
  }
  return buf;
}