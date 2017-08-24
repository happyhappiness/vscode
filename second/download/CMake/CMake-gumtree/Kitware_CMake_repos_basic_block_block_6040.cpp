f(*proxyptr) {
    struct proxy_info *proxyinfo =
      sockstype ? &conn->socks_proxy : &conn->http_proxy;
    proxyinfo->proxytype = proxytype;

    if(proxyuser) {
      /* found user and password, rip them out.  note that we are unescaping
         them, as there is otherwise no way to have a username or password
         with reserved characters like ':' in them. */
      Curl_safefree(proxyinfo->user);
      proxyinfo->user = curl_easy_unescape(data, proxyuser, 0, NULL);
      Curl_safefree(proxyuser);

      if(!proxyinfo->user) {
        Curl_safefree(proxypasswd);
        return CURLE_OUT_OF_MEMORY;
      }

      Curl_safefree(proxyinfo->passwd);
      if(proxypasswd && strlen(proxypasswd) < MAX_CURL_PASSWORD_LENGTH)
        proxyinfo->passwd = curl_easy_unescape(data, proxypasswd, 0, NULL);
      else
        proxyinfo->passwd = strdup("");
      Curl_safefree(proxypasswd);

      if(!proxyinfo->passwd)
        return CURLE_OUT_OF_MEMORY;

      conn->bits.proxy_user_passwd = TRUE; /* enable it */
    }

    if(port >= 0) {
      proxyinfo->port = port;
      if(conn->port < 0 || sockstype || !conn->socks_proxy.host.rawalloc)
        conn->port = port;
    }

    /* now, clone the cleaned proxy host name */
    Curl_safefree(proxyinfo->host.rawalloc);
    proxyinfo->host.rawalloc = strdup(proxyptr);
    proxyinfo->host.name = proxyinfo->host.rawalloc;

    if(!proxyinfo->host.rawalloc)
      return CURLE_OUT_OF_MEMORY;
  }