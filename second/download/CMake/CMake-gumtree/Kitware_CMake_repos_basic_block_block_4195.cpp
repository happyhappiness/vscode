r(; http->push_headers_used > 0; --http->push_headers_used) {
        free(http->push_headers[http->push_headers_used - 1]);
      }