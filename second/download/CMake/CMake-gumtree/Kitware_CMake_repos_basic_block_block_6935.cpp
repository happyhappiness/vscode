{
      infof(data, "SSL certificate issuer check failed\n");
      result = CURLE_SSL_ISSUER_ERROR;
      goto error;
    }