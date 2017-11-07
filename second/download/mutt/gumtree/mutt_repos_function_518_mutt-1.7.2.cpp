int mutt_count_body_parts (CONTEXT *ctx, HEADER *hdr)
{
  short keep_parts = 0;

  if (hdr->attach_valid)
    return hdr->attach_total;
  
  if (hdr->content->parts)
    keep_parts = 1;
  else
    mutt_parse_mime_message (ctx, hdr);
  
  if (AttachAllow || AttachExclude || InlineAllow || InlineExclude)
    hdr->attach_total = count_body_parts(hdr->content, MUTT_PARTS_TOPLEVEL);
  else
    hdr->attach_total = 0;

  hdr->attach_valid = 1;
  
  if (!keep_parts)
    mutt_free_body (&hdr->content->parts);
  
  return hdr->attach_total;
}