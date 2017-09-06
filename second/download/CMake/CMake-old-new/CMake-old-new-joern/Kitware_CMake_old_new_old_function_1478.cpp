static CURLcode CreateConnection(struct SessionHandle *data,
                                 struct connectdata **in_connect)
{
  char *tmp;
  char *buf;
  CURLcode result=CURLE_OK;
  char resumerange[40]="";
  struct connectdata *conn;
  struct connectdata *conn_temp;
  char endbracket;
  int urllen;
#ifdef HAVE_INET_NTOA_R
  char ntoa_buf[64];
#endif
#ifdef HAVE_ALARM
  unsigned int prev_alarm;
#endif

#ifdef HAVE_SIGACTION
  struct sigaction keep_sigact;   /* store the old struct here */
  bool keep_copysig;              /* did copy it? */
#else
#ifdef HAVE_SIGNAL
  void *keep_sigact;              /* store the old handler here */
#endif
#endif

  /*************************************************************
   * Check input data
   *************************************************************/

  if(!data->change.url)
    return CURLE_URL_MALFORMAT;

  /* First, split up the current URL in parts so that we can use the
     parts for checking against the already present connections. In order
     to not have to modify everything at once, we allocate a temporary
     connection data struct and fill in for comparison purposes. */

  conn = (struct connectdata *)malloc(sizeof(struct connectdata));
  if(!conn) {
    *in_connect = NULL; /* clear the pointer */
    return CURLE_OUT_OF_MEMORY;
  }
  /* We must set the return variable as soon as possible, so that our
     parent can cleanup any possible allocs we may have done before
     any failure */
  *in_connect = conn;

  /* we have to init the struct */
  memset(conn, 0, sizeof(struct connectdata));

  /* and we setup a few fields in case we end up actually using this struct */
  conn->data = data;           /* remember our daddy */
  conn->firstsocket = -1;     /* no file descriptor */
  conn->secondarysocket = -1; /* no file descriptor */
  conn->connectindex = -1;    /* no index */
  conn->bits.httpproxy = data->change.proxy?TRUE:FALSE; /* proxy-or-not */
  conn->bits.use_range = data->set.set_range?TRUE:FALSE; /* range status */
  conn->range = data->set.set_range;               /* clone the range setting */
  conn->resume_from = data->set.set_resume_from;   /* inherite resume_from */

  /* Default protocol-independent behavior doesn't support persistant
     connections, so we set this to force-close. Protocols that support
     this need to set this to FALSE in their "curl_do" functions. */
  conn->bits.close = TRUE;
  
  /* inherite initial knowledge from the data struct */
  conn->bits.user_passwd = data->set.userpwd?1:0;
  conn->bits.proxy_user_passwd = data->set.proxyuserpwd?1:0;

  /* maxdownload must be -1 on init, as 0 is a valid value! */
  conn->maxdownload = -1;  /* might have been used previously! */

  /* Store creation time to help future close decision making */
  conn->created = Curl_tvnow();


  /***********************************************************
   * We need to allocate memory to store the path in. We get the size of the
   * full URL to be sure, and we need to make it at least 256 bytes since
   * other parts of the code will rely on this fact
   ***********************************************************/
#define LEAST_PATH_ALLOC 256
  urllen=strlen(data->change.url);
  if(urllen < LEAST_PATH_ALLOC)
    urllen=LEAST_PATH_ALLOC;
  
  conn->path=(char *)malloc(urllen);
  if(NULL == conn->path)
    return CURLE_OUT_OF_MEMORY; /* really bad error */

