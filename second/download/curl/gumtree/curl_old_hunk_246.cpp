  else {
    curl_off_t oval = va_arg(arg, curl_off_t);
    snprintf(value, sizeof(value), "(curl_off_t)%Od", oval);
    ret = curl_easy_setopt(curl, tag, oval);
  }

  bufp = curl_maprintf("%scurl_easy_setopt(hnd, %s, %s);%s",
                       remark?"/* ":"", name, value,
                       remark?" [REMARK] */":"");

  if (!curl_slist_append(easycode, bufp))
    ret = CURLE_OUT_OF_MEMORY;
  curl_free(bufp);
  va_end(arg);

  return ret;
}

static const char * const srchead[]={
