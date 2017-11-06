void
mutt_make_string_info (char *dst, size_t dstlen, int cols, const char *s, struct hdr_format_info *hfi, format_flag flags)
{
  mutt_FormatString (dst, dstlen, 0, cols, s, hdr_format_str, (unsigned long) hfi, flags);
}