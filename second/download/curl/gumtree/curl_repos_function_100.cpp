CURLcode curl_connect(CURL *curl, CURLconnect **in_connect)
{
  char *tmp;
  char *buf;
  CURLcode result;
  char resumerange[12]="";
  struct UrlData *data = curl;
  struct connectdata *conn;

  /* I believe the longest possible name in a DNS is set to 255 letters, FQDN.
     Although the buffer required for storing all possible aliases and IP
     numbers is according to Stevens' Unix Network Programming 2nd editor,
     p. 304: 8192 bytes. Let's go with that! */
  char hostent_buf[8192];

  if(!data || (data->handle != STRUCT_OPEN))
    return CURLE_BAD_FUNCTION_ARGUMENT; /* TBD: make error codes */

  if(!data->url)
    return CURLE_URL_MALFORMAT;

  conn = (struct connectdata *)malloc(sizeof(struct connectdata));
  if(!conn) {
    *in_connect = NULL; /* clear the pointer */
    return CURLE_OUT_OF_MEMORY;
  }
  *in_connect = conn;

  memset(conn, 0, sizeof(struct connectdata));
  conn->handle = STRUCT_CONNECT;

  conn->data = data; /* remember our daddy */
  conn->state = CONN_INIT;

  buf = data->buffer; /* this is our buffer */

#if 0
  signal(SIGALRM, alarmfunc);
#endif

  /* Parse <url> */
  /* We need to parse the url, even when using the proxy, because
   * we will need the hostname and port in case we are trying
   * to SSL connect through the proxy -- and we don't know if we
   * will need to use SSL until we parse the url ...
   */
  if((2 == sscanf(data->url, "%64[^:]://%" URL_MAX_LENGTH_TXT "[^\n]",
                  conn->proto,
                  conn->path)) && strequal(conn->proto, "file")) {
    /* we deal with file://<host>/<path> differently since it
       supports no hostname other than "localhost" and "127.0.0.1",
       which is unique among the protocols specified in RFC 1738 */
    if (strnequal(conn->path, "localhost/", 10) ||
        strnequal(conn->path, "127.0.0.1/", 10))
      /* ... since coincidentally both host strings are of equal length
         otherwise, <host>/ is quietly ommitted */
      strcpy(conn->path, &conn->path[10]);

    strcpy(conn->proto, "file");
  }
  else {
    /* Set default host and default path */
    strcpy(conn->gname, "curl.haxx.se");
    strcpy(conn->path, "/");

    if (2 > sscanf(data->url,
                   "%64[^\n:]://%256[^\n/]%" URL_MAX_LENGTH_TXT "[^\n]",
                   conn->proto, conn->gname, conn->path)) {
      
      /* badly formatted, let's try the browser-style _without_ 'http://' */
      if((1 > sscanf(data->url, "%256[^\n/]%" URL_MAX_LENGTH_TXT "[^\n]",
                     conn->gname, conn->path)) ) {
        failf(data, "<url> malformed");
        return CURLE_URL_MALFORMAT;
      }
      if(strnequal(conn->gname, "FTP", 3)) {
        strcpy(conn->proto, "ftp");
      }
      else if(strnequal(conn->gname, "GOPHER", 6))
        strcpy(conn->proto, "gopher");
#ifdef USE_SSLEAY
      else if(strnequal(conn->gname, "HTTPS", 5))
        strcpy(conn->proto, "https");
#endif /* USE_SSLEAY */
      else if(strnequal(conn->gname, "TELNET", 6))
        strcpy(conn->proto, "telnet");
      else if (strnequal(conn->gname, "DICT", sizeof("DICT")-1))
        strcpy(conn->proto, "DICT");
      else if (strnequal(conn->gname, "LDAP", sizeof("LDAP")-1))
        strcpy(conn->proto, "LDAP");
      else {
        strcpy(conn->proto, "http");
      }

      conn->protocol |= PROT_MISSING; /* not given in URL */
    }
  }


  if(data->bits.user_passwd && !data->bits.use_netrc) {
    data->user[0] =0;
    data->passwd[0]=0;

    if(*data->userpwd != ':') {
      /* the name is given, get user+password */
      sscanf(data->userpwd, "%127[^:]:%127[^@]",
             data->user, data->passwd);
      }
    else
      /* no name given, get the password only */
      sscanf(data->userpwd+1, "%127[^@]", data->passwd);

    /* check for password, if no ask for one */
    if( !data->passwd[0] ) {
      strncpy(data->passwd, getpass("password: "), sizeof(data->passwd));
    }
  }

  if(data->bits.proxy_user_passwd) {
    data->proxyuser[0] =0;
    data->proxypasswd[0]=0;

    if(*data->proxyuserpwd != ':') {
      /* the name is given, get user+password */
      sscanf(data->proxyuserpwd, "%127[^:]:%127[^@]",
             data->proxyuser, data->proxypasswd);
      }
    else
      /* no name given, get the password only */
      sscanf(data->proxyuserpwd+1, "%127[^@]", data->proxypasswd);

    /* check for password, if no ask for one */
    if( !data->proxypasswd[0] ) {
      strncpy(data->proxypasswd, getpass("proxy password: "), sizeof(data->proxypasswd));
    }

  }

  conn->name = conn->gname;
  conn->ppath = conn->path;
  data->hostname = conn->name;


  if(!data->bits.httpproxy) {
    /* If proxy was not specified, we check for default proxy environment
       variables, to enable i.e Lynx compliance:

       HTTP_PROXY http://some.server.dom:port/
       HTTPS_PROXY http://some.server.dom:port/
       FTP_PROXY http://some.server.dom:port/
       GOPHER_PROXY http://some.server.dom:port/
       NO_PROXY host.domain.dom  (a comma-separated list of hosts which should
       not be proxied, or an asterisk to override all proxy variables)
       ALL_PROXY seems to exist for the CERN www lib. Probably the first to
       check for.
 
       */
    char *no_proxy=GetEnv("NO_PROXY");
    char *proxy=NULL;
    char proxy_env[128];

    if(!no_proxy || !strequal("*", no_proxy)) {
      /* NO_PROXY wasn't specified or it wasn't just an asterisk */
      char *nope;

      nope=no_proxy?strtok(no_proxy, ", "):NULL;
      while(nope) {
        if(strlen(nope) <= strlen(conn->name)) {
          char *checkn=
            conn->name + strlen(conn->name) - strlen(nope);
          if(strnequal(nope, checkn, strlen(nope))) {
            /* no proxy for this host! */
            break;
          }
        }
	nope=strtok(NULL, ", ");
      }
      if(!nope) {
	/* It was not listed as without proxy */
	char *protop = conn->proto;
	char *envp = proxy_env;
	char *prox;

	/* Now, build <PROTOCOL>_PROXY and check for such a one to use */
	while(*protop) {
	  *envp++ = toupper(*protop++);
	}
	/* append _PROXY */
	strcpy(envp, "_PROXY");
#if 0
	infof(data, "DEBUG: checks the environment variable %s\n", proxy_env);
#endif
	/* read the protocol proxy: */
	prox=GetEnv(proxy_env);

	if(prox && *prox) { /* don't count "" strings */
	  proxy = prox; /* use this */
        }
        else
          proxy = GetEnv("ALL_PROXY"); /* default proxy to use */

        if(proxy && *proxy) {
          /* we have a proxy here to set */
          data->proxy = proxy;
          data->bits.proxystringalloc=1; /* this needs to be freed later */
          data->bits.httpproxy=1;
        }
      } /* if (!nope) - it wasn't specfied non-proxy */
    } /* NO_PROXY wasn't specified or '*' */
    if(no_proxy)
      free(no_proxy);
  } /* if not using proxy */

  if((conn->protocol&PROT_MISSING) && data->bits.httpproxy ) {
    /* We're guessing prefixes here and since we're told to use a proxy, we
       need to add the protocol prefix to the URL string before we continue!
       */
    char *reurl;

    reurl = maprintf("%s://%s", conn->proto, data->url);

    if(!reurl)
      return CURLE_OUT_OF_MEMORY;

    data->url = reurl;
    if(data->freethis)
      free(data->freethis);
    data->freethis = reurl;

    conn->protocol &= ~PROT_MISSING; /* switch that one off again */
  }

  /* RESUME on a HTTP page is a tricky business. First, let's just check that
     'range' isn't used, then set the range parameter and leave the resume as
     it is to inform about this situation for later use. We will then
     "attempt" to resume, and if we're talking to a HTTP/1.1 (or later)
     server, we will get the document resumed. If we talk to a HTTP/1.0
     server, we just fail since we can't rewind the file writing from within
     this function. */
  if(data->resume_from) {
    if(!data->bits.set_range) {
      /* if it already was in use, we just skip this */
      sprintf(resumerange, "%d-", data->resume_from);
      data->range=resumerange; /* tell ourselves to fetch this range */
      data->bits.set_range = 1; /* switch on range usage */
    }
  }


  if(data->timeout) {
    /* We set the timeout on the connection/resolving phase first, separately
       from the download/upload part to allow a maximum time on everything */
    myalarm(data->timeout); /* this sends a signal when the timeout fires
			       off, and that will abort system calls */
  }

  /*
   * Hmm, if we are using a proxy, then we can skip the GOPHER and the
   * FTP steps, although we cannot skip the HTTPS step (since the proxy
   * works differently, depending on whether its SSL or not).
   */

  if (strequal(conn->proto, "HTTP")) {
    if(!data->port)
      data->port = PORT_HTTP;
    data->remote_port = PORT_HTTP;
    conn->protocol |= PROT_HTTP;
    conn->curl_do = http;
    conn->curl_done = http_done;
    conn->curl_close = http_close;
  }
  else if (strequal(conn->proto, "HTTPS")) {
#ifdef USE_SSLEAY
    if(!data->port)
      data->port = PORT_HTTPS;
    data->remote_port = PORT_HTTPS;
    conn->protocol |= PROT_HTTP;
    conn->protocol |= PROT_HTTPS;

    conn->curl_do = http;
    conn->curl_done = http_done;
    conn->curl_connect = http_connect;
    conn->curl_close = http_close;

#else /* USE_SSLEAY */
    failf(data, "SSL is disabled, https: not supported!");
    return CURLE_UNSUPPORTED_PROTOCOL;
#endif /* !USE_SSLEAY */
  }
  else if (strequal(conn->proto, "GOPHER")) {
    if(!data->port)
      data->port = PORT_GOPHER;
    data->remote_port = PORT_GOPHER;
    /* Skip /<item-type>/ in path if present */
    if (isdigit((int)conn->path[1])) {
      conn->ppath = strchr(&conn->path[1], '/');
      if (conn->ppath == NULL)
	conn->ppath = conn->path;
      }
    conn->protocol |= PROT_GOPHER;
    conn->curl_do = http;
    conn->curl_done = http_done;
    conn->curl_close = http_close;
  }
  else if(strequal(conn->proto, "FTP")) {
    char *type;
    if(!data->port)
      data->port = PORT_FTP;
    data->remote_port = PORT_FTP;
    conn->protocol |= PROT_FTP;

    if(data->bits.httpproxy) {
      conn->curl_do = http;
      conn->curl_done = http_done;
      conn->curl_close = http_close;
    }
    else {
      conn->curl_do = ftp;
      conn->curl_done = ftp_done;
      conn->curl_connect = ftp_connect;
    }

    conn->ppath++; /* don't include the initial slash */

    /* FTP URLs support an extension like ";type=<typecode>" that
       we'll try to get now! */
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
	data->bits.ftp_ascii = 1;
	break;
      case 'D': /* directory mode */
	data->bits.ftp_list_only = 1;
	break;
      case 'I': /* binary mode */
      default:
	/* switch off ASCII */
	data->bits.ftp_ascii = 0;
	break;
      }
    }
  }
  else if(strequal(conn->proto, "TELNET")) {
    /* telnet testing factory */
    conn->protocol |= PROT_TELNET;
    if(!data->port)
      data->port = PORT_TELNET;
    data->remote_port = PORT_TELNET;

    conn->curl_do = telnet;
    conn->curl_done = telnet_done;

  }
  else if (strequal(conn->proto, "DICT")) {
    conn->protocol |= PROT_DICT;
    if(!data->port)
      data->port = PORT_DICT;
    data->remote_port = PORT_DICT;
    conn->curl_do = dict;
    conn->curl_done = dict_done;
  }
  else if (strequal(conn->proto, "LDAP")) {
    conn->protocol |= PROT_LDAP;
    if(!data->port)
      data->port = PORT_LDAP;
    data->remote_port = PORT_LDAP;
    conn->curl_do = ldap;
    conn->curl_done = ldap_done;
  }
  else if (strequal(conn->proto, "FILE")) {
    conn->protocol |= PROT_FILE;

    conn->curl_do = file;
    /* no done() function */
  }

  else {
    failf(data, "Unsupported protocol: %s", conn->proto);
    return CURLE_UNSUPPORTED_PROTOCOL;
  }

  if(data->bits.use_netrc) {
    if(ParseNetrc(data->hostname, data->user, data->passwd)) {
      infof(data, "Couldn't find host %s in the .netrc file, using defaults",
            data->hostname);
    }
    /* weather we failed or not, we don't know which fields that were filled
       in anyway */
    if(!data->user[0])
      strcpy(data->user, CURL_DEFAULT_USER);
    if(!data->passwd[0])
      strcpy(data->passwd, CURL_DEFAULT_PASSWORD);
    if(conn->protocol&PROT_HTTP) {
      data->bits.user_passwd = 1; /* enable user+password */
    }
  }
  else if(!(data->bits.user_passwd) &&
	  (conn->protocol & (PROT_FTP|PROT_HTTP)) ) {
    /* This is a FTP or HTTP URL, and we haven't got the user+password in
       the extra parameter, we will now try to extract the possible
       user+password pair in a string like:
       ftp://user:password@ftp.my.site:8021/README */
    char *ptr=NULL; /* assign to remove possible warnings */
#if 0
    if(':' == *conn->name) {
      failf(data, "URL malformat: user can't be zero length");
      return CURLE_URL_MALFORMAT_USER;
    }
#endif
    if(ptr=strchr(conn->name, '@')) {
      /* there's a user+password given here, to the left of the @ */

      data->user[0] =0;
      data->passwd[0]=0;

      if(*conn->name != ':') {
        /* the name is given, get user+password */
        sscanf(conn->name, "%127[^:]:%127[^@]",
               data->user, data->passwd);
      }
      else
        /* no name given, get the password only */
        sscanf(conn->name+1, "%127[^@]", data->passwd);

      /* check for password, if no ask for one */
      if( !data->passwd[0] ) {
        strncpy(data->passwd, getpass("password: "), sizeof(data->passwd));
      }

      conn->name = ++ptr;
      data->bits.user_passwd=1; /* enable user+password */
    }
    else {
      strcpy(data->user, CURL_DEFAULT_USER);
      strcpy(data->passwd, CURL_DEFAULT_PASSWORD);
    }
  }

  if(!data->bits.httpproxy) {
    /* If not connecting via a proxy, extract the port from the URL, if it is
     * there, thus overriding any defaults that might have been set above. */
    tmp = strchr(conn->name, ':');
    if (tmp) {
      *tmp++ = '\0';
      data->port = atoi(tmp);
    }
    
    /* Connect to target host right on */
    if(!(conn->hp = GetHost(data, conn->name, hostent_buf, sizeof(hostent_buf)))) {
      failf(data, "Couldn't resolv host '%s'", conn->name);
      return CURLE_COULDNT_RESOLVE_HOST;
    }
  }
  else {
    char *prox_portno;
    char *endofprot;

    /* We need to make a duplicate of the proxy so that we can modify the
       string safely. */
    char *proxydup=strdup(data->proxy);

    /* We use 'proxyptr' to point to the proxy name from now on... */
    char *proxyptr=proxydup;

    if(NULL == proxydup) {
      failf(data, "memory shortage");
      return CURLE_OUT_OF_MEMORY;
    }

    /* we use proxy all right, but we wanna know the remote port for SSL
       reasons */
    tmp = strchr(conn->name, ':');
    if (tmp) {
      *tmp++ = '\0'; /* cut off the name there */
      data->remote_port = atoi(tmp);
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
      data->port = atoi(prox_portno);
    }
    else if(data->proxyport) {
      /* None given in the proxy string, then get the default one if it is
         given */
      data->port = data->proxyport;
    }

    /* connect to proxy */
    if(!(conn->hp = GetHost(data, proxyptr, hostent_buf, sizeof(hostent_buf)))) {
      failf(data, "Couldn't resolv proxy '%s'", proxyptr);
      return CURLE_COULDNT_RESOLVE_PROXY;
    }

    free(proxydup); /* free the duplicate pointer and not the modified */
  }
  pgrsTime(data, TIMER_NAMELOOKUP);

  data->firstsocket = socket(AF_INET, SOCK_STREAM, 0);

  memset((char *) &conn->serv_addr, '\0', sizeof(conn->serv_addr));
  memcpy((char *)&(conn->serv_addr.sin_addr),
         conn->hp->h_addr, conn->hp->h_length);
  conn->serv_addr.sin_family = conn->hp->h_addrtype;
  conn->serv_addr.sin_port = htons(data->port);

  if (connect(data->firstsocket,
              (struct sockaddr *) &(conn->serv_addr),
              sizeof(conn->serv_addr)
              ) < 0) {
    switch(errno) {
#ifdef ECONNREFUSED
      /* this should be made nicer */
    case ECONNREFUSED:
      failf(data, "Connection refused");
      break;
#endif
#ifdef EINTR
    case EINTR:
      failf(data, "Connection timeouted");
      break;
#endif
    default:
      failf(data, "Can't connect to server: %d", errno);
      break;
    }
    return CURLE_COULDNT_CONNECT;
  }

  if(data->bits.proxy_user_passwd) {
    char authorization[512];
    sprintf(data->buffer, "%s:%s", data->proxyuser, data->proxypasswd);
    base64Encode(data->buffer, authorization);

    data->ptr_proxyuserpwd = maprintf("Proxy-authorization: Basic %s\015\012",
				      authorization);
  }
  if((conn->protocol&PROT_HTTP) || data->bits.httpproxy) {
    if(data->useragent) {
      data->ptr_uagent = maprintf("User-Agent: %s\015\012", data->useragent);
    }
  }

  if(conn->curl_connect) {
    /* is there a connect() procedure? */
    conn->now = tvnow(); /* set this here for timeout purposes in the
                            connect procedure, it is later set again for the
                            progress meter purpose */
    result = conn->curl_connect(conn);
    if(result != CURLE_OK)
      return result; /* pass back errors */
  }

  pgrsTime(data, TIMER_CONNECT); /* we're connected */

  conn->now = tvnow(); /* time this *after* the connect is done */
  conn->bytecount = 0;
  
  /* Figure out the ip-number and the first host name it shows: */
  {
    struct in_addr in;
    (void) memcpy(&in.s_addr, *conn->hp->h_addr_list, sizeof (in.s_addr));
    infof(data, "Connected to %s (%s)\n", conn->hp->h_name, inet_ntoa(in));
  }

#if 0 /* Kerberos experiements! Beware! Take cover! */
  kerberos_connect(data, name);
#endif

#ifdef __EMX__
  /* 20000330 mgs
   * the check is quite a hack...
   * we're calling _fsetmode to fix the problem with fwrite converting newline
   * characters (you get mangled text files, and corrupted binary files when
   * you download to stdout and redirect it to a file). */

  if ((data->out)->_handle == NULL) {
    _fsetmode(stdout, "b");
  }
#endif

  return CURLE_OK;
}