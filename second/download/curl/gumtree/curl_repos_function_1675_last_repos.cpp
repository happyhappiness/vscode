static int showit(struct Curl_easy *data, curl_infotype type,
                  char *ptr, size_t size)
{
  static const char s_infotype[CURLINFO_END][3] = {
    "* ", "< ", "> ", "{ ", "} ", "{ ", "} " };
  int rc = 0;

#ifdef CURL_DOES_CONVERSIONS
  char *buf = NULL;
  size_t conv_size = 0;

  switch(type) {
  case CURLINFO_HEADER_OUT:
    buf = Curl_memdup(ptr, size);
    if(!buf)
      return 1;
    conv_size = size;

    /* Special processing is needed for this block if it
     * contains both headers and data (separated by CRLFCRLF).
     * We want to convert just the headers, leaving the data as-is.
     */
    if(size > 4) {
      size_t i;
      for(i = 0; i < size-4; i++) {
        if(memcmp(&buf[i], "\x0d\x0a\x0d\x0a", 4) == 0) {
          /* convert everything through this CRLFCRLF but no further */
          conv_size = i + 4;
          break;
        }
      }
    }

    Curl_convert_from_network(data, buf, conv_size);
    /* Curl_convert_from_network calls failf if unsuccessful */
    /* we might as well continue even if it fails...   */
    ptr = buf; /* switch pointer to use my buffer instead */
    break;
  default:
    /* leave everything else as-is */
    break;
  }
#endif /* CURL_DOES_CONVERSIONS */

  if(data->set.fdebug)
    rc = (*data->set.fdebug)(data, type, ptr, size, data->set.debugdata);
  else {
    switch(type) {
    case CURLINFO_TEXT:
    case CURLINFO_HEADER_OUT:
    case CURLINFO_HEADER_IN:
      fwrite(s_infotype[type], 2, 1, data->set.err);
      fwrite(ptr, size, 1, data->set.err);
#ifdef CURL_DOES_CONVERSIONS
      if(size != conv_size) {
        /* we had untranslated data so we need an explicit newline */
        fwrite("\n", 1, 1, data->set.err);
      }
#endif
      break;
    default: /* nada */
      break;
    }
  }
#ifdef CURL_DOES_CONVERSIONS
  free(buf);
#endif
  return rc;
}