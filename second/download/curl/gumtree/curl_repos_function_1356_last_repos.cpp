int curl_formget(struct curl_httppost *form, void *arg,
                 curl_formget_callback append)
{
  CURLcode result;
  curl_mimepart toppart;

  Curl_mime_initpart(&toppart, NULL); /* default form is empty */
  result = Curl_getformdata(NULL, &toppart, form, NULL);
  if(!result)
    result = Curl_mime_prepare_headers(&toppart, "multipart/form-data",
                                       NULL, MIMESTRATEGY_FORM);

  while(!result) {
    char buffer[8192];
    size_t nread = Curl_mime_read(buffer, 1, sizeof buffer, &toppart);

    if(!nread)
      break;

    switch(nread) {
    default:
      if(append(arg, buffer, nread) != nread)
        result = CURLE_READ_ERROR;
      break;
    case CURL_READFUNC_ABORT:
    case CURL_READFUNC_PAUSE:
      break;
    }
  }

  Curl_mime_cleanpart(&toppart);
  return (int) result;
}