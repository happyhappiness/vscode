CHUNKcode Curl_httpchunk_read(struct connectdata *conn,
                              char *datap,
                              ssize_t datalen,
                              ssize_t *wrotep)
{
  CURLcode result=CURLE_OK;
  struct SessionHandle *data = conn->data;
  struct Curl_chunker *ch = &conn->chunk;
  struct SingleRequest *k = &data->req;
  size_t piece;
  size_t length = (size_t)datalen;
  size_t *wrote = (size_t *)wrotep;

  *wrote = 0; /* nothing's written yet */

  /* the original data is written to the client, but we go on with the
     chunk read process, to properly calculate the content length*/
  if(data->set.http_te_skip && !k->ignorebody) {
    result = Curl_client_write(conn, CLIENTWRITE_BODY, datap, datalen);
    if(result)
      return CHUNKE_WRITE_ERROR;
  }

  while(length) {
    switch(ch->state) {
    case CHUNK_HEX:
      /* Check for an ASCII hex digit.
         We avoid the use of isxdigit to accommodate non-ASCII hosts. */
      if((*datap >= 0x30 && *datap <= 0x39)    /* 0-9 */
         || (*datap >= 0x41 && *datap <= 0x46)    /* A-F */
         || (*datap >= 0x61 && *datap <= 0x66)) { /* a-f */
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
#ifdef CURL_DOES_CONVERSIONS
        /* convert to host encoding before calling strtoul */
        result = Curl_convert_from_network(conn->data,
                                           ch->hexbuffer,
                                           ch->hexindex);
        if(result != CURLE_OK) {
          /* Curl_convert_from_network calls failf if unsuccessful */
          /* Treat it as a bad hex character */
          return(CHUNKE_ILLEGAL_HEX);
        }
#endif /* CURL_DOES_CONVERSIONS */
        ch->datasize=strtoul(ch->hexbuffer, NULL, 16);
        ch->state = CHUNK_POSTHEX;
      }
      break;

    case CHUNK_POSTHEX:
      /* In this state, we're waiting for CRLF to arrive. We support
         this to allow so called chunk-extensions to show up here
         before the CRLF comes. */
      if(*datap == 0x0d)
        ch->state = CHUNK_CR;
      length--;
      datap++;
      break;

    case CHUNK_CR:
      /* waiting for the LF */
      if(*datap == 0x0a) {
        /* we're now expecting data to come, unless size was zero! */
        if(0 == ch->datasize) {
          if(k->trailerhdrpresent!=TRUE) {
            /* No Trailer: header found - revert to original Curl processing */
            ch->state = CHUNK_STOPCR;

            /* We need to increment the datap here since we bypass the
               increment below with the immediate break */
            length--;
            datap++;

            /* This is the final byte, continue to read the final CRLF */
            break;
          }
          else {
            ch->state = CHUNK_TRAILER; /* attempt to read trailers */
            conn->trlPos=0;
          }
        }
        else {
          ch->state = CHUNK_DATA;
        }
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
      switch (conn->data->set.http_ce_skip?
              IDENTITY : data->req.content_encoding) {
      case IDENTITY:
#endif
        if(!k->ignorebody) {
          if( !data->set.http_te_skip )
            result = Curl_client_write(conn, CLIENTWRITE_BODY, datap,
                                       piece);
          else
            result = CURLE_OK;
        }
#ifdef HAVE_LIBZ
        break;

      case DEFLATE:
        /* update data->req.keep.str to point to the chunk data. */
        data->req.str = datap;
        result = Curl_unencode_deflate_write(conn, &data->req,
                                             (ssize_t)piece);
        break;

      case GZIP:
        /* update data->req.keep.str to point to the chunk data. */
        data->req.str = datap;
        result = Curl_unencode_gzip_write(conn, &data->req,
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
      if(*datap == 0x0d) {
        ch->state = CHUNK_POSTLF;
        datap++;
        length--;
      }
      else {
        return CHUNKE_BAD_CHUNK;
      }
      break;

    case CHUNK_POSTLF:
      if(*datap == 0x0a) {
        /*
         * The last one before we go back to hex state and start all
         * over.
         */
        Curl_httpchunk_init(conn);
        datap++;
        length--;
      }
      else {
        return CHUNKE_BAD_CHUNK;
      }

      break;

    case CHUNK_TRAILER:
      /* conn->trailer is assumed to be freed in url.c on a
         connection basis */
      if(conn->trlPos >= conn->trlMax) {
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

      if(*datap == 0x0d)
        ch->state = CHUNK_TRAILER_CR;
      else {
        datap++;
        length--;
      }
      break;

    case CHUNK_TRAILER_CR:
      if(*datap == 0x0d) {
        ch->state = CHUNK_TRAILER_POSTCR;
        datap++;
        length--;
      }
      else
        return CHUNKE_BAD_CHUNK;
      break;

    case CHUNK_TRAILER_POSTCR:
      if(*datap == 0x0a) {
        conn->trailer[conn->trlPos++]=0x0a;
        conn->trailer[conn->trlPos]=0;
        if(conn->trlPos==2) {
          ch->state = CHUNK_STOP;
          datap++;
          length--;

          /*
           * Note that this case skips over the final STOP states since we've
           * already read the final CRLF and need to return
           */

          ch->dataleft = length;

          return CHUNKE_STOP; /* return stop */
        }
        else {
#ifdef CURL_DOES_CONVERSIONS
          /* Convert to host encoding before calling Curl_client_write */
          result = Curl_convert_from_network(conn->data,
                                             conn->trailer,
                                             conn->trlPos);
          if(result != CURLE_OK) {
            /* Curl_convert_from_network calls failf if unsuccessful */
            /* Treat it as a bad chunk */
            return(CHUNKE_BAD_CHUNK);
          }
#endif /* CURL_DOES_CONVERSIONS */
          if(!data->set.http_te_skip) {
            result = Curl_client_write(conn, CLIENTWRITE_HEADER,
                                       conn->trailer, conn->trlPos);
            if(result)
              return CHUNKE_WRITE_ERROR;
          }
        }
        ch->state = CHUNK_TRAILER;
        conn->trlPos=0;
        datap++;
        length--;
      }
      else
        return CHUNKE_BAD_CHUNK;
      break;

    case CHUNK_STOPCR:
      /* Read the final CRLF that ends all chunk bodies */

      if(*datap == 0x0d) {
        ch->state = CHUNK_STOP;
        datap++;
        length--;
      }
      else {
        return CHUNKE_BAD_CHUNK;
      }
      break;

    case CHUNK_STOP:
      if(*datap == 0x0a) {
        datap++;
        length--;

        /* Record the length of any data left in the end of the buffer
           even if there's no more chunks to read */

        ch->dataleft = length;
        return CHUNKE_STOP; /* return stop */
      }
      else {
        return CHUNKE_BAD_CHUNK;
      }

    default:
      return CHUNKE_STATE_ERROR;
    }
  }
  return CHUNKE_OK;
}