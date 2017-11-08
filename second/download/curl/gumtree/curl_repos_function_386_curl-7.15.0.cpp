CHUNKcode Curl_httpchunk_read(struct connectdata *conn,
                              char *datap,
                              ssize_t datalen,
                              ssize_t *wrotep)
{
  CURLcode result=CURLE_OK;
  struct Curl_chunker *ch = &conn->proto.http->chunk;
  struct Curl_transfer_keeper *k = &conn->keep;
  size_t piece;
  size_t length = (size_t)datalen;
  size_t *wrote = (size_t *)wrotep;

  *wrote = 0; /* nothing's written yet */

  while(length) {
    switch(ch->state) {
    case CHUNK_HEX:
      if(isxdigit((int)*datap)) {
        if(ch->hexindex < MAXNUM_SIZE) {
          ch->hexbuffer[ch->hexindex] = *datap;
          datap++;
          length--;
          ch->hexindex++;
        }
        else {
          return CHUNKE_TOO_LONG_HEX; /* longer hex than we support */
        }
      }
      else {
        if(0 == ch->hexindex) {
          /* This is illegal data, we received junk where we expected
             a hexadecimal digit. */
          return CHUNKE_ILLEGAL_HEX;
        }
        /* length and datap are unmodified */
        ch->hexbuffer[ch->hexindex]=0;
        ch->datasize=strtoul(ch->hexbuffer, NULL, 16);
        ch->state = CHUNK_POSTHEX;
      }
      break;

    case CHUNK_POSTHEX:
      /* In this state, we're waiting for CRLF to arrive. We support
         this to allow so called chunk-extensions to show up here
         before the CRLF comes. */
      if(*datap == '\r')
        ch->state = CHUNK_CR;
      length--;
      datap++;
      break;

    case CHUNK_CR:
      /* waiting for the LF */
      if(*datap == '\n') {
        /* we're now expecting data to come, unless size was zero! */
        if(0 == ch->datasize) {
          if (conn->bits.trailerHdrPresent!=TRUE) {
            /* No Trailer: header found - revert to original Curl processing */
            ch->state = CHUNK_STOP;
            if (1 == length) {
               /* This is the final byte, return right now */
               return CHUNKE_STOP;
            }
          }
          else {
            ch->state = CHUNK_TRAILER; /* attempt to read trailers */
            conn->trlPos=0;
          }
        }
        else
          ch->state = CHUNK_DATA;
      }
      else
        /* previously we got a fake CR, go back to CR waiting! */
        ch->state = CHUNK_CR;
      datap++;
      length--;
      break;

    case CHUNK_DATA:
      /* we get pure and fine data

         We expect another 'datasize' of data. We have 'length' right now,
         it can be more or less than 'datasize'. Get the smallest piece.
      */
      piece = (ch->datasize >= length)?length:ch->datasize;

      /* Write the data portion available */
#ifdef HAVE_LIBZ
      switch (conn->keep.content_encoding) {
        case IDENTITY:
#endif
          if(!k->ignorebody)
            result = Curl_client_write(conn->data, CLIENTWRITE_BODY, datap,
                                       piece);
#ifdef HAVE_LIBZ
          break;

        case DEFLATE:
          /* update conn->keep.str to point to the chunk data. */
          conn->keep.str = datap;
          result = Curl_unencode_deflate_write(conn->data, &conn->keep,
                                               (ssize_t)piece);
          break;

        case GZIP:
          /* update conn->keep.str to point to the chunk data. */
          conn->keep.str = datap;
          result = Curl_unencode_gzip_write(conn->data, &conn->keep,
                                            (ssize_t)piece);
          break;

        case COMPRESS:
        default:
          failf (conn->data,
                 "Unrecognized content encoding type. "
                 "libcurl understands `identity', `deflate' and `gzip' "
                 "content encodings.");
          return CHUNKE_BAD_ENCODING;
      }
#endif

      if(result)
        return CHUNKE_WRITE_ERROR;

      *wrote += piece;

      ch->datasize -= piece; /* decrease amount left to expect */
      datap += piece;    /* move read pointer forward */
      length -= piece;   /* decrease space left in this round */

      if(0 == ch->datasize)
        /* end of data this round, we now expect a trailing CRLF */
        ch->state = CHUNK_POSTCR;
      break;

    case CHUNK_POSTCR:
      if(*datap == '\r') {
        ch->state = CHUNK_POSTLF;
        datap++;
        length--;
      }
      else
        return CHUNKE_BAD_CHUNK;
      break;

    case CHUNK_POSTLF:
      if(*datap == '\n') {
        /*
         * The last one before we go back to hex state and start all
         * over.
         */
        Curl_httpchunk_init(conn);
        datap++;
        length--;
      }
      else
        return CHUNKE_BAD_CHUNK;
      break;

    case CHUNK_TRAILER:
      /* conn->trailer is assumed to be freed in url.c on a
         connection basis */
      if (conn->trlPos >= conn->trlMax) {
        char *ptr;
        if(conn->trlMax) {
          conn->trlMax *= 2;
          ptr = (char*)realloc(conn->trailer,conn->trlMax);
        }
        else {
          conn->trlMax=128;
          ptr = (char*)malloc(conn->trlMax);
        }
        if(!ptr)
          return CHUNKE_OUT_OF_MEMORY;
        conn->trailer = ptr;
      }
      conn->trailer[conn->trlPos++]=*datap;

      if(*datap == '\r')
        ch->state = CHUNK_TRAILER_CR;
      else {
        datap++;
        length--;
     }
      break;

    case CHUNK_TRAILER_CR:
      if(*datap == '\r') {
        ch->state = CHUNK_TRAILER_POSTCR;
        datap++;
        length--;
      }
      else
        return CHUNKE_BAD_CHUNK;
      break;

    case CHUNK_TRAILER_POSTCR:
      if (*datap == '\n') {
        conn->trailer[conn->trlPos++]='\n';
        conn->trailer[conn->trlPos]=0;
        if (conn->trlPos==2) {
          ch->state = CHUNK_STOP;
          return CHUNKE_STOP;
        }
        else {
          Curl_client_write(conn->data, CLIENTWRITE_HEADER,
                            conn->trailer, conn->trlPos);
        }
        ch->state = CHUNK_TRAILER;
        conn->trlPos=0;
        datap++;
        length--;
      }
      else
        return CHUNKE_BAD_CHUNK;
      break;

    case CHUNK_STOP:
      /* If we arrive here, there is data left in the end of the buffer
         even if there's no more chunks to read */
      ch->dataleft = length;
      return CHUNKE_STOP; /* return stop */
    default:
      return CHUNKE_STATE_ERROR;
    }
  }
  return CHUNKE_OK;
}