char *suburl(char *base, int i)
{
  return curl_maprintf("%s000%c", base, 48+i);
}