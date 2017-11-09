static const char *
cb_format_str (char *dest, size_t destlen, size_t col, int cols, char op, const char *src,
  const char *fmt, const char *ifstring, const char *elsestring,
  unsigned long data, format_flag flags)
{
  if (!dest || (data == 0))
    return src;

  CONTEXT *ctx = (CONTEXT *) data;

  switch (op)
  {
    case 'f':
      /* Compressed file */
      snprintf (dest, destlen, "%s", NONULL (escape_path (ctx->realpath)));
      break;
    case 't':
      /* Plaintext, temporary file */
      snprintf (dest, destlen, "%s", NONULL (escape_path (ctx->path)));
      break;
  }
  return src;
}