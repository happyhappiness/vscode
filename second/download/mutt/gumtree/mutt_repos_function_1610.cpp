static int smtp_code (char *buf, size_t len, int *n)
{
  char code[4];

  if (len < 4)
    return -1;
  code[0] = buf[0];
  code[1] = buf[1];
  code[2] = buf[2];
  code[3] = 0;
  if (mutt_atoi (code, n) < 0)
    return -1;
  return 0;
}