{
    Curl_ssl_sessionid_lock(conn);
    if(!Curl_ssl_getsessionid(conn, (void **)&old_cred, NULL, sockindex)) {
      connssl->cred = old_cred;
      infof(data, "schannel: re-using existing credential handle\n");

      /* increment the reference counter of the credential/session handle */
      connssl->cred->refcount++;
      infof(data, "schannel: incremented credential handle refcount = %d\n",
            connssl->cred->refcount);
    }
    Curl_ssl_sessionid_unlock(conn);
  }