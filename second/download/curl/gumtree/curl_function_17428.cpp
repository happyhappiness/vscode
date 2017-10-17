static int 
operate(struct Configurable *config, int argc, char *argv[])
{
  char errorbuffer[CURL_ERROR_SIZE];
  char useragent[128]; /* buah, we don't want a larger default user agent */
  struct ProgressData progressbar;
  struct getout *urlnode;
  struct getout *nextnode;

  struct OutStruct outs;
  struct OutStruct heads;

  char *url = NULL;

  URLGlob *urls=NULL;
  int urlnum;
  char *outfiles;
  int separator = 0;
  
  FILE *infd = stdin;
  FILE *headerfilep = NULL;
  char *urlbuffer=NULL;
  int infilesize=-1; /* -1 means unknown */
  bool stillflags=TRUE;

  bool allocuseragent=FALSE;

  char *httpgetfields=NULL;

  CURL *curl;
  int res = 0;
  int i;

#ifdef MALLOCDEBUG
  /* this sends all memory debug messages to a logfile named memdump */
  char *env;
  env = curl_getenv("CURL_MEMDEBUG");
  if(env) {
    free(env);
    curl_memdebug("memdump");
  }
#endif

  errorbuffer[0]=0; /* prevent junk from being output */

  main_init(); /* inits */

  config->showerror=TRUE;
  config->conf=CONF_DEFAULT;
  config->use_httpget=FALSE;

  if(argc>1 &&
     (!strnequal("--", argv[1], 2) && (argv[1][0] == '-')) &&
     strchr(argv[1], 'q')) {
    /*
     * The first flag, that is not a verbose name, but a shortname
     * and it includes the 'q' flag!
     */
    ;
  }
  else {
    res = parseconfig(NULL, config);
    if(res)
      return res;
  }

  if ((argc < 2)  && !config->url_list) {
    helpf(NULL);
    return CURLE_FAILED_INIT;
  }

  /* Parse options */
  for (i = 1; i < argc; i++) {
    if(stillflags &&
       ('-' == argv[i][0])) {
      char *nextarg;
      bool passarg;
      char *origopt=argv[i];
      
      char *flag = argv[i];

      if(strequal("--", argv[i]))
	/* this indicates the end of the flags and thus enables the
	   following (URL) argument to start with -. */
	stillflags=FALSE;
      else {
	nextarg= (i < argc - 1)? argv[i+1]: NULL;

	res = getparameter(flag, nextarg, &passarg, config);
	if(res) {
          switch(res) {
          case PARAM_OPTION_AMBIGUOUS:
            helpf("option %s is ambiguous\n", origopt);
            break;
          case PARAM_OPTION_UNKNOWN:
            helpf("option %s is unknown\n", origopt);
            break;
          case PARAM_REQUIRES_PARAMETER:
            helpf("option %s requires an extra argument!\n", origopt);
            break;
          case PARAM_BAD_USE:
            helpf("option %s was wrongly used!\n", origopt);
            break;
          case PARAM_HELP_REQUESTED:
            /* no text */
            break;
          }
          clean_getout(config);
	  return CURLE_FAILED_INIT;
        }

	if(passarg) /* we're supposed to skip this */
	  i++;
      }
    }
    else {
      bool used;
      /* just add the URL please */
      res = getparameter((char *)"--url", argv[i], &used, config);
      if(res)
        return res;
    }
  }

  if(!config->url_list) {
    helpf("no URL specified!\n");
    return CURLE_FAILED_INIT;
  }
  if(NULL == config->useragent) {
    /* set non-zero default values: */
    snprintf(useragent, sizeof(useragent),
             CURL_NAME "/" CURL_VERSION " (" OS ") " "%s", curl_version());
    config->useragent= useragent;
  }
  else
    allocuseragent = TRUE;

  if (config->postfields) {
    if (config->use_httpget) {
      /* Use the postfields data for a http get */
      httpgetfields = strdup(config->postfields);
      free(config->postfields);
      config->postfields = NULL;
      if(SetHTTPrequest((config->conf&CONF_NOBODY?HTTPREQ_HEAD:HTTPREQ_GET),
                        &config->httpreq)) {
        free(httpgetfields);
        return PARAM_BAD_USE;
      }
    }
    else {
      if(SetHTTPrequest(HTTPREQ_SIMPLEPOST, &config->httpreq))
        return PARAM_BAD_USE;
    }
  }

  /*
   * Get a curl handle to use for all forthcoming curl transfers.  Cleanup
   * when all transfers are done. This is supported with libcurl 7.7 and
   * should not be attempted on previous versions.
   */
  curl = curl_easy_init();
  if(!curl)
    return CURLE_FAILED_INIT;

  urlnode = config->url_list;

  if(config->headerfile) {
    /* open file for output: */
    if(strcmp(config->headerfile,"-")) {
      heads.filename = config->headerfile;
      headerfilep=NULL;
    }
    else
      headerfilep=stdout;
    heads.stream = headerfilep;
    heads.config = config;
  }

  /* loop through the list of given URLs */
  while(urlnode) {

    /* get the full URL (it might be NULL) */
    url=urlnode->url;

    if(NULL == url) {
      /* This node had no URL, skip it and continue to the next */
      if(urlnode->outfile)
        free(urlnode->outfile);
    
      /* move on to the next URL */
      nextnode=urlnode->next;
      free(urlnode); /* free the node */
      urlnode = nextnode;
      continue; /* next please */
    }

    /* default output stream is stdout */
    outs.stream = stdout;
    outs.config = config;

    if(!config->globoff) {
      /* Unless explicitly shut off, we expand '{...}' and '[...]' expressions
         and return total number of URLs in pattern set */
      res = glob_url(&urls, url, &urlnum);
      if(res != CURLE_OK)
        return res;
    }


    /* save outfile pattern before expansion */
    outfiles = urlnode->outfile?strdup(urlnode->outfile):NULL;

    if ((!outfiles || strequal(outfiles, "-")) && urlnum > 1) {
      /* multiple files extracted to stdout, insert separators! */
      separator = 1;
    }
    for(i = 0;
        (url = urls?next_url(urls):(i?NULL:strdup(url)));
        i++) {
      char *outfile;
      outfile = outfiles?strdup(outfiles):NULL;
 
      if((urlnode->flags&GETOUT_USEREMOTE) ||
         (outfile && !strequal("-", outfile)) ) {

        /* 
         * We have specified a file name to store the result in, or we have
         * decided we want to use the remote file name.
         */
      
        if(!outfile) {
          /* Find and get the remote file name */
          char * pc =strstr(url, "://");
          if(pc)
            pc+=3;
          else
            pc=url;
          pc = strrchr(pc, '/');
          outfile = (char *) NULL == pc ? NULL : strdup(pc+1) ;
          if(!outfile) {
            helpf("Remote file name has no length!\n");
            return CURLE_WRITE_ERROR;
          }
        }
        else if(urls) {
          /* fill '#1' ... '#9' terms from URL pattern */
          char *storefile = outfile;
          outfile = match_url(storefile, urls);
          free(storefile);
        }
      
        if(config->resume_from_current) {
          /* we're told to continue where we are now, then we get the size of
             the file as it is now and open it for append instead */

          struct stat fileinfo;

/*VMS?? -- Danger, the filesize is only valid for stream files */
          if(0 == stat(outfile, &fileinfo)) {
            /* set offset to current file size: */
            config->resume_from = fileinfo.st_size;
          }
          /* else let offset remain 0 */
        }
      
        if(config->resume_from) {
          /* open file for output: */
          outs.stream=(FILE *) fopen(outfile, config->resume_from?"ab":"wb");
          if (!outs.stream) {
            helpf("Can't open '%s'!\n", outfile);
            return CURLE_WRITE_ERROR;
          }
        }
        else {
          outs.filename = outfile;
          outs.stream = NULL; /* open when needed */
        }
      }
      if(config->infile) {
        /*
         * We have specified a file to upload
         */
        struct stat fileinfo;

        /* If no file name part is given in the URL, we add this file name */
        char *ptr=strstr(url, "://");
        if(ptr)
          ptr+=3;
        else
          ptr=url;
        ptr = strrchr(ptr, '/');
        if(!ptr || !strlen(++ptr)) {
          /* The URL has no file name part, add the local file name. In order
             to be able to do so, we have to create a new URL in another
             buffer.*/

          /* We only want the part of the local path that is on the right
             side of the rightmost slash and backslash. */
          char *filep = strrchr(config->infile, '/');
          char *file2 = strrchr(filep?filep:config->infile, '\\');

          if(file2)
            filep = file2+1;
          else if(filep)
            filep++;
          else
            filep = config->infile;

          urlbuffer=(char *)malloc(strlen(url) + strlen(filep) + 3);
          if(!urlbuffer) {
            helpf("out of memory\n");
            return CURLE_OUT_OF_MEMORY;
          }
          if(ptr)
            /* there is a trailing slash on the URL */
            sprintf(urlbuffer, "%s%s", url, filep);
          else
            /* thers is no trailing slash on the URL */
            sprintf(urlbuffer, "%s/%s", url, filep);
          
          url = urlbuffer; /* use our new URL instead! */
        }
/*VMS??-- Reading binary from files can be a problem... */
/*VMS??   Only FIXED, VAR etc WITHOUT implied CC will work */
/*VMS??   Others need a \n appended to a line */
/*VMS??-- Stat gives a size but this is UNRELIABLE in VMS */
/*VMS??   As a f.e. a fixed file with implied CC needs to have a byte added */
/*VMS??   for every record processed, this can by derived from Filesize & recordsize */
/*VMS??   for VARiable record files the records need to be counted! */
/*VMS??   for every record add 1 for linefeed and subtract 2 for the record header */
/*VMS??   for VARIABLE header files only the bare record data needs to be considered with one appended if implied CC */

        infd=(FILE *) fopen(config->infile, "rb");
        if (!infd || stat(config->infile, &fileinfo)) {
          helpf("Can't open '%s'!\n", config->infile);
          return CURLE_READ_ERROR;
        }
        infilesize=fileinfo.st_size;
      
      }
      if((config->conf&CONF_UPLOAD) &&
         config->resume_from_current) {
        config->resume_from = -1; /* -1 will then force get-it-yourself */
      }
      if(outs.stream && isatty(fileno(outs.stream)) &&
         !(config->conf&(CONF_UPLOAD|CONF_HTTPPOST)))
        /* we send the output to a tty and it isn't an upload operation,
           therefore we switch off the progress meter */
        config->conf |= CONF_NOPROGRESS;
    

      if (urlnum > 1) {
        fprintf(stderr, "\n[%d/%d]: %s --> %s\n",
                i+1, urlnum, url, outfile ? outfile : "<stdout>");
        if (separator)
          printf("%s%s\n", CURLseparator, url);
      }
      if (httpgetfields) {
        /* Find out whether the url contains a file name */
        char *pc =strstr(url, "://");
        char separator='?';
        if(pc)
          pc+=3;
        else
          pc=url;

        pc = strrchr(pc, '/'); /* check for a slash */

        if(pc) {
          /* there is a slash present in the URL */

          if(strchr(pc, '?'))
          /* Ouch, there's already a question mark in the URL string, we
             then appead the data with an amperand separator instead! */
            separator='&';
        }
        /*
         * Then append ? followed by the get fields to the url.
         */
        urlbuffer=(char *)malloc(strlen(url) + strlen(httpgetfields) + 2);
        if(!urlbuffer) {
          helpf("out of memory\n");
          return CURLE_OUT_OF_MEMORY;
        }
        if (pc)
          sprintf(urlbuffer, "%s%c%s", url, separator, httpgetfields);
        else
          /* Append  / before the ? to create a well-formed url
             if the url contains a hostname only
          */
          sprintf(urlbuffer, "%s/?%s", url, httpgetfields);
 
        free(url); /* free previous URL */
        url = urlbuffer; /* use our new URL instead! */
      }

      if(!config->errors)
        config->errors = stderr;

#if defined(WIN32) && !defined(__CYGWIN32__)
      if(!outfile && !(config->conf & CONF_GETTEXT)) {
        /* We get the output to stdout and we have not got the ASCII/text flag,
           then set stdout to be binary */
        setmode( 1, O_BINARY );
      }
#endif

      curl_easy_setopt(curl, CURLOPT_SSLENGINE, config->engine);
      curl_easy_setopt(curl, CURLOPT_SSLENGINE_DEFAULT, 1);

      curl_easy_setopt(curl, CURLOPT_FILE, (FILE *)&outs); /* where to store */
      /* what call to write: */
      curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
      curl_easy_setopt(curl, CURLOPT_INFILE, infd); /* for uploads */
      /* size of uploaded file: */
      curl_easy_setopt(curl, CURLOPT_INFILESIZE, infilesize);
      curl_easy_setopt(curl, CURLOPT_URL, url);     /* what to fetch */
      curl_easy_setopt(curl, CURLOPT_PROXY, config->proxy); /* proxy to use */
      curl_easy_setopt(curl, CURLOPT_HEADER, config->conf&CONF_HEADER);
      curl_easy_setopt(curl, CURLOPT_NOPROGRESS, config->conf&CONF_NOPROGRESS);
      curl_easy_setopt(curl, CURLOPT_NOBODY, config->conf&CONF_NOBODY);
      curl_easy_setopt(curl, CURLOPT_FAILONERROR,
                       config->conf&CONF_FAILONERROR);
      curl_easy_setopt(curl, CURLOPT_UPLOAD, config->conf&CONF_UPLOAD);
      curl_easy_setopt(curl, CURLOPT_FTPLISTONLY,
                       config->conf&CONF_FTPLISTONLY);
      curl_easy_setopt(curl, CURLOPT_FTPAPPEND, config->conf&CONF_FTPAPPEND);

      if (config->conf&CONF_NETRC_OPT)
        curl_easy_setopt(curl, CURLOPT_NETRC, CURL_NETRC_OPTIONAL);
      else if (config->conf&CONF_NETRC)
        curl_easy_setopt(curl, CURLOPT_NETRC, CURL_NETRC_REQUIRED);
      else
        curl_easy_setopt(curl, CURLOPT_NETRC, CURL_NETRC_IGNORED);

      curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION,
                       config->conf&CONF_FOLLOWLOCATION);
      curl_easy_setopt(curl, CURLOPT_TRANSFERTEXT, config->conf&CONF_GETTEXT);
      curl_easy_setopt(curl, CURLOPT_MUTE, config->conf&CONF_MUTE);
      curl_easy_setopt(curl, CURLOPT_USERPWD, config->userpwd);
      curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, config->proxyuserpwd);
      curl_easy_setopt(curl, CURLOPT_RANGE, config->range);
      curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuffer);
      curl_easy_setopt(curl, CURLOPT_TIMEOUT, config->timeout);
      curl_easy_setopt(curl, CURLOPT_POSTFIELDS, config->postfields);
        
      /* new in libcurl 7.2: */
      curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, config->postfieldsize);
        
      curl_easy_setopt(curl, CURLOPT_REFERER, config->referer);
      curl_easy_setopt(curl, CURLOPT_AUTOREFERER,
                       config->conf&CONF_AUTO_REFERER);
      curl_easy_setopt(curl, CURLOPT_USERAGENT, config->useragent);
      curl_easy_setopt(curl, CURLOPT_FTPPORT, config->ftpport);
      curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, config->low_speed_limit);
      curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, config->low_speed_time);
      curl_easy_setopt(curl, CURLOPT_RESUME_FROM,
                       config->use_resume?config->resume_from:0);
      curl_easy_setopt(curl, CURLOPT_COOKIE, config->cookie);
      curl_easy_setopt(curl, CURLOPT_HTTPHEADER, config->headers);
      curl_easy_setopt(curl, CURLOPT_HTTPPOST, config->httppost);
      curl_easy_setopt(curl, CURLOPT_SSLCERT, config->cert);
      curl_easy_setopt(curl, CURLOPT_SSLCERTTYPE, config->cert_type);
      curl_easy_setopt(curl, CURLOPT_SSLKEY, config->key);
      curl_easy_setopt(curl, CURLOPT_SSLKEYTYPE, config->key_type);
      curl_easy_setopt(curl, CURLOPT_SSLKEYPASSWD, config->key_passwd);

      if(config->cacert || config->capath) {
        if (config->cacert) curl_easy_setopt(curl, CURLOPT_CAINFO, config->cacert);
        if (config->capath) curl_easy_setopt(curl, CURLOPT_CAPATH, config->capath);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, TRUE);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2);
      }
      else
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1);
      
      if((config->conf&CONF_NOBODY) ||
         config->remote_time) {
        /* no body or use remote time */
        curl_easy_setopt(curl, CURLOPT_FILETIME, TRUE);
      }
      
      if (config->maxredirs) 
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, config->maxredirs); 
      else 
        curl_easy_setopt(curl, CURLOPT_MAXREDIRS, DEFAULT_MAXREDIRS); 
 
      curl_easy_setopt(curl, CURLOPT_CRLF, config->crlf);
      curl_easy_setopt(curl, CURLOPT_QUOTE, config->quote);
      curl_easy_setopt(curl, CURLOPT_POSTQUOTE, config->postquote);
      curl_easy_setopt(curl, CURLOPT_WRITEHEADER,
                       config->headerfile?&heads:NULL);
      curl_easy_setopt(curl, CURLOPT_COOKIEFILE, config->cookiefile);
      /* cookie jar was added in 7.9 */
      curl_easy_setopt(curl, CURLOPT_COOKIEJAR, config->cookiejar);
      /* cookie session added in 7.9.7 */
      curl_easy_setopt(curl, CURLOPT_COOKIESESSION, config->cookiesession);

      curl_easy_setopt(curl, CURLOPT_SSLVERSION, config->ssl_version);
      curl_easy_setopt(curl, CURLOPT_TIMECONDITION, config->timecond);
      curl_easy_setopt(curl, CURLOPT_TIMEVALUE, config->condtime);
      curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, config->customrequest);
      curl_easy_setopt(curl, CURLOPT_STDERR, config->errors);
      
      /* three new ones in libcurl 7.3: */
      curl_easy_setopt(curl, CURLOPT_HTTPPROXYTUNNEL, config->proxytunnel);
      curl_easy_setopt(curl, CURLOPT_INTERFACE, config->iface);
      curl_easy_setopt(curl, CURLOPT_KRB4LEVEL, config->krb4level);
      
      if((config->progressmode == CURL_PROGRESS_BAR) &&
         !(config->conf&(CONF_NOPROGRESS|CONF_MUTE))) {
        /* we want the alternative style, then we have to implement it
           ourselves! */
        progressbarinit(&progressbar, config);
        curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, myprogress);
        curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &progressbar);
      }
        
      /* new in libcurl 7.6.2: */
      curl_easy_setopt(curl, CURLOPT_TELNETOPTIONS, config->telnet_options);

      /* new in libcurl 7.7: */
      curl_easy_setopt(curl, CURLOPT_RANDOM_FILE, config->random_file);
      curl_easy_setopt(curl, CURLOPT_EGDSOCKET, config->egd_file);
      curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, config->connecttimeout);

      if(config->cipher_list)
        curl_easy_setopt(curl, CURLOPT_SSL_CIPHER_LIST, config->cipher_list);

      if(config->httpversion)
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, config->httpversion);

      /* new in libcurl 7.9.2: */
      if(config->disable_epsv)
        /* disable it */
        curl_easy_setopt(curl, CURLOPT_FTP_USE_EPSV, FALSE);

      /* new in curl 7.9.7 */
      if(config->trace_dump) {
        curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
        curl_easy_setopt(curl, CURLOPT_DEBUGDATA, config);
        config->conf |= CONF_VERBOSE; /* force verbose */
      }
      curl_easy_setopt(curl, CURLOPT_VERBOSE, config->conf&CONF_VERBOSE);
      
      res = curl_easy_perform(curl);
        
      if((config->progressmode == CURL_PROGRESS_BAR) &&
         progressbar.calls) {
        /* if the custom progress bar has been displayed, we output a
           newline here */
        fputs("\n", progressbar.out);
      }

      if(config->writeout) {
        ourWriteOut(curl, config->writeout);
      }
