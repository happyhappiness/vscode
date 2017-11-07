void mutt_make_attribution (CONTEXT *ctx, HEADER *cur, FILE *out)
{
  char buffer[STRING];
  if (Attribution)
  {
    mutt_make_string (buffer, sizeof (buffer), Attribution, ctx, cur);
    fputs (buffer, out);
    fputc ('\n', out);
  }
}