void fgetconv_close (FGETCONV **_fc)
{
  struct fgetconv_s *fc = (struct fgetconv_s *) *_fc;

  if (fc->cd != (iconv_t)-1)
    iconv_close (fc->cd);
  safe_free ((void **) _fc);
}