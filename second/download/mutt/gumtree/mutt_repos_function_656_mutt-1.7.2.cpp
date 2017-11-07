int main(void)
{
  unsigned char r[16];
  int rc;

  if ((rc = md5_stream(stdin, r)))
    return rc;

  printf("%02x%02x%02x%02x%02x%02x%02x%02x"
         "%02x%02x%02x%02x%02x%02x%02x%02x\n",
         r[0], r[1], r[2], r[3], r[4], r[5], r[6], r[7],
         r[8], r[9], r[10], r[11], r[12], r[13], r[14], r[15]);

  return 0;
}