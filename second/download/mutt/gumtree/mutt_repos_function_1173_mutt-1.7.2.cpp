void
_mutt_make_string (char *dest, size_t destlen, const char *s, CONTEXT *ctx, HEADER *hdr, format_flag flags)
{
  struct hdr_format_info hfi;

  hfi.hdr = hdr;
  hfi.ctx = ctx;
  hfi.pager_progress = 0;

  mutt_FormatString (dest, destlen, 0, MuttIndexWindow->cols, s, hdr_format_str, (unsigned long) &hfi, flags);
}