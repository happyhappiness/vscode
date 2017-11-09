void mutt_generate_boundary (PARAMETER **parm)
{
  char rs[BOUNDARYLEN + 1];
  char *p = rs;
  int i;

  rs[BOUNDARYLEN] = 0;
  for (i=0;i<BOUNDARYLEN;i++)
    *p++ = B64Chars[LRAND() % sizeof (B64Chars)];
  *p = 0;

  mutt_set_parameter ("boundary", rs, parm);
}