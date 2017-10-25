int main(int argc, char *argv[])
{
  char errorbuffer[CURL_ERROR_SIZE];
  struct ProgressData progressbar;

  struct OutStruct outs;
  struct OutStruct heads;

  char *url = NULL;

  URLGlob *urls;
  int urlnum;
  char *outfiles;
  int separator = 0;
  
  FILE *infd = stdin;
  FILE *headerfilep = NULL;
  char *urlbuffer=NULL;
  int infilesize=-1; /* -1 means unknown */
  bool stillflags=TRUE;

  CURL *curl;
  int res;
  int i;

  outs.stream = stdout;

  memset(&config, 0, sizeof(struct Configurable));
  
  /* set non-zero default values: */
  config.useragent= maprintf(CURL_NAME "/" CURL_VERSION " (" OS ") "
                             "%s", curl_version());
  config.showerror=TRUE;
  config.conf=CONF_DEFAULT;
#if 0
  config.crlf=FALSE;
  config.quote=NULL;
#endif

  if(argc>1 &&
     (!strnequal("--", argv[1], 2) && (argv[1][0] == '-')) &&
     strchr(argv[1], 'q')) {
    /*
     * The first flag, that is not a verbose name, but a shortname
     * and it includes the 'q' flag!
     */
#if 0
    fprintf(stderr, "I TURNED OFF THE CRAP\n");
#endif
    ;
  }
  else {
    res = parseconfig(NULL, &config);
    if(res)
      return res;
  }

  if ((argc < 2)  && !config.url) {
    helpf(NULL);
    return CURLE_FAILED_INIT;
  }

  /* Parse options */
  for (i = 1; i < argc; i++) {
    if(stillflags &&
       ('-' == argv[i][0])) {
      char *nextarg;
      bool passarg;
      
      char *flag = &argv[i][1];

      if(strequal("--", argv[i]))
	/* this indicates the end of the flags and thus enables the
	   following (URL) argument to start with -. */
	stillflags=FALSE;
      else {
	nextarg= (i < argc - 1)? argv[i+1]: NULL;

	res = getparameter ( flag,
			     nextarg,
			     &passarg,
			   &config );
	if(res)
	  return res;

	if(passarg) /* we're supposed to skip this */
	  i++;
      }
    }
    else {
      if(url) {
	helpf("only one URL is supported!\n");
	return CURLE_FAILED_INIT;
      }
      url = argv[i];
    }
  }

  /* if no URL was specified and there was one in the config file, get that
     one */
  if(!url && config.url)
    url = config.url;
  
  if(!url) {
    helpf("no URL specified!\n");
    return CURLE_FAILED_INIT;
  }
#if 0
  fprintf(stderr, "URL: %s PROXY: %s\n", url, config.proxy?config.proxy:"none");
#endif

  /* expand '{...}' and '[...]' expressions and return total number of URLs
     in pattern set */
  res = glob_url(&urls, url, &urlnum);
  if(res != CURLE_OK)
    return res;

  outfiles = config.outfile;		/* save outfile pattern befor expansion */
  if (!outfiles && !config.remotefile && urlnum > 1) {
#ifdef CURL_SEPARATORS
    /* multiple files extracted to stdout, insert separators! */
    separator = 1;
#endif
#ifdef MIME_SEPARATORS
    /* multiple files extracted to stdout, insert MIME separators! */
    separator = 1;
    printf("MIME-Version: 1.0\n");
    printf("Content-Type: multipart/mixed; boundary=%s\n\n", MIMEseparator);
#endif
  }
  for (i = 0; (url = next_url(urls)); ++i) {
    if (outfiles)
      config.outfile = strdup(outfiles);

  if(config.outfile && config.infile) {
    helpf("you can't both upload and download!\n");
    return CURLE_FAILED_INIT;
  }
 
  if (config.outfile || config.remotefile) {
    /* 
     * We have specified a file name to store the result in, or we have
     * decided we want to use the remote file name.
     */

    if(config.remotefile) {
      /* Find and get the remote file name */
      config.outfile=strstr(url, "://");
      if(config.outfile)
        config.outfile+=3;
      else
        config.outfile=url;
      config.outfile = strrchr(config.outfile, '/');
      if(!config.outfile || !strlen(++config.outfile)) {
        helpf("Remote file name has no length!\n");
        return CURLE_WRITE_ERROR;
      }
    }
    else	/* fill '#1' ... '#9' terms from URL pattern */
      config.outfile = match_url(config.outfile, *urls);

    if((0 == config.resume_from) && config.use_resume) {
      /* we're told to continue where we are now, then we get the size of the
	 file as it is now and open it for append instead */
      struct stat fileinfo;

      if(0 == stat(config.outfile, &fileinfo)) {
	/* set offset to current file size: */
	config.resume_from = fileinfo.st_size;
      }
      /* else let offset remain 0 */
    }

    if(config.resume_from) {
      /* open file for output: */
      outs.stream=(FILE *) fopen(config.outfile, config.resume_from?"ab":"wb");
      if (!outs.stream) {
        helpf("Can't open '%s'!\n", config.outfile);
        return CURLE_WRITE_ERROR;
      }
    }
    else {
      outs.filename = config.outfile;
      outs.stream = NULL; /* open when needed */
    }
  }
  if (config.infile) {
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
         to be able to do so, we have to create a new URL in another buffer.*/
      urlbuffer=(char *)malloc(strlen(url) + strlen(config.infile) + 3);
      if(!urlbuffer) {
        helpf("out of memory\n");
        return CURLE_OUT_OF_MEMORY;
      }
      if(ptr)
        /* there is a trailing slash on the URL */
        sprintf(urlbuffer, "%s%s", url, config.infile);
      else
        /* thers is no trailing slash on the URL */
        sprintf(urlbuffer, "%s/%s", url, config.infile);

      url = urlbuffer; /* use our new URL instead! */
    }

    infd=(FILE *) fopen(config.infile, "rb");
    if (!infd || stat(config.infile, &fileinfo)) {
      helpf("Can't open '%s'!\n", config.infile);
      return CURLE_READ_ERROR;
    }
    infilesize=fileinfo.st_size;

  }
  if((config.conf&CONF_UPLOAD) &&
     config.use_resume &&
     (0==config.resume_from)) {
    config.resume_from = -1; /* -1 will then force get-it-yourself */
  }
  if(config.headerfile) {
    /* open file for output: */
    if(strcmp(config.headerfile,"-"))
    {
      heads.filename = config.headerfile;
      headerfilep=NULL;
    }
    else
      headerfilep=stdout;
    heads.stream = headerfilep;
  }

  if(outs.stream && isatty(fileno(outs.stream)) &&
     !(config.conf&(CONF_UPLOAD|CONF_HTTPPOST)))
    /* we send the output to a tty and it isn't an upload operation, therefore
       we switch off the progress meter */
    config.conf |= CONF_NOPROGRESS;


  if (urlnum > 1) {
    fprintf(stderr, "\n[%d/%d]: %s --> %s\n", i+1, urlnum, url, config.outfile ? config.outfile : "<stdout>");
    if (separator) {
#ifdef CURL_SEPARATORS
      printf("%s%s\n", CURLseparator, url);
#endif
#ifdef MIME_SEPARATORS
      printf("--%s\n", MIMEseparator);
      printf("Content-ID: %s\n\n", url); 
#endif
    }
  }

  if(!config.errors)
    config.errors = stderr;

#ifdef WIN32
  if(!config.outfile && !(config.conf & CONF_GETTEXT)) {
    /* We get the output to stdout and we have not got the ASCII/text flag,
       then set stdout to be binary */
    setmode( 1, O_BINARY );
  }
#endif


  main_init();

#if 0
  /* This is code left from the pre-v7 time, left here mainly as a reminder
     and possibly as a warning! ;-) */

  res = curl_urlget(CURLOPT_FILE, (FILE *)&outs,  /* where to store */
                    CURLOPT_WRITEFUNCTION, my_fwrite, /* what call to write */
                    CURLOPT_INFILE, infd, /* for uploads */
                    CURLOPT_INFILESIZE, infilesize, /* size of uploaded file */
                    CURLOPT_URL, url,     /* what to fetch */
                    CURLOPT_PROXY, config.proxy, /* proxy to use */
                    CURLOPT_FLAGS, config.conf, /* flags */
                    CURLOPT_USERPWD, config.userpwd, /* user + passwd */
                    CURLOPT_PROXYUSERPWD, config.proxyuserpwd, /* Proxy user + passwd */
                    CURLOPT_RANGE, config.range, /* range of document */
                    CURLOPT_ERRORBUFFER, errorbuffer,
                    CURLOPT_TIMEOUT, config.timeout,
                    CURLOPT_POSTFIELDS, config.postfields,
                    CURLOPT_REFERER, config.referer,
                    CURLOPT_USERAGENT, config.useragent,
                    CURLOPT_FTPPORT, config.ftpport,
                    CURLOPT_LOW_SPEED_LIMIT, config.low_speed_limit,
                    CURLOPT_LOW_SPEED_TIME, config.low_speed_time,
                    CURLOPT_RESUME_FROM, config.use_resume?config.resume_from:0,
                    CURLOPT_COOKIE, config.cookie,
                    CURLOPT_HTTPHEADER, config.headers,
                    CURLOPT_HTTPPOST, config.httppost,
                    CURLOPT_SSLCERT, config.cert,
                    CURLOPT_SSLCERTPASSWD, config.cert_passwd,
                    CURLOPT_CRLF, config.crlf,
                    CURLOPT_QUOTE, config.quote,
                    CURLOPT_POSTQUOTE, config.postquote,
                    CURLOPT_WRITEHEADER, config.headerfile?&heads:NULL,
                    CURLOPT_COOKIEFILE, config.cookiefile,
                    CURLOPT_SSLVERSION, config.ssl_version,
                    CURLOPT_TIMECONDITION, config.timecond,
                    CURLOPT_TIMEVALUE, config.condtime,
                    CURLOPT_CUSTOMREQUEST, config.customrequest,
                    CURLOPT_STDERR, config.errors,
                    CURLOPT_PROGRESSMODE, config.progressmode,
                    CURLOPT_WRITEINFO, config.writeout,
                    CURLOPT_DONE); /* always terminate the list of tags */

#endif
  /* The new, v7-style easy-interface! */
  curl = curl_easy_init();
  if(curl) {
    curl_easy_setopt(curl, CURLOPT_FILE, (FILE *)&outs);  /* where to store */
    /* what call to write: */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_fwrite);
    curl_easy_setopt(curl, CURLOPT_INFILE, infd); /* for uploads */
    /* size of uploaded file: */
    curl_easy_setopt(curl, CURLOPT_INFILESIZE, infilesize);
    curl_easy_setopt(curl, CURLOPT_URL, url);     /* what to fetch */
    curl_easy_setopt(curl, CURLOPT_PROXY, config.proxy); /* proxy to use */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, config.conf&CONF_VERBOSE);
    curl_easy_setopt(curl, CURLOPT_HEADER, config.conf&CONF_HEADER);
    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, config.conf&CONF_NOPROGRESS);
    curl_easy_setopt(curl, CURLOPT_NOBODY, config.conf&CONF_NOBODY);
    curl_easy_setopt(curl, CURLOPT_FAILONERROR, config.conf&CONF_FAILONERROR);
    curl_easy_setopt(curl, CURLOPT_UPLOAD, config.conf&CONF_UPLOAD);
    curl_easy_setopt(curl, CURLOPT_POST, config.conf&CONF_POST);
    curl_easy_setopt(curl, CURLOPT_FTPLISTONLY, config.conf&CONF_FTPLISTONLY);
    curl_easy_setopt(curl, CURLOPT_FTPAPPEND, config.conf&CONF_FTPAPPEND);
    curl_easy_setopt(curl, CURLOPT_NETRC, config.conf&CONF_NETRC);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION,
                     config.conf&CONF_FOLLOWLOCATION);
    curl_easy_setopt(curl, CURLOPT_TRANSFERTEXT, config.conf&CONF_GETTEXT);
    curl_easy_setopt(curl, CURLOPT_PUT, config.conf&CONF_PUT);
    curl_easy_setopt(curl, CURLOPT_MUTE, config.conf&CONF_MUTE);
    curl_easy_setopt(curl, CURLOPT_USERPWD, config.userpwd);
    curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, config.proxyuserpwd);
    curl_easy_setopt(curl, CURLOPT_RANGE, config.range);
    curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errorbuffer);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, config.timeout);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, config.postfields);
    curl_easy_setopt(curl, CURLOPT_REFERER, config.referer);
    curl_easy_setopt(curl, CURLOPT_AUTOREFERER, config.conf&CONF_AUTO_REFERER);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, config.useragent);
    curl_easy_setopt(curl, CURLOPT_FTPPORT, config.ftpport);
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_LIMIT, config.low_speed_limit);
    curl_easy_setopt(curl, CURLOPT_LOW_SPEED_TIME, config.low_speed_time);
    curl_easy_setopt(curl, CURLOPT_RESUME_FROM,
                     config.use_resume?config.resume_from:0);
    curl_easy_setopt(curl, CURLOPT_COOKIE, config.cookie);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, config.headers);
    curl_easy_setopt(curl, CURLOPT_HTTPPOST, config.httppost);
    curl_easy_setopt(curl, CURLOPT_SSLCERT, config.cert);
    curl_easy_setopt(curl, CURLOPT_SSLCERTPASSWD, config.cert_passwd);
    curl_easy_setopt(curl, CURLOPT_CRLF, config.crlf);
    curl_easy_setopt(curl, CURLOPT_QUOTE, config.quote);
    curl_easy_setopt(curl, CURLOPT_POSTQUOTE, config.postquote);
    curl_easy_setopt(curl, CURLOPT_WRITEHEADER, config.headerfile?&heads:NULL);
    curl_easy_setopt(curl, CURLOPT_COOKIEFILE, config.cookiefile);
    curl_easy_setopt(curl, CURLOPT_SSLVERSION, config.ssl_version);
    curl_easy_setopt(curl, CURLOPT_TIMECONDITION, config.timecond);
    curl_easy_setopt(curl, CURLOPT_TIMEVALUE, config.condtime);
    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, config.customrequest);
    curl_easy_setopt(curl, CURLOPT_STDERR, config.errors);
    curl_easy_setopt(curl, CURLOPT_WRITEINFO, config.writeout);

    if((config.progressmode == CURL_PROGRESS_BAR) &&
       !(config.conf&(CONF_NOPROGRESS|CONF_MUTE))) {
      /* we want the alternative style, then we have to implement it
         ourselves! */
      progressbarinit(&progressbar);
      curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, myprogress);
      curl_easy_setopt(curl, CURLOPT_PROGRESSDATA, &progressbar);
    }

    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);

    if((res!=CURLE_OK) && config.showerror)
      fprintf(config.errors, "curl: (%d) %s\n", res, errorbuffer);
  }
  else
    fprintf(config.errors, "curl: failed to init libcurl!\n");

  main_free();

  if((config.errors != stderr) &&
     (config.errors != stdout))
    /* it wasn't directed to stdout or stderr so close the file! */
    fclose(config.errors);

  if(config.headerfile && !headerfilep && heads.stream)
    fclose(heads.stream);

  if(urlbuffer)
    free(urlbuffer);
  if (config.outfile && outs.stream)
    fclose(outs.stream);
  if (config.infile)
    fclose(infd);
  if(headerfilep)
    fclose(headerfilep);

  if(config.url)
    free(config.url);

  if(url)
    free(url);
  if(config.outfile && !config.remotefile)
    free(config.outfile);
  }
#ifdef MIME_SEPARATORS
  if (separator)
    printf("--%s--\n", MIMEseparator);
#endif

  curl_slist_free_all(config.quote); /* the checks for config.quote == NULL */
  curl_slist_free_all(config.postquote); /*  */
  curl_slist_free_all(config.headers); /*  */

  return(res);
}