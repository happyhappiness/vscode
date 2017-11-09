char *hexdump(const unsigned char *buffer, size_t len)
{
  static char dump[200 * 3 + 1];
  char *p = dump;
  size_t i;
  if(len > 200)
    return NULL;
  for(i = 0; i<len; i++, p += 3)
    snprintf(p, 4, "%02x ", buffer[i]);
  return dump;
}