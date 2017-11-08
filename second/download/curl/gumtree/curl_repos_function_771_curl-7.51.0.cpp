static unsigned char hex_to_uint(const char *s)
{
  char buf[3];
  unsigned long val;
  buf[0] = s[0];
  buf[1] = s[1];
  buf[2] = 0;
  val = strtoul(buf, NULL, 16);
  return (unsigned char)(val&0xff);
}