  /*************************************************************
   * Parse the URL.
   *
   * We need to parse the url even when using the proxy, because we will need
   * the hostname and port in case we are trying to SSL connect through the
   * proxy -- and we don't know if we will need to use SSL until we parse the
   * url ...
   ************************************************************/
  if((2 == sscanf(data->change.url, "%64[^:]://%[^\n]",
                  conn->protostr,
                  conn->path)) && strequal(conn->protostr, "file")) {
    /*
     * we deal with file://<host>/<path> differently since it supports no
     * hostname other than "localhost" and "127.0.0.1", which is unique among
     * the URL protocols specified in RFC 1738
     */
    if(conn->path[0] != '/') {
      /* the URL included a host name, we ignore host names in file:// URLs
         as the standards don't define what to do with them */
      char *ptr=strchr(conn->path, '/');
      if(ptr) {
        /* there was a slash present
           
           RFC1738 (section 3.1, page 5) says:
 
           The rest of the locator consists of data specific to the scheme,
           and is known as the "url-path". It supplies the details of how the
           specified resource can be accessed. Note that the "/" between the
           host (or port) and the url-path is NOT part of the url-path.
 
           As most agents use file://localhost/foo to get '/foo' although the
           slash preceeding foo is a separator and not a slash for the path,
           a URL as file://localhost//foo must be valid as well, to refer to
           the same file with an absolute path.
        */

        if(ptr[1] && ('/' == ptr[1]))
          /* if there was two slashes, we skip the first one as that is then
             used truly as a separator */
          ptr++; 
        
        strcpy(conn->path, ptr);
      }
    }

    strcpy(conn->protostr, "file"); /* store protocol string lowercase */
  }
  else {
    /* Set default host and default path */
    strcpy(conn->gname, "curl.haxx.se");
    strcpy(conn->path, "/");

    if (2 > sscanf(data->change.url,
                   "%64[^\n:]://%512[^\n/]%[^\n]",
                   conn->protostr, conn->gname, conn->path)) {
      
      /*
       * The URL was badly formatted, let's try the browser-style _without_
       * protocol specified like 'http://'.
       */
      if((1 > sscanf(data->change.url, "%512[^\n/]%[^\n]",
                     conn->gname, conn->path)) ) {
        /*
         * We couldn't even get this format.
         */
        failf(data, "<url> malformed");
        return CURLE_URL_MALFORMAT;
      }

      /*
       * Since there was no protocol part specified, we guess what protocol it
       * is based on the first letters of the server name.
       */

      if(strnequal(conn->gname, "FTP", 3)) {
        strcpy(conn->protostr, "ftp");
      }
      else if(strnequal(conn->gname, "GOPHER", 6))
        strcpy(conn->protostr, "gopher");
#ifdef USE_SSLEAY
      else if(strnequal(conn->gname, "HTTPS", 5))
        strcpy(conn->protostr, "https");
      else if(strnequal(conn->gname, "FTPS", 4))
        strcpy(conn->protostr, "ftps");
#endif /* USE_SSLEAY */
      else if(strnequal(conn->gname, "TELNET", 6))
        strcpy(conn->protostr, "telnet");
      else if (strnequal(conn->gname, "DICT", sizeof("DICT")-1))
        strcpy(conn->protostr, "DICT");
      else if (strnequal(conn->gname, "LDAP", sizeof("LDAP")-1))
        strcpy(conn->protostr, "LDAP");
      else {
        strcpy(conn->protostr, "http");
      }

      conn->protocol |= PROT_MISSING; /* not given in URL */
    }
  }

  buf = data->state.buffer; /* this is our buffer */

  /*************************************************************
   * Take care of user and password authentication stuff
   *************************************************************/

  if(conn->bits.user_passwd && !data->set.use_netrc) {
    data->state.user[0] =0;
    data->state.passwd[0]=0;

    if(*data->set.userpwd != ':') {
      /* the name is given, get user+password */
      sscanf(data->set.userpwd, "%127[^:]:%127[^\n]",
             data->state.user, data->state.passwd);
    }
    else
      /* no name given, get the password only */
      sscanf(data->set.userpwd+1, "%127[^\n]", data->state.passwd);

    /* check for password, if no ask for one */
    if( !data->state.passwd[0] ) {
      if(!data->set.fpasswd ||
         data->set.fpasswd(data->set.passwd_client,
                       "password:", data->state.passwd,
                           sizeof(data->state.passwd)))
        return CURLE_BAD_PASSWORD_ENTERED;
    }
  }

  /*************************************************************
   * Take care of proxy authentication stuff
   *************************************************************/
  if(conn->bits.proxy_user_passwd) {
    data->state.proxyuser[0] =0;
    data->state.proxypasswd[0]=0;

    if(*data->set.proxyuserpwd != ':') {
      /* the name is given, get user+password */
      sscanf(data->set.proxyuserpwd, "%127[^:]:%127[^\n]",
             data->state.proxyuser, data->state.proxypasswd);
      }
    else
      /* no name given, get the password only */
      sscanf(data->set.proxyuserpwd+1, "%127[^\n]", data->state.proxypasswd);

    /* check for password, if no ask for one */
    if( !data->state.proxypasswd[0] ) {
      if(!data->set.fpasswd ||
         data->set.fpasswd( data->set.passwd_client,
                        "proxy password:",
                        data->state.proxypasswd,
                        sizeof(data->state.proxypasswd)))
        return CURLE_BAD_PASSWORD_ENTERED;
    }

  }

  /*************************************************************
   * Set a few convenience pointers 
   *************************************************************/
  conn->name = conn->gname;
  conn->ppath = conn->path;
  conn->hostname = conn->name;


