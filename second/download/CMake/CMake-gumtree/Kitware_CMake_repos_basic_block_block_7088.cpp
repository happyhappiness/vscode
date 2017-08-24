f(result) {
        Curl_ssl_sessionid_unlock(conn);
        failf(data, "schannel: failed to store credential handle");
        return result;
      }
      else {
        /* this cred session is now also referenced by sessionid cache */
        connssl->cred->refcount++;
        infof(data, "schannel: stored credential handle in session cache\n");
      }