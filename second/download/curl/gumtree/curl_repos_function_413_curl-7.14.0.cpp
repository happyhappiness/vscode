CURLcode Curl_setopt(struct SessionHandle *data, CURLoption option, ...)
{
  va_list param;
  char *argptr;
  CURLcode result = CURLE_OK;

  va_start(param, option);

  switch(option) {
  case CURLOPT_DNS_CACHE_TIMEOUT:
    data->set.dns_cache_timeout = va_arg(param, int);
    break;
  case CURLOPT_DNS_USE_GLOBAL_CACHE:
    {
      int use_cache = va_arg(param, int);
      if (use_cache) {
        Curl_global_host_cache_init();
      }

      data->set.global_dns_cache = use_cache;
    }
    break;
  case CURLOPT_SSL_CIPHER_LIST:
    /* set a list of cipher we want to use in the SSL connection */
    data->set.ssl.cipher_list = va_arg(param, char *);
    break;

  case CURLOPT_RANDOM_FILE:
    /*
     * This is the path name to a file that contains random data to seed
     * the random SSL stuff with. The file is only used for reading.
     */
    data->set.ssl.random_file = va_arg(param, char *);
    break;
  case CURLOPT_EGDSOCKET:
    /*
     * The Entropy Gathering Daemon socket pathname
     */
    data->set.ssl.egdsocket = va_arg(param, char *);
    break;
  case CURLOPT_MAXCONNECTS:
    /*
     * Set the absolute number of maximum simultaneous alive connection that
     * libcurl is allowed to have.
     */
    {
      long newconnects= va_arg(param, long);
      struct connectdata **newptr;
      long i;

      if(newconnects < data->state.numconnects) {
        /* Since this number is *decreased* from the existing number, we must
           close the possibly open connections that live on the indexes that
           are being removed! */
        for(i=newconnects; i< data->state.numconnects; i++)
          Curl_disconnect(data->state.connects[i]);
      }
      if(newconnects) {
        newptr= (struct connectdata **)
          realloc(data->state.connects,
                  sizeof(struct connectdata *) * newconnects);
        if(!newptr)
          /* we closed a few connections in vain, but so what? */
          return CURLE_OUT_OF_MEMORY;

        /* nullify the newly added pointers */
        for(i=data->state.numconnects; i<newconnects; i++) {
          newptr[i] = NULL;
        }

        data->state.connects = newptr;
        data->state.numconnects = newconnects;
      }
      else {
        /* zero makes NO cache at all */
        if(data->state.connects)
          free(data->state.connects);
        data->state.connects=NULL;
        data->state.numconnects=0;
      }
    }
    break;
  case CURLOPT_FORBID_REUSE:
    /*
     * When this transfer is done, it must not be left to be reused by a
     * subsequent transfer but shall be closed immediately.
     */
    data->set.reuse_forbid = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_FRESH_CONNECT:
    /*
     * This transfer shall not use a previously cached connection but
     * should be made with a fresh new connect!
     */
    data->set.reuse_fresh = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_VERBOSE:
    /*
     * Verbose means infof() calls that give a lot of information about
     * the connection and transfer procedures as well as internal choices.
     */
    data->set.verbose = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_HEADER:
    /*
     * Set to include the header in the general data output stream.
     */
    data->set.include_header = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_NOPROGRESS:
    /*
     * Shut off the internal supported progress meter
     */
    data->set.hide_progress = va_arg(param, long)?TRUE:FALSE;
    if(data->set.hide_progress)
      data->progress.flags |= PGRS_HIDE;
    else
      data->progress.flags &= ~PGRS_HIDE;
    break;
  case CURLOPT_NOBODY:
    /*
     * Do not include the body part in the output data stream.
     */
    data->set.opt_no_body = va_arg(param, long)?TRUE:FALSE;
    if(data->set.opt_no_body)
      /* in HTTP lingo, this means using the HEAD request */
      data->set.httpreq = HTTPREQ_HEAD;
    break;
  case CURLOPT_FAILONERROR:
    /*
     * Don't output the >=300 error code HTML-page, but instead only
     * return error.
     */
    data->set.http_fail_on_error = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_UPLOAD:
  case CURLOPT_PUT:
    /*
     * We want to sent data to the remote host. If this is HTTP, that equals
     * using the PUT request.
     */
    data->set.upload = va_arg(param, long)?TRUE:FALSE;
    if(data->set.upload)
      /* If this is HTTP, PUT is what's needed to "upload" */
      data->set.httpreq = HTTPREQ_PUT;
    break;
  case CURLOPT_FILETIME:
    /*
     * Try to get the file time of the remote document. The time will
     * later (possibly) become available using curl_easy_getinfo().
     */
    data->set.get_filetime = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_FTP_CREATE_MISSING_DIRS:
    /*
     * An FTP option that modifies an upload to create missing directories on
     * the server.
     */
    data->set.ftp_create_missing_dirs = va_arg( param , long )?TRUE:FALSE;
    break;
  case CURLOPT_FTP_RESPONSE_TIMEOUT:
    /*
     * An FTP option that specifies how quickly an FTP response must be
     * obtained before it is considered failure.
     */
    data->set.ftp_response_timeout = va_arg( param , long );
    break;
  case CURLOPT_FTPLISTONLY:
    /*
     * An FTP option that changes the command to one that asks for a list
     * only, no file info details.
     */
    data->set.ftp_list_only = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_FTPAPPEND:
    /*
     * We want to upload and append to an existing (FTP) file.
     */
    data->set.ftp_append = va_arg(param, long)?TRUE:FALSE;
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
    data->set.netrc_file = va_arg(param, char *);
    break;
  case CURLOPT_TRANSFERTEXT:
    /*
     * This option was previously named 'FTPASCII'. Renamed to work with
     * more protocols than merely FTP.
     *
     * Transfer using ASCII (instead of BINARY).
     */
    data->set.ftp_ascii = va_arg(param, long)?TRUE:FALSE;
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
    data->set.http_auto_referer = va_arg(param, long)?1:0;
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
    data->set.encoding = va_arg(param, char *);
    if(data->set.encoding && !*data->set.encoding)
      data->set.encoding = (char*)ALL_CONTENT_ENCODINGS;
    break;

  case CURLOPT_FOLLOWLOCATION:
    /*
     * Follow Location: header hints on a HTTP-server.
     */
    data->set.http_follow_location = va_arg(param, long)?TRUE:FALSE;
    break;

  case CURLOPT_UNRESTRICTED_AUTH:
    /*
     * Send authentication (user+password) when following locations, even when
     * hostname changed.
     */
    data->set.http_disable_hostname_check_before_authentication =
      va_arg(param, long)?TRUE:FALSE;
    break;

  case CURLOPT_MAXREDIRS:
    /*
     * The maximum amount of hops you allow curl to follow Location:
     * headers. This should mostly be used to detect never-ending loops.
     */
    data->set.maxredirs = va_arg(param, long);
    break;

  case CURLOPT_POST:
    /* Does this option serve a purpose anymore? Yes it does, when
       CURLOPT_POSTFIELDS isn't used and the POST data is read off the
       callback! */
    if(va_arg(param, long))
      data->set.httpreq = HTTPREQ_POST;
    else
      data->set.httpreq = HTTPREQ_GET;
    break;

  case CURLOPT_POSTFIELDS:
    /*
     * A string with POST data. Makes curl HTTP POST. Even if it is NULL.
     */
    data->set.postfields = va_arg(param, char *);
    data->set.httpreq = HTTPREQ_POST;
    break;

  case CURLOPT_POSTFIELDSIZE:
    /*
     * The size of the POSTFIELD data to prevent libcurl to do strlen() to
     * figure it out. Enables binary posts.
     */
    data->set.postfieldsize = va_arg(param, long);
    break;

  case CURLOPT_POSTFIELDSIZE_LARGE:
    /*
     * The size of the POSTFIELD data to prevent libcurl to do strlen() to
     * figure it out. Enables binary posts.
     */
    data->set.postfieldsize = va_arg(param, curl_off_t);
    break;

  case CURLOPT_HTTPPOST:
    /*
     * Set to make us do HTTP POST
     */
    data->set.httppost = va_arg(param, struct curl_httppost *);
    data->set.httpreq = HTTPREQ_POST_FORM;
    break;

  case CURLOPT_REFERER:
    /*
     * String to set in the HTTP Referer: field.
     */
    if(data->change.referer_alloc) {
      free(data->change.referer);
      data->change.referer_alloc = FALSE;
    }
    data->set.set_referer = va_arg(param, char *);
    data->change.referer = data->set.set_referer;
    break;

  case CURLOPT_USERAGENT:
    /*
     * String to use in the HTTP User-Agent field
     */
    data->set.useragent = va_arg(param, char *);
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
    data->set.cookie = va_arg(param, char *);
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

      data->change.cookielist = cl;
    }
    break;

  case CURLOPT_COOKIEJAR:
    /*
     * Set cookie file name to dump all cookies to when we're done.
     */
    data->set.cookiejar = (char *)va_arg(param, void *);

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
    data->set.cookiesession = (bool)va_arg(param, long);
    break;
#endif /* CURL_DISABLE_COOKIES */

  case CURLOPT_HTTPGET:
    /*
     * Set to force us do HTTP GET
     */
    if(va_arg(param, long)) {
      data->set.httpreq = HTTPREQ_GET;
      data->set.upload = FALSE; /* switch off upload */
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
    data->set.tunnel_thru_httpproxy = va_arg(param, long)?TRUE:FALSE;
    break;

  case CURLOPT_CUSTOMREQUEST:
    /*
     * Set a custom string to use as request
     */
    data->set.customrequest = va_arg(param, char *);

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
    if(data->change.proxy_alloc) {
      /*
       * The already set string is allocated, free that first
       */
      data->change.proxy_alloc=FALSE;;
      free(data->change.proxy);
    }
    data->set.set_proxy = va_arg(param, char *);
    data->change.proxy = data->set.set_proxy;
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
    data->set.ftpport = va_arg(param, char *);
    data->set.ftp_use_port = data->set.ftpport?1:0;
    break;

  case CURLOPT_FTP_USE_EPRT:
    data->set.ftp_use_eprt = va_arg(param, long)?TRUE:FALSE;
    data->set.ftp_use_lprt = data->set.ftp_use_eprt;
    break;

  case CURLOPT_FTP_USE_EPSV:
    data->set.ftp_use_epsv = va_arg(param, long)?TRUE:FALSE;
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
    data->set.set_url = va_arg(param, char *);
    data->change.url = data->set.set_url;
    data->change.url_changed = TRUE;
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
    data->set.timeout = va_arg(param, long);
    break;
  case CURLOPT_CONNECTTIMEOUT:
    /*
     * The maximum time you allow curl to use to connect.
     */
    data->set.connecttimeout = va_arg(param, long);
    break;

  case CURLOPT_USERPWD:
    /*
     * user:password to use in the operation
     */
    data->set.userpwd = va_arg(param, char *);
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
    data->set.proxyuserpwd = va_arg(param, char *);
    break;
  case CURLOPT_RANGE:
    /*
     * What range of the file you want to transfer
     */
    data->set.set_range = va_arg(param, char *);
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
    data->set.fwrite = va_arg(param, curl_write_callback);
    if(!data->set.fwrite)
      /* When set to NULL, reset to our internal default function */
      data->set.fwrite = (curl_write_callback)fwrite;
    break;
  case CURLOPT_READFUNCTION:
    /*
     * Read data callback
     */
    data->set.fread = va_arg(param, curl_read_callback);
    if(!data->set.fread)
      /* When set to NULL, reset to our internal default function */
      data->set.fread = (curl_read_callback)fread;
    break;
  case CURLOPT_IOCTLFUNCTION:
    /*
     * I/O control callback. Might be NULL.
     */
    data->set.ioctl = va_arg(param, curl_ioctl_callback);
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
    data->set.cert = va_arg(param, char *);
    break;
  case CURLOPT_SSLCERTTYPE:
    /*
     * String that holds file type of the SSL certificate to use
     */
    data->set.cert_type = va_arg(param, char *);
    break;
  case CURLOPT_SSLKEY:
    /*
     * String that holds file name of the SSL certificate to use
     */
    data->set.key = va_arg(param, char *);
    break;
  case CURLOPT_SSLKEYTYPE:
    /*
     * String that holds file type of the SSL certificate to use
     */
    data->set.key_type = va_arg(param, char *);
    break;
  case CURLOPT_SSLKEYPASSWD:
    /*
     * String that holds the SSL private key password.
     */
    data->set.key_passwd = va_arg(param, char *);
    break;
  case CURLOPT_SSLENGINE:
    /*
     * String that holds the SSL crypto engine.
     */
    argptr = va_arg(param, char *);
    if (argptr && argptr[0])
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
     * Kludgy option to enable CRLF convertions. Subject for removal.
     */
    data->set.crlf = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_INTERFACE:
    /*
     * Set what interface to bind to when performing an operation and thus
     * what from-IP your connection will use.
     */
    data->set.device = va_arg(param, char *);
    break;
  case CURLOPT_KRB4LEVEL:
    /*
     * A string that defines the krb4 security level.
     */
    data->set.krb4_level = va_arg(param, char *);
    data->set.krb4=data->set.krb4_level?TRUE:FALSE;
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
  case CURLOPT_CAINFO:
    /*
     * Set CA info for SSL connection. Specify file name of the CA certificate
     */
    data->set.ssl.CAfile = va_arg(param, char *);
    break;
  case CURLOPT_CAPATH:
    /*
     * Set CA path info for SSL connection. Specify directory name of the CA
     * certificates which have been prepared using openssl c_rehash utility.
     */
    /* This does not work on windows. */
    data->set.ssl.CApath = va_arg(param, char *);
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
    data->set.no_signal = va_arg(param, long) ? TRUE : FALSE;
    break;

  case CURLOPT_SHARE:
    {
      struct Curl_share *set;
      set = va_arg(param, struct Curl_share *);

      /* disconnect from old share, if any */
      if(data->share) {
        Curl_share_lock(data, CURL_LOCK_DATA_SHARE, CURL_LOCK_ACCESS_SINGLE);

        if(data->share->hostcache == data->hostcache)
          data->hostcache = NULL;

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
          /* use shared host cache, first free own one if any */
          if(data->hostcache)
            Curl_hash_destroy(data->hostcache);

          data->hostcache = data->share->hostcache;
        }
#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
        if(data->share->cookies) {
          /* use shared cookie list, first free own one if any */
          if (data->cookies)
            Curl_cookie_cleanup(data->cookies);
          data->cookies = data->share->cookies;
        }
#endif   /* CURL_DISABLE_HTTP */
        Curl_share_unlock(data, CURL_LOCK_DATA_SHARE);

      }
#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
      /* check cookie list is set */
      if(!data->cookies)
        data->cookies = Curl_cookie_init(data, NULL, NULL, TRUE );
#endif   /* CURL_DISABLE_HTTP */
      /* check for host cache not needed,
       * it will be done by curl_easy_perform */
    }
    break;

  case CURLOPT_PROXYTYPE:
    /*
     * Set proxy type. HTTP/SOCKS4/SOCKS5
     */
    data->set.proxytype = (curl_proxytype)va_arg(param, long);
    break;

  case CURLOPT_PRIVATE:
    /*
     * Set private data pointer.
     */
    data->set.private_data = va_arg(param, char *);
    break;

  case CURLOPT_MAXFILESIZE:
    /*
     * Set the maximum size of a file to download.
     */
    data->set.max_filesize = va_arg(param, long);
    break;

  case CURLOPT_FTP_SSL:
    /*
     * Make FTP transfers attempt to use SSL/TLS.
     */
    data->set.ftp_ssl = (curl_ftpssl)va_arg(param, long);
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
    data->set.tcp_nodelay = (bool)va_arg(param, long);
    break;

  /*********** 3rd party transfer options ***********/
  case CURLOPT_SOURCE_URL:
    /*
     * SOURCE URL
     */
    data->set.source_url = va_arg(param, char *);
    data->set.printhost = (data->set.source_url != NULL);
    break;

  case CURLOPT_SOURCE_USERPWD:
    /*
     * Use SOURCE USER[:PASSWORD]
     */
    data->set.source_userpwd = va_arg(param, char *);
    break;

  case CURLOPT_SOURCE_QUOTE:
    /*
     * List of RAW FTP commands to use after a connect
     */
    data->set.source_quote = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_SOURCE_PREQUOTE:
    /*
     * List of RAW FTP commands to use before a transfer on the source host
     */
    data->set.source_prequote = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_SOURCE_POSTQUOTE:
    /*
     * List of RAW FTP commands to use after a transfer on the source host
     */
    data->set.source_postquote = va_arg(param, struct curl_slist *);
    break;

  case CURLOPT_FTP_ACCOUNT:
    data->set.ftp_account = va_arg(param, char *);
    break;

  default:
    /* unknown tag and its companion, just ignore: */
    result = CURLE_FAILED_INIT; /* correct this */
    break;
  }

  return result;
}