  /*************************************************************
   * Detect what (if any) proxy to use
   *************************************************************/
  if(!data->change.proxy) {
    /* If proxy was not specified, we check for default proxy environment
     * variables, to enable i.e Lynx compliance:
     *
     * http_proxy=http://some.server.dom:port/
     * https_proxy=http://some.server.dom:port/
     * ftp_proxy=http://some.server.dom:port/
     * gopher_proxy=http://some.server.dom:port/
     * no_proxy=domain1.dom,host.domain2.dom
     *   (a comma-separated list of hosts which should
     *   not be proxied, or an asterisk to override
     *   all proxy variables)
     * all_proxy=http://some.server.dom:port/
     *   (seems to exist for the CERN www lib. Probably
     *   the first to check for.)
     *
     * For compatibility, the all-uppercase versions of these variables are
     * checked if the lowercase versions don't exist.
     */
    char *no_proxy=NULL;
    char *no_proxy_tok_buf;
    char *proxy=NULL;
    char proxy_env[128];

    no_proxy=curl_getenv("no_proxy");
    if(!no_proxy)
      no_proxy=curl_getenv("NO_PROXY");

    if(!no_proxy || !strequal("*", no_proxy)) {
      /* NO_PROXY wasn't specified or it wasn't just an asterisk */
      char *nope;

      nope=no_proxy?strtok_r(no_proxy, ", ", &no_proxy_tok_buf):NULL;
      while(nope) {
        if(strlen(nope) <= strlen(conn->name)) {
          char *checkn=
            conn->name + strlen(conn->name) - strlen(nope);
          if(strnequal(nope, checkn, strlen(nope))) {
            /* no proxy for this host! */
            break;
          }
        }
        nope=strtok_r(NULL, ", ", &no_proxy_tok_buf);
      }
      if(!nope) {
        /* It was not listed as without proxy */
        char *protop = conn->protostr;
        char *envp = proxy_env;
        char *prox;

        /* Now, build <protocol>_proxy and check for such a one to use */
        while(*protop)
          *envp++ = tolower(*protop++);

        /* append _proxy */
        strcpy(envp, "_proxy");

        /* read the protocol proxy: */
        prox=curl_getenv(proxy_env);

        /*
         * We don't try the uppercase version of HTTP_PROXY because of
         * security reasons:
         *
         * When curl is used in a webserver application
         * environment (cgi or php), this environment variable can
         * be controlled by the web server user by setting the
         * http header 'Proxy:' to some value.
         * 
         * This can cause 'internal' http/ftp requests to be
         * arbitrarily redirected by any external attacker.
         */
        if(!prox && !strequal("http_proxy", proxy_env)) {
          /* There was no lowercase variable, try the uppercase version: */
          for(envp = proxy_env; *envp; envp++)
            *envp = toupper(*envp);
          prox=curl_getenv(proxy_env);
        }

        if(prox && *prox) { /* don't count "" strings */
          proxy = prox; /* use this */
        }
        else {
          proxy = curl_getenv("all_proxy"); /* default proxy to use */
          if(!proxy)
            proxy=curl_getenv("ALL_PROXY");
        }

        if(proxy && *proxy) {
          /* we have a proxy here to set */
          data->change.proxy = proxy;
          data->change.proxy_alloc=TRUE; /* this needs to be freed later */
          conn->bits.httpproxy = TRUE;
        }
      } /* if (!nope) - it wasn't specified non-proxy */
    } /* NO_PROXY wasn't specified or '*' */
    if(no_proxy)
      free(no_proxy);
  } /* if not using proxy */

  /*************************************************************
   * No protocol part in URL was used, add it!
   *************************************************************/
  if(conn->protocol&PROT_MISSING) {
    /* We're guessing prefixes here and if we're told to use a proxy or if
       we're gonna follow a Location: later or... then we need the protocol
       part added so that we have a valid URL. */
    char *reurl;

    reurl = aprintf("%s://%s", conn->protostr, data->change.url);

    if(!reurl)
      return CURLE_OUT_OF_MEMORY;

    data->change.url = reurl;
    data->change.url_alloc = TRUE; /* free this later */
    conn->protocol &= ~PROT_MISSING; /* switch that one off again */
  }

