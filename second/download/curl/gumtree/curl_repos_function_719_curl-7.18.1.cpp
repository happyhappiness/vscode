static CURLcode CreateConnection(struct SessionHandle *data,
                                 struct connectdata **in_connect,
                                 struct Curl_dns_entry **addr,
                                 bool *async)
{

  char *tmp;
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
  char *proxy = NULL;

#ifndef USE_ARES
#ifdef SIGALRM
#ifdef HAVE_SIGACTION
  struct sigaction keep_sigact;   /* store the old struct here */
  bool keep_copysig=FALSE;        /* did copy it? */
#else
#ifdef HAVE_SIGNAL
  void (*keep_sigact)(int);       /* store the old handler here */
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

  conn = (struct connectdata *)calloc(1, sizeof(struct connectdata));
  if(!conn) {
    *in_connect = NULL; /* clear the pointer */
    return CURLE_OUT_OF_MEMORY;
  }
  /* We must set the return variable as soon as possible, so that our
     parent can cleanup any possible allocs we may have done before
     any failure */
  *in_connect = conn;

  conn->handler = &Curl_handler_dummy;  /* Be sure we have a handler defined
                                           already from start to avoid NULL
                                           situations and checks */

  /* and we setup a few fields in case we end up actually using this struct */

  conn->data = data; /* Setup the association between this connection
                        and the SessionHandle */

  conn->sock[FIRSTSOCKET] = CURL_SOCKET_BAD;     /* no file descriptor */
  conn->sock[SECONDARYSOCKET] = CURL_SOCKET_BAD; /* no file descriptor */
  conn->connectindex = -1;    /* no index */

  conn->proxytype = data->set.proxytype; /* type */
  conn->bits.proxy = (bool)(data->set.str[STRING_PROXY] &&
                            *data->set.str[STRING_PROXY]);
  conn->bits.httpproxy = (bool)(conn->bits.proxy
                                && (conn->proxytype == CURLPROXY_HTTP));


  /* Default protocol-independent behavior doesn't support persistent
     connections, so we set this to force-close. Protocols that support
     this need to set this to FALSE in their "curl_do" functions. */
  conn->bits.close = TRUE;

  conn->readchannel_inuse = FALSE;
  conn->writechannel_inuse = FALSE;

  conn->read_pos = 0;
  conn->buf_len = 0;

  /* Store creation time to help future close decision making */
  conn->created = Curl_tvnow();

  conn->bits.user_passwd = (bool)(NULL != data->set.str[STRING_USERPWD]);
  conn->bits.proxy_user_passwd = (bool)(NULL != data->set.str[STRING_PROXYUSERPWD]);
  conn->bits.tunnel_proxy = data->set.tunnel_thru_httpproxy;
  conn->bits.ftp_use_epsv = data->set.ftp_use_epsv;
  conn->bits.ftp_use_eprt = data->set.ftp_use_eprt;

  if(data->multi && Curl_multi_canPipeline(data->multi) &&
      !conn->master_buffer) {
    /* Allocate master_buffer to be used for pipelining */
    conn->master_buffer = calloc(BUFSIZE, sizeof (char));
    if(!conn->master_buffer)
      return CURLE_OUT_OF_MEMORY;
  }

  /* Initialize the pipeline lists */
  conn->send_pipe = Curl_llist_alloc((curl_llist_dtor) llist_dtor);
  conn->recv_pipe = Curl_llist_alloc((curl_llist_dtor) llist_dtor);
  conn->pend_pipe = Curl_llist_alloc((curl_llist_dtor) llist_dtor);
  if(!conn->send_pipe || !conn->recv_pipe || !conn->pend_pipe)
    return CURLE_OUT_OF_MEMORY;

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

  /* Free the old buffer */
  Curl_safefree(data->state.pathbuffer);

  /*
   * We malloc() the buffers below urllen+2 to make room for to possibilities:
   * 1 - an extra terminating zero
   * 2 - an extra slash (in case a syntax like "www.host.com?moo" is used)
   */

  data->state.pathbuffer=(char *)malloc(urllen+2);
  if(NULL == data->state.pathbuffer)
    return CURLE_OUT_OF_MEMORY; /* really bad error */
  data->state.path = data->state.pathbuffer;

  conn->host.rawalloc=(char *)malloc(urllen+2);
  if(NULL == conn->host.rawalloc)
    return CURLE_OUT_OF_MEMORY;

  conn->host.name = conn->host.rawalloc;
  conn->host.name[0] = 0;

  result = ParseURLAndFillConnection(data, conn);
  if(result != CURLE_OK) {
      return result;
  }

  /*************************************************************
   * Take care of proxy authentication stuff
   *************************************************************/
  if(conn->bits.proxy_user_passwd) {
    result = parse_proxy_auth(data, conn);
    if(result != CURLE_OK)
        return result;
  }

  /*************************************************************
   * Detect what (if any) proxy to use
   *************************************************************/
  if(data->set.str[STRING_PROXY]) {
    proxy = strdup(data->set.str[STRING_PROXY]);
    /* if global proxy is set, this is it */
    if(NULL == proxy) {
      failf(data, "memory shortage");
      return CURLE_OUT_OF_MEMORY;
    }
  }

  if(!proxy)
    proxy = detect_proxy(conn);
  if(proxy && !*proxy) {
    free(proxy);  /* Don't bother with an empty proxy string */
    proxy = NULL;
  }
  /* proxy must be freed later unless NULL */

  /*************************************************************
   * No protocol part in URL was used, add it!
   *************************************************************/
  if(conn->protocol&PROT_MISSING) {
    /* We're guessing prefixes here and if we're told to use a proxy or if
       we're gonna follow a Location: later or... then we need the protocol
       part added so that we have a valid URL. */
    char *reurl;

    reurl = aprintf("%s://%s", conn->protostr, data->change.url);

    if(!reurl) {
      Curl_safefree(proxy);
      return CURLE_OUT_OF_MEMORY;
    }

    data->change.url = reurl;
    data->change.url_alloc = TRUE; /* free this later */
    conn->protocol &= ~PROT_MISSING; /* switch that one off again */
  }

  /*************************************************************
   * Setup internals depending on protocol
   *************************************************************/
  result = setup_connection_internals(data, conn);
  if(result != CURLE_OK) {
    Curl_safefree(proxy);
    return result;
  }


  /***********************************************************************
   * If this is supposed to use a proxy, we need to figure out the proxy
   * host name, so that we can re-use an existing connection
   * that may exist registered to the same proxy host.
   ***********************************************************************/
  if(proxy) {
    result = parse_proxy(data, conn, proxy);
    /* parse_proxy has freed the proxy string, so don't try to use it again */
    proxy = NULL;
    if(result != CURLE_OK)
      return result;
  }


  /***********************************************************************
   * file: is a special case in that it doesn't need a network connection
   ***********************************************************************/
#ifndef CURL_DISABLE_FILE
  if(conn->protocol & PROT_FILE) {
    bool done;
    /* this is supposed to be the connect function so we better at least check
       that the file is present here! */
    DEBUGASSERT(conn->handler->connect_it);
    result = conn->handler->connect_it(conn, &done);

    /* Setup a "faked" transfer that'll do nothing */
    if(CURLE_OK == result) {
      conn->data = data;
      conn->bits.tcpconnect = TRUE; /* we are "connected */

      ConnectionStore(data, conn);

      result = setup_range(data);
      if(result) {
        DEBUGASSERT(conn->handler->done);
        /* we ignore the return code for the protocol-specific DONE */
        (void)conn->handler->done(conn, result, FALSE);
        return result;
      }

      result = Curl_setup_transfer(conn, -1, -1, FALSE,
                                   NULL, /* no download */
                                   -1, NULL); /* no upload */
    }

    return result;
  }
#endif

  /*************************************************************
   * If the protocol is using SSL and HTTP proxy is used, we set
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

  if(conn->protocol & (PROT_FTP|PROT_HTTP|PROT_SCP|PROT_SFTP)) {
    /* This is a FTP, HTTP, SCP or SFTP URL, we will now try to extract the
     * possible user+password pair in a string like:
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

      if(data->set.use_netrc != CURL_NETRC_REQUIRED) {
        /* We could use the one in the URL */

        conn->bits.user_passwd = 1; /* enable user+password */

        if(*userpass != ':') {
          /* the name is given, get user+password */
          sscanf(userpass, "%" MAX_CURL_USER_LENGTH_TXT "[^:@]:"
                 "%" MAX_CURL_PASSWORD_LENGTH_TXT "[^@]",
                 user, passwd);
        }
        else
          /* no name given, get the password only */
          sscanf(userpass, ":%" MAX_CURL_PASSWORD_LENGTH_TXT "[^@]", passwd);

        if(user[0]) {
          char *newname=curl_easy_unescape(data, user, 0, NULL);
          if(!newname)
            return CURLE_OUT_OF_MEMORY;
          if(strlen(newname) < sizeof(user))
            strcpy(user, newname);

          /* if the new name is longer than accepted, then just use
             the unconverted name, it'll be wrong but what the heck */
          free(newname);
        }
        if(passwd[0]) {
          /* we have a password found in the URL, decode it! */
          char *newpasswd=curl_easy_unescape(data, passwd, 0, NULL);
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

      url = aprintf("%s://%s:%d%s", conn->protostr, conn->host.name,
                    conn->remote_port, data->state.path);
      if(!url)
        return CURLE_OUT_OF_MEMORY;

      if(data->change.url_alloc)
        free(data->change.url);

      data->change.url = url;
      data->change.url_alloc = TRUE;
    }
  }
  else if(tmp) {
    /* no CURLOPT_PORT given, extract the one from the URL */

    char *rest;
    unsigned long port;

    port=strtoul(tmp+1, &rest, 10);  /* Port number must be decimal */

    if(rest != (tmp+1) && *rest == '\0') {
      /* The colon really did have only digits after it,
       * so it is either a port number or a mistake */

      if(port > 0xffff) {   /* Single unix standard says port numbers are
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
   * user_password is set in "inherit initial knowledge' above,
   * so it doesn't have to be set in this block
   */
  if(data->set.str[STRING_USERPWD] != NULL) {
    /* the name is given, get user+password */
    sscanf(data->set.str[STRING_USERPWD],
           "%" MAX_CURL_USER_LENGTH_TXT "[^:]:"
           "%" MAX_CURL_PASSWORD_LENGTH_TXT "[^\n]",
           user, passwd);
  }

  conn->bits.netrc = FALSE;
  if(data->set.use_netrc != CURL_NETRC_IGNORED) {
    if(Curl_parsenetrc(conn->host.name,
                       user, passwd,
                       data->set.str[STRING_NETRC_FILE])) {
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
  if( (conn->protocol & PROT_FTP) &&
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

  /* Get a cloned copy of the SSL config situation stored in the
     connection struct. But to get this going nicely, we must first make
     sure that the strings in the master copy are pointing to the correct
     strings in the session handle strings array!

     Keep in mind that the pointers in the master copy are pointing to strings
     that will be freed as part of the SessionHandle struct, but all cloned
     copies will be separately allocated.
  */
  data->set.ssl.CApath = data->set.str[STRING_SSL_CAPATH];
  data->set.ssl.CAfile = data->set.str[STRING_SSL_CAFILE];
  data->set.ssl.random_file = data->set.str[STRING_SSL_RANDOM_FILE];
  data->set.ssl.egdsocket = data->set.str[STRING_SSL_EGDSOCKET];
  data->set.ssl.cipher_list = data->set.str[STRING_SSL_CIPHER_LIST];

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

    conn->data = old_conn->data;

    /* get the user+password information from the old_conn struct since it may
     * be new for this request even when we re-use an existing connection */
    conn->bits.user_passwd = old_conn->bits.user_passwd;
    if(conn->bits.user_passwd) {
      /* use the new user namd and password though */
      Curl_safefree(conn->user);
      Curl_safefree(conn->passwd);
      conn->user = old_conn->user;
      conn->passwd = old_conn->passwd;
      old_conn->user = NULL;
      old_conn->passwd = NULL;
    }

    conn->bits.proxy_user_passwd = old_conn->bits.proxy_user_passwd;
    if(conn->bits.proxy_user_passwd) {
      /* use the new proxy user name and proxy password though */
      Curl_safefree(conn->proxyuser);
      Curl_safefree(conn->proxypasswd);
      conn->proxyuser = old_conn->proxyuser;
      conn->proxypasswd = old_conn->proxypasswd;
      old_conn->proxyuser = NULL;
      old_conn->proxypasswd = NULL;
    }

    /* host can change, when doing keepalive with a proxy ! */
    if(conn->bits.proxy) {
      free(conn->host.rawalloc);
      conn->host=old_conn->host;
    }
    else
      free(old_conn->host.rawalloc); /* free the newly allocated name buffer */

    /* re-use init */
    conn->bits.reuse = TRUE; /* yes, we're re-using here */

    Curl_safefree(old_conn->user);
    Curl_safefree(old_conn->passwd);
    Curl_safefree(old_conn->proxyuser);
    Curl_safefree(old_conn->proxypasswd);
    Curl_llist_destroy(old_conn->send_pipe, NULL);
    Curl_llist_destroy(old_conn->recv_pipe, NULL);
    Curl_llist_destroy(old_conn->pend_pipe, NULL);
    Curl_safefree(old_conn->master_buffer);

    free(old_conn);          /* we don't need this anymore */

    *in_connect = conn;      /* return this instead! */

    infof(data, "Re-using existing connection! (#%ld) with host %s\n",
          conn->connectindex,
          conn->proxy.name?conn->proxy.dispname:conn->host.dispname);
  }
  else {
    /*
     * This is a brand new connection, so let's store it in the connection
     * cache of ours!
     */
    ConnectionStore(data, conn);
  }

  result = setup_range(data);
  if(result)
    return result;

  /* Continue connectdata initialization here. */

  /*
   *
   * Inherit the proper values from the urldata struct AFTER we have arranged
   * the persistent connection stuff */
  conn->fread_func = data->set.fread_func;
  conn->fread_in = data->set.in;
  conn->seek_func = data->set.seek_func;
  conn->seek_client = data->set.seek_client;

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
#ifdef HAVE_ALARM
    long shortest;
#endif
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
    shortest = data->set.timeout; /* default to this timeout value */
    if(shortest && data->set.connecttimeout &&
       (data->set.connecttimeout < shortest))
      /* if both are set, pick the shortest */
      shortest = data->set.connecttimeout;
    else if(!shortest)
      /* if timeout is not set, use the connect timeout */
      shortest = data->set.connecttimeout;

    if(shortest < 1000)
      /* the alarm() function only provide integer second resolution, so if
         we want to wait less than one second we must bail out already now. */
      return CURLE_OPERATION_TIMEDOUT;

    /* alarm() makes a signal get sent when the timeout fires off, and that
       will abort system calls */
    prev_alarm = alarm((unsigned int) (shortest ? shortest/1000L : shortest));
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

    if(conn->bits.proxy)
      fix_hostname(data, conn, &conn->host);
  }
  else {
    /* this is a fresh connect */

    /* set a pointer to the hostname we display */
    fix_hostname(data, conn, &conn->host);

    if(!conn->proxy.name || !*conn->proxy.name) {
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
      fix_hostname(data, conn, &conn->proxy);

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
        result = CURLE_OPERATION_TIMEDOUT;
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