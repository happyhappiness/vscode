void mutt_format_s (char *dest,
		    size_t destlen,
		    const char *prefix,
		    const char *s)
{
  mutt_format_s_x (dest, destlen, prefix, s, 0);
}