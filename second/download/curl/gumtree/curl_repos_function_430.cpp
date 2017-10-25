static CURLcode CreateConnection(struct SessionHandle *data,
                                 struct connectdata **in_connect,
                                 struct Curl_dns_entry **addr,
                                 bool *async)
{
  char *tmp;
  char *at;
  CURLcode result=CURLE_OK;
  struct connectdata *conn;
  struct connectdata *conn_temp = NULL;
  size_t urllen;
  struct Curl_dns_entry *hostaddr;
#if defined(HAVE_ALARM) && !defined(USE_ARES)
  unsigned int prev_alarm=0;
#endif
  char endbracket;
  char user[MAX_CURL_USER_LENGTH];
  char passwd[MAX_CURL_PASSWORD_LENGTH];
  int rc;
  bool reuse;

#ifndef USE_ARES
#ifdef SIGALRM
#ifdef HAVE_SIGACTION
  struct sigaction keep_sigact;   /* store the old struct here */
  bool keep_copysig=FALSE;        /* did copy it? */
#else
#ifdef HAVE_SIGNAL
  void *keep_sigact;              /* store the old handler here */
#endif /* HAVE_SIGNAL */
#endif /* HAVE_SIGACTION */
#endif /* SIGALRM */
#endif /* USE_ARES */

  *addr = NULL; /* nothing yet */
  *async = FALSE;

  /*************************************************************
   * Check input data
   *************************************************************/

  if(!data->change.url)
    return CURLE_URL_MALFORMAT;

  /* First, split up the current URL in parts so that we can use the
     parts for checking against the already present connections. In order
     to not have to modify everything at once, we allocate a temporary
     connection data struct and fill in for comparison purposes. */

  conn = (struct connectdata *)calloc(sizeof(struct connectdata), 1);
  if(!conn) {
    *in_connect = NULL; /* clear the pointer */
    return CURLE_OUT_OF_MEMORY;
  }
  /* We must set the return variable as soon as possible, so that our
     parent can cleanup any possible allocs we may have done before
     any failure */
  *in_connect = conn;

  /* and we setup a few fields in case we end up actually using this struct */
  conn->data = data;           /* remember our daddy */
  conn->sock[FIRSTSOCKET] = CURL_SOCKET_BAD;     /* no file descriptor */
  conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD; /* no file descriptor */
  conn->connectindex = -1;    /* no index */
  conn->bits.httpproxy = (data->change.proxy && *data->change.proxy &&
                          (data->set.proxytype == CURLPROXY_HTTP))?
    TRUE:FALSE; /* http proxy or not */

  /* Default protocol-independent behavior doesn't support persistant
     connections, so we set this to force-close. Protocols that support
     this need to set this to FALSE in their "curl_do" functions. */
  conn->bits.close = TRUE;

  /* maxdownload must be -1 on init, as 0 is a valid value! */
  conn->maxdownload = -1;  /* might have been used previously! */

  /* Store creation time to help future close decision making */
  conn->created = Curl_tvnow();

  conn->bits.use_range = data->set.set_range?TRUE:FALSE; /* range status */
  conn->range = data->set.set_range;              /* clone the range setting */
  conn->resume_from = data->set.set_resume_from;   /* inherite resume_from */

  conn->bits.user_passwd = data->set.userpwd?1:0;
  conn->bits.proxy_user_passwd = data->set.proxyuserpwd?1:0;
  conn->bits.no_body = data->set.opt_no_body;
  conn->bits.tunnel_proxy = data->set.tunnel_thru_httpproxy;
  conn->bits.ftp_use_epsv = data->set.ftp_use_epsv;
  conn->bits.ftp_use_eprt = data->set.ftp_use_eprt;
  conn->bits.ftp_use_lprt = data->set.ftp_use_lprt;

  /* This initing continues below, see the comment "Continue connectdata
   * initialization here" */

  /***********************************************************
   * We need to allocate memory to store the path in. We get the size of the
   * full URL to be sure, and we need to make it at least 256 bytes since
   * other parts of the code will rely on this fact
   ***********************************************************/
#define LEAST_PATH_ALLOC 256
  urllen=strlen(data->change.url);
  if(urllen < LEAST_PATH_ALLOC)
    urllen=LEAST_PATH_ALLOC;

  conn->pathbuffer=(char *)malloc(urllen);
  if(NULL == conn->pathbuffer)
    return CURLE_OUT_OF_MEMORY; /* really bad error */
  conn->path = conn->pathbuffer;

  conn->host.rawalloc=(char *)malloc(urllen);
  if(NULL == conn->host.rawalloc)
    return CURLE_OUT_OF_MEMORY;
  conn->host.name = conn->host.rawalloc;
  conn->host.name[0] = 0;

  /*************************************************************
   * Parse the URL.
   *
   * We need to parse the url even when using the proxy, because we will need
   * the hostname and port in case we are trying to SSL connect through the
   * proxy -- and we don't know if we will need to use SSL until we parse the
   * url ...
   ************************************************************/
  if((2 == sscanf(data->change.url, "%15[^:]:%[^\n]",
                  conn->protostr,
                  conn->path)) && strequal(conn->protostr, "file")) {
    if(conn->path[0] == '/' && conn->path[1] == '/') {
      /* Allow omitted hostname (e.g. file:/<path>).  This is not strictly
       * speaking a valid file: URL by RFC 1738, but treating file:/<path> as
       * file://localhost/<path> is similar to how other schemes treat missing
       * hostnames.  See RFC 1808. */

      /* This cannot be done with strcpy() in a portable manner, since the
         memory areas overlap! */
      memmove(conn->path, conn->path + 2, strlen(conn->path + 2)+1);
    }
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

        /* This cannot be made with strcpy, as the memory chunks overlap! */
        memmove(conn->path, ptr, strlen(ptr)+1);
      }
    }

    strcpy(conn->protostr, "file"); /* store protocol string lowercase */
  }
  else {
    /* Set default path */
    strcpy(conn->path, "/");

    if (2 > sscanf(data->change.url,
                   "%15[^\n:]://%[^\n/]%[^\n]",
                   conn->protostr,
                   conn->host.name, conn->path)) {

      /*
       * The URL was badly formatted, let's try the browser-style _without_
       * protocol specified like 'http://'.
       */
      if((1 > sscanf(data->change.url, "%[^\n/]%[^\n]",
                     conn->host.name, conn->path)) ) {
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

      /* Note: if you add a new protocol, please update the list in
       * lib/version.c too! */

      if(checkprefix("GOPHER.", conn->host.name))
        strcpy(conn->protostr, "gopher");
#ifdef USE_SSL
      else if(checkprefix("FTPS", conn->host.name))
        strcpy(conn->protostr, "ftps");
#endif /* USE_SSL */
      else if(checkprefix("FTP.", conn->host.name))
        strcpy(conn->protostr, "ftp");
      else if(checkprefix("TELNET.", conn->host.name))
        strcpy(conn->protostr, "telnet");
      else if (checkprefix("DICT.", conn->host.name))
        strcpy(conn->protostr, "DICT");
      else if (checkprefix("LDAP.", conn->host.name))
        strcpy(conn->protostr, "LDAP");
      else {
        strcpy(conn->protostr, "http");
      }

      conn->protocol |= PROT_MISSING; /* not given in URL */
    }
  }

  /* We search for '?' in the host name (but only on the right side of a
   * @-letter to allow ?-letters in username and password) to handle things
   * like http://example.com?param= (notice the missing '/').
   */
  at = strchr(conn->host.name, '@');
  if(at)
    tmp = strchr(at+1, '?');
  else
    tmp = strchr(conn->host.name, '?');

  if(tmp) {
    /* The right part of the ?-letter needs to be moved to prefix
       the current path buffer! */
    size_t len = strlen(tmp);
    /* move the existing path plus the zero byte */
    memmove(conn->path+len+1, conn->path, strlen(conn->path)+1);
    conn->path[0]='/'; /* prepend the missing slash */
    memcpy(conn->path+1, tmp, len); /* now copy the prefix part */
    *tmp=0; /* now cut off the hostname at the ? */
  }

  /* If the URL is malformatted (missing a '/' after hostname before path) we
   * insert a slash here. The only letter except '/' we accept to start a path
   * is '?'.
   */
  if(conn->path[0] == '?') {
    /* We need this function to deal with overlapping memory areas. We know
       that the memory area 'path' points to is 'urllen' bytes big and that
       is bigger than the path. Use +1 to move the zero byte too. */
    memmove(&conn->path[1], conn->path, strlen(conn->path)+1);
    conn->path[0] = '/';
  }

  /*
   * So if the URL was A://B/C,
   *   conn->protostr is A
   *   conn->host.name is B
   *   conn->path is /C
   */

  /*************************************************************
   * Take care of proxy authentication stuff
   *************************************************************/
  if(conn->bits.proxy_user_passwd) {
    char proxyuser[MAX_CURL_USER_LENGTH]="";
    char proxypasswd[MAX_CURL_PASSWORD_LENGTH]="";

    sscanf(data->set.proxyuserpwd,
           "%" MAX_CURL_USER_LENGTH_TXT "[^:]:"
           "%" MAX_CURL_PASSWORD_LENGTH_TXT "[^\n]",
           proxyuser, proxypasswd);

    conn->proxyuser = strdup(proxyuser);
    if(!conn->proxyuser)
      return CURLE_OUT_OF_MEMORY;

    conn->proxypasswd = strdup(proxypasswd);
    if(!conn->proxypasswd)
      return CURLE_OUT_OF_MEMORY;
  }

#ifndef CURL_DISABLE_HTTP
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
        size_t namelen;
        char *endptr = strchr(conn->host.name, ':');
        if(endptr)
          namelen=endptr-conn->host.name;
        else
          namelen=strlen(conn->host.name);

        if(strlen(nope) <= namelen) {
          char *checkn=
            conn->host.name + namelen - strlen(nope);
          if(checkprefix(nope, checkn)) {
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
          *envp++ = tolower((int)*protop++);

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
            *envp = toupper((int)*envp);
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
          char *ptr;
          char proxyuser[MAX_CURL_USER_LENGTH];
          char proxypasswd[MAX_CURL_PASSWORD_LENGTH];

          char *fineptr;

          /* skip the possible protocol piece */
          ptr=strstr(proxy, "://");
          if(ptr)
            ptr += 3;
          else
            ptr = proxy;

          fineptr = ptr;

          /* check for an @-letter */
          ptr = strchr(ptr, '@');
          if(ptr && (2 == sscanf(fineptr,
                                 "%" MAX_CURL_USER_LENGTH_TXT"[^:]:"
                                 "%" MAX_CURL_PASSWORD_LENGTH_TXT "[^@]",
                                 proxyuser, proxypasswd))) {
            CURLcode res = CURLE_OK;

            /* found user and password, rip them out */
            Curl_safefree(conn->proxyuser);
            conn->proxyuser = strdup(proxyuser);

            if(!conn->proxyuser)
              res = CURLE_OUT_OF_MEMORY;
            else {
              Curl_safefree(conn->proxypasswd);
              conn->proxypasswd = strdup(proxypasswd);

              if(!conn->proxypasswd)
                res = CURLE_OUT_OF_MEMORY;
            }

            if(CURLE_OK == res) {
              conn->bits.proxy_user_passwd = TRUE; /* enable it */
              ptr = strdup(ptr+1); /* the right side of the @-letter */

              if(ptr) {
                free(proxy); /* free the former proxy string */
                proxy = ptr; /* now use this instead */
              }
              else
                res = CURLE_OUT_OF_MEMORY;
            }

            if(res) {
              free(proxy); /* free the allocated proxy string */
              return res;
            }
          }

          data->change.proxy = proxy;
          data->change.proxy_alloc=TRUE; /* this needs to be freed later */
          conn->bits.httpproxy = TRUE;
        }
      } /* if (!nope) - it wasn't specified non-proxy */
    } /* NO_PROXY wasn't specified or '*' */
    if(no_proxy)
      free(no_proxy);
  } /* if not using proxy */
