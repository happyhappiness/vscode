static void strnfcpy(char *d, char *s, size_t siz, size_t len)
{
  if(len > siz)
    len = siz - 1;
  strfcpy(d, s, len);
}