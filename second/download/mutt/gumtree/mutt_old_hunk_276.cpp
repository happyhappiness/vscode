
void mutt_make_attribution (CONTEXT *ctx, HEADER *cur, FILE *out)
{
  char buffer[LONG_STRING];
  if (Attribution)
  {
    mutt_make_string (buffer, sizeof (buffer), Attribution, ctx, cur);
    fputs (buffer, out);
    fputc ('\n', out);
  }
}

void mutt_make_post_indent (CONTEXT *ctx, HEADER *cur, FILE *out)
