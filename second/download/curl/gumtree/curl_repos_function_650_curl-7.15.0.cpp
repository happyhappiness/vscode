struct curl_slist *Curl_cookie_list(struct SessionHandle *data)
{
  struct curl_slist *list = NULL;
  struct curl_slist *beg;
  struct Cookie *c;
  char *line;

  if ((data->cookies == NULL) ||
      (data->cookies->numcookies == 0))
    return NULL;

  c = data->cookies->cookies;

  beg = list;
  while (c) {
    /* fill the list with _all_ the cookies we know */
    line = get_netscape_format(c);
    if (line == NULL) {
      /* get_netscape_format returns null only if we run out of memory */

      curl_slist_free_all(beg); /* free some memory */
      return NULL;
    }
    list = curl_slist_append(list, line);
    free(line);
    c = c->next;
  }

  return list;
}