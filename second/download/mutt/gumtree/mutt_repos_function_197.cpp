int mutt_atos (const char *str, short *dst)
{
  int rc;
  long res;
  short tmp;
  short *t = dst ? dst : &tmp;

  *t = 0;

  if ((rc = mutt_atol (str, &res)) < 0)
    return rc;
  if ((short) res != res)
    return -2;

  *t = (short) res;
  return 0;
}