  /************************************************************
   * RESUME on a HTTP page is a tricky business. First, let's just check that
   * 'range' isn't used, then set the range parameter and leave the resume as
   * it is to inform about this situation for later use. We will then
   * "attempt" to resume, and if we're talking to a HTTP/1.1 (or later)
   * server, we will get the document resumed. If we talk to a HTTP/1.0
   * server, we just fail since we can't rewind the file writing from within
   * this function.
   ***********************************************************/
  if(conn->resume_from) {
    if(!conn->bits.use_range) {
      /* if it already was in use, we just skip this */
      snprintf(resumerange, sizeof(resumerange), "%d-", conn->resume_from);
      conn->range=strdup(resumerange); /* tell ourselves to fetch this range */
      conn->bits.rangestringalloc = TRUE; /* mark as allocated */
      conn->bits.use_range = 1; /* switch on range usage */
    }
  }

  /*************************************************************
   * Setup internals depending on protocol
   *************************************************************/

  if (strequal(conn->protostr, "HTTP")) {
    conn->port = (data->set.use_port && data->state.allow_port)?
      data->set.use_port:PORT_HTTP;
    conn->remote_port = PORT_HTTP;
    conn->protocol |= PROT_HTTP;
    conn->curl_do = Curl_http;
    conn->curl_done = Curl_http_done;
    conn->curl_connect = Curl_http_connect;
  }
  else if (strequal(conn->protostr, "HTTPS")) {
#ifdef USE_SSLEAY

    conn->port = (data->set.use_port && data->state.allow_port)?
      data->set.use_port:PORT_HTTPS;
    conn->remote_port = PORT_HTTPS;
    conn->protocol |= PROT_HTTP|PROT_HTTPS|PROT_SSL;

    conn->curl_do = Curl_http;
    conn->curl_done = Curl_http_done;
    conn->curl_connect = Curl_http_connect;

#else /* USE_SSLEAY */
    failf(data, LIBCURL_NAME
          " was built with SSL disabled, https: not supported!");
    return CURLE_UNSUPPORTED_PROTOCOL;
#endif /* !USE_SSLEAY */
  }
  else if (strequal(conn->protostr, "GOPHER")) {
    conn->port = (data->set.use_port && data->state.allow_port)?
      data->set.use_port:PORT_GOPHER;
    conn->remote_port = PORT_GOPHER;
    /* Skip /<item-type>/ in path if present */
    if (isdigit((int)conn->path[1])) {
      conn->ppath = strchr(&conn->path[1], '/');
      if (conn->ppath == NULL)
        conn->ppath = conn->path;
      }
    conn->protocol |= PROT_GOPHER;
    conn->curl_do = Curl_http;
    conn->curl_done = Curl_http_done;
  }
  else if(strequal(conn->protostr, "FTP") ||
          strequal(conn->protostr, "FTPS")) {
    char *type;

    if(strequal(conn->protostr, "FTPS")) {
#ifdef USE_SSLEAY
      conn->protocol |= PROT_FTPS|PROT_SSL;
#else
      failf(data, LIBCURL_NAME
            " was built with SSL disabled, ftps: not supported!");
      return CURLE_UNSUPPORTED_PROTOCOL;
#endif /* !USE_SSLEAY */
    }

    conn->port = (data->set.use_port && data->state.allow_port)?
      data->set.use_port:PORT_FTP;
    conn->remote_port = PORT_FTP;
    conn->protocol |= PROT_FTP;

    if(data->change.proxy &&
       !data->set.tunnel_thru_httpproxy) {
      /* Unless we have asked to tunnel ftp operations through the proxy, we
         switch and use HTTP operations only */
      if(conn->protocol & PROT_FTPS) {
        /* FTPS is a hacked protocol and does not work through your
           ordinary http proxy! */
        failf(data, "ftps does not work through http proxy!");
        return CURLE_UNSUPPORTED_PROTOCOL;
      }
      conn->curl_do = Curl_http;
      conn->curl_done = Curl_http_done;
    }
    else {
      conn->curl_do = Curl_ftp;
      conn->curl_done = Curl_ftp_done;
      conn->curl_connect = Curl_ftp_connect;
      conn->curl_disconnect = Curl_ftp_disconnect;
    }

    conn->ppath++; /* don't include the initial slash */

    /* FTP URLs support an extension like ";type=<typecode>" that
     * we'll try to get now! */
    type=strstr(conn->ppath, ";type=");
    if(!type) {
      type=strstr(conn->gname, ";type=");
    }
    if(type) {
      char command;
      *type=0;
      command = toupper(type[6]);
      switch(command) {
      case 'A': /* ASCII mode */
        data->set.ftp_ascii = 1;
        break;
      case 'D': /* directory mode */
        data->set.ftp_list_only = 1;
        break;
      case 'I': /* binary mode */
      default:
        /* switch off ASCII */
        data->set.ftp_ascii = 0;
        break;
      }
    }
  }
  else if(strequal(conn->protostr, "TELNET")) {
    /* telnet testing factory */
    conn->protocol |= PROT_TELNET;

    conn->port = (data->set.use_port && data->state.allow_port)?
      data->set.use_port: PORT_TELNET;
    conn->remote_port = PORT_TELNET;
    conn->curl_do = Curl_telnet;
    conn->curl_done = Curl_telnet_done;
  }
  else if (strequal(conn->protostr, "DICT")) {
    conn->protocol |= PROT_DICT;
    conn->port = (data->set.use_port && data->state.allow_port)?
      data->set.use_port:PORT_DICT;
    conn->remote_port = PORT_DICT;
    conn->curl_do = Curl_dict;
    conn->curl_done = NULL; /* no DICT-specific done */
  }
  else if (strequal(conn->protostr, "LDAP")) {
    conn->protocol |= PROT_LDAP;
    conn->port = (data->set.use_port && data->state.allow_port)?
      data->set.use_port:PORT_LDAP;
    conn->remote_port = PORT_LDAP;
    conn->curl_do = Curl_ldap;
    conn->curl_done = NULL; /* no LDAP-specific done */
  }
  else if (strequal(conn->protostr, "FILE")) {
    conn->protocol |= PROT_FILE;

    conn->curl_do = Curl_file;
    /* no done() function */

    /* anyway, this is supposed to be the connect function so we better
       at least check that the file is present here! */
    result = Curl_file_connect(conn);

    /* Setup a "faked" transfer that'll do nothing */
    if(CURLE_OK == result) {
      result = Curl_Transfer(conn, -1, -1, FALSE, NULL, /* no download */
                             -1, NULL); /* no upload */
    }

    return result;
  }
  else {
    /* We fell through all checks and thus we don't support the specified
       protocol */
    failf(data, "Unsupported protocol: %s", conn->protostr);
    return CURLE_UNSUPPORTED_PROTOCOL;
  }

