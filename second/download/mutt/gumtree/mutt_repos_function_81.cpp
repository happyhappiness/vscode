void mutt_make_post_indent (CONTEXT *ctx, HEADER *cur, FILE *out)
{
  char buffer[STRING];
  if (PostIndentString)
  {
    mutt_make_string (buffer, sizeof (buffer), PostIndentString, ctx, cur);
    fputs (buffer, out);
    fputc ('\n', out);
  }
}