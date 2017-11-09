void mutt_forward_intro (CONTEXT *ctx, HEADER *cur, FILE *fp)
{
  char buffer[LONG_STRING];

  if (ForwardAttrIntro)
  {
    setlocale (LC_TIME, NONULL (AttributionLocale));
    mutt_make_string (buffer, sizeof (buffer), ForwardAttrIntro, ctx, cur);
    setlocale (LC_TIME, "");
    fputs (buffer, fp);
    fputs ("\n\n", fp);
  }
}