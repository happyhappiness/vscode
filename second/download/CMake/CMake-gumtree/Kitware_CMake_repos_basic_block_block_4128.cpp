r(i=0; i<stream->push_headers_used; i++) {
      if(!strncmp(header, stream->push_headers[i], len)) {
        /* sub-match, make sure that it is followed by a colon */
        if(stream->push_headers[i][len] != ':')
          continue;
        return &stream->push_headers[i][len+1];
      }
    }