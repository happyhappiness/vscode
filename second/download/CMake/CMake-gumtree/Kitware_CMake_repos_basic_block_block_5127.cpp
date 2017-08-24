{
        /* now reset a few variables to start over nicely from the start of
           the big buffer */
        pp->nread_resp = 0; /* start over from scratch in the buffer */
        ptr = pp->linestart_resp = buf;
        perline = 0;
      }