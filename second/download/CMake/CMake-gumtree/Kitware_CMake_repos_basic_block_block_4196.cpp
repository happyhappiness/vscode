f(http->push_headers) {
      /* if they weren't used and then freed before */
      for(; http->push_headers_used > 0; --http->push_headers_used) {
        free(http->push_headers[http->push_headers_used - 1]);
      }
      free(http->push_headers);
      http->push_headers = NULL;
    }