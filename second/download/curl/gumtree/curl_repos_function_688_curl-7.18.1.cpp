CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option,
                     va_list param)
{
  char *argptr;
  CURLcode result = CURLE_OK;
#ifndef CURL_DISABLE_HTTP
  curl_off_t bigsize;
#endif

  switch(option) {
  case CURLOPT_DNS_CACHE_TIMEOUT:
    data->set.dns_cache_timeout = va_arg(param, long);
    break;
  case CURLOPT_DNS_USE_GLOBAL_CACHE:
    {
      /* remember we want this enabled */
      long use_cache = va_arg(param, long);
      data->set.global_dns_cache = (bool)(0 != use_cache);
    }
    break;
  case CURLOPT_SSL_CIPHER_LIST:
    /* set a list of cipher we want to use in the SSL connection */
    result = setstropt(&data->set.str[STRING_SSL_CIPHER_LIST],
                            va_arg(param, char *));
    break;

  case CURLOPT_RANDOM_FILE:
    /*
     * This is the path name to a file that contains random data to seed
     * the random SSL stuff with. The file is only used for reading.
     */
    result = setstropt(&data->set.str[STRING_SSL_RANDOM_FILE],
                            va_arg(param, char *));
    break;
  case CURLOPT_EGDSOCKET:
    /*
     * The Entropy Gathering Daemon socket pathname
     */
    result = setstropt(&data->set.str[STRING_SSL_EGDSOCKET],
                            va_arg(param, char *));
    break;
  case CURLOPT_MAXCONNECTS:
    /*
     * Set the absolute number of maximum simultaneous alive connection that
     * libcurl is allowed to have.
     */
    result = Curl_ch_connc(data, data->state.connc, va_arg(param, long));
    break;
  case CURLOPT_FORBID_REUSE:
    /*
     * When this transfer is done, it must not be left to be reused by a
     * subsequent transfer but shall be closed immediately.
     */
    data->set.reuse_forbid = (bool)(0 != va_arg(param, long));
    break;
  case CURLOPT_FRESH_CONNECT:
    /*
     * This transfer shall not use a previously cached connection but
     * should be made with a fresh new connect!
     */
    data->set.reuse_fresh = (bool)(0 != va_arg(param, long));
    break;
  case CURLOPT_VERBOSE:
    /*
     * Verbose means infof() calls that give a lot of information about
     * the connection and transfer procedures as well as internal choices.
     */
    data->set.verbose = (bool)(0 != va_arg(param, long));
    break;
  case CURLOPT_HEADER:
    /*
     * Set to include the header in the general data output stream.
     */
    data->set.include_header = (bool)(0 != va_arg(param, long));
    break;
  case CURLOPT_NOPROGRESS:
    /*
     * Shut off the internal supported progress meter
     */
    data->set.hide_progress = (bool)(0 != va_arg(param, long));
    if(data->set.hide_progress)
      data->progress.flags |= PGRS_HIDE;
    else
      data->progress.flags &= ~PGRS_HIDE;
    break;
  case CURLOPT_NOBODY:
    /*
     * Do not include the body part in the output data stream.
     */
    data->set.opt_no_body = (bool)(0 != va_arg(param, long));
    if(data->set.opt_no_body)
      /* in HTTP lingo, this means using the HEAD request */
      data->set.httpreq = HTTPREQ_HEAD;
    break;
  case CURLOPT_FAILONERROR:
    /*
     * Don't output the >=300 error code HTML-page, but instead only
     * return error.
     */
    data->set.http_fail_on_error = (bool)(0 != va_arg(param, long));
    break;
  case CURLOPT_UPLOAD:
  case CURLOPT_PUT:
    /*
     * We want to sent data to the remote host. If this is HTTP, that equals
     * using the PUT request.
     */
    data->set.upload = (bool)(0 != va_arg(param, long));
    if(data->set.upload)
      /* If this is HTTP, PUT is what's needed to "upload" */
      data->set.httpreq = HTTPREQ_PUT;
    break;
  case CURLOPT_FILETIME:
    /*
     * Try to get the file time of the remote document. The time will
     * later (possibly) become available using curl_easy_getinfo().
     */
    data->set.get_filetime = (bool)(0 != va_arg(param, long));
    break;
  case CURLOPT_FTP_CREATE_MISSING_DIRS:
    /*
     * An FTP option that modifies an upload to create missing directories on
     * the server.
     */
    data->set.ftp_create_missing_dirs = (bool)(0 != va_arg(param, long));
    break;
  case CURLOPT_FTP_RESPONSE_TIMEOUT:
    /*
     * An FTP option that specifies how quickly an FTP response must be
     * obtained before it is considered failure.
     */
    data->set.ftp_response_timeout = va_arg( param , long ) * 1000;
    break;
  case CURLOPT_DIRLISTONLY:
    /*
     * An option that changes the command to one that asks for a list
     * only, no file info details.
     */
    data->set.ftp_list_only = (bool)(0 != va_arg(param, long));
    break;
  case CURLOPT_APPEND:
    /*
     * We want to upload and append to an existing file.
     */
    data->set.ftp_append = (bool)(0 != va_arg(param, long));
    break;
  case CURLOPT_FTP_FILEMETHOD:
    /*
     * How do access files over FTP.
     */
    data->set.ftp_filemethod = (curl_ftpfile)va_arg(param, long);
    break;
  case CURLOPT_NETRC:
    /*
     * Parse the $HOME/.netrc file
     */
    data->set.use_netrc = (enum CURL_NETRC_OPTION)va_arg(param, long);
    break;
  case CURLOPT_NETRC_FILE:
    /*
     * Use this file instead of the $HOME/.netrc file
     */
    result = setstropt(&data->set.str[STRING_NETRC_FILE],
                            va_arg(param, char *));
    break;
  case CURLOPT_TRANSFERTEXT:
    /*
     * This option was previously named 'FTPASCII'. Renamed to work with
     * more protocols than merely FTP.
     *
     * Transfer using ASCII (instead of BINARY).
     */
    data->set.prefer_ascii = (bool)(0 != va_arg(param, long));
    break;
  case CURLOPT_TIMECONDITION:
    /*
     * Set HTTP time condition. This must be one of the defines in the
     * curl/curl.h header file.
     */
    data->set.timecondition = (curl_TimeCond)va_arg(param, long);
    break;
  case CURLOPT_TIMEVALUE:
    /*
     * This is the value to compare with the remote document with the
     * method set with CURLOPT_TIMECONDITION
     */
    data->set.timevalue = (time_t)va_arg(param, long);
    break;
  case CURLOPT_SSLVERSION:
    /*
     * Set explicit SSL version to try to connect with, as some SSL
     * implementations are lame.
     */
    data->set.ssl.version = va_arg(param, long);
    break;

#ifndef CURL_DISABLE_HTTP
  case CURLOPT_AUTOREFERER:
    /*
     * Switch on automatic referer that gets set if curl follows locations.
     */
    data->set.http_auto_referer = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_ENCODING:
    /*
     * String to use at the value of Accept-Encoding header.
     *
     * If the encoding is set to "" we use an Accept-Encoding header that
     * encompasses all the encodings we support.
     * If the encoding is set to NULL we don't send an Accept-Encoding header
     * and ignore an received Content-Encoding header.
     *
     */
    argptr = va_arg(param, char *);
    result = setstropt(&data->set.str[STRING_ENCODING],
                            (argptr && !*argptr)?
                            (char *) ALL_CONTENT_ENCODINGS: argptr);
    break;

  case CURLOPT_FOLLOWLOCATION:
    /*
     * Follow Location: header hints on a HTTP-server.
     */
    data->set.http_follow_location = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_UNRESTRICTED_AUTH:
    /*
     * Send authentication (user+password) when following locations, even when
     * hostname changed.
     */
    data->set.http_disable_hostname_check_before_authentication =
      (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_MAXREDIRS:
    /*
     * The maximum amount of hops you allow curl to follow Location:
     * headers. This should mostly be used to detect never-ending loops.
     */
    data->set.maxredirs = va_arg(param, long);
    break;

  case CURLOPT_POST301:
    /*
     * Obey RFC 2616/10.3.2 and resubmit a POST as a POST after a 301.
     */
    data->set.post301 = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_POST:
    /* Does this option serve a purpose anymore? Yes it does, when
       CURLOPT_POSTFIELDS isn't used and the POST data is read off the
       callback! */
    if(va_arg(param, long)) {
      data->set.httpreq = HTTPREQ_POST;
      data->set.opt_no_body = FALSE; /* this is implied */
    }
    else
      data->set.httpreq = HTTPREQ_GET;
    break;

  case CURLOPT_COPYPOSTFIELDS:
    /*
     * A string with POST data. Makes curl HTTP POST. Even if it is NULL.
     * If needed, CURLOPT_POSTFIELDSIZE must have been set prior to
     *  CURLOPT_COPYPOSTFIELDS and not altered later.
     */
    argptr = va_arg(param, char *);

    if(!argptr || data->set.postfieldsize == -1)
      result = setstropt(&data->set.str[STRING_COPYPOSTFIELDS], argptr);
    else {
      /*
       *  Check that requested length does not overflow the size_t type.
       */

      if((data->set.postfieldsize < 0) ||
          ((sizeof(curl_off_t) != sizeof(size_t)) &&
           (data->set.postfieldsize > (curl_off_t)((size_t)-1))))
        result = CURLE_OUT_OF_MEMORY;
      else {
        char * p;

        (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);

        /* Allocate even when size == 0. This satisfies the need of possible
           later address compare to detect the COPYPOSTFIELDS mode, and
           to mark that postfields is used rather than read function or
           form data.
         */
        p = malloc((size_t)(data->set.postfieldsize?data->set.postfieldsize:1));

        if(!p)
          result = CURLE_OUT_OF_MEMORY;
        else {
          if(data->set.postfieldsize)
            memcpy(p, argptr, (size_t)data->set.postfieldsize);

          data->set.str[STRING_COPYPOSTFIELDS] = p;
        }
      }
    }

    data->set.postfields = data->set.str[STRING_COPYPOSTFIELDS];
    data->set.httpreq = HTTPREQ_POST;
    break;

  case CURLOPT_POSTFIELDS:
    /*
     * Like above, but use static data instead of copying it.
     */
    data->set.postfields = va_arg(param, void *);
    /* Release old copied data. */
    (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);
    data->set.httpreq = HTTPREQ_POST;
    break;

  case CURLOPT_POSTFIELDSIZE:
    /*
     * The size of the POSTFIELD data to prevent libcurl to do strlen() to
     * figure it out. Enables binary posts.
     */
    bigsize = va_arg(param, long);

    if(data->set.postfieldsize < bigsize &&
        data->set.postfields == data->set.str[STRING_COPYPOSTFIELDS]) {
      /* Previous CURLOPT_COPYPOSTFIELDS is no longer valid. */
      (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);
      data->set.postfields = NULL;
      }

    data->set.postfieldsize = bigsize;
    break;

  case CURLOPT_POSTFIELDSIZE_LARGE:
    /*
     * The size of the POSTFIELD data to prevent libcurl to do strlen() to
     * figure it out. Enables binary posts.
     */
    bigsize = va_arg(param, curl_off_t);

    if(data->set.postfieldsize < bigsize &&
        data->set.postfields == data->set.str[STRING_COPYPOSTFIELDS]) {
      /* Previous CURLOPT_COPYPOSTFIELDS is no longer valid. */
      (void) setstropt(&data->set.str[STRING_COPYPOSTFIELDS], NULL);
      data->set.postfields = NULL;
      }

    data->set.postfieldsize = bigsize;
    break;

  case CURLOPT_HTTPPOST:
    /*
     * Set to make us do HTTP POST
     */
    data->set.httppost = va_arg(param, struct curl_httppost *);
    data->set.httpreq = HTTPREQ_POST_FORM;
    data->set.opt_no_body = FALSE; /* this is implied */
    break;

  case CURLOPT_REFERER:
    /*
     * String to set in the HTTP Referer: field.
     */
    if(data->change.referer_alloc) {
      free(data->change.referer);
      data->change.referer_alloc = FALSE;
    }
    result = setstropt(&data->set.str[STRING_SET_REFERER],
                            va_arg(param, char *));
    data->change.referer = data->set.str[STRING_SET_REFERER];
    break;

  case CURLOPT_USERAGENT:
    /*
     * String to use in the HTTP User-Agent field
     */
    result = setstropt(&data->set.str[STRING_USERAGENT],
                            va_arg(param, char *));
    break;

  case CURLOPT_HTTPHEADER:
    /*
     * Set a list with HTTP headers to use (or replace internals with)
     */
    data->set.headers = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_HTTP200ALIASES:
    /*
     * Set a list of aliases for HTTP 200 in response header
     */
    data->set.http200aliases = va_arg(param, struct curl_slist *);
    break;

#if !defined(CURL_DISABLE_COOKIES)
  case CURLOPT_COOKIE:
    /*
     * Cookie string to send to the remote server in the request.
     */
    result = setstropt(&data->set.str[STRING_COOKIE],
                            va_arg(param, char *));
    break;

  case CURLOPT_COOKIEFILE:
    /*
     * Set cookie file to read and parse. Can be used multiple times.
     */
    argptr = (char *)va_arg(param, void *);
    if(argptr) {
      struct curl_slist *cl;
      /* append the cookie file name to the list of file names, and deal with
         them later */
      cl = curl_slist_append(data->change.cookielist, argptr);

      if(!cl)
        return CURLE_OUT_OF_MEMORY;

      data->change.cookielist = cl; /* store the list for later use */
    }
    break;

  case CURLOPT_COOKIEJAR:
    /*
     * Set cookie file name to dump all cookies to when we're done.
     */
    result = setstropt(&data->set.str[STRING_COOKIEJAR],
                            va_arg(param, char *));

    /*
     * Activate the cookie parser. This may or may not already
     * have been made.
     */
    data->cookies = Curl_cookie_init(data, NULL, data->cookies,
                                     data->set.cookiesession);
    break;

  case CURLOPT_COOKIESESSION:
    /*
     * Set this option to TRUE to start a new "cookie session". It will
     * prevent the forthcoming read-cookies-from-file actions to accept
     * cookies that are marked as being session cookies, as they belong to a
     * previous session.
     *
     * In the original Netscape cookie spec, "session cookies" are cookies
     * with no expire date set. RFC2109 describes the same action if no
     * 'Max-Age' is set and RFC2965 includes the RFC2109 description and adds
     * a 'Discard' action that can enforce the discard even for cookies that
     * have a Max-Age.
     *
     * We run mostly with the original cookie spec, as hardly anyone implements
     * anything else.
     */
    data->set.cookiesession = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_COOKIELIST:
    argptr = va_arg(param, char *);

    if(argptr == NULL)
      break;

    if(strequal(argptr, "ALL")) {
      /* clear all cookies */
      Curl_cookie_clearall(data->cookies);
      break;
    }
    else if(strequal(argptr, "SESS")) {
      /* clear session cookies */
      Curl_cookie_clearsess(data->cookies);
      break;
    }
    else if(strequal(argptr, "FLUSH")) {
      /* flush cookies to file */
      flush_cookies(data, 0);
      break;
    }

    if(!data->cookies)
      /* if cookie engine was not running, activate it */
      data->cookies = Curl_cookie_init(data, NULL, NULL, TRUE);

    argptr = strdup(argptr);
    if(!argptr) {
      result = CURLE_OUT_OF_MEMORY;
      break;
    }

    if(checkprefix("Set-Cookie:", argptr))
      /* HTTP Header format line */
      Curl_cookie_add(data, data->cookies, TRUE, argptr + 11, NULL, NULL);

    else
      /* Netscape format line */
      Curl_cookie_add(data, data->cookies, FALSE, argptr, NULL, NULL);

    free(argptr);
    break;
#endif /* CURL_DISABLE_COOKIES */

  case CURLOPT_HTTPGET:
    /*
     * Set to force us do HTTP GET
     */
    if(va_arg(param, long)) {
      data->set.httpreq = HTTPREQ_GET;
      data->set.upload = FALSE; /* switch off upload */
      data->set.opt_no_body = FALSE; /* this is implied */
    }
    break;

  case CURLOPT_HTTP_VERSION:
    /*
     * This sets a requested HTTP version to be used. The value is one of
     * the listed enums in curl/curl.h.
     */
    data->set.httpversion = va_arg(param, long);
    break;

  case CURLOPT_HTTPPROXYTUNNEL:
    /*
     * Tunnel operations through the proxy instead of normal proxy use
     */
    data->set.tunnel_thru_httpproxy = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_CUSTOMREQUEST:
    /*
     * Set a custom string to use as request
     */
    result = setstropt(&data->set.str[STRING_CUSTOMREQUEST],
                            va_arg(param, char *));

    /* we don't set
       data->set.httpreq = HTTPREQ_CUSTOM;
       here, we continue as if we were using the already set type
       and this just changes the actual request keyword */
    break;

  case CURLOPT_PROXYPORT:
    /*
     * Explicitly set HTTP proxy port number.
     */
    data->set.proxyport = va_arg(param, long);
    break;

  case CURLOPT_HTTPAUTH:
    /*
     * Set HTTP Authentication type BITMASK.
     */
  {
    long auth = va_arg(param, long);
    /* switch off bits we can't support */
#ifndef USE_NTLM
    auth &= ~CURLAUTH_NTLM; /* no NTLM without SSL */
#endif
#ifndef HAVE_GSSAPI
    auth &= ~CURLAUTH_GSSNEGOTIATE; /* no GSS-Negotiate without GSSAPI */
#endif
    if(!auth)
      return CURLE_FAILED_INIT; /* no supported types left! */

    data->set.httpauth = auth;
  }
  break;

  case CURLOPT_PROXYAUTH:
    /*
     * Set HTTP Authentication type BITMASK.
     */
  {
    long auth = va_arg(param, long);
    /* switch off bits we can't support */
#ifndef USE_NTLM
    auth &= ~CURLAUTH_NTLM; /* no NTLM without SSL */
#endif
#ifndef HAVE_GSSAPI
    auth &= ~CURLAUTH_GSSNEGOTIATE; /* no GSS-Negotiate without GSSAPI */
#endif
    if(!auth)
      return CURLE_FAILED_INIT; /* no supported types left! */

    data->set.proxyauth = auth;
  }
  break;
#endif   /* CURL_DISABLE_HTTP */

  case CURLOPT_PROXY:
    /*
     * Set proxy server:port to use as HTTP proxy.
     *
     * If the proxy is set to "" we explicitly say that we don't want to use a
     * proxy (even though there might be environment variables saying so).
     *
     * Setting it to NULL, means no proxy but allows the environment variables
     * to decide for us.
     */
    result = setstropt(&data->set.str[STRING_PROXY],
                            va_arg(param, char *));
    break;

  case CURLOPT_WRITEHEADER:
    /*
     * Custom pointer to pass the header write callback function
     */
    data->set.writeheader = (void *)va_arg(param, void *);
    break;
  case CURLOPT_ERRORBUFFER:
    /*
     * Error buffer provided by the caller to get the human readable
     * error string in.
     */
    data->set.errorbuffer = va_arg(param, char *);
    break;
  case CURLOPT_FILE:
    /*
     * FILE pointer to write to or include in the data write callback
     */
    data->set.out = va_arg(param, FILE *);
    break;
  case CURLOPT_FTPPORT:
    /*
     * Use FTP PORT, this also specifies which IP address to use
     */
    result = setstropt(&data->set.str[STRING_FTPPORT],
                            va_arg(param, char *));
    data->set.ftp_use_port = (bool)(NULL != data->set.str[STRING_FTPPORT]);
    break;

  case CURLOPT_FTP_USE_EPRT:
    data->set.ftp_use_eprt = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_FTP_USE_EPSV:
    data->set.ftp_use_epsv = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_FTP_SSL_CCC:
    data->set.ftp_ccc = (curl_ftpccc)va_arg(param, long);
    break;

  case CURLOPT_FTP_SKIP_PASV_IP:
    /*
     * Enable or disable FTP_SKIP_PASV_IP, which will disable/enable the
     * bypass of the IP address in PASV responses.
     */
    data->set.ftp_skip_ip = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_INFILE:
    /*
     * FILE pointer to read the file to be uploaded from. Or possibly
     * used as argument to the read callback.
     */
    data->set.in = va_arg(param, FILE *);
    break;
  case CURLOPT_INFILESIZE:
    /*
     * If known, this should inform curl about the file size of the
     * to-be-uploaded file.
     */
    data->set.infilesize = va_arg(param, long);
    break;
  case CURLOPT_INFILESIZE_LARGE:
    /*
     * If known, this should inform curl about the file size of the
     * to-be-uploaded file.
     */
    data->set.infilesize = va_arg(param, curl_off_t);
    break;
  case CURLOPT_LOW_SPEED_LIMIT:
    /*
     * The low speed limit that if transfers are below this for
     * CURLOPT_LOW_SPEED_TIME, the transfer is aborted.
     */
    data->set.low_speed_limit=va_arg(param, long);
    break;
  case CURLOPT_MAX_SEND_SPEED_LARGE:
    /*
     * The max speed limit that sends transfer more than
     * CURLOPT_MAX_SEND_PER_SECOND bytes per second the transfer is
     * throttled..
     */
    data->set.max_send_speed=va_arg(param, curl_off_t);
    break;
  case CURLOPT_MAX_RECV_SPEED_LARGE:
    /*
     * The max speed limit that sends transfer more than
     * CURLOPT_MAX_RECV_PER_SECOND bytes per second the transfer is
     * throttled..
     */
    data->set.max_recv_speed=va_arg(param, curl_off_t);
    break;
  case CURLOPT_LOW_SPEED_TIME:
    /*
     * The low speed time that if transfers are below the set
     * CURLOPT_LOW_SPEED_LIMIT during this time, the transfer is aborted.
     */
    data->set.low_speed_time=va_arg(param, long);
    break;
  case CURLOPT_URL:
    /*
     * The URL to fetch.
     */
    if(data->change.url_alloc) {
      /* the already set URL is allocated, free it first! */
      free(data->change.url);
      data->change.url_alloc=FALSE;
    }
    result = setstropt(&data->set.str[STRING_SET_URL],
                            va_arg(param, char *));
    data->change.url = data->set.str[STRING_SET_URL];
    break;
  case CURLOPT_PORT:
    /*
     * The port number to use when getting the URL
     */
    data->set.use_port = va_arg(param, long);
    break;
  case CURLOPT_TIMEOUT:
    /*
     * The maximum time you allow curl to use for a single transfer
     * operation.
     */
    data->set.timeout = va_arg(param, long) * 1000L;
    break;

  case CURLOPT_TIMEOUT_MS:
    data->set.timeout = va_arg(param, long);
    break;

  case CURLOPT_CONNECTTIMEOUT:
    /*
     * The maximum time you allow curl to use to connect.
     */
    data->set.connecttimeout = va_arg(param, long) * 1000L;
    break;

  case CURLOPT_CONNECTTIMEOUT_MS:
    data->set.connecttimeout = va_arg(param, long);
    break;

  case CURLOPT_USERPWD:
    /*
     * user:password to use in the operation
     */
    result = setstropt(&data->set.str[STRING_USERPWD],
                            va_arg(param, char *));
    break;
  case CURLOPT_POSTQUOTE:
    /*
     * List of RAW FTP commands to use after a transfer
     */
    data->set.postquote = va_arg(param, struct curl_slist *);
    break;
  case CURLOPT_PREQUOTE:
    /*
     * List of RAW FTP commands to use prior to RETR (Wesley Laxton)
     */
    data->set.prequote = va_arg(param, struct curl_slist *);
    break;
  case CURLOPT_QUOTE:
    /*
     * List of RAW FTP commands to use before a transfer
     */
    data->set.quote = va_arg(param, struct curl_slist *);
    break;
  case CURLOPT_PROGRESSFUNCTION:
    /*
     * Progress callback function
     */
    data->set.fprogress = va_arg(param, curl_progress_callback);
    if(data->set.fprogress)
      data->progress.callback = TRUE; /* no longer internal */
    else
      data->progress.callback = FALSE; /* NULL enforces internal */

    break;
  case CURLOPT_PROGRESSDATA:
    /*
     * Custom client data to pass to the progress callback
     */
    data->set.progress_client = va_arg(param, void *);
    break;
  case CURLOPT_PROXYUSERPWD:
    /*
     * user:password needed to use the proxy
     */
    result = setstropt(&data->set.str[STRING_PROXYUSERPWD],
                            va_arg(param, char *));
    break;
  case CURLOPT_RANGE:
    /*
     * What range of the file you want to transfer
     */
    result = setstropt(&data->set.str[STRING_SET_RANGE],
                            va_arg(param, char *));
    break;
  case CURLOPT_RESUME_FROM:
    /*
     * Resume transfer at the give file position
     */
    data->set.set_resume_from = va_arg(param, long);
    break;
  case CURLOPT_RESUME_FROM_LARGE:
    /*
     * Resume transfer at the give file position
     */
    data->set.set_resume_from = va_arg(param, curl_off_t);
    break;
  case CURLOPT_DEBUGFUNCTION:
    /*
     * stderr write callback.
     */
    data->set.fdebug = va_arg(param, curl_debug_callback);
    /*
     * if the callback provided is NULL, it'll use the default callback
     */
    break;
  case CURLOPT_DEBUGDATA:
    /*
     * Set to a void * that should receive all error writes. This
     * defaults to CURLOPT_STDERR for normal operations.
     */
    data->set.debugdata = va_arg(param, void *);
    break;
  case CURLOPT_STDERR:
    /*
     * Set to a FILE * that should receive all error writes. This
     * defaults to stderr for normal operations.
     */
    data->set.err = va_arg(param, FILE *);
    if(!data->set.err)
      data->set.err = stderr;
    break;
  case CURLOPT_HEADERFUNCTION:
    /*
     * Set header write callback
     */
    data->set.fwrite_header = va_arg(param, curl_write_callback);
    break;
  case CURLOPT_WRITEFUNCTION:
    /*
     * Set data write callback
     */
    data->set.fwrite_func = va_arg(param, curl_write_callback);
    if(!data->set.fwrite_func)
      /* When set to NULL, reset to our internal default function */
      data->set.fwrite_func = (curl_write_callback)fwrite;
    break;
  case CURLOPT_READFUNCTION:
    /*
     * Read data callback
     */
    data->set.fread_func = va_arg(param, curl_read_callback);
    if(!data->set.fread_func)
      /* When set to NULL, reset to our internal default function */
      data->set.fread_func = (curl_read_callback)fread;
    break;
  case CURLOPT_SEEKFUNCTION:
    /*
     * Seek callback. Might be NULL.
     */
    data->set.seek_func = va_arg(param, curl_seek_callback);
    break;
  case CURLOPT_SEEKDATA:
    /*
     * Seek control callback. Might be NULL.
     */
    data->set.seek_client = va_arg(param, void *);
    break;
  case CURLOPT_CONV_FROM_NETWORK_FUNCTION:
    /*
     * "Convert from network encoding" callback
     */
    data->set.convfromnetwork = va_arg(param, curl_conv_callback);
    break;
  case CURLOPT_CONV_TO_NETWORK_FUNCTION:
    /*
     * "Convert to network encoding" callback
     */
    data->set.convtonetwork = va_arg(param, curl_conv_callback);
    break;
  case CURLOPT_CONV_FROM_UTF8_FUNCTION:
    /*
     * "Convert from UTF-8 encoding" callback
     */
    data->set.convfromutf8 = va_arg(param, curl_conv_callback);
    break;
  case CURLOPT_IOCTLFUNCTION:
    /*
     * I/O control callback. Might be NULL.
     */
    data->set.ioctl_func = va_arg(param, curl_ioctl_callback);
    break;
  case CURLOPT_IOCTLDATA:
    /*
     * I/O control data pointer. Might be NULL.
     */
    data->set.ioctl_client = va_arg(param, void *);
    break;
  case CURLOPT_SSLCERT:
    /*
     * String that holds file name of the SSL certificate to use
     */
    result = setstropt(&data->set.str[STRING_CERT],
                            va_arg(param, char *));
    break;
  case CURLOPT_SSLCERTTYPE:
    /*
     * String that holds file type of the SSL certificate to use
     */
    result = setstropt(&data->set.str[STRING_CERT_TYPE],
                            va_arg(param, char *));
    break;
  case CURLOPT_SSLKEY:
    /*
     * String that holds file name of the SSL certificate to use
     */
    result = setstropt(&data->set.str[STRING_KEY],
                            va_arg(param, char *));
    break;
  case CURLOPT_SSLKEYTYPE:
    /*
     * String that holds file type of the SSL certificate to use
     */
    result = setstropt(&data->set.str[STRING_KEY_TYPE],
                            va_arg(param, char *));
    break;
  case CURLOPT_KEYPASSWD:
    /*
     * String that holds the SSL or SSH private key password.
     */
    result = setstropt(&data->set.str[STRING_KEY_PASSWD],
                            va_arg(param, char *));
    break;
  case CURLOPT_SSLENGINE:
    /*
     * String that holds the SSL crypto engine.
     */
    argptr = va_arg(param, char *);
    if(argptr && argptr[0])
       result = Curl_ssl_set_engine(data, argptr);
    break;

  case CURLOPT_SSLENGINE_DEFAULT:
    /*
     * flag to set engine as default.
     */
    result = Curl_ssl_set_engine_default(data);
    break;
  case CURLOPT_CRLF:
    /*
     * Kludgy option to enable CRLF conversions. Subject for removal.
     */
    data->set.crlf = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_INTERFACE:
    /*
     * Set what interface or address/hostname to bind the socket to when
     * performing an operation and thus what from-IP your connection will use.
     */
    result = setstropt(&data->set.str[STRING_DEVICE],
                            va_arg(param, char *));
    break;
  case CURLOPT_LOCALPORT:
    /*
     * Set what local port to bind the socket to when performing an operation.
     */
    data->set.localport = (unsigned short) va_arg(param, long);
    break;
  case CURLOPT_LOCALPORTRANGE:
    /*
     * Set number of local ports to try, starting with CURLOPT_LOCALPORT.
     */
    data->set.localportrange = (int) va_arg(param, long);
    break;
  case CURLOPT_KRBLEVEL:
    /*
     * A string that defines the kerberos security level.
     */
    result = setstropt(&data->set.str[STRING_KRB_LEVEL],
                            va_arg(param, char *));
    data->set.krb = (bool)(NULL != data->set.str[STRING_KRB_LEVEL]);
    break;
  case CURLOPT_SSL_VERIFYPEER:
    /*
     * Enable peer SSL verifying.
     */
    data->set.ssl.verifypeer = va_arg(param, long);
    break;
  case CURLOPT_SSL_VERIFYHOST:
    /*
     * Enable verification of the CN contained in the peer certificate
     */
    data->set.ssl.verifyhost = va_arg(param, long);
    break;
#ifdef USE_SSLEAY
    /* since these two options are only possible to use on an OpenSSL-
       powered libcurl we #ifdef them on this condition so that libcurls
       built against other SSL libs will return a proper error when trying
       to set this option! */
  case CURLOPT_SSL_CTX_FUNCTION:
    /*
     * Set a SSL_CTX callback
     */
    data->set.ssl.fsslctx = va_arg(param, curl_ssl_ctx_callback);
    break;
  case CURLOPT_SSL_CTX_DATA:
    /*
     * Set a SSL_CTX callback parameter pointer
     */
    data->set.ssl.fsslctxp = va_arg(param, void *);
    break;
#endif
  case CURLOPT_CAINFO:
    /*
     * Set CA info for SSL connection. Specify file name of the CA certificate
     */
    result = setstropt(&data->set.str[STRING_SSL_CAFILE],
                            va_arg(param, char *));
    break;
  case CURLOPT_CAPATH:
    /*
     * Set CA path info for SSL connection. Specify directory name of the CA
     * certificates which have been prepared using openssl c_rehash utility.
     */
    /* This does not work on windows. */
    result = setstropt(&data->set.str[STRING_SSL_CAPATH],
                            va_arg(param, char *));
    break;
  case CURLOPT_TELNETOPTIONS:
    /*
     * Set a linked list of telnet options
     */
    data->set.telnet_options = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_BUFFERSIZE:
    /*
     * The application kindly asks for a differently sized receive buffer.
     * If it seems reasonable, we'll use it.
     */
    data->set.buffer_size = va_arg(param, long);

    if((data->set.buffer_size> (BUFSIZE -1 )) ||
       (data->set.buffer_size < 1))
      data->set.buffer_size = 0; /* huge internal default */

    break;

  case CURLOPT_NOSIGNAL:
    /*
     * The application asks not to set any signal() or alarm() handlers,
     * even when using a timeout.
     */
    data->set.no_signal = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_SHARE:
    {
      struct Curl_share *set;
      set = va_arg(param, struct Curl_share *);

      /* disconnect from old share, if any */
      if(data->share) {
        Curl_share_lock(data, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE);

        if(data->dns.hostcachetype == HCACHE_SHARED) {
          data->dns.hostcache = NULL;
          data->dns.hostcachetype = HCACHE_NONE;
        }

        if(data->share->cookies == data->cookies)
          data->cookies = NULL;

        data->share->dirty--;

        Curl_share_unlock(data, CURL_LOCK_DATA_SHARE);
        data->share = NULL;
      }

      /* use new share if it set */
      data->share = set;
      if(data->share) {

        Curl_share_lock(data, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE);

        data->share->dirty++;

        if(data->share->hostcache) {
          /* use shared host cache, first free the private one if any */
          if(data->dns.hostcachetype == HCACHE_PRIVATE)
            Curl_hash_destroy(data->dns.hostcache);

          data->dns.hostcache = data->share->hostcache;
          data->dns.hostcachetype = HCACHE_SHARED;
        }
#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
        if(data->share->cookies) {
          /* use shared cookie list, first free own one if any */
          if(data->cookies)
            Curl_cookie_cleanup(data->cookies);
          /* enable cookies since we now use a share that uses cookies! */
          data->cookies = data->share->cookies;
        }
#endif   /* CURL_DISABLE_HTTP */
        Curl_share_unlock(data, CURL_LOCK_DATA_SHARE);

      }
      /* check for host cache not needed,
       * it will be done by curl_easy_perform */
    }
    break;

  case CURLOPT_PROXYTYPE:
    /*
     * Set proxy type. HTTP/SOCKS4/SOCKS4a/SOCKS5/SOCKS5_HOSTNAME
     */
    data->set.proxytype = (curl_proxytype)va_arg(param, long);
    break;

  case CURLOPT_PRIVATE:
    /*
     * Set private data pointer.
     */
    data->set.private_data = va_arg(param, void *);
    break;

  case CURLOPT_MAXFILESIZE:
    /*
     * Set the maximum size of a file to download.
     */
    data->set.max_filesize = va_arg(param, long);
    break;

  case CURLOPT_USE_SSL:
    /*
     * Make transfers attempt to use SSL/TLS.
     */
    data->set.ftp_ssl = (curl_usessl)va_arg(param, long);
    break;

  case CURLOPT_FTPSSLAUTH:
    /*
     * Set a specific auth for FTP-SSL transfers.
     */
    data->set.ftpsslauth = (curl_ftpauth)va_arg(param, long);
    break;

  case CURLOPT_IPRESOLVE:
    data->set.ip_version = va_arg(param, long);
    break;

  case CURLOPT_MAXFILESIZE_LARGE:
    /*
     * Set the maximum size of a file to download.
     */
    data->set.max_filesize = va_arg(param, curl_off_t);
    break;

  case CURLOPT_TCP_NODELAY:
    /*
     * Enable or disable TCP_NODELAY, which will disable/enable the Nagle
     * algorithm
     */
    data->set.tcp_nodelay = (bool)(0 != va_arg(param, long));
    break;

    /*
      case CURLOPT_SOURCE_URL:
      case CURLOPT_SOURCE_USERPWD:
      case CURLOPT_SOURCE_QUOTE:
      case CURLOPT_SOURCE_PREQUOTE:
      case CURLOPT_SOURCE_POSTQUOTE:
      These former 3rd party transfer options are deprecated */

  case CURLOPT_FTP_ACCOUNT:
    result = setstropt(&data->set.str[STRING_FTP_ACCOUNT],
                            va_arg(param, char *));
    break;

  case CURLOPT_IGNORE_CONTENT_LENGTH:
    data->set.ignorecl = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_CONNECT_ONLY:
    /*
     * No data transfer, set up connection and let application use the socket
     */
    data->set.connect_only = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_FTP_ALTERNATIVE_TO_USER:
    result = setstropt(&data->set.str[STRING_FTP_ALTERNATIVE_TO_USER],
                            va_arg(param, char *));
    break;

  case CURLOPT_SOCKOPTFUNCTION:
    /*
     * socket callback function: called after socket() but before connect()
     */
    data->set.fsockopt = va_arg(param, curl_sockopt_callback);
    break;

  case CURLOPT_SOCKOPTDATA:
    /*
     * socket callback data pointer. Might be NULL.
     */
    data->set.sockopt_client = va_arg(param, void *);
    break;

  case CURLOPT_OPENSOCKETFUNCTION:
    /*
     * open/create socket callback function: called instead of socket(),
     * before connect()
     */
    data->set.fopensocket = va_arg(param, curl_opensocket_callback);
    break;

  case CURLOPT_OPENSOCKETDATA:
    /*
     * socket callback data pointer. Might be NULL.
     */
    data->set.opensocket_client = va_arg(param, void *);
    break;

  case CURLOPT_SSL_SESSIONID_CACHE:
    data->set.ssl.sessionid = (bool)(0 != va_arg(param, long));
    break;

  case CURLOPT_SSH_AUTH_TYPES:
    data->set.ssh_auth_types = va_arg(param, long);
    break;

  case CURLOPT_SSH_PUBLIC_KEYFILE:
    /*
     * Use this file instead of the $HOME/.ssh/id_dsa.pub file
     */
    result = setstropt(&data->set.str[STRING_SSH_PUBLIC_KEY],
                            va_arg(param, char *));
    break;

  case CURLOPT_SSH_PRIVATE_KEYFILE:
    /*
     * Use this file instead of the $HOME/.ssh/id_dsa file
     */
    result = setstropt(&data->set.str[STRING_SSH_PRIVATE_KEY],
                            va_arg(param, char *));
    break;
  case CURLOPT_SSH_HOST_PUBLIC_KEY_MD5:
    /*
     * Option to allow for the MD5 of the host public key to be checked
     * for validation purposes.
     */
    result = setstropt(&data->set.str[STRING_SSH_HOST_PUBLIC_KEY_MD5],
                            va_arg(param, char *));
    break;
  case CURLOPT_HTTP_TRANSFER_DECODING:
    /*
     * disable libcurl transfer encoding is used
     */
    data->set.http_te_skip = (bool)(0 == va_arg(param, long));
    break;

  case CURLOPT_HTTP_CONTENT_DECODING:
    /*
     * raw data passed to the application when content encoding is used
     */
    data->set.http_ce_skip = (bool)(0 == va_arg(param, long));
    break;

  case CURLOPT_NEW_FILE_PERMS:
    /*
     * Uses these permissions instead of 0644
     */
    data->set.new_file_perms = va_arg(param, long);
    break;

  case CURLOPT_NEW_DIRECTORY_PERMS:
    /*
     * Uses these permissions instead of 0755
     */
    data->set.new_directory_perms = va_arg(param, long);
    break;
  case CURLOPT_PROXY_TRANSFER_MODE:
    /*
     * set transfer mode (;type=<a|i>) when doing FTP via an HTTP proxy
     */
    switch (va_arg(param, long)) {
      case 0:
        data->set.proxy_transfer_mode = FALSE;
        break;
      case 1:
        data->set.proxy_transfer_mode = TRUE;
        break;
      default:
        /* reserve other values for future use */
        result = CURLE_FAILED_INIT;
        break;
    }
    break;

  default:
    /* unknown tag and its companion, just ignore: */
    result = CURLE_FAILED_INIT; /* correct this */
    break;
  }

  return result;
}