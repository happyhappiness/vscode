static int getparameter(char *flag, /* f or -long-flag */
			char *nextarg, /* NULL if unset */
			bool *usedarg, /* set to TRUE if the arg has been
					  used */
			struct Configurable *config)
{
  char letter;
  char *parse=NULL;
  int res;
  struct HttpHeader *head;
  int j;
  time_t now;
  int hit=-1;

  /* single-letter,
     long-name,
     boolean whether it takes an additional argument
     */
  struct LongShort aliases[]= {
    {"9", "crlf",        FALSE},
    {"2", "sslv2",       FALSE},
    {"3", "sslv3",       FALSE},
    {"a", "append",      FALSE},
    {"A", "user-agent",  TRUE},
    {"b", "cookie",      TRUE},
    {"B", "ftp-ascii",   FALSE},
    {"c", "continue",    FALSE},
    {"C", "continue-at", TRUE},
    {"d", "data",        TRUE},
    {"D", "dump-header", TRUE},
    {"e", "referer",     TRUE},
    {"E", "cert",        TRUE},
    {"f", "fail",        FALSE},
    {"F", "form",        TRUE},
#ifdef MULTIDOC
    {"g", "get-too",     TRUE},
    {"G", "get-store",   TRUE},
#endif
    {"h", "help",        FALSE},
    {"H", "header",      TRUE},
    {"i", "include",     FALSE},
    {"I", "head",        FALSE},
    {"K", "config",      TRUE},
    {"l", "list-only",   FALSE},
    {"L", "location",    FALSE},
    {"m", "max-time",    TRUE},
    {"M", "manual",      FALSE},
    {"n", "netrc",       FALSE},
    {"o", "output",      TRUE},
    {"O", "remote-name", FALSE},
    {"p", "port",        TRUE},
    {"P", "ftpport",     TRUE},
    {"q", "disable",     FALSE},
    {"Q", "quote",       TRUE},
    {"r", "range",       TRUE},
    {"s", "silent",      FALSE},
    {"S", "show-error",  FALSE},
    {"t", "upload",      FALSE},
    {"T", "upload-file", TRUE},
    {"u", "user",        TRUE},
    {"U", "proxy-user",  TRUE},
    {"v", "verbose",     FALSE},
    {"V", "version",     FALSE},
    {"x", "proxy",       TRUE},
    {"X", "http-request", TRUE},
    {"y", "speed-time",  TRUE},
    {"Y", "speed-limit", TRUE},
    {"z", "time-cond",   TRUE},
    {"#", "progress-bar",FALSE},
  };

  if('-' == flag[0]) {
    /* try a long name */
    int fnam=strlen(&flag[1]);
    for(j=0; j< sizeof(aliases)/sizeof(aliases[0]); j++) {
      if(strnequal(aliases[j].lname, &flag[1], fnam)) {
        if(strequal(aliases[j].lname, &flag[1])) {
          parse = aliases[j].letter;
          hit = j;
          break;
        }
	if(parse) {
	  /* this is the second match, we can't continue! */
	  helpf("option --%s is ambiguous\n", &flag[1]);
	  return URG_FAILED_INIT;
	}
	parse = aliases[j].letter;
	hit = j;
      }
    }
    if(hit < 0) {
      helpf("unknown option -%s.\n", flag);
      return URG_FAILED_INIT;
    }    
  }
  else {
    hit=-1;
    parse = flag;
  }

