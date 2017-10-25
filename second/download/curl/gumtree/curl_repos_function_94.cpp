CURLcode curl_setopt(CURL *curl, CURLoption option, ...)
{
  struct UrlData *data = curl;
  va_list param;
  char *cookiefile;

  va_start(param, option);

  switch(option) {
  case CURLOPT_VERBOSE:
    data->bits.verbose = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_HEADER:
    data->bits.http_include_header = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_NOPROGRESS:
    data->bits.hide_progress = va_arg(param, long)?TRUE:FALSE;
    if(data->bits.hide_progress)
      data->progress.flags |= PGRS_HIDE;
    break;
  case CURLOPT_NOBODY:
    data->bits.no_body = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_FAILONERROR:
    data->bits.http_fail_on_error = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_UPLOAD:
    data->bits.upload = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_POST:
    data->bits.http_post = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_FTPLISTONLY:
    data->bits.ftp_list_only = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_FTPAPPEND:
    data->bits.ftp_append = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_NETRC:
    data->bits.use_netrc = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_FOLLOWLOCATION:
    data->bits.http_follow_location = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_FTPASCII:
    data->bits.ftp_ascii = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_PUT:
    data->bits.http_put = va_arg(param, long)?TRUE:FALSE;
    break;
  case CURLOPT_MUTE:
    data->bits.mute = va_arg(param, long)?TRUE:FALSE;
    break;

  case CURLOPT_TIMECONDITION:
    data->timecondition = va_arg(param, long);
    break;

  case CURLOPT_TIMEVALUE:
    data->timevalue = va_arg(param, long);
    break;

  case CURLOPT_SSLVERSION:
    data->ssl_version = va_arg(param, long);
    break;

  case CURLOPT_COOKIEFILE:
    cookiefile = (char *)va_arg(param, void *);
    if(cookiefile) {
      data->cookies = cookie_init(cookiefile);
    }
    break;
  case CURLOPT_WRITEHEADER:
    data->writeheader = (FILE *)va_arg(param, FILE *);
    break;
  case CURLOPT_COOKIE:
    data->cookie = va_arg(param, char *);
    break;
  case CURLOPT_ERRORBUFFER:
    data->errorbuffer = va_arg(param, char *);
    break;
  case CURLOPT_FILE:
    data->out = va_arg(param, FILE *);
    break;
  case CURLOPT_FTPPORT:
    data->ftpport = va_arg(param, char *);
    data->bits.ftp_use_port = data->ftpport?1:0;
    break;
  case CURLOPT_HTTPHEADER:
    data->headers = va_arg(param, struct curl_slist *);
    break;
  case CURLOPT_CUSTOMREQUEST:
    data->customrequest = va_arg(param, char *);
    break;
  case CURLOPT_HTTPPOST:
    data->httppost = va_arg(param, struct HttpPost *);
    data->bits.http_formpost = data->httppost?1:0;
    break;
  case CURLOPT_INFILE:
    data->in = va_arg(param, FILE *);
    break;
  case CURLOPT_INFILESIZE:
    data->infilesize = va_arg(param, long);
    break;
  case CURLOPT_LOW_SPEED_LIMIT:
    data->low_speed_limit=va_arg(param, long);
    break;
  case CURLOPT_LOW_SPEED_TIME:
    data->low_speed_time=va_arg(param, long);
    break;
  case CURLOPT_URL:
    data->url = va_arg(param, char *);
    break;
  case CURLOPT_PORT:
    /* this typecast is used to fool the compiler to NOT warn for a
       "cast from pointer to integer of different size" */
    data->port = (unsigned short)(va_arg(param, long));
    break;
  case CURLOPT_POSTFIELDS:
    data->postfields = va_arg(param, char *);
    break;
  case CURLOPT_REFERER:
    data->referer = va_arg(param, char *);
    data->bits.http_set_referer = (data->referer && *data->referer)?1:0;
    break;
  case CURLOPT_AUTOREFERER:
    data->bits.http_auto_referer = va_arg(param, long)?1:0;
    break;
  case CURLOPT_PROXY:
    data->proxy = va_arg(param, char *);
    data->bits.httpproxy = data->proxy?1:0;
    break;
  case CURLOPT_PROXYPORT:
    data->proxyport = va_arg(param, long);
    break;
  case CURLOPT_TIMEOUT:
    data->timeout = va_arg(param, long);
    break;
  case CURLOPT_USERAGENT:
    data->useragent = va_arg(param, char *);
    break;
  case CURLOPT_USERPWD:
    data->userpwd = va_arg(param, char *);
    data->bits.user_passwd = data->userpwd?1:0;
    break;
  case CURLOPT_POSTQUOTE:
    data->postquote = va_arg(param, struct curl_slist *);
    break;
  case CURLOPT_PROGRESSFUNCTION:
    data->fprogress = va_arg(param, curl_progress_callback);
    data->progress.callback = TRUE; /* no longer internal */
    break;
  case CURLOPT_PROGRESSDATA:
    data->progress_client = va_arg(param, void *);
    break;
  case CURLOPT_PROXYUSERPWD:
    data->proxyuserpwd = va_arg(param, char *);
    data->bits.proxy_user_passwd = data->proxyuserpwd?1:0;
    break;
  case CURLOPT_RANGE:
    data->range = va_arg(param, char *);
    data->bits.set_range = data->range?1:0;
    break;
  case CURLOPT_RESUME_FROM:
    data->resume_from = va_arg(param, long);
    break;
  case CURLOPT_STDERR:
    data->err = va_arg(param, FILE *);
    break;
  case CURLOPT_WRITEFUNCTION:
    data->fwrite = va_arg(param, curl_write_callback);
    break;
  case CURLOPT_WRITEINFO:
    data->writeinfo = va_arg(param, char *);
    break;
  case CURLOPT_READFUNCTION:
    data->fread = va_arg(param, curl_read_callback);
    break;
  case CURLOPT_SSLCERT:
    data->cert = va_arg(param, char *);
    break;
  case CURLOPT_SSLCERTPASSWD:
    data->cert_passwd = va_arg(param, char *);
    break;
  case CURLOPT_CRLF:
    data->crlf = va_arg(param, long);
    break;
  case CURLOPT_QUOTE:
    data->quote = va_arg(param, struct curl_slist *);
    break;
  default:
    /* unknown tag and its companion, just ignore: */
    return CURLE_READ_ERROR; /* correct this */
  }
  return CURLE_OK;
}