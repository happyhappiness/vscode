CURLcode tool_setopt_slist(CURL *curl, struct GlobalConfig *config,
                           const char *name, CURLoption tag,
                           struct curl_slist *list)
{
  CURLcode ret = CURLE_OK;
  char *escaped = NULL;
  bool skip = FALSE;

  ret = curl_easy_setopt(curl, tag, list);
  if(!list)
    skip = TRUE;

  if(config->libcurl && !skip && !ret) {
    struct curl_slist *s;
    int i;
    /* May need several slist variables, so invent name */
    i = ++ easysrc_slist_count;
    DECL1("struct curl_slist *slist%d;", i);
    DATA1("slist%d = NULL;", i);
    CLEAN1("curl_slist_free_all(slist%d);", i);
    CLEAN1("slist%d = NULL;", i);
    for(s=list; s; s=s->next) {
      Curl_safefree(escaped);
      escaped = c_escape(s->data);
      if(!escaped) {
        ret = CURLE_OUT_OF_MEMORY;
        goto nomem;
      }
      DATA3("slist%d = curl_slist_append(slist%d, \"%s\");", i, i, escaped);
    }
    CODE2("curl_easy_setopt(hnd, %s, slist%d);", name, i);
  }

 nomem:
  Curl_safefree(escaped);
  return ret;
}