#endif /* CURL_DISABLE_HTTP */

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

#ifndef CURL_DISABLE_HTTP
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
      conn->range = aprintf("%" FORMAT_OFF_T "-", conn->resume_from);
      if(!conn->range)
        return CURLE_OUT_OF_MEMORY;
      conn->bits.rangestringalloc = TRUE; /* mark as allocated */
      conn->bits.use_range = 1; /* switch on range usage */
    }
  }
#endif
  /*************************************************************
   * Setup internals depending on protocol
   *************************************************************/

  if (strequal(conn->protostr, "HTTP")) {
#ifndef CURL_DISABLE_HTTP
    conn->port = PORT_HTTP;
    conn->remote_port = PORT_HTTP;
    conn->protocol |= PROT_HTTP;
    conn->curl_do = Curl_http;
    conn->curl_do_more = NULL;
    conn->curl_done = Curl_http_done;
    conn->curl_connect = Curl_http_connect;
#else
    failf(data, LIBCURL_NAME
          " was built with HTTP disabled, http: not supported!");
    return CURLE_UNSUPPORTED_PROTOCOL;
#endif
  }
  else if (strequal(conn->protostr, "HTTPS")) {
#if defined(USE_SSL) && !defined(CURL_DISABLE_HTTP)

    conn->port = PORT_HTTPS;
    conn->remote_port = PORT_HTTPS;
    conn->protocol |= PROT_HTTP|PROT_HTTPS|PROT_SSL;

    conn->curl_do = Curl_http;
    conn->curl_do_more = NULL;
    conn->curl_done = Curl_http_done;
    conn->curl_connect = Curl_http_connect;

#else /* USE_SS */
    failf(data, LIBCURL_NAME
          " was built with SSL disabled, https: not supported!");
    return CURLE_UNSUPPORTED_PROTOCOL;
#endif /* !USE_SSL */
  }
  else if (strequal(conn->protostr, "GOPHER")) {
#ifndef CURL_DISABLE_GOPHER
    conn->port = PORT_GOPHER;
    conn->remote_port = PORT_GOPHER;
    /* Skip /<item-type>/ in path if present */
    if (isdigit((int)conn->path[1])) {
      conn->path = strchr(&conn->path[1], '/');
      if (conn->path == NULL)
        conn->path = conn->pathbuffer;
    }
    conn->protocol |= PROT_GOPHER;
    conn->curl_do = Curl_http;
    conn->curl_do_more = NULL;
    conn->curl_done = Curl_http_done;
#else
    failf(data, LIBCURL_NAME
          " was built with GOPHER disabled, gopher: not supported!");
#endif
  }
  else if(strequal(conn->protostr, "FTP") ||
          strequal(conn->protostr, "FTPS")) {

#ifndef CURL_DISABLE_FTP
    char *type;
    int port = PORT_FTP;

    if(strequal(conn->protostr, "FTPS")) {
#ifdef USE_SSL
      conn->protocol |= PROT_FTPS|PROT_SSL;
      conn->ssl[SECONDARYSOCKET].use = TRUE; /* send data securely */
      port = PORT_FTPS;
#else
      failf(data, LIBCURL_NAME
            " was built with SSL disabled, ftps: not supported!");
      return CURLE_UNSUPPORTED_PROTOCOL;
#endif /* !USE_SSL */
    }

    conn->port = port;
    conn->remote_port = port;
    conn->protocol |= PROT_FTP;

    if(data->change.proxy &&
       *data->change.proxy &&
       !data->set.tunnel_thru_httpproxy) {
      /* Unless we have asked to tunnel ftp operations through the proxy, we
         switch and use HTTP operations only */
      if(conn->protocol & PROT_FTPS) {
        /* FTPS is a hacked protocol and does not work through your
           ordinary http proxy! */
        failf(data, "ftps does not work through http proxy!");
        return CURLE_UNSUPPORTED_PROTOCOL;
      }
#ifndef CURL_DISABLE_HTTP
      conn->curl_do = Curl_http;
      conn->curl_done = Curl_http_done;
#else
      failf(data, "FTP over http proxy requires HTTP support built-in!");
      return CURLE_UNSUPPORTED_PROTOCOL;
#endif
    }
    else {
      conn->curl_do = Curl_ftp;
      conn->curl_do_more = Curl_ftp_nextconnect;
      conn->curl_done = Curl_ftp_done;
      conn->curl_connect = Curl_ftp_connect;
      conn->curl_connecting = Curl_ftp_multi_statemach;
      conn->curl_doing = Curl_ftp_doing;
      conn->curl_proto_fdset = Curl_ftp_fdset;
      conn->curl_doing_fdset = Curl_ftp_fdset;
      conn->curl_disconnect = Curl_ftp_disconnect;
    }

    conn->path++; /* don't include the initial slash */

    /* FTP URLs support an extension like ";type=<typecode>" that
     * we'll try to get now! */
    type=strstr(conn->path, ";type=");
    if(!type) {
      type=strstr(conn->host.rawalloc, ";type=");
    }
    if(type) {
      char command;
      *type=0;                     /* it was in the middle of the hostname */
      command = toupper((int)type[6]);
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
#else /* CURL_DISABLE_FTP */
    failf(data, LIBCURL_NAME
          " was built with FTP disabled, ftp/ftps: not supported!");
    return CURLE_UNSUPPORTED_PROTOCOL;
#endif
  }
  else if(strequal(conn->protostr, "TELNET")) {
#ifndef CURL_DISABLE_TELNET
    /* telnet testing factory */
    conn->protocol |= PROT_TELNET;

    conn->port = PORT_TELNET;
    conn->remote_port = PORT_TELNET;
    conn->curl_do = Curl_telnet;
    conn->curl_done = Curl_telnet_done;
#else
    failf(data, LIBCURL_NAME
          " was built with TELNET disabled!");
#endif
  }
  else if (strequal(conn->protostr, "DICT")) {
#ifndef CURL_DISABLE_DICT
    conn->protocol |= PROT_DICT;
    conn->port = PORT_DICT;
    conn->remote_port = PORT_DICT;
    conn->curl_do = Curl_dict;
    conn->curl_done = NULL; /* no DICT-specific done */
#else
    failf(data, LIBCURL_NAME
          " was built with DICT disabled!");
#endif
  }
  else if (strequal(conn->protostr, "LDAP")) {
#ifndef CURL_DISABLE_LDAP
    conn->protocol |= PROT_LDAP;
    conn->port = PORT_LDAP;
    conn->remote_port = PORT_LDAP;
    conn->curl_do = Curl_ldap;
    conn->curl_done = NULL; /* no LDAP-specific done */
#else
    failf(data, LIBCURL_NAME
          " was built with LDAP disabled!");
#endif
  }
  else if (strequal(conn->protostr, "FILE")) {
#ifndef CURL_DISABLE_FILE
    conn->protocol |= PROT_FILE;

    conn->curl_do = Curl_file;
    conn->curl_done = Curl_file_done;

    /* anyway, this is supposed to be the connect function so we better
       at least check that the file is present here! */
    result = Curl_file_connect(conn);

    /* Setup a "faked" transfer that'll do nothing */
    if(CURLE_OK == result) {
      conn->bits.tcpconnect = TRUE; /* we are "connected */
      result = Curl_Transfer(conn, -1, -1, FALSE, NULL, /* no download */
                             -1, NULL); /* no upload */
    }

    return result;
#else
    failf(data, LIBCURL_NAME
          " was built with FILE disabled!");
#endif
  }
  else {
    /* We fell through all checks and thus we don't support the specified
       protocol */
    failf(data, "Unsupported protocol: %s", conn->protostr);
    return CURLE_UNSUPPORTED_PROTOCOL;
  }

  if(data->change.proxy && *data->change.proxy) {
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
    conn->proxy.rawalloc = strdup(proxyptr);
    conn->proxy.name = conn->proxy.rawalloc;

    free(proxydup); /* free the duplicate pointer and not the modified */
    if(!conn->proxy.rawalloc)
      return CURLE_OUT_OF_MEMORY;
  }

  /*************************************************************
   * If the protcol is using SSL and HTTP proxy is used, we set
   * the tunnel_proxy bit.
   *************************************************************/
  if((conn->protocol&PROT_SSL) && conn->bits.httpproxy)
    conn->bits.tunnel_proxy = TRUE;

  /*************************************************************
   * Take care of user and password authentication stuff
   *************************************************************/

  /*
   * Inputs: data->set.userpwd   (CURLOPT_USERPWD)
   *         data->set.fpasswd   (CURLOPT_PASSWDFUNCTION)
   *         data->set.use_netrc (CURLOPT_NETRC)
   *         conn->host.name
   *         netrc file
   *         hard-coded defaults
   *
   * Outputs: (almost :- all currently undefined)
   *          conn->bits.user_passwd  - non-zero if non-default passwords exist
   *          conn->user              - non-zero length if defined
   *          conn->passwd            -   ditto
   *          conn->host.name          - remove user name and password
   */

  /* At this point, we're hoping all the other special cases have
   * been taken care of, so conn->host.name is at most
   *    [user[:password]]@]hostname
   *
   * We need somewhere to put the embedded details, so do that first.
   */

  user[0] =0;   /* to make everything well-defined */
  passwd[0]=0;

  if (conn->protocol & (PROT_FTP|PROT_HTTP)) {
    /* This is a FTP or HTTP URL, we will now try to extract the possible
     * user+password pair in a string like:
     * ftp://user:password@ftp.my.site:8021/README */
    char *ptr=strchr(conn->host.name, '@');
    char *userpass = conn->host.name;
    if(ptr != NULL) {
      /* there's a user+password given here, to the left of the @ */

      conn->host.name = ++ptr;

      /* So the hostname is sane.  Only bother interpreting the
       * results if we could care.  It could still be wasted
       * work because it might be overtaken by the programmatically
       * set user/passwd, but doing that first adds more cases here :-(
       */

      if (data->set.use_netrc != CURL_NETRC_REQUIRED) {
        /* We could use the one in the URL */

        conn->bits.user_passwd = 1; /* enable user+password */

        if(*userpass != ':') {
          /* the name is given, get user+password */
          sscanf(userpass, "%127[^:@]:%127[^@]",
                 user, passwd);
        }
        else
          /* no name given, get the password only */
          sscanf(userpass, ":%127[^@]", passwd);

        if(user[0]) {
          char *newname=curl_unescape(user, 0);
          if(!newname)
            return CURLE_OUT_OF_MEMORY;
          if(strlen(newname) < sizeof(user))
            strcpy(user, newname);

          /* if the new name is longer than accepted, then just use
             the unconverted name, it'll be wrong but what the heck */
          free(newname);
        }
        if (passwd[0]) {
          /* we have a password found in the URL, decode it! */
          char *newpasswd=curl_unescape(passwd, 0);
          if(!newpasswd)
            return CURLE_OUT_OF_MEMORY;
          if(strlen(newpasswd) < sizeof(passwd))
            strcpy(passwd, newpasswd);

          free(newpasswd);
        }
      }
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
   *
   * The conn->host.name is currently [user:passwd@]host[:port] where host
   * could be a hostname, IPv4 address or IPv6 address.
   *************************************************************/
  if((1 == sscanf(conn->host.name, "[%*39[0-9a-fA-F:.]%c", &endbracket)) &&
     (']' == endbracket)) {
    /* this is a RFC2732-style specified IP-address */
    conn->bits.ipv6_ip = TRUE;

    conn->host.name++; /* pass the starting bracket */
    tmp = strchr(conn->host.name, ']');
    *tmp = 0; /* zero terminate */
    tmp++; /* pass the ending bracket */
    if(':' != *tmp)
      tmp = NULL; /* no port number available */
  }
  else
    tmp = strrchr(conn->host.name, ':');

  if(data->set.use_port && data->state.allow_port) {
    /* if set, we use this and ignore the port possibly given in the URL */
    conn->remote_port = (unsigned short)data->set.use_port;
    if(tmp)
      *tmp = '\0'; /* cut off the name there anyway - if there was a port
                      number - since the port number is to be ignored! */
    if(conn->bits.httpproxy) {
      /* we need to create new URL with the new port number */
      char *url;

      url = aprintf("http://%s:%d%s", conn->host.name, conn->remote_port,
                    conn->path);
      if(!url)
        return CURLE_OUT_OF_MEMORY;

      if(data->change.url_alloc)
        free(data->change.url);

      data->change.url = url;
      data->change.url_alloc = TRUE;
    }
  }
  else if (tmp) {
    /* no CURLOPT_PORT given, extract the one from the URL */

    char *rest;
    unsigned long port;

    port=strtoul(tmp+1, &rest, 10);  /* Port number must be decimal */

    if (rest != (tmp+1) && *rest == '\0') {
      /* The colon really did have only digits after it,
       * so it is either a port number or a mistake */

      if (port > 0xffff) {   /* Single unix standard says port numbers are
                              * 16 bits long */
        failf(data, "Port number too large: %lu", port);
        return CURLE_URL_MALFORMAT;
      }

      *tmp = '\0'; /* cut off the name there */
      conn->remote_port = (unsigned short)port;
    }
  }

  /* Programmatically set password:
   *   - always applies, if available
   *   - takes precedence over the values we just set above
   * so scribble it over the top.
   * User-supplied passwords are assumed not to need unescaping.
   *
   * user_password is set in "inherite initial knowledge' above,
   * so it doesn't have to be set in this block
   */
  if (data->set.userpwd != NULL) {
    /* the name is given, get user+password */
    sscanf(data->set.userpwd,
           "%" MAX_CURL_USER_LENGTH_TXT "[^:]:"
           "%" MAX_CURL_PASSWORD_LENGTH_TXT "[^\n]",
           user, passwd);
  }

  conn->bits.netrc = FALSE;
  if (data->set.use_netrc != CURL_NETRC_IGNORED) {
    if(Curl_parsenetrc(conn->host.name,
                       user, passwd,
                       data->set.netrc_file)) {
      infof(data, "Couldn't find host %s in the " DOT_CHAR
            "netrc file, using defaults\n",
            conn->host.name);
    }
    else {
      /* set bits.netrc TRUE to remember that we got the name from a .netrc
         file, so that it is safe to use even if we followed a Location: to a
         different host or similar. */
      conn->bits.netrc = TRUE;

      conn->bits.user_passwd = 1; /* enable user+password */
    }
  }

  /* If our protocol needs a password and we have none, use the defaults */
  if ( (conn->protocol & PROT_FTP) &&
       !conn->bits.user_passwd) {

    conn->user = strdup(CURL_DEFAULT_USER);
    conn->passwd = strdup(CURL_DEFAULT_PASSWORD);
    /* This is the default password, so DON'T set conn->bits.user_passwd */
  }
  else {
    /* store user + password, zero-length if not set */
    conn->user = strdup(user);
    conn->passwd = strdup(passwd);
  }
  if(!conn->user || !conn->passwd)
    return CURLE_OUT_OF_MEMORY;

  /*************************************************************
   * Check the current list of connections to see if we can
   * re-use an already existing one or if we have to create a
   * new one.
   *************************************************************/

  /* get a cloned copy of the SSL config situation stored in the
     connection struct */
  if(!Curl_clone_ssl_config(&data->set.ssl, &conn->ssl_config))
    return CURLE_OUT_OF_MEMORY;

  /* reuse_fresh is TRUE if we are told to use a new connection by force, but
     we only acknowledge this option if this is not a re-used connection
     already (which happens due to follow-location or during a HTTP
     authentication phase). */
  if(data->set.reuse_fresh && !data->state.this_is_a_follow)
    reuse = FALSE;
  else
    reuse = ConnectionExists(data, conn, &conn_temp);

  if(reuse) {
    /*
     * We already have a connection for this, we got the former connection
     * in the conn_temp variable and thus we need to cleanup the one we
     * just allocated before we can move along and use the previously
     * existing one.
     */
    struct connectdata *old_conn = conn;

    if(old_conn->proxy.rawalloc)
      free(old_conn->proxy.rawalloc);

    /* free the SSL config struct from this connection struct as this was
       allocated in vain and is targeted for destruction */
    Curl_free_ssl_config(&conn->ssl_config);

    conn = conn_temp;        /* use this connection from now on */

    /* get the user+password information from the old_conn struct since it may
     * be new for this request even when we re-use an existing connection */
    conn->bits.user_passwd = old_conn->bits.user_passwd;
    if (conn->bits.user_passwd) {
      /* use the new user namd and password though */
      Curl_safefree(conn->user);
      Curl_safefree(conn->passwd);
      conn->user = old_conn->user;
      conn->passwd = old_conn->passwd;
      old_conn->user = NULL;
      old_conn->passwd = NULL;
    }

    conn->bits.proxy_user_passwd = old_conn->bits.proxy_user_passwd;
    if (conn->bits.proxy_user_passwd) {
      /* use the new proxy user name and proxy password though */
      Curl_safefree(conn->proxyuser);
      Curl_safefree(conn->proxypasswd);
      conn->proxyuser = old_conn->proxyuser;
      conn->proxypasswd = old_conn->proxypasswd;
      old_conn->proxyuser = NULL;
      old_conn->proxypasswd = NULL;
    }

    /* host can change, when doing keepalive with a proxy ! */
    if (conn->bits.httpproxy) {
      free(conn->host.rawalloc);
      conn->host=old_conn->host;
    }

    /* get the newly set value, not the old one */
    conn->bits.no_body = old_conn->bits.no_body;

    if (!conn->bits.httpproxy)
      free(old_conn->host.rawalloc); /* free the newly allocated name buffer */

    free(conn->pathbuffer); /* free the newly allocated path pointer */
    conn->pathbuffer = old_conn->pathbuffer; /* use the old one */
    conn->path = old_conn->path;

    /* re-use init */
    conn->bits.reuse = TRUE; /* yes, we're re-using here */
    conn->bits.chunk = FALSE; /* always assume not chunked unless told
                                 otherwise */
    conn->maxdownload = -1;  /* might have been used previously! */

    Curl_safefree(old_conn->user);
    Curl_safefree(old_conn->passwd);
    Curl_safefree(old_conn->proxyuser);
    Curl_safefree(old_conn->proxypasswd);

    if(old_conn->bits.rangestringalloc)
      free(old_conn->range);

    free(old_conn);          /* we don't need this anymore */

    /*
     * If we're doing a resumed transfer, we need to setup our stuff
     * properly.
     */
    conn->resume_from = data->set.set_resume_from;
    if (conn->resume_from) {
      if (conn->bits.rangestringalloc == TRUE)
        free(conn->range);
      conn->range = aprintf("%" FORMAT_OFF_T "-", conn->resume_from);
      if(!conn->range)
        return CURLE_OUT_OF_MEMORY;

      /* tell ourselves to fetch this range */
      conn->bits.use_range = TRUE;        /* enable range download */
      conn->bits.rangestringalloc = TRUE; /* mark range string allocated */
    }
    else if (data->set.set_range) {
      /* There is a range, but is not a resume, useful for random ftp access */
      conn->range = strdup(data->set.set_range);
      if(!conn->range)
        return CURLE_OUT_OF_MEMORY;
      conn->bits.rangestringalloc = TRUE; /* mark range string allocated */
      conn->bits.use_range = TRUE;        /* enable range download */
    }
    else
      conn->bits.use_range = FALSE; /* disable range download */

    *in_connect = conn;      /* return this instead! */

    infof(data, "Re-using existing connection! (#%ld) with host %s\n",
          conn->connectindex,
          conn->bits.httpproxy?conn->proxy.dispname:conn->host.dispname);
  }
  else {
    /*
     * This is a brand new connection, so let's store it in the connection
     * cache of ours!
     */
    ConnectionStore(data, conn);
  }

  /* Continue connectdata initialization here.
   *
   * Inherit the proper values from the urldata struct AFTER we have arranged
   * the persistant conncetion stuff */
  conn->fread = data->set.fread;
  conn->fread_in = data->set.in;

  conn->bits.upload_chunky =
    ((conn->protocol&PROT_HTTP) &&
     data->set.upload &&
     (data->set.infilesize == -1) &&
     (data->set.httpversion != CURL_HTTP_VERSION_1_0))?
    /* HTTP, upload, unknown file size and not HTTP 1.0 */
    TRUE:
  /* else, no chunky upload */
  FALSE;

#ifndef USE_ARES
  /*************************************************************
   * Set timeout if that is being used, and we're not using an asynchronous
   * name resolve.
   *************************************************************/
  if((data->set.timeout || data->set.connecttimeout) && !data->set.no_signal) {
    /*************************************************************
     * Set signal handler to catch SIGALRM
     * Store the old value to be able to set it back later!
     *************************************************************/

#ifdef SIGALRM
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
#else /* HAVE_SIGACTION */
    /* no sigaction(), revert to the much lamer signal() */
#ifdef HAVE_SIGNAL
    keep_sigact = signal(SIGALRM, alarmfunc);
#endif
#endif /* HAVE_SIGACTION */

    /* We set the timeout on the name resolving phase first, separately from
     * the download/upload part to allow a maximum time on everything. This is
     * a signal-based timeout, why it won't work and shouldn't be used in
     * multi-threaded environments. */

#ifdef HAVE_ALARM
    /* alarm() makes a signal get sent when the timeout fires off, and that
       will abort system calls */
    prev_alarm = alarm((unsigned int) (data->set.connecttimeout?
                                       data->set.connecttimeout:
                                       data->set.timeout));
    /* We can expect the conn->created time to be "now", as that was just
       recently set in the beginning of this function and nothing slow
       has been done since then until now. */
#endif
#endif /* SIGALRM */
  }
#endif /* USE_ARES */

  /*************************************************************
   * Resolve the name of the server or proxy
   *************************************************************/
  if(conn->bits.reuse) {
    /* re-used connection, no resolving is necessary */
    hostaddr = NULL;
    /* we'll need to clear conn->dns_entry later in Curl_disconnect() */

    if (conn->bits.httpproxy)
      fix_hostname(conn, &conn->host);
  }
  else {
    /* this is a fresh connect */

    /* set a pointer to the hostname we display */
    fix_hostname(conn, &conn->host);

    if(!data->change.proxy || !*data->change.proxy) {
      /* If not connecting via a proxy, extract the port from the URL, if it is
       * there, thus overriding any defaults that might have been set above. */
      conn->port =  conn->remote_port; /* it is the same port */

      /* Resolve target host right on */
      rc = Curl_resolv(conn, conn->host.name, (int)conn->port, &hostaddr);
      if(rc == CURLRESOLV_PENDING)
        *async = TRUE;

      else if(!hostaddr) {
        failf(data, "Couldn't resolve host '%s'", conn->host.dispname);
        result =  CURLE_COULDNT_RESOLVE_HOST;
        /* don't return yet, we need to clean up the timeout first */
      }
    }
    else {
      /* This is a proxy that hasn't been resolved yet. */

      /* IDN-fix the proxy name */
      fix_hostname(conn, &conn->proxy);

      /* resolve proxy */
      rc = Curl_resolv(conn, conn->proxy.name, (int)conn->port, &hostaddr);

      if(rc == CURLRESOLV_PENDING)
        *async = TRUE;

      else if(!hostaddr) {
        failf(data, "Couldn't resolve proxy '%s'", conn->proxy.dispname);
        result = CURLE_COULDNT_RESOLVE_PROXY;
        /* don't return yet, we need to clean up the timeout first */
      }
    }
  }
  *addr = hostaddr;

#if defined(HAVE_ALARM) && defined(SIGALRM) && !defined(USE_ARES)
  if((data->set.timeout || data->set.connecttimeout) && !data->set.no_signal) {
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
#endif /* HAVE_SIGACTION */

    /* switch back the alarm() to either zero or to what it was before minus
       the time we spent until now! */
    if(prev_alarm) {
      /* there was an alarm() set before us, now put it back */
      unsigned long elapsed_ms = Curl_tvdiff(Curl_tvnow(), conn->created);
      unsigned long alarm_set;

      /* the alarm period is counted in even number of seconds */
      alarm_set = prev_alarm - elapsed_ms/1000;

      if(!alarm_set ||
         ((alarm_set >= 0x80000000) && (prev_alarm < 0x80000000)) ) {
        /* if the alarm time-left reached zero or turned "negative" (counted
           with unsigned values), we should fire off a SIGALRM here, but we
           won't, and zero would be to switch it off so we never set it to
           less than 1! */
        alarm(1);
        result = CURLE_OPERATION_TIMEOUTED;
        failf(data, "Previous alarm fired off!");
      }
      else
        alarm((unsigned int)alarm_set);
    }
    else
      alarm(0); /* just shut it off */
  }
#endif

  return result;
}