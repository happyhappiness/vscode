static void decodeQuantum(unsigned char *dest, const char *src)
{
  unsigned int x = 0;
  int i;
  char *found;

  for(i = 0; i < 4; i++) {
    if((found = strchr(table64, src[i])) != NULL)
      x = (x << 6) + (unsigned int)(found - table64);
    else if(src[i] == '=')
      x = (x << 6);
  }

  dest[2] = (unsigned char)(x & 255);
  x >>= 8;
  dest[1] = (unsigned char)(x & 255);
  x >>= 8;
  dest[0] = (unsigned char)(x & 255);
}