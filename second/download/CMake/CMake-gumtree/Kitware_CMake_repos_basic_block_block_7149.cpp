f(inbuf[3].BufferType == SECBUFFER_EXTRA && inbuf[3].cbBuffer > 0) {
        infof(data, "schannel: encrypted data length: %lu\n",
              inbuf[3].cbBuffer);

        /* check if the remaining data is less than the total amount
         * and therefore begins after the already processed data
         */
        if(connssl->encdata_offset > inbuf[3].cbBuffer) {
          /* move remaining encrypted data forward to the beginning of
             buffer */
          memmove(connssl->encdata_buffer,
                  (connssl->encdata_buffer + connssl->encdata_offset) -
                  inbuf[3].cbBuffer, inbuf[3].cbBuffer);
          connssl->encdata_offset = inbuf[3].cbBuffer;
        }

        infof(data, "schannel: encrypted data cached: offset %zu length %zu\n",
              connssl->encdata_offset, connssl->encdata_length);
      }
      else {
        /* reset encrypted buffer offset, because there is no data remaining */
        connssl->encdata_offset = 0;
      }