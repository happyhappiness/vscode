{
        /* init the "upload from here" pointer */
        conn->upload_fromhere = k->uploadbuf;

        nread = data->set.fread(conn->upload_fromhere, 1,
                                BUFSIZE, data->set.in);

        /* the signed int typecase of nread of for systems that has
           unsigned size_t */
        if (nread<=0) {
          /* done */
          k->keepon &= ~KEEP_WRITE; /* we're done writing */
          FD_ZERO(&k->wkeepfd);
          break;
        }

        /* store number of bytes available for upload */
        conn->upload_present = nread;

        /* convert LF to CRLF if so asked */
        if (data->set.crlf) {
          for(i = 0, si = 0; i < nread; i++, si++) {
            if (k->buf[i] == 0x0a) {
              data->state.scratch[si++] = 0x0d;
              data->state.scratch[si] = 0x0a;
            }
            else {
              data->state.scratch[si] = k->uploadbuf[i];
            }
          }
          nread = si;
          k->buf = data->state.scratch; /* point to the new buffer */
        }
      }