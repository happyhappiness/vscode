{
        /* this cred session is now also referenced by sessionid cache */
        connssl->cred->refcount++;
        infof(data, "schannel: stored credential handle in session cache\n");
      }