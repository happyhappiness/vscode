f(!result) {
      len -= nread;
      to_p += nread;
    }
    else {
      /* FIXME: We are doing a busy wait */
      if(result == CURLE_AGAIN)
        continue;
      return result;
    }