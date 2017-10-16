static ParameterError getparameter(char *flag, /* f or -long-flag */
                                   char *nextarg, /* NULL if unset */
                                   bool *usedarg, /* set to TRUE if the arg
                                                     has been used */
                                   struct Configurable *config)
{
  char letter;
  char subletter=0; /* subletters can only occur on long options */

  const char *parse=NULL;
  int res;
  unsigned int j;
  time_t now;
  int hit=-1;
  bool longopt=FALSE;
  bool singleopt=FALSE; /* when true means '-o foo' used '-ofoo' */


  /* single-letter,
     long-name,
     boolean whether it takes an additional argument
     */
  struct LongShort aliases[]= {
    /* all these ones, starting with "*" as a short-option have *no* short
       option to mention. */
    {"*", "url",         TRUE},
    {"*a", "random-file", TRUE},
    {"*b", "egd-file",   TRUE},
    {"*c", "connect-timeout", TRUE},
    {"*d", "ciphers",    TRUE},
    {"*e", "disable-epsv", FALSE},
#ifdef USE_ENVIRONMENT
    {"*f", "environment", FALSE},
#endif
    {"*g", "trace",      TRUE},
    {"*h", "trace-ascii", TRUE},
    {"*i", "limit-rate", TRUE},
    {"*j", "compressed",  FALSE}, /* might take an arg someday */
    {"*k", "digest",     FALSE},
    {"*l", "negotiate",  FALSE},
    {"*m", "ntlm",       FALSE},
    {"*n", "basic",      FALSE},
    {"*o", "anyauth",    FALSE},
#ifdef __DJGPP__
    {"*p", "wdebug",     FALSE},
#endif
    {"*q", "ftp-create-dirs", FALSE},    
    {"*r", "create-dirs", FALSE},
    {"*s", "max-redirs",   TRUE},
    {"*t", "proxy-ntlm",   FALSE},
    {"*u", "crlf",        FALSE},
    {"*v", "stderr",      TRUE},
    {"*w", "interface",   TRUE},
    {"*x", "krb4",        TRUE},
    {"*y", "max-filesize", TRUE},
    {"*z", "disable-eprt", FALSE},
    {"0", "http1.0",     FALSE},
    {"1", "tlsv1",       FALSE},
    {"2", "sslv2",       FALSE},
    {"3", "sslv3",       FALSE},
    {"4", "ipv4",       FALSE},
    {"6", "ipv6",       FALSE},
    {"a", "append",      FALSE},
    {"A", "user-agent",  TRUE},
    {"b", "cookie",      TRUE},
    {"B", "use-ascii",   FALSE},
    {"c", "cookie-jar",  TRUE},
    {"C", "continue-at", TRUE},
    {"d", "data",        TRUE},
    {"da", "data-ascii", TRUE},
    {"db", "data-binary", TRUE},
    {"D", "dump-header", TRUE},
    {"e", "referer",     TRUE},
    {"E", "cert",        TRUE},
    {"Ea", "cacert",     TRUE},
    {"Eb","cert-type",   TRUE},
    {"Ec","key",         TRUE},
    {"Ed","key-type",    TRUE},
    {"Ee","pass",        TRUE},
    {"Ef","engine",      TRUE},
    {"Eg","capath ",     TRUE},
    {"f", "fail",        FALSE},
    {"F", "form",        TRUE},
    {"g", "globoff",     FALSE},
    {"G", "get",         FALSE},
    {"h", "help",        FALSE},
    {"H", "header",      TRUE},
    {"i", "include",     FALSE},
    {"I", "head",        FALSE},
    {"j", "junk-session-cookies", FALSE},
    {"k", "insecure",    FALSE},
    {"K", "config",      TRUE},
    {"l", "list-only",   FALSE},
    {"L", "location",    FALSE},
    {"Lt", "location-trusted", FALSE},
    {"m", "max-time",    TRUE},
    {"M", "manual",      FALSE},
    {"n", "netrc",       FALSE},
    {"no", "netrc-optional", FALSE},
    {"N", "no-buffer",   FALSE},
    {"o", "output",      TRUE},
    {"O", "remote-name", FALSE},
    {"p", "proxytunnel", FALSE},
    {"P", "ftpport",     TRUE},
    {"q", "disable",     FALSE},
    {"Q", "quote",       TRUE},
    {"r", "range",       TRUE},
    {"R", "remote-time", FALSE},
    {"s", "silent",      FALSE},
    {"S", "show-error",  FALSE},
    {"t", "telnet-options", TRUE},
    {"T", "upload-file", TRUE},
    {"u", "user",        TRUE},
    {"U", "proxy-user",  TRUE},
    {"v", "verbose",     FALSE},
    {"V", "version",     FALSE},
    {"w", "write-out",   TRUE},
    {"x", "proxy",       TRUE},
    {"X", "request",     TRUE},
    {"X", "http-request", TRUE}, /* OBSOLETE VERSION */
    {"Y", "speed-limit",  TRUE},
    {"y", "speed-time", TRUE},
    {"z", "time-cond",   TRUE},
    {"#", "progress-bar",FALSE},
  };