  /*************************************************************
   * .netrc scanning coming up
   *************************************************************/
  if(data->set.use_netrc) {
    if(Curl_parsenetrc(conn->hostname,
                       data->state.user,
                       data->state.passwd)) {
      infof(data, "Couldn't find host %s in the .netrc file, using defaults",
            conn->hostname);
    }
    else
      conn->bits.user_passwd = 1; /* enable user+password */

    /* weather we failed or not, we don't know which fields that were filled
       in anyway */
    if(!data->state.user[0])
      strcpy(data->state.user, CURL_DEFAULT_USER);
    if(!data->state.passwd[0])
      strcpy(data->state.passwd, CURL_DEFAULT_PASSWORD);
  }
  else if(!(conn->bits.user_passwd) &&
          (conn->protocol & (PROT_FTP|PROT_HTTP)) ) {
    /* This is a FTP or HTTP URL, and we haven't got the user+password in
     * the extra parameter, we will now try to extract the possible
     * user+password pair in a string like:
     * ftp://user:password@ftp.my.site:8021/README */
    char *ptr=NULL; /* assign to remove possible warnings */
    if((ptr=strchr(conn->name, '@'))) {
      /* there's a user+password given here, to the left of the @ */

      data->state.user[0] =0;
      data->state.passwd[0]=0;

      if(*conn->name != ':') {
        /* the name is given, get user+password */
        sscanf(conn->name, "%127[^:@]:%127[^@]",
               data->state.user, data->state.passwd);
      }
      else
        /* no name given, get the password only */
        sscanf(conn->name+1, "%127[^@]", data->state.passwd);

      if(data->state.user[0]) {
        char *newname=curl_unescape(data->state.user, 0);
        if(strlen(newname) < sizeof(data->state.user)) {
          strcpy(data->state.user, newname);
        }
        /* if the new name is longer than accepted, then just use
           the unconverted name, it'll be wrong but what the heck */
        free(newname);
      }

      /* check for password, if no ask for one */
      if( !data->state.passwd[0] ) {
        if(!data->set.fpasswd ||
           data->set.fpasswd(data->set.passwd_client,
                             "password:", data->state.passwd,
                             sizeof(data->state.passwd)))
          return CURLE_BAD_PASSWORD_ENTERED;
      }
      else {
        /* we have a password found in the URL, decode it! */
        char *newpasswd=curl_unescape(data->state.passwd, 0);
        if(strlen(newpasswd) < sizeof(data->state.passwd)) {
          strcpy(data->state.passwd, newpasswd);
        }
        free(newpasswd);
      }

      conn->name = ++ptr;
      conn->bits.user_passwd=TRUE; /* enable user+password */
    }
    else {
      strcpy(data->state.user, CURL_DEFAULT_USER);
      strcpy(data->state.passwd, CURL_DEFAULT_PASSWORD);
    }
  }

