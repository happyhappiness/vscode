void mutt_write_references (LIST *r, FILE *f, int trim)
{
  LIST **ref = NULL;
  int refcnt = 0, refmax = 0;

  for ( ; (trim == 0 || refcnt < trim) && r ; r = r->next)
  {
    if (refcnt == refmax)
      safe_realloc (&ref, (refmax += REF_INC) * sizeof (LIST *));
    ref[refcnt++] = r;
  }

  while (refcnt-- > 0)
  {
    fputc (' ', f);
    fputs (ref[refcnt]->data, f);
    if (refcnt >= 1)
      fputc ('\n', f);
  }

  FREE (&ref);
}