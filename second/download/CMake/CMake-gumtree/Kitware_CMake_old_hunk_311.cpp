    else {
      CURLcode result;
      ssl_sessionid =
        aprintf("%s:%d:%d:%s:%hu", data->set.str[STRING_SSL_CAFILE],
                data->set.ssl.verifypeer, data->set.ssl.verifyhost,
                conn->host.name, conn->remote_port);
      ssl_sessionid_len = strlen(ssl_sessionid);

      err = SSLSetPeerID(connssl->ssl_ctx, ssl_sessionid, ssl_sessionid_len);
