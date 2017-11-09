void mutt_forward_trailer (CONTEXT *ctx, HEADER *cur, FILE *fp)
{
  char buffer[LONG_STRING];

  if (ForwardAttrTrailer)
  {
    setlocale (LC_TIME, NONULL (AttributionLocale));
    mutt_make_string (buffer, sizeof (buffer), ForwardAttrTrailer, ctx, cur);
    setlocale (LC_TIME, "");
    fputc ('\n', fp);
    fputs (buffer, fp);
    fputc ('\n', fp);
  }
}