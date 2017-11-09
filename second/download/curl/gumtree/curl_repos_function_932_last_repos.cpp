CURLcode tool_setopt(CURL *curl, bool str, struct GlobalConfig *config,
                     const char *name, CURLoption tag, ...)
{
  va_list arg;
  char buf[256];
  const char *value = NULL;
  bool remark = FALSE;
  bool skip = FALSE;
  bool escape = FALSE;
  char *escaped = NULL;
  CURLcode ret = CURLE_OK;

  va_start(arg, tag);

  if(tag < CURLOPTTYPE_OBJECTPOINT) {
    /* Value is expected to be a long */
    long lval = va_arg(arg, long);
    long defval = 0L;
    const NameValue *nv = NULL;
    for(nv = setopt_nv_CURLNONZERODEFAULTS; nv->name; nv++) {
      if(!strcmp(name, nv->name)) {
        defval = nv->value;
        break; /* found it */
      }
    }

    snprintf(buf, sizeof(buf), "%ldL", lval);
    value = buf;
    ret = curl_easy_setopt(curl, tag, lval);
    if(lval == defval)
      skip = TRUE;
  }
  else if(tag < CURLOPTTYPE_OFF_T) {
    /* Value is some sort of object pointer */
    void *pval = va_arg(arg, void *);

    /* function pointers are never printable */
    if(tag >= CURLOPTTYPE_FUNCTIONPOINT) {
      if(pval) {
        value = "functionpointer";
        remark = TRUE;
      }
      else
        skip = TRUE;
    }

    else if(pval && str) {
      value = (char *)pval;
      escape = TRUE;
    }
    else if(pval) {
      value = "objectpointer";
      remark = TRUE;
    }
    else
      skip = TRUE;

    ret = curl_easy_setopt(curl, tag, pval);

  }
  else {
    /* Value is expected to be curl_off_t */
    curl_off_t oval = va_arg(arg, curl_off_t);
    snprintf(buf, sizeof(buf),
             "(curl_off_t)%" CURL_FORMAT_CURL_OFF_T, oval);
    value = buf;
    ret = curl_easy_setopt(curl, tag, oval);

    if(!oval)
      skip = TRUE;
  }

  va_end(arg);

  if(config->libcurl && !skip && !ret) {
    /* we only use this for real if --libcurl was used */

    if(remark)
      REM2("%s set to a %s", name, value);
    else {
      if(escape) {
        escaped = c_escape(value, CURL_ZERO_TERMINATED);
        if(!escaped) {
          ret = CURLE_OUT_OF_MEMORY;
          goto nomem;
        }
        CODE2("curl_easy_setopt(hnd, %s, \"%s\");", name, escaped);
      }
      else
        CODE2("curl_easy_setopt(hnd, %s, %s);", name, value);
    }
  }

 nomem:
  Curl_safefree(escaped);
  return ret;
}