  /*************************************************************
   * Figure out the remote port number
   *
   * No matter if we use a proxy or not, we have to figure out the remote
   * port number of various reasons.
   *
   * To be able to detect port number flawlessly, we must not confuse them
   * IPv6-specified addresses in the [0::1] style. (RFC2732)
   *************************************************************/

  if((1 == sscanf(conn->name, "[%*39[0-9a-fA-F:.]%c", &endbracket)) &&
     (']' == endbracket)) {
    /* This is a (IPv6-style) specified IP-address. We support _any_
       IP within brackets to be really generic. */
    conn->name++; /* pass the starting bracket */

    tmp = strchr(conn->name, ']');
    *tmp = 0; /* zero terminate */

    tmp++; /* pass the ending bracket */
    if(':' != *tmp)
      tmp = NULL; /* no port number available */
  }
  else {
    /* traditional IPv4-style port-extracting */
    tmp = strchr(conn->name, ':');
  }

  if (tmp) {
    *tmp++ = '\0'; /* cut off the name there */
    conn->remote_port = atoi(tmp);
  }

  if(data->change.proxy) {
    /* If this is supposed to use a proxy, we need to figure out the proxy
       host name name, so that we can re-use an existing connection
       that may exist registered to the same proxy host. */

    char *prox_portno;
    char *endofprot;

    /* We need to make a duplicate of the proxy so that we can modify the
       string safely. */
    char *proxydup=strdup(data->change.proxy);

    /* We use 'proxyptr' to point to the proxy name from now on... */
    char *proxyptr=proxydup;

    if(NULL == proxydup) {
      failf(data, "memory shortage");
      return CURLE_OUT_OF_MEMORY;
    }

    /* Daniel Dec 10, 1998:
       We do the proxy host string parsing here. We want the host name and the
       port name. Accept a protocol:// prefix, even though it should just be
       ignored. */

    /* 1. skip the protocol part if present */
    endofprot=strstr(proxyptr, "://");
    if(endofprot) {
      proxyptr = endofprot+3;
    }

    /* allow user to specify proxy.server.com:1080 if desired */
    prox_portno = strchr (proxyptr, ':');
    if (prox_portno) {
      *prox_portno = 0x0; /* cut off number from host name */
      prox_portno ++;
      /* now set the local port number */
      conn->port = atoi(prox_portno);
    }
    else if(data->set.proxyport) {
      /* None given in the proxy string, then get the default one if it is
         given */
      conn->port = data->set.proxyport;
    }

    /* now, clone the cleaned proxy host name */
    conn->proxyhost = strdup(proxyptr);

    free(proxydup); /* free the duplicate pointer and not the modified */
  }

  /*************************************************************
   * Check the current list of connections to see if we can
   * re-use an already existing one or if we have to create a
   * new one.
   *************************************************************/

  /* reuse_fresh is set TRUE if we are told to use a fresh connection
     by force */
  if(!data->set.reuse_fresh &&
     ConnectionExists(data, conn, &conn_temp)) {
    /*
     * We already have a connection for this, we got the former connection
     * in the conn_temp variable and thus we need to cleanup the one we
     * just allocated before we can move along and use the previously
     * existing one.
     */
    struct connectdata *old_conn = conn;
    char *path = old_conn->path; /* setup the current path pointer properly */
    char *ppath = old_conn->ppath; /* this is the modified path pointer */
    if(old_conn->proxyhost)
      free(old_conn->proxyhost);
    conn = conn_temp;        /* use this connection from now on */

    /* we need these pointers if we speak over a proxy */
    conn->hostname = conn->gname;
    conn->name = &conn->gname[old_conn->name - old_conn->gname];

    free(conn->path);    /* free the previously allocated path pointer */

    /* 'path' points to the allocated data, 'ppath' may have been advanced
       to point somewhere within the 'path' area. */
    conn->path = path; 
    conn->ppath = ppath;

    /* re-use init */
    conn->bits.reuse = TRUE; /* yes, we're re-using here */
    conn->bits.chunk = FALSE; /* always assume not chunked unless told
                                 otherwise */
    conn->maxdownload = -1;  /* might have been used previously! */

    free(old_conn);          /* we don't need this anymore */

    /*
     * If we're doing a resumed transfer, we need to setup our stuff
     * properly.
     */
    conn->resume_from = data->set.set_resume_from;
    if (conn->resume_from) {
        snprintf(resumerange, sizeof(resumerange), "%d-", conn->resume_from);
        if (conn->bits.rangestringalloc == TRUE) 
            free(conn->range);
        
        /* tell ourselves to fetch this range */
        conn->range = strdup(resumerange);
        conn->bits.use_range = TRUE;        /* enable range download */
        conn->bits.rangestringalloc = TRUE; /* mark range string allocated */
    }
    else if (data->set.set_range) {
      /* There is a range, but is not a resume, useful for random ftp access */
      conn->range = strdup(data->set.set_range);
      conn->bits.rangestringalloc = TRUE; /* mark range string allocated */
      conn->bits.use_range = TRUE;        /* enable range download */
    }
    
    *in_connect = conn;      /* return this instead! */

    infof(data, "Re-using existing connection! (#%d)\n", conn->connectindex);
  }
  else {
    /*
     * This is a brand new connection, so let's store it in the connection
     * cache of ours!
     */
    ConnectionStore(data, conn);
  }