#ifdef USE_ENVIRONMENT
      if (config->writeenv)
        ourWriteEnv(curl);
#endif

#ifdef	VMS
      if (!config->showerror)  {
        vms_show = VMSSTS_HIDE;
      }
#else
      if((res!=CURLE_OK) && config->showerror)
        fprintf(config->errors, "curl: (%d) %s\n", res, errorbuffer);
#endif

      if (outfile && !strequal(outfile, "-") && outs.stream)
        fclose(outs.stream);

#ifdef HAVE_UTIME
      /* Important that we set the time _after_ the file has been 
         closed, as is done above here */
      if(config->remote_time && outs.filename) {
        /* as libcurl if we got a time. Pretty please */
        long filetime;
        curl_easy_getinfo(curl, CURLINFO_FILETIME, &filetime);
        if(filetime >= 0) {
          struct utimbuf times;
          times.actime = filetime;
          times.modtime = filetime;
          utime(outs.filename, &times); /* set the time we got */
        }
      }
#endif

      if (config->infile)
        fclose(infd);
      if(headerfilep)
        fclose(headerfilep);
      
      if (httpgetfields)
        free(httpgetfields);

      if(url)
        free(url);

      if(outfile)
        free(outfile);
    }
    if(outfiles)
      free(outfiles);

    if(urls)
      /* cleanup memory used for URL globbing patterns */
      glob_cleanup(urls);

    /* empty this urlnode struct */
    if(urlnode->url)
      free(urlnode->url);
    if(urlnode->outfile)
      free(urlnode->outfile);
    
    /* move on to the next URL */
    nextnode=urlnode->next;
    free(urlnode); /* free the node */
    urlnode = nextnode;

  } /* while-loop through all URLs */

  if(config->headerfile && !headerfilep && heads.stream)
    fclose(heads.stream);

  if(config->trace_fopened)
    fclose(config->trace_stream);

  if(allocuseragent)
    free(config->useragent);

  /* cleanup the curl handle! */
  curl_easy_cleanup(curl);

  if(config->errors_fopened)
    fclose(config->errors);

  main_free(); /* cleanup */

  return res;
}