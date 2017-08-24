{
        infof(data, "schannel: old credential handle is stale, removing\n");
        /* we're not taking old_cred ownership here, no refcount++ is needed */
        Curl_ssl_delsessionid(conn, (void *)old_cred);
        incache = FALSE;
      }