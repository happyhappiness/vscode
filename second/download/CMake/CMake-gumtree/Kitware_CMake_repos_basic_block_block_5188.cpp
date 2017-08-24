e(len > 0) {
    result = Curl_read_plain(fd, to_p, len, &nread);
    if(!result) {
      len -= nread;
      to_p += nread;
    }
    else {
      /* FIXME: We are doing a busy wait */
      if(result == CURLE_AGAIN)
        continue;
      return result;
    }
  }