{
      free(our_ssl_sessionid);
      failf(data, "failed to store ssl session");
      return retcode;
    }