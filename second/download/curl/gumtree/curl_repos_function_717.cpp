CURLcode curl_easy_setopt(CURL *curl, CURLoption tag, ...)
{
  va_list arg;
  func_T param_func = (func_T)0;
  long param_long = 0;
  void *param_obj = NULL;
  curl_off_t param_offset = 0;
  struct SessionHandle *data = curl;
  CURLcode ret=CURLE_FAILED_INIT;

  if(!curl)
    return CURLE_BAD_FUNCTION_ARGUMENT;

  va_start(arg, tag);

  /* PORTING NOTE:
     Object pointers can't necessarily be casted to function pointers and
     therefore we need to know what type it is and read the correct type
     at once. This should also correct problems with different sizes of
     the types.
  */

  if(tag < CURLOPTTYPE_OBJECTPOINT) {
    /* This is a LONG type */
    param_long = va_arg(arg, long);
    ret = Curl_setopt(data, tag, param_long);
  }
  else if(tag < CURLOPTTYPE_FUNCTIONPOINT) {
    /* This is a object pointer type */
    param_obj = va_arg(arg, void *);
    ret = Curl_setopt(data, tag, param_obj);
  }
  else if(tag < CURLOPTTYPE_OFF_T) {
    /* This is a function pointer type */
    param_func = va_arg(arg, func_T );
    ret = Curl_setopt(data, tag, param_func);
  }
  else {
    /* This is a curl_off_t type */
    param_offset = va_arg(arg, curl_off_t);
    ret = Curl_setopt(data, tag, param_offset);
  }

  va_end(arg);
  return ret;
}