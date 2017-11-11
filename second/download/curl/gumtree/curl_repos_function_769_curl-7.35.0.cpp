CURLcode tool_setopt_httppost(CURL *curl, struct Configurable *config,
                              const char *name, CURLoption tag,
                              struct curl_httppost *post)
{
  CURLcode ret = CURLE_OK;
  char *escaped = NULL;
  bool skip = FALSE;

  ret = curl_easy_setopt(curl, tag, post);
  if(!post)
    skip = TRUE;

  if(config->libcurl && !skip && !ret) {
    struct curl_httppost *pp, *p;
    int i;
    /* May use several httppost lists, if multiple POST actions */
    i = ++ easysrc_form_count;
    DECL1("struct curl_httppost *post%d;", i);
    DATA1("post%d = NULL;", i);
    CLEAN1("curl_formfree(post%d);", i);
    CLEAN1("post%d = NULL;", i);
    if(i == 1)
      DECL0("struct curl_httppost *postend;");
    DATA0("postend = NULL;");
    for(p=post; p; p=p->next) {
      DATA1("curl_formadd(&post%d, &postend,", i);
      DATA1("             CURLFORM_COPYNAME, \"%s\",", p->name);
      for(pp=p; pp; pp=pp->more) {
        /* May be several files uploaded for one name;
         * these are linked through the 'more' pointer */
        Curl_safefree(escaped);
        escaped = c_escape(pp->contents);
        if(!escaped) {
          ret = CURLE_OUT_OF_MEMORY;
          goto nomem;
        }
        if(pp->flags & HTTPPOST_FILENAME) {
          /* file upload as for -F @filename */
          DATA1("             CURLFORM_FILE, \"%s\",", escaped);
        }
        else if(pp->flags & HTTPPOST_READFILE) {
          /* content from file as for -F <filename */
          DATA1("             CURLFORM_FILECONTENT, \"%s\",", escaped);
        }
        else
          DATA1("             CURLFORM_COPYCONTENTS, \"%s\",", escaped);
        if(pp->showfilename) {
          Curl_safefree(escaped);
          escaped = c_escape(pp->showfilename);
          if(!escaped) {
            ret = CURLE_OUT_OF_MEMORY;
            goto nomem;
          }
          DATA1("             CURLFORM_FILENAME, \"%s\",", escaped);
        }
        if(pp->contenttype) {
          Curl_safefree(escaped);
          escaped = c_escape(pp->contenttype);
          if(!escaped) {
            ret = CURLE_OUT_OF_MEMORY;
            goto nomem;
          }
          DATA1("             CURLFORM_CONTENTTYPE, \"%s\",", escaped);
        }
      }
      DATA0("             CURLFORM_END);");
    }
    CODE2("curl_easy_setopt(hnd, %s, post%d);", name, i);
  }

 nomem:
  Curl_safefree(escaped);
  return ret;
}