  /*************************************************************
   * Set timeout if that is being used
   *************************************************************/
  if(data->set.timeout || data->set.connecttimeout) {
    /*************************************************************
     * Set signal handler to catch SIGALRM
     * Store the old value to be able to set it back later!
     *************************************************************/

#ifdef HAVE_SIGACTION
    struct sigaction sigact;
    sigaction(SIGALRM, NULL, &sigact);
    keep_sigact = sigact;
    keep_copysig = TRUE; /* yes, we have a copy */
    sigact.sa_handler = alarmfunc;
#ifdef SA_RESTART
    /* HPUX doesn't have SA_RESTART but defaults to that behaviour! */
    sigact.sa_flags &= ~SA_RESTART;
#endif
    /* now set the new struct */
    sigaction(SIGALRM, &sigact, NULL);
#else
    /* no sigaction(), revert to the much lamer signal() */
#ifdef HAVE_SIGNAL
    keep_sigact = signal(SIGALRM, alarmfunc);
#endif
#endif

    /* We set the timeout on the name resolving phase first, separately from
     * the download/upload part to allow a maximum time on everything. This is
     * a signal-based timeout, why it won't work and shouldn't be used in
     * multi-threaded environments. */

#ifdef HAVE_ALARM
    /* alarm() makes a signal get sent when the timeout fires off, and that
       will abort system calls */
    prev_alarm = alarm(data->set.connecttimeout?
                       data->set.connecttimeout:
                       data->set.timeout);
    /* We can expect the conn->created time to be "now", as that was just
       recently set in the beginning of this function and nothing slow
       has been done since then until now. */
#endif
  }

  /*************************************************************
   * Resolve the name of the server or proxy
   *************************************************************/
  if(!data->change.proxy) {
    /* If not connecting via a proxy, extract the port from the URL, if it is
     * there, thus overriding any defaults that might have been set above. */
    conn->port =  conn->remote_port; /* it is the same port */

    /* Resolve target host right on */
    if(!conn->hostaddr) {
      /* it might already be set if reusing a connection */
      conn->hostaddr = Curl_resolv(data, conn->name, conn->port,
                                   &conn->hostent_buf);
    }
    if(!conn->hostaddr) {
      failf(data, "Couldn't resolve host '%s'", conn->name);
      result =  CURLE_COULDNT_RESOLVE_HOST;
      /* don't return yet, we need to clean up the timeout first */
    }
  }
  else if(!conn->hostaddr) {
    /* This is a proxy that hasn't been resolved yet. It may be resolved
       if we're reusing an existing connection. */

    /* resolve proxy */
    /* it might already be set if reusing a connection */
    conn->hostaddr = Curl_resolv(data, conn->proxyhost, conn->port,
                                 &conn->hostent_buf);

    if(!conn->hostaddr) {
      failf(data, "Couldn't resolve proxy '%s'", conn->proxyhost);
      result = CURLE_COULDNT_RESOLVE_PROXY;
      /* don't return yet, we need to clean up the timeout first */
    }
  }
  Curl_pgrsTime(data, TIMER_NAMELOOKUP);
#ifdef HAVE_ALARM
  if(data->set.timeout || data->set.connecttimeout) {
#ifdef HAVE_SIGACTION
    if(keep_copysig) {
      /* we got a struct as it looked before, now put that one back nice
         and clean */
      sigaction(SIGALRM, &keep_sigact, NULL); /* put it back */
    }
#else
#ifdef HAVE_SIGNAL
    /* restore the previous SIGALRM handler */
    signal(SIGALRM, keep_sigact);
#endif
#endif
    /* switch back the alarm() to either zero or to what it was before minus
       the time we spent until now! */
    if(prev_alarm) {
      /* there was an alarm() set before us, now put it back */
      long elapsed_ms = Curl_tvdiff(Curl_tvnow(), conn->created);
      long alarm_set;

      /* the alarm period is counted in even number of seconds */
      alarm_set = prev_alarm - elapsed_ms/1000;

      if(alarm_set<=0) {
        /* if it turned negative, we should fire off a SIGALRM here, but we
           won't, and zero would be to switch it off so we never set it to
           less than 1! */
        alarm(1);
        result = CURLE_OPERATION_TIMEOUTED;
        failf(data, "Previous alarm fired off!");
      }
      else
        alarm(alarm_set);
    }
    else
      alarm(0); /* just shut it off */
  }
#endif
  if(result)
    return result;

