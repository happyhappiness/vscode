{
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