FGETCONV *fgetconv_open (FILE *file, const char *from, const char *to, int flags)
{
  struct fgetconv_s *fc;
  iconv_t cd = (iconv_t)-1;
  static ICONV_CONST char *repls[] = { "\357\277\275", "?", 0 };

  if (from && to)
    cd = mutt_iconv_open (to, from, flags);

  if (cd != (iconv_t)-1)
  {
    fc = safe_malloc (sizeof (struct fgetconv_s));
    fc->p = fc->ob = fc->bufo;
    fc->ib = fc->bufi;
    fc->ibl = 0;
    fc->inrepls = mutt_is_utf8 (to) ? repls : repls + 1;
  }
  else
    fc = safe_malloc (sizeof (struct fgetconv_not));
  fc->file = file;
  fc->cd = cd;
  return (FGETCONV *)fc;
}