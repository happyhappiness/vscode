{
    bool incache;
    struct curl_schannel_cred *old_cred = NULL;

    Curl_ssl_sessionid_lock(conn);
    incache = !(Curl_ssl_getsessionid(conn, (void **)&old_cred, NULL,
                                      sockindex));
    if(incache) {
      if(old_cred != connssl->cred) {
        infof(data, "schannel: old credential handle is stale, removing\n");
        /* we're not taking old_cred ownership here, no refcount++ is needed */
        Curl_ssl_delsessionid(conn, (void *)old_cred);
        incache = FALSE;
      }
    }
    if(!incache) {
      result = Curl_ssl_addsessionid(conn, (void *)connssl->cred,
                                     sizeof(struct curl_schannel_cred),
                                     sockindex);
      if(result) {
        Curl_ssl_sessionid_unlock(conn);
        failf(data, "schannel: failed to store credential handle");
        return result;
      }
      else {
        /* this cred session is now also referenced by sessionid cache */
        connssl->cred->refcount++;
        infof(data, "schannel: stored credential handle in session cache\n");
      }
    }
    Curl_ssl_sessionid_unlock(conn);
  }