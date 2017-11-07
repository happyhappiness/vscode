void mutt_format_s_tree (char *dest,
			 size_t destlen,
			 const char *prefix,
			 const char *s)
{
  mutt_format_s_x (dest, destlen, prefix, s, 1);
}