static struct curl_slist *cookie_list(struct Curl_easy *data)
{
  struct curl_slist *list = NULL;
  struct curl_slist *beg;
  struct Cookie *c;
  char *line;

  if((data->cookies == NULL) ||
      (data->cookies->numcookies == 0))
    return NULL;

  for(c = data->cookies->cookies; c; c = c->next) {
    if(!c->domain)
      continue;
    line = get_netscape_format(c);
    if(!line) {
      curl_slist_free_all(list);
      return NULL;
    }
    beg = Curl_slist_append_nodup(list, line);
    if(!beg) {
      free(line);
      curl_slist_free_all(list);
      return NULL;
    }
    list = beg;
  }

  return list;
}