  do {
    /* we can loop here if we have multiple single-letters */

    letter = parse?*parse:'\0';
    *usedarg = FALSE; /* default is that we don't use the arg */

#if 0
    fprintf(stderr, "OPTION: %c %s\n", letter, nextarg?nextarg:"<null>");
#endif
    if(hit < 0) {
      for(j=0; j< sizeof(aliases)/sizeof(aliases[0]); j++) {
	if(letter == *aliases[j].letter) {
	  hit = j;
	  break;
	}
      }
      if(hit < 0) {
	helpf("unknown option -%c.\n", letter);
	return URG_FAILED_INIT;      
      }
    }
    if(hit < 0) {
      helpf("unknown option -%c.\n", letter);
      return URG_FAILED_INIT;
    }    
    if(!nextarg && aliases[hit].extraparam) {
      helpf("option -%s/--%s requires an extra argument!\n",
	    aliases[hit].letter,
	    aliases[hit].lname);
      return URG_FAILED_INIT;
    }
    else if(nextarg && aliases[hit].extraparam)
      *usedarg = TRUE; /* mark it as used */

    switch(letter) {
    case 'z': /* time condition coming up */
      switch(*nextarg) {
      case '+':
        nextarg++;
      default:
        /* If-Modified-Since: (section 14.28 in RFC2068) */
        config->timecond = TIMECOND_IFMODSINCE;
        break;
      case '-':
        /* If-Unmodified-Since:  (section 14.24 in RFC2068) */
        config->timecond = TIMECOND_IFUNMODSINCE;
        nextarg++;
        break;
      case '=':
        /* Last-Modified:  (section 14.29 in RFC2068) */
        config->timecond = TIMECOND_LASTMOD;
        nextarg++;
        break;
      }
      now=time(NULL);
      config->condtime=get_date(nextarg, &now);
      if(-1 == config->condtime) {
        /* now let's see if it is a file name to get the time from instead! */
        struct stat statbuf;
        if(-1 == stat(nextarg, &statbuf)) {
          /* failed, remove time condition */
          config->timecond = TIMECOND_NONE;
        }
        else {
          /* pull the time out from the file */
          config->condtime = statbuf.st_mtime;
        }
      }
      break;
    case '9': /* there is no short letter for this */
      /* LF -> CRLF conversinon? */
      config->crlf = TRUE;
      break;
    case '#': /* 19990617 larsa */
      ProgressMode(1);
      break;
    case '2': 
      /* SSL version 2 */
      config->ssl_version = 2;
      break;
    case '3': 
      /* SSL version 2 */
      config->ssl_version = 3;
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
      if(strchr(nextarg, '=')) {
        /* A cookie string must have a =-letter */
        GetStr(&config->cookie, nextarg);
      }
      else {
        /* We have a cookie file to read from! */
        GetStr(&config->cookiefile, nextarg);
      }
      break;
    case 'B':
      /* use type ASCII when transfering ftp files */
      config->conf ^= CONF_FTPASCII;
      break;
    case 'c':
      /* This makes us continue an ftp transfer */
      config->use_resume^=TRUE;
      break;
    case 'C':
      /* This makes us continue an ftp transfer at given position */
      config->resume_from= atoi(nextarg);
      config->use_resume=TRUE;
      break;
    case 'd':
      /* postfield data */
      if('@' == *nextarg) {
        /* the data begins with a '@' letter, it means that a file name
           or - (stdin) follows */
        FILE *file;
        nextarg++; /* pass the @ */
        if(strequal("-", nextarg))
          file = stdin;
        else 
          file = fopen(nextarg, "r");
        config->postfields = file2string(file);
        if(file && (file != stdin))
          fclose(stdin);
      }
      else {
        GetStr(&config->postfields, nextarg);
      }
      if(config->postfields)
        config->conf |= CONF_POST;
      break;
    case 'D':
      /* dump-header to given file name */
      GetStr(&config->headerfile, nextarg);
      break;
    case 'e':
      GetStr(&config->referer, nextarg);
      config->conf |= CONF_REFERER;
      break;
    case 'E':
      {
	char *ptr = strchr(nextarg, ':');
	if(ptr) {
	  /* we have a password too */
	  *ptr=0;
	  ptr++;
	  GetStr(&config->cert_passwd, ptr);
	}
	GetStr(&config->cert, nextarg);
      }
      break;
    case 'f':
      /* fail hard on errors  */
      config->conf ^= CONF_FAILONERROR;
      break;
    case 'F':
      /* "form data" simulation, this is a little advanced so lets do our best
	 to sort this out slowly and carefully */
      if(curl_FormParse(nextarg,
                        &config->httppost,
                        &config->last_post))
	return URG_FAILED_INIT;    
      config->conf |= CONF_HTTPPOST; /* no toggle, OR! */
      break;
#ifdef MULTIDOC
    case 'g':
      /* specify an additional document to get from the same server as the
         main URL */
      {
        struct MoreDoc *newdoc = (struct MoreDoc *)malloc(sizeof(struct MoreDoc));
        if(newdoc) {
          newdoc->next = NULL;
          newdoc->store = NULL; /* FILE * to store this file at */
          newdoc->path = NULL; /* first zero this */
          GetStr(&newdoc->path, nextarg); /* now get the path */

          /* point on our new one */
          if(config->last_newdoc)
            config->last_newdoc->next = newdoc;
          else {
            config->newdoc = newdoc;
          }
          config->last_newdoc = newdoc;
        }
      }
    break;
    case 'G':
      {
        FILE *docfile;
        if(!config->last_newdoc ||
           config->last_newdoc->store) {
          /* bad usage, just ignore */
        }
        else {
          docfile = fopen(nextarg, "w");
          if(docfile)
            config->last_newdoc->store = docfile;
          else
            fprintf(stderr, "Couldn't open file %s\n", nextarg);
        }
      }
    break;
#endif
    case 'h': /* h for help */
      help();
      return URG_FAILED_INIT;
    case 'H':
      head = (struct HttpHeader *)malloc(sizeof(struct HttpHeader));
      if(head) {
	head->next = NULL;
	head->header = NULL; /* first zero this */
	GetStr(&head->header, nextarg); /* now get the header line */

	/* point on our new one */
	if(config->last_header)
	  config->last_header->next = head;
	else {
	  config->headers = head;
	}

	config->last_header = head;
      }
      break;
    case 'i':
      config->conf ^= CONF_HEADER; /* include the HTTP header as well */
      break;
    case 'I':
      config->conf ^= CONF_HEADER; /* include the HTTP header in the output */
      config->conf ^= CONF_NOBODY; /* don't fetch the body at all */
      break;
    case 'K':
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
      break;
    case 'm':
      /* specified max time */
      config->timeout = atoi(nextarg);
      break;
    case 'M': /* M for manual, huge help */
      hugehelp();
      return URG_FAILED_INIT;
    case 'n':
      /* pick info from .netrc, if this is used for http, curl will
	 automatically enfore user+password with the request */
      config->conf ^= CONF_NETRC;
      break;
    case 'o':
      /* output file */
      GetStr(&config->outfile, nextarg); /* write to this file */
      break;
    case 'O':
      /* output file */
      config->remotefile ^= TRUE;
      break;
    case 'P':
      /* This makes the FTP sessions use PORT instead of PASV */
      /* use <eth0> or <192.168.10.10> style addresses. Anything except
	 this will make us try to get the "default" address.
	 NOTE: this is a changed behaviour since the released 4.1!
	 */
      config->conf |= CONF_FTPPORT;
      GetStr(&config->ftpport, nextarg);
      break;
    case 'p':
      /* specified port */
      fputs("You've used the -p option, it will be removed in a future version\n",
	    stderr);
      config->porttouse = atoi(nextarg);
      config->conf |= CONF_PORT; /* changed port */
      break;
    case 'q': /* if used first, already taken care of, we do it like
		 this so we don't cause an error! */
      break;
    case 'Q':
      /* QUOTE command to send to FTP server */
      config->quote = curl_slist_append(config->quote, nextarg);
      break;
    case 'r':
      /* byte range requested */
      GetStr(&config->range, nextarg);
      config->conf |= CONF_RANGE;
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
      /* we are uploading */
      config->conf ^= CONF_UPLOAD;
      break;
    case 'T':
      /* we are uploading */
      config->conf |= CONF_UPLOAD;
      GetStr(&config->infile, nextarg);
      break;
    case 'u':
      /* user:password  */
      GetStr(&config->userpwd, nextarg);
      config->conf |= CONF_USERPWD;
      break;
    case 'U':
      /* Proxy user:password  */
      GetStr(&config->proxyuserpwd, nextarg);
      config->conf |= CONF_PROXYUSERPWD;
      break;
    case 'v':
      config->conf ^= CONF_VERBOSE; /* talk a lot */
      break;
    case 'V':
      printf(CURL_ID "%s\n", curl_version());
      return URG_FAILED_INIT;
    case 'x':
      /* proxy */
      if(!*nextarg) {
	/* disable proxy when no proxy is given */
	config->conf &= ~CONF_PROXY;
      }
      else { 
	config->conf |= CONF_PROXY;
	GetStr(&config->proxy, nextarg);
      }
      break;
    case 'X':
      /* HTTP request */
      GetStr(&config->httprequest, nextarg);
      break;
    case 'Y':
      /* low speed time */
      config->low_speed_time = atoi(nextarg);
      if(!config->low_speed_limit)
	config->low_speed_limit = 1;
      break;
    case 'y':
      /* low speed limit */
      config->low_speed_limit = atoi(nextarg);
      if(!config->low_speed_time)
	config->low_speed_time=30;
      break;

    default: /* unknown flag */
      if(letter)	
	helpf("Unknown option '%c'\n", letter);
      else
	helpf("Unknown option\n"); /* short help blurb */
      return URG_FAILED_INIT;
    }
    hit = -1;

  } while(*++parse && !*usedarg);

  return URG_OK;
}