void mutt_expand_file_fmt (char *dest, size_t destlen, const char *fmt, const char *src)
{
  char tmp[LONG_STRING];
  
  mutt_quote_filename (tmp, sizeof (tmp), src);
  mutt_expand_fmt (dest, destlen, fmt, tmp);
}