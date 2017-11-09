static CURLcode CopyCertSubject(struct Curl_easy *data,
                                SecCertificateRef cert, char **certp)
{
  CFStringRef c = getsubject(cert);
  CURLcode result = CURLE_OK;
  const char *direct;
  char *cbuf = NULL;
  *certp = NULL;

  if(!c) {
    failf(data, "SSL: invalid CA certificate subject");
    return CURLE_OUT_OF_MEMORY;
  }

  /* If the subject is already available as UTF-8 encoded (ie 'direct') then
     use that, else convert it. */
  direct = CFStringGetCStringPtr(c, kCFStringEncodingUTF8);
  if(direct) {
    *certp = strdup(direct);
    if(!*certp) {
      failf(data, "SSL: out of memory");
      result = CURLE_OUT_OF_MEMORY;
    }
  }
  else {
    size_t cbuf_size = ((size_t)CFStringGetLength(c) * 4) + 1;
    cbuf = calloc(cbuf_size, 1);
    if(cbuf) {
      if(!CFStringGetCString(c, cbuf, cbuf_size,
                             kCFStringEncodingUTF8)) {
        failf(data, "SSL: invalid CA certificate subject");
        result = CURLE_SSL_CACERT;
      }
      else
        /* pass back the buffer */
        *certp = cbuf;
    }
    else {
      failf(data, "SSL: couldn't allocate %zu bytes of memory", cbuf_size);
      result = CURLE_OUT_OF_MEMORY;
    }
  }
  if(result)
    free(cbuf);
  CFRelease(c);
  return result;
}