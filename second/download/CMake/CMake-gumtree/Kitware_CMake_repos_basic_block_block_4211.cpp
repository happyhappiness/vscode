r(; trailer_pos < trailer_end;) {
      uint32_t n;
      memcpy(&n, trailer_pos, sizeof(n));
      trailer_pos += sizeof(n);

      result = Curl_client_write(conn, CLIENTWRITE_HEADER, trailer_pos, n);
      if(result) {
        *err = result;
        return -1;
      }

      trailer_pos += n + 1;
    }