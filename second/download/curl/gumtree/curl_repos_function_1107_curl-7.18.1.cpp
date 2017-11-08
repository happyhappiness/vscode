void curl_easy_reset(CURL *curl)
{
  struct SessionHandle *data = (struct SessionHandle *)curl;

  Curl_safefree(data->state.pathbuffer);
  data->state.pathbuffer=NULL;

  Curl_safefree(data->state.proto.generic);
  data->state.proto.generic=NULL;

  /* zero out UserDefined data: */
  Curl_freeset(data);
  memset(&data->set, 0, sizeof(struct UserDefined));

  /* zero out Progress data: */
  memset(&data->progress, 0, sizeof(struct Progress));

  /* init Handle data */
  Curl_easy_initHandleData(data);

  /* The remainder of these calls have been taken from Curl_open() */

  data->set.out = stdout; /* default output to stdout */
  data->set.in  = stdin;  /* default input from stdin */
  data->set.err  = stderr;  /* default stderr to stderr */

  /* use fwrite as default function to store output */
  data->set.fwrite_func = (curl_write_callback)fwrite;

  /* use fread as default function to read input */
  data->set.fread_func = (curl_read_callback)fread;

  data->set.infilesize = -1; /* we don't know any size */
  data->set.postfieldsize = -1;

  data->state.current_speed = -1; /* init to negative == impossible */

  data->set.httpreq = HTTPREQ_GET; /* Default HTTP request */
  data->set.ftp_use_epsv = TRUE;   /* FTP defaults to EPSV operations */
  data->set.ftp_use_eprt = TRUE;   /* FTP defaults to EPRT operations */

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

  /*
   * libcurl 7.10 introduced SSL verification *by default*! This needs to be
   * switched off unless wanted.
   */
  data->set.ssl.verifypeer = TRUE;
  data->set.ssl.verifyhost = 2;
  /* This is our prefered CA cert bundle/path since install time */
#if defined(CURL_CA_BUNDLE)
  (void) curl_easy_setopt(curl, CURLOPT_CAINFO, (char *) CURL_CA_BUNDLE);
#elif defined(CURL_CA_PATH)
  (void) curl_easy_setopt(curl, CURLOPT_CAPATH, (char *) CURL_CA_PATH);
#endif

  data->set.ssh_auth_types = CURLSSH_AUTH_DEFAULT; /* defaults to any auth
                                                      type */
  data->set.new_file_perms = 0644;    /* Default permissions */
  data->set.new_directory_perms = 0755; /* Default permissions */
}