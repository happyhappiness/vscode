static size_t encoder_nop_read(char *buffer, size_t size, bool ateof,
                               curl_mimepart *part)
{
  mime_encoder_state *st = &part->encstate;
  size_t insize = st->bufend - st->bufbeg;

  (void) ateof;

  if(size > insize)
    size = insize;
  if(size)
    memcpy(buffer, st->buf, size);
  st->bufbeg += size;
  return size;
}