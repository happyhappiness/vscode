CURLcode Curl_open(struct SessionHandle **curl)
{
  CURLcode res = CURLE_OK;
  struct SessionHandle *data;
#ifdef USE_ARES
  int status;
#endif

  /* Very simple start-up: alloc the struct, init it with zeroes and return */
  data = (struct SessionHandle *)calloc(1, sizeof(struct SessionHandle));
  if(!data) {
    /* this is a very serious error */
    DEBUGF(fprintf(stderr, "Error: calloc of SessionHandle failed\n"));
    return CURLE_OUT_OF_MEMORY;
  }

  data->magic = CURLEASY_MAGIC_NUMBER;

#ifdef USE_ARES
  if((status = ares_init(&data->state.areschannel)) != ARES_SUCCESS) {
    DEBUGF(fprintf(stderr, "Error: ares_init failed\n"));
    free(data);
    if(status == ARES_ENOMEM)
      return CURLE_OUT_OF_MEMORY;
    else
      return CURLE_FAILED_INIT;
  }
  /* make sure that all other returns from this function should destroy the
     ares channel before returning error! */
#endif

  /* We do some initial setup here, all those fields that can't be just 0 */

  data->state.headerbuff=(char*)malloc(HEADERSIZE);
  if(!data->state.headerbuff) {
    DEBUGF(fprintf(stderr, "Error: malloc of headerbuff failed\n"));
    res = CURLE_OUT_OF_MEMORY;
  }
  else {
    data->state.headersize=HEADERSIZE;

    data->set.out = stdout; /* default output to stdout */
    data->set.in  = stdin;  /* default input from stdin */
    data->set.err  = stderr;  /* default stderr to stderr */

    /* use fwrite as default function to store output */
    data->set.fwrite_func = (curl_write_callback)fwrite;

    /* use fread as default function to read input */
    data->set.fread_func = (curl_read_callback)fread;

    /* don't use a seek function by default */
    data->set.seek_func = ZERO_NULL;
    data->set.seek_client = ZERO_NULL;

    /* conversion callbacks for non-ASCII hosts */
    data->set.convfromnetwork = ZERO_NULL;
    data->set.convtonetwork   = ZERO_NULL;
    data->set.convfromutf8    = ZERO_NULL;

#if defined(CURL_DOES_CONVERSIONS) && defined(HAVE_ICONV)
    /* conversion descriptors for iconv calls */
    data->outbound_cd = (iconv_t)-1;
    data->inbound_cd  = (iconv_t)-1;
    data->utf8_cd     = (iconv_t)-1;
#endif /* CURL_DOES_CONVERSIONS && HAVE_ICONV */

    data->set.infilesize = -1; /* we don't know any size */
    data->set.postfieldsize = -1;
    data->set.maxredirs = -1; /* allow any amount by default */
    data->state.current_speed = -1; /* init to negative == impossible */

    data->set.httpreq = HTTPREQ_GET; /* Default HTTP request */
    data->set.ftp_use_epsv = TRUE;   /* FTP defaults to EPSV operations */
    data->set.ftp_use_eprt = TRUE;   /* FTP defaults to EPRT operations */
    data->set.ftp_filemethod = FTPFILE_MULTICWD;
    data->set.dns_cache_timeout = 60; /* Timeout every 60 seconds by default */

    /* make libcurl quiet by default: */
    data->set.hide_progress = TRUE;  /* CURLOPT_NOPROGRESS changes these */
    data->progress.flags |= PGRS_HIDE;

    /* Set the default size of the SSL session ID cache */
    data->set.ssl.numsessions = 5;

    data->set.proxyport = 1080;
    data->set.proxytype = CURLPROXY_HTTP; /* defaults to HTTP proxy */
    data->set.httpauth = CURLAUTH_BASIC;  /* defaults to basic */
    data->set.proxyauth = CURLAUTH_BASIC; /* defaults to basic */

    /* This no longer creates a connection cache here. It is instead made on
       the first call to curl_easy_perform() or when the handle is added to a
       multi stack. */

    data->set.ssh_auth_types = CURLSSH_AUTH_DEFAULT; /* defaults to any auth
                                                        type */
    data->set.new_file_perms = 0644;    /* Default permissions */
    data->set.new_directory_perms = 0755; /* Default permissions */

    /* most recent connection is not yet defined */
    data->state.lastconnect = -1;

    Curl_easy_initHandleData(data);

    /*
     * libcurl 7.10 introduced SSL verification *by default*! This needs to be
     * switched off unless wanted.
     */
    data->set.ssl.verifypeer = TRUE;
    data->set.ssl.verifyhost = 2;
    data->set.ssl.sessionid = TRUE; /* session ID caching enabled by default */
    /* This is our preferred CA cert bundle/path since install time */
#if defined(CURL_CA_BUNDLE)
    res = setstropt(&data->set.str[STRING_SSL_CAFILE],
                         (char *) CURL_CA_BUNDLE);
#elif defined(CURL_CA_PATH)
    res = setstropt(&data->set.str[STRING_SSL_CAPATH], (char *) CURL_CA_PATH);
#endif
  }

  if(res) {
    ares_destroy(data->state.areschannel);
    if(data->state.headerbuff)
      free(data->state.headerbuff);
    Curl_freeset(data);
    free(data);
    data = NULL;
  }
  else
    *curl = data;

  return res;
}