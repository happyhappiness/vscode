CURLcode Curl_open(struct SessionHandle **curl)
{
  CURLcode res = CURLE_OK;
  struct SessionHandle *data;
  /* Very simple start-up: alloc the struct, init it with zeroes and return */
  data = (struct SessionHandle *)calloc(1, sizeof(struct SessionHandle));
  if(!data)
    /* this is a very serious error */
    return CURLE_OUT_OF_MEMORY;

#ifdef USE_ARES
  if(ARES_SUCCESS != ares_init(&data->state.areschannel)) {
    free(data);
    return CURLE_FAILED_INIT;
  }
  /* make sure that all other returns from this function should destroy the
     ares channel before returning error! */
#endif

  /* We do some initial setup here, all those fields that can't be just 0 */

  data->state.headerbuff=(char*)malloc(HEADERSIZE);
  if(!data->state.headerbuff)
    res = CURLE_OUT_OF_MEMORY;
  else {
    data->state.headersize=HEADERSIZE;

    data->set.out = stdout; /* default output to stdout */
    data->set.in  = stdin;  /* default input from stdin */
    data->set.err  = stderr;  /* default stderr to stderr */

    /* use fwrite as default function to store output */
    data->set.fwrite = (curl_write_callback)fwrite;

    /* use fread as default function to read input */
    data->set.fread = (curl_read_callback)fread;

    data->set.infilesize = -1; /* we don't know any size */
    data->set.postfieldsize = -1;

    data->state.current_speed = -1; /* init to negative == impossible */

    data->set.httpreq = HTTPREQ_GET; /* Default HTTP request */
    data->set.ftp_use_epsv = TRUE;   /* FTP defaults to EPSV operations */
    data->set.ftp_use_eprt = TRUE;   /* FTP defaults to EPRT operations */
    data->set.ftp_use_lprt = TRUE;   /* FTP defaults to EPRT operations */

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

    /* create an array with connection data struct pointers */
    data->state.numconnects = 5; /* hard-coded right now */
    data->state.connects = (struct connectdata **)
      malloc(sizeof(struct connectdata *) * data->state.numconnects);

    if(!data->state.connects)
      res = CURLE_OUT_OF_MEMORY;
    else
      memset(data->state.connects, 0,
             sizeof(struct connectdata *)*data->state.numconnects);

    /*
     * libcurl 7.10 introduced SSL verification *by default*! This needs to be
     * switched off unless wanted.
     */
    data->set.ssl.verifypeer = TRUE;
    data->set.ssl.verifyhost = 2;
#ifdef CURL_CA_BUNDLE
    /* This is our prefered CA cert bundle since install time */
    data->set.ssl.CAfile = (char *)CURL_CA_BUNDLE;
#endif
  }

  if(res) {
#ifdef USE_ARES
    ares_destroy(data->state.areschannel);
#endif
    if(data->state.headerbuff)
      free(data->state.headerbuff);
    free(data);
    data = NULL;
  }

  *curl = data;
  return CURLE_OK;
}