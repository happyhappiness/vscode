static char *suburl(const char *base, int i)
{
  return curl_maprintf("%s%.4d", base, i);
}