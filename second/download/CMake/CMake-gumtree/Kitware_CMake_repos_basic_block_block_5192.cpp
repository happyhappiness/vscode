{
    result = Curl_write_plain(conn, fd, to_p, len, &written);
    if(!result) {
      len -= written;
      to_p += written;
    }
    else {
      /* FIXME: We are doing a busy wait */
      if(result == CURLE_AGAIN)
        continue;
      return result;
    }
  }