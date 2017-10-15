
void mutt_make_attribution (CONTEXT *ctx, HEADER *cur, FILE *out)
{
  char buffer[LONG_STRING];
  if (Attribution)
  {
    setlocale (LC_TIME, NONULL (AttributionLocale));
    mutt_make_string (buffer, sizeof (buffer), Attribution, ctx, cur);
    setlocale (LC_TIME, "");
    fputs (buffer, out);
    fputc ('\n', out);
  }
}

void mutt_make_post_indent (CONTEXT *ctx, HEADER *cur, FILE *out)
