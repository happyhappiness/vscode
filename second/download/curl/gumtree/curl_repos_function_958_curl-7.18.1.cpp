struct curl_slist *Curl_cookie_list(struct SessionHandle *data)
{
  struct curl_slist *list = NULL;
  struct curl_slist *beg;
  struct Cookie *c;
  char *line;

  if((data->cookies == NULL) ||
      (data->cookies->numcookies == 0))
    return NULL;

  c = data->cookies->cookies;

  beg = list;
  while(c) {
    /* fill the list with _all_ the cookies we know */
    line = get_netscape_format(c);
    if(line == NULL) {
      curl_slist_free_all(beg);
      return NULL;
    }
    list = curl_slist_append(list, line);
    free(line);
    if(list == NULL) {
      curl_slist_free_all(beg);
      return NULL;
    }
    else if(beg == NULL) {
      beg = list;
    }
    c = c->next;
  }

  return list;
}