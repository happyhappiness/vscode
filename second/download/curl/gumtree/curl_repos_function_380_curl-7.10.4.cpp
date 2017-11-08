CURLcode Curl_getinfo(struct SessionHandle *data, CURLINFO info, ...)
{
  va_list arg;
  long *param_longp=NULL;
  double *param_doublep=NULL;
  char **param_charp=NULL;
  va_start(arg, info);

  switch(info&CURLINFO_TYPEMASK) {
  default:
    return CURLE_BAD_FUNCTION_ARGUMENT;
  case CURLINFO_STRING:
    param_charp = va_arg(arg, char **);  
    if(NULL == param_charp)
      return CURLE_BAD_FUNCTION_ARGUMENT;
    break;
  case CURLINFO_LONG:
    param_longp = va_arg(arg, long *);
    if(NULL == param_longp)
      return CURLE_BAD_FUNCTION_ARGUMENT;
    break;
  case CURLINFO_DOUBLE:
    param_doublep = va_arg(arg, double *);
    if(NULL == param_doublep)
      return CURLE_BAD_FUNCTION_ARGUMENT;
    break;
  }
  
  switch(info) {
  case CURLINFO_EFFECTIVE_URL:
    *param_charp = data->change.url?data->change.url:(char *)"";
    break;
  case CURLINFO_HTTP_CODE:
    *param_longp = data->info.httpcode;
    break;
  case CURLINFO_FILETIME:
    *param_longp = data->info.filetime;
    break;
  case CURLINFO_HEADER_SIZE:
    *param_longp = data->info.header_size;
    break;
  case CURLINFO_REQUEST_SIZE:
    *param_longp = data->info.request_size;
    break;
  case CURLINFO_TOTAL_TIME:
    *param_doublep = data->progress.timespent;
    break;
  case CURLINFO_NAMELOOKUP_TIME:
    *param_doublep = data->progress.t_nslookup;
    break;
  case CURLINFO_CONNECT_TIME:
    *param_doublep = data->progress.t_connect;
    break;
  case CURLINFO_PRETRANSFER_TIME:
    *param_doublep =  data->progress.t_pretransfer;
    break;
  case CURLINFO_STARTTRANSFER_TIME:
    *param_doublep = data->progress.t_starttransfer;
    break;
  case CURLINFO_SIZE_UPLOAD:
    *param_doublep =  data->progress.uploaded;
    break;
  case CURLINFO_SIZE_DOWNLOAD:
    *param_doublep = data->progress.downloaded;
    break;
  case CURLINFO_SPEED_DOWNLOAD:
    *param_doublep =  data->progress.dlspeed;
    break;
  case CURLINFO_SPEED_UPLOAD:
    *param_doublep = data->progress.ulspeed;
    break;
  case CURLINFO_SSL_VERIFYRESULT:
    *param_longp = data->set.ssl.certverifyresult;
    break;
  case CURLINFO_CONTENT_LENGTH_DOWNLOAD:
    *param_doublep = data->progress.size_dl;
    break;
  case CURLINFO_CONTENT_LENGTH_UPLOAD:
    *param_doublep = data->progress.size_ul;
    break;
  case CURLINFO_REDIRECT_TIME:
    *param_doublep =  data->progress.t_redirect;
    break;
  case CURLINFO_REDIRECT_COUNT:
    *param_longp = data->set.followlocation;
    break;
  case CURLINFO_CONTENT_TYPE:
    *param_charp = data->info.contenttype;
    break;
  case CURLINFO_PRIVATE:
    *param_charp = data->set.private;
    break;
  default:
    return CURLE_BAD_FUNCTION_ARGUMENT;
  }
  return CURLE_OK;
}