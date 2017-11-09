static size_t encoder_7bit_read(char *buffer, size_t size, bool ateof,
                                curl_mimepart *part)
{
  mime_encoder_state *st = &part->encstate;
  size_t cursize = st->bufend - st->bufbeg;

  (void) ateof;

  if(size > cursize)
    size = cursize;

  for(cursize = 0; cursize < size; cursize++) {
    *buffer = st->buf[st->bufbeg];
    if(*buffer++ & 0x80)
      return cursize? cursize: READ_ERROR;
    st->bufbeg++;
  }

  return cursize;
}