  if(('-' != flag[0]) ||
     (('-' == flag[0]) && ('-' == flag[1]))) {
    /* this should be a long name */
    char *word=('-' == flag[0])?flag+2:flag;
    int fnam=strlen(word);
    int numhits=0;
    for(j=0; j< sizeof(aliases)/sizeof(aliases[0]); j++) {
      if(curl_strnequal(aliases[j].lname, word, fnam)) {
        longopt = TRUE;
        numhits++;
        if(curl_strequal(aliases[j].lname, word)) {
          parse = aliases[j].letter;
          hit = j;
          numhits = 1; /* a single unique hit */
          break;
        }
	parse = aliases[j].letter;
	hit = j;
      }
    }
    if(numhits>1) {
      /* this is at least the second match! */
      return PARAM_OPTION_AMBIGUOUS;
    }
    if(hit < 0) {
      return PARAM_OPTION_UNKNOWN;
    }    
  }
  else {
    flag++; /* prefixed with one dash, pass it */
    hit=-1;
    parse = flag;
  }

  do {
    /* we can loop here if we have multiple single-letters */

    if(!longopt)
      letter = parse?*parse:'\0';
    else {
      letter = parse[0];
      subletter = parse[1];
    }
    *usedarg = FALSE; /* default is that we don't use the arg */

#if 0
    fprintf(stderr, "OPTION: %c %s\n", letter, nextarg?nextarg:"<null>");
#endif
    if(hit < 0) {
      for(j=0; j< sizeof(aliases)/sizeof(aliases[0]); j++) {
	if(letter == aliases[j].letter[0]) {
	  hit = j;
	  break;
	}
      }
      if(hit < 0) {
	return PARAM_OPTION_UNKNOWN;
      }
    }
    if(hit < 0) {
      return PARAM_OPTION_UNKNOWN;
    }    
    if(!longopt && aliases[hit].extraparam && parse[1]) {
      nextarg=(char *)&parse[1]; /* this is the actual extra parameter */
      singleopt=TRUE;   /* don't loop anymore after this */
    }
    else if(!nextarg && aliases[hit].extraparam) {
      return PARAM_REQUIRES_PARAMETER;
    }
    else if(nextarg && aliases[hit].extraparam)
      *usedarg = TRUE; /* mark it as used */

    switch(letter) {
    case '*': /* options without a short option */
      switch(subletter) {
      case 'a': /* random-file */
        GetStr(&config->random_file, nextarg);
        break;
      case 'b': /* egd-file */
        GetStr(&config->egd_file, nextarg);
        break;
      case 'c': /* connect-timeout */
        if(str2num(&config->connecttimeout, nextarg))
          return PARAM_BAD_NUMERIC;
        break;
      case 'd': /* ciphers */
        GetStr(&config->cipher_list, nextarg);
        break;
      case 'e': /* --disable-epsv */
        config->disable_epsv ^= TRUE;
        break;
#ifdef USE_ENVIRONMENT
      case 'f':
        config->writeenv ^= TRUE;
        break;
#endif
      case 'g': /* --trace */
        GetStr(&config->trace_dump, nextarg);
        break;
      case 'h': /* --trace-ascii */
        GetStr(&config->trace_dump, nextarg);
        config->trace_ascii = TRUE;
        break;
      case 'i': /* --limit-rate */
        {
          /* We support G, M, K too */
          char *unit;
          unsigned long value = strtol(nextarg, &unit, 0);
          switch(nextarg[strlen(nextarg)-1]) {
          case 'G':
          case 'g':
            value *= 1024*1024*1024;
            break;
          case 'M':
          case 'm':
            value *= 1024*1024;
            break;
          case 'K':
          case 'k':
            value *= 1024;
            break;
          }
          config->recvpersecond = value;
          config->sendpersecond = value;
        }
        break;

      case 'j': /* --compressed */
 	config->encoding ^= TRUE;
 	break;

      case 'k': /* --digest */
 	config->authtype = CURLAUTH_DIGEST;
 	break;

      case 'l': /* --negotiate */
	config->authtype = CURLAUTH_GSSNEGOTIATE;
	break;

      case 'm': /* --ntlm */
	config->authtype = CURLAUTH_NTLM;
	break;

      case 'n': /* --basic for completeness */
	config->authtype = CURLAUTH_BASIC;
	break;

      case 'o': /* --anyauth, let libcurl pick it */
	config->authtype = CURLAUTH_ANY;
	break;

#ifdef __DJGPP__
      case 'p': /* --wdebug */
        dbug_init();
        break;
#endif
      case 'q': /* --ftp-create-dirs */
        config->ftp_create_dirs ^= TRUE;
        break;

      case 'r': /* --create-dirs */
        config->create_dirs = TRUE;
        break;

      case 's': /* --max-redirs */
        /* specified max no of redirects (http(s)) */
        if(str2num(&config->maxredirs, nextarg))
          return PARAM_BAD_NUMERIC;
        break;

      case 't': /* --proxy-ntlm */
        config->proxyntlm ^= TRUE;
        break;

      case 'u': /* --crlf */
        /* LF -> CRLF conversinon? */
        config->crlf = TRUE;
        break;

      case 'v': /* --stderr */
        if(strcmp(nextarg, "-")) {
          config->errors = fopen(nextarg, "wt");
          config->errors_fopened = TRUE;
        }
        else
          config->errors = stdout;
      break;
      case 'w': /* --interface */
        /* interface */
        GetStr(&config->iface, nextarg);
        break;
      case 'x': /* --krb4 */
        /* krb4 level string */
        GetStr(&config->krb4level, nextarg);
        break;
      case 'y': /* --max-filesize */
        if(str2num(&config->max_filesize, nextarg))
          return PARAM_BAD_NUMERIC;
        break;
      case 'z': /* --disable-eprt */
        config->disable_eprt ^= TRUE;
        break;

      default: /* the URL! */
        {
          struct getout *url;
          if(config->url_get || (config->url_get=config->url_list)) {
            /* there's a node here, if it already is filled-in continue to find
               an "empty" node */
            while(config->url_get && (config->url_get->flags&GETOUT_URL))
              config->url_get = config->url_get->next;
          }

          /* now there might or might not be an available node to fill in! */

          if(config->url_get)
            /* existing node */
            url = config->url_get;
          else
            /* there was no free node, create one! */
            url=new_getout(config);
          
          if(url) {
            /* fill in the URL */
            GetStr(&url->url, nextarg);
            url->flags |= GETOUT_URL;
          }
        }
      }
      break;
    case '#': /* added 19990617 larsa */
      config->progressmode ^= CURL_PROGRESS_BAR;
      break;
    case '0': 
      /* HTTP version 1.0 */
      config->httpversion = CURL_HTTP_VERSION_1_0;
      break;
    case '1':
      /* TLS version 1 */
      config->ssl_version = CURL_SSLVERSION_TLSv1;
      break;
    case '2': 
      /* SSL version 2 */
      config->ssl_version = CURL_SSLVERSION_SSLv2;
      break;
    case '3': 
      /* SSL version 3 */
      config->ssl_version = CURL_SSLVERSION_SSLv3;
      break;
    case '4': 
      /* IPv4 */
      config->ip_version = 4;
      break;
    case '6': 
      /* IPv6 */
      config->ip_version = 6;
      break;
    case 'a':
      /* This makes the FTP sessions use APPE instead of STOR */
      config->conf ^= CONF_FTPAPPEND;
      break;
    case 'A':
      /* This specifies the User-Agent name */
      GetStr(&config->useragent, nextarg);
      break;
    case 'b': /* cookie string coming up: */
      if(nextarg[0] == '@') {
        nextarg++;
      }
      else if(strchr(nextarg, '=')) {
        /* A cookie string must have a =-letter */
        GetStr(&config->cookie, nextarg);
        break;
      }
      /* We have a cookie file to read from! */
      GetStr(&config->cookiefile, nextarg);
      break;
    case 'B':
      /* use ASCII/text when transfering */
      config->conf ^= CONF_GETTEXT;
      break;
    case 'c':
      /* get the file name to dump all cookies in */
      GetStr(&config->cookiejar, nextarg);
      break;
    case 'C':
      /* This makes us continue an ftp transfer at given position */
      if(!curl_strequal(nextarg, "-")) {
        if(str2num(&config->resume_from, nextarg))
          return PARAM_BAD_NUMERIC;
        config->resume_from_current = FALSE;
      }
      else {
        config->resume_from_current = TRUE;
        config->resume_from = 0;
      }
      config->use_resume=TRUE;
      break;
    case 'd':
      /* postfield data */
      {
        char *postdata=NULL;

        if('@' == *nextarg) {
          /* the data begins with a '@' letter, it means that a file name
             or - (stdin) follows */
          FILE *file;

          nextarg++; /* pass the @ */

          if(curl_strequal("-", nextarg))
            file = stdin;
          else 
            file = fopen(nextarg, "rb");

          if(subletter == 'b') /* forced binary */
            postdata = file2memory(file, &config->postfieldsize);
          else
            postdata = file2string(file);
          if(file && (file != stdin))
            fclose(file);
        }
        else {
          GetStr(&postdata, nextarg);
        }

        if(config->postfields) {
          /* we already have a string, we append this one
             with a separating &-letter */
          char *oldpost=config->postfields;
          config->postfields=aprintf("%s&%s", oldpost, postdata);
          free(oldpost);
          free(postdata);
        }
        else
          config->postfields=postdata;
      }
      /*
        We can't set the request type here, as this data might be used in
        a simple GET if -G is used. Already or soon.

        if(SetHTTPrequest(HTTPREQ_SIMPLEPOST, &config->httpreq))
          return PARAM_BAD_USE;
      */
      break;
    case 'D':
      /* dump-header to given file name */
      GetStr(&config->headerfile, nextarg);
      break;
    case 'e':
      {
        char *ptr = strstr(nextarg, ";auto");
        if(ptr) {
          /* Automatic referer requested, this may be combined with a
             set initial one */
          config->conf |= CONF_AUTO_REFERER;
          *ptr = 0; /* zero terminate here */
        }
        GetStr(&config->referer, nextarg);
      }
      break;
    case 'E':
      switch(subletter) {
      case 'a': /* CA info PEM file */
        /* CA info PEM file */
        GetStr(&config->cacert, nextarg);
        break;
      case 'b': /* cert file type */
        GetStr(&config->cert_type, nextarg);
        break;
      case 'c': /* private key file */
        GetStr(&config->key, nextarg);
        break;
      case 'd': /* private key file type */
        GetStr(&config->key_type, nextarg);
        break;
      case 'e': /* private key passphrase */
        GetStr(&config->key_passwd, nextarg);
        cleanarg(nextarg);
        break;
      case 'f': /* crypto engine */
        GetStr(&config->engine, nextarg);
        break;
      case 'g': /* CA info PEM file */
        /* CA cert directory */
        GetStr(&config->capath, nextarg);
        break;
      default: /* certificate file */
        {
          char *ptr = strchr(nextarg, ':');
          /* Since we live in a world of weirdness and confusion, the win32
             dudes can use : when using drive letters and thus
             c:\file:password needs to work. In order not to break
             compatibility, we still use : as separator, but we try to detect
             when it is used for a file name! On windows. */
#ifdef WIN32
          if(ptr &&
             (ptr == &nextarg[1]) &&
             (nextarg[2] == '\\') &&
             (isalpha((int)nextarg[0])) )
             /* colon in the second column, followed by a backslash, and the
                first character is an alphabetic letter:

                this is a drive letter colon */
            ptr = strchr(&nextarg[3], ':'); /* find the next one instead */
#endif
          if(ptr) {
            /* we have a password too */
            *ptr=0;
            ptr++;
            GetStr(&config->key_passwd, ptr);
          }
          GetStr(&config->cert, nextarg);
          cleanarg(nextarg);
        }
      }
      break;
    case 'f':
      /* fail hard on errors  */
      config->conf ^= CONF_FAILONERROR;
      break;
    case 'F':
      /* "form data" simulation, this is a little advanced so lets do our best
	 to sort this out slowly and carefully */
      if(formparse(nextarg,
                   &config->httppost,
                   &config->last_post))
	return PARAM_BAD_USE;
      if(SetHTTPrequest(HTTPREQ_POST, &config->httpreq))
        return PARAM_BAD_USE;
      break;

    case 'g': /* g disables URLglobbing */
      config->globoff ^= TRUE;
      break;

    case 'G': /* HTTP GET */
      config->use_httpget = TRUE;
      break;

    case 'h': /* h for help */
      help();
      return PARAM_HELP_REQUESTED;
    case 'H':
      /* A custom header to append to a list */
      config->headers = curl_slist_append(config->headers, nextarg);
      break;
    case 'i':
      config->conf ^= CONF_HEADER; /* include the HTTP header as well */
      break;
    case 'j':
      config->cookiesession ^= TRUE;
      break;
    case 'I':
      /*
       * This is a bit tricky. We either SET both bits, or we clear both
       * bits. Let's not make any other outcomes from this.
       */
      if((CONF_HEADER|CONF_NOBODY) !=
         (config->conf&(CONF_HEADER|CONF_NOBODY)) ) {
        /* one of them weren't set, set both */
        config->conf |= (CONF_HEADER|CONF_NOBODY);
        if(SetHTTPrequest(HTTPREQ_HEAD, &config->httpreq))
          return PARAM_BAD_USE;
      }
      else {
        /* both were set, clear both */
        config->conf &= ~(CONF_HEADER|CONF_NOBODY);
        if(SetHTTPrequest(HTTPREQ_GET, &config->httpreq))
          return PARAM_BAD_USE;
      }
      break;
    case 'k': /* allow insecure SSL connects */
      config->insecure_ok ^= TRUE;
      break;
    case 'K': /* parse config file */
      res = parseconfig(nextarg, config);
      config->configread = TRUE;
      if(res)
	return res;
      break;
    case 'l':
      config->conf ^= CONF_FTPLISTONLY; /* only list the names of the FTP dir */
      break;
    case 'L':
      config->conf ^= CONF_FOLLOWLOCATION; /* Follow Location: HTTP headers */
      switch (subletter) {
      case 't':
        /* Continue to send authentication (user+password) when following
         * locations, even when hostname changed */
        config->conf ^= CONF_UNRESTRICTED_AUTH;
        break;
      }
      break;
    case 'm':
      /* specified max time */
      if(str2num(&config->timeout, nextarg))
        return PARAM_BAD_NUMERIC;
      break;
    case 'M': /* M for manual, huge help */
      hugehelp();
      return PARAM_HELP_REQUESTED;
    case 'n':
      switch(subletter) {
      case 'o': /* CA info PEM file */
        /* use .netrc or URL */
        config->conf ^= CONF_NETRC_OPT;
        break;
      default:
        /* pick info from .netrc, if this is used for http, curl will
           automatically enfore user+password with the request */
        config->conf ^= CONF_NETRC;
        break;
      }
      break;
    case 'N':
      /* disable the output I/O buffering */
      config->nobuffer ^= 1;
      break;
    case 'o':
    case 'O':
      /* output file */
      {
        struct getout *url;
        if(config->url_out || (config->url_out=config->url_list)) {
          /* there's a node here, if it already is filled-in continue to find
             an "empty" node */
          while(config->url_out && (config->url_out->flags&GETOUT_OUTFILE))
            config->url_out = config->url_out->next;
        }

        /* now there might or might not be an available node to fill in! */

        if(config->url_out)
          /* existing node */
          url = config->url_out;
        else
          /* there was no free node, create one! */
          url=new_getout(config);

        if(url) {
          /* fill in the outfile */
          if('o' == letter)
            GetStr(&url->outfile, nextarg);
          else {
            url->outfile=NULL; /* leave it */
            url->flags |= GETOUT_USEREMOTE;
          }
          url->flags |= GETOUT_OUTFILE;
        }
      }
      break;
    case 'P':
      /* This makes the FTP sessions use PORT instead of PASV */
      /* use <eth0> or <192.168.10.10> style addresses. Anything except
	 this will make us try to get the "default" address.
	 NOTE: this is a changed behaviour since the released 4.1!
	 */
      GetStr(&config->ftpport, nextarg);
      break;
    case 'p':
      /* proxy tunnel for non-http protocols */
      config->proxytunnel ^= TRUE;
      break;

    case 'q': /* if used first, already taken care of, we do it like
		 this so we don't cause an error! */
      break;
    case 'Q':
      /* QUOTE command to send to FTP server */
      switch(nextarg[0]) {
      case '-':
        /* prefixed with a dash makes it a POST TRANSFER one */
        nextarg++;
        config->postquote = curl_slist_append(config->postquote, nextarg);
        break;
      case '+':
        /* prefixed with a plus makes it a just-before-transfer one */
        nextarg++;
        config->prequote = curl_slist_append(config->prequote, nextarg);
        break;
      default:
        config->quote = curl_slist_append(config->quote, nextarg);
      }
      break;
    case 'r':
      /* byte range requested */
      GetStr(&config->range, nextarg);
      break;
    case 'R':
      /* use remote file's time */
      config->remote_time ^= TRUE;
      break;
    case 's':
      /* don't show progress meter, don't show errors : */
      config->conf |= (CONF_MUTE|CONF_NOPROGRESS);
      config->showerror ^= TRUE; /* toggle off */
      break;
    case 'S':
      /* show errors */
      config->showerror ^= TRUE; /* toggle on if used with -s */
      break;
    case 't':
      /* Telnet options */
      config->telnet_options =
        curl_slist_append(config->telnet_options, nextarg);
      break;
    case 'T':
      /* we are uploading */
      {
        struct getout *url;
        if(config->url_out || (config->url_out=config->url_list)) {
          /* there's a node here, if it already is filled-in continue to find
             an "empty" node */
          while(config->url_out && (config->url_out->flags&GETOUT_UPLOAD))
            config->url_out = config->url_out->next;
        }

        /* now there might or might not be an available node to fill in! */

        if(config->url_out)
          /* existing node */
          url = config->url_out;
        else
          /* there was no free node, create one! */
          url=new_getout(config);

        if(url) {
          url->flags |= GETOUT_UPLOAD; /* mark -T used */
          if(!*nextarg)
            url->flags |= GETOUT_NOUPLOAD;
          else {
            /* "-" equals stdin, but keep the string around for now */
            GetStr(&url->infile, nextarg);
          }
        }
      }
      break;
    case 'u':
      /* user:password  */
      GetStr(&config->userpwd, nextarg);
      cleanarg(nextarg);
      checkpasswd("host", &config->userpwd);
      break;
    case 'U':
      /* Proxy user:password  */
      GetStr(&config->proxyuserpwd, nextarg);
      cleanarg(nextarg);
      checkpasswd("proxy", &config->proxyuserpwd);
      break;
    case 'v':
      config->conf ^= CONF_VERBOSE; /* talk a lot */
      break;
    case 'V':
    {
      const char **proto;

      printf(CURL_ID "%s\n", curl_version());
      if (curlinfo->protocols) {
        printf("Protocols: ");
        for (proto=curlinfo->protocols; *proto; ++proto) {
          printf("%s ", *proto);
        }
        puts(""); /* newline */
      }
      if(curlinfo->features) {
        unsigned int i;
        struct feat {
          const char *name;
          int bitmask;
        };
        struct feat feats[] = {
          {"IPv6", CURL_VERSION_IPV6},
          {"krb4", CURL_VERSION_KERBEROS4},
          {"SSL",  CURL_VERSION_SSL},
          {"libz", CURL_VERSION_LIBZ},
          {"NTLM", CURL_VERSION_NTLM},
          {"GSS-Negotiate", CURL_VERSION_GSSNEGOTIATE},
          {"Debug", CURL_VERSION_DEBUG},
          {"AsynchDNS", CURL_VERSION_ASYNCHDNS},
          {"SPNEGO", CURL_VERSION_SPNEGO}
        };
        printf("Features: ");
        for(i=0; i<sizeof(feats)/sizeof(feats[0]); i++) {
          if(curlinfo->features & feats[i].bitmask)
            printf("%s ", feats[i].name);
        }
        puts(""); /* newline */
      }
    }
    return PARAM_HELP_REQUESTED;
    case 'w':
      /* get the output string */
      if('@' == *nextarg) {
        /* the data begins with a '@' letter, it means that a file name
           or - (stdin) follows */
        FILE *file;
        nextarg++; /* pass the @ */
        if(curl_strequal("-", nextarg))
          file = stdin;
        else 
          file = fopen(nextarg, "r");
        config->writeout = file2string(file);
        if(file && (file != stdin))
          fclose(file);
      }
      else 
        GetStr(&config->writeout, nextarg);
      break;
    case 'x':
      /* proxy */
      GetStr(&config->proxy, nextarg);
      break;
    case 'X':
      /* set custom request */
      GetStr(&config->customrequest, nextarg);
      break;
    case 'y':
      /* low speed time */
      if(str2num(&config->low_speed_time, nextarg))
        return PARAM_BAD_NUMERIC;
      if(!config->low_speed_limit)
	config->low_speed_limit = 1;
      break;
    case 'Y':
      /* low speed limit */
      if(str2num(&config->low_speed_limit, nextarg))
        return PARAM_BAD_NUMERIC;
      if(!config->low_speed_time)
	config->low_speed_time=30;
      break;
    case 'z': /* time condition coming up */
      switch(*nextarg) {
      case '+':
        nextarg++;
      default:
        /* If-Modified-Since: (section 14.28 in RFC2068) */
        config->timecond = CURL_TIMECOND_IFMODSINCE;
        break;
      case '-':
        /* If-Unmodified-Since:  (section 14.24 in RFC2068) */
        config->timecond = CURL_TIMECOND_IFUNMODSINCE;
        nextarg++;
        break;
      case '=':
        /* Last-Modified:  (section 14.29 in RFC2068) */
        config->timecond = CURL_TIMECOND_LASTMOD;
        nextarg++;
        break;
      }
      now=time(NULL);
      config->condtime=curl_getdate(nextarg, &now);
      if(-1 == (int)config->condtime) {
        /* now let's see if it is a file name to get the time from instead! */
        struct stat statbuf;
        if(-1 == stat(nextarg, &statbuf)) {
          /* failed, remove time condition */
          config->timecond = CURL_TIMECOND_NONE;
        }
        else {
          /* pull the time out from the file */
          config->condtime = statbuf.st_mtime;
        }
      }
      break;
    default: /* unknown flag */
      return PARAM_OPTION_UNKNOWN;
    }
    hit = -1;

  } while(!longopt && !singleopt && *++parse && !*usedarg);

  return PARAM_OK;
}