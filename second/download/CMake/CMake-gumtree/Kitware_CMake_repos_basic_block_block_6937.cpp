f(nickname) {
      /* we support only nicknames in case of issuercert for now */
      ret = check_issuer_cert(connssl->handle, nickname);
      free(nickname);
    }