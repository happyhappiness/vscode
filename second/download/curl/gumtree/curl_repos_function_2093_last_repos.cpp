static size_t read_encoded_part_content(curl_mimepart *part,
                                        char *buffer, size_t bufsize)
{
  mime_encoder_state *st = &part->encstate;
  size_t cursize = 0;
  size_t sz;
  bool ateof = FALSE;

  while(bufsize) {
    if(st->bufbeg < st->bufend || ateof) {
      /* Encode buffered data. */
      sz = part->encoder->encodefunc(buffer, bufsize, ateof, part);
      switch(sz) {
      case 0:
        if(ateof)
          return cursize;
        break;
      case CURL_READFUNC_ABORT:
      case CURL_READFUNC_PAUSE:
      case READ_ERROR:
        return cursize? cursize: sz;
      default:
        cursize += sz;
        buffer += sz;
        bufsize -= sz;
        continue;
      }
    }

    /* We need more data in input buffer. */
    if(st->bufbeg) {
      size_t len = st->bufend - st->bufbeg;

      if(len)
        memmove(st->buf, st->buf + st->bufbeg, len);
      st->bufbeg = 0;
      st->bufend = len;
    }
    if(st->bufend >= sizeof st->buf)
      return cursize? cursize: READ_ERROR;    /* Buffer full. */
    sz = read_part_content(part, st->buf + st->bufend,
                           sizeof st->buf - st->bufend);
    switch(sz) {
    case 0:
      ateof = TRUE;
      break;
    case CURL_READFUNC_ABORT:
    case CURL_READFUNC_PAUSE:
    case READ_ERROR:
      return cursize? cursize: sz;
    default:
      st->bufend += sz;
      break;
    }
  }

  return cursize;
}