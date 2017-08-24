{
          /* move remaining encrypted data forward to the beginning of
             buffer */
          memmove(connssl->encdata_buffer,
                  (connssl->encdata_buffer + connssl->encdata_offset) -
                  inbuf[3].cbBuffer, inbuf[3].cbBuffer);
          connssl->encdata_offset = inbuf[3].cbBuffer;
        }