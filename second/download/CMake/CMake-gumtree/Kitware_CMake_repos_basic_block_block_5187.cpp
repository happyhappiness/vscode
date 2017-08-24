{
      /* FIXME: We are doing a busy wait */
      if(result == CURLE_AGAIN)
        continue;
      return result;
    }