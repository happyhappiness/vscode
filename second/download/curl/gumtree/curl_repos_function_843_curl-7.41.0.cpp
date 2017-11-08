CURLcode easysrc_addf(struct curl_slist **plist, const char *fmt, ...)
{
  CURLcode ret;
  char *bufp;
  va_list ap;
  va_start(ap, fmt);
  bufp = curlx_mvaprintf(fmt, ap);
  va_end(ap);
  if(! bufp) {
    ret = CURLE_OUT_OF_MEMORY;
  }
  else {
    ret = easysrc_add(plist, bufp);
    curl_free(bufp);
  }
  return ret;
}