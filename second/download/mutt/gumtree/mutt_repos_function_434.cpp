static int test_last_status_new (FILE * f)
{
  HEADER *hdr;
  ENVELOPE* tmp_envelope;
  int result = 0;

  if (fseek_last_message (f) == -1)
    return (0);

  hdr = mutt_new_header ();
  tmp_envelope = mutt_read_rfc822_header (f, hdr, 0, 0);
  if (!(hdr->read || hdr->old))
    result = 1;

  mutt_free_envelope(&tmp_envelope);
  mutt_free_header (&hdr);

  return result;
}