  /*************************************************************
   * Proxy authentication
   *************************************************************/
  if(conn->bits.proxy_user_passwd) {
    char *authorization;
    snprintf(data->state.buffer, BUFSIZE, "%s:%s",
             data->state.proxyuser, data->state.proxypasswd);
    if(Curl_base64_encode(data->state.buffer, strlen(data->state.buffer),
                          &authorization) >= 0) {
      if(conn->allocptr.proxyuserpwd)
        free(conn->allocptr.proxyuserpwd);
      conn->allocptr.proxyuserpwd =
        aprintf("Proxy-authorization: Basic %s\015\012", authorization);
      free(authorization);
    }
  }

  /*************************************************************
   * Send user-agent to HTTP proxies even if the target protocol
   * isn't HTTP.
   *************************************************************/
  if((conn->protocol&PROT_HTTP) || data->change.proxy) {
    if(data->set.useragent) {
      if(conn->allocptr.uagent)
        free(conn->allocptr.uagent);
      conn->allocptr.uagent =
        aprintf("User-Agent: %s\015\012", data->set.useragent);
    }
  }

  if(-1 == conn->firstsocket) {
    /* Connect only if not already connected! */
    result = ConnectPlease(conn);
    if(CURLE_OK != result)
      return result;

    if(conn->curl_connect) {
      /* is there a connect() procedure? */

      /* set start time here for timeout purposes in the
       * connect procedure, it is later set again for the
       * progress meter purpose */
      conn->now = Curl_tvnow();

      /* Call the protocol-specific connect function */
      result = conn->curl_connect(conn);
      if(result != CURLE_OK)
        return result; /* pass back errors */
    }
  }

  Curl_pgrsTime(data, TIMER_CONNECT); /* we're connected */

  conn->now = Curl_tvnow(); /* time this *after* the connect is done */
  conn->bytecount = 0;
  conn->headerbytecount = 0;
  
  /* Figure out the ip-number and display the first host name it shows: */
#ifdef ENABLE_IPV6
  {
    char hbuf[NI_MAXHOST];
#ifdef NI_WITHSCOPEID
    const int niflags = NI_NUMERICHOST | NI_WITHSCOPEID;
#else
    const int niflags = NI_NUMERICHOST;
#endif
    struct addrinfo *ai = conn->serv_addr;

    if (getnameinfo(ai->ai_addr, ai->ai_addrlen, hbuf, sizeof(hbuf), NULL, 0,
        niflags)) {
      snprintf(hbuf, sizeof(hbuf), "?");
    }
    if (ai->ai_canonname) {
      infof(data, "Connected to %s (%s) port %d\n", ai->ai_canonname, hbuf,
            conn->port);
    } else {
      infof(data, "Connected to %s port %d\n", hbuf, conn->port);
    }
  }
#else
  {
    struct in_addr in;
    (void) memcpy(&in.s_addr, &conn->serv_addr.sin_addr, sizeof (in.s_addr));
    infof(data, "Connected to %s (%s)\n", conn->hostaddr->h_name,
#if defined(HAVE_INET_NTOA_R)
          inet_ntoa_r(in, ntoa_buf, sizeof(ntoa_buf))
#else
          inet_ntoa(in)
#endif
          );
  }
#endif

#ifdef __EMX__
  /* 20000330 mgs
   * the check is quite a hack...
   * we're calling _fsetmode to fix the problem with fwrite converting newline
   * characters (you get mangled text files, and corrupted binary files when
   * you download to stdout and redirect it to a file). */

  if ((data->set.out)->_handle == NULL) {
    _fsetmode(stdout, "b");
  }
#endif

  return CURLE_OK;
}