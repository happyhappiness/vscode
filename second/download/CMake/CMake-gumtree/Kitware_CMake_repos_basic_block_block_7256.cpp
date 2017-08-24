f(pubkeylen == size) {
      if(!memcmp(pubkey, buf, pubkeylen))
        result = CURLE_OK;
      break;
    }