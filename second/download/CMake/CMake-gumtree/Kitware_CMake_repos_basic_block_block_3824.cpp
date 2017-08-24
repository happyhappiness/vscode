{
      /* If there is a list of cookie files to read, do it first so that
         we have all the told files read before we write the new jar.
         Curl_cookie_loadfiles() LOCKS and UNLOCKS the share itself! */
      Curl_cookie_loadfiles(data);
    }