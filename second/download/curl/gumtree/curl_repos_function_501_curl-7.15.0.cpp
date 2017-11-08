struct curl_slist *curl_slist_append(struct curl_slist *list,
                                     const char *data)
{
  struct curl_slist     *last;
  struct curl_slist     *new_item;

  new_item = (struct curl_slist *) malloc(sizeof(struct curl_slist));
  if (new_item) {
    char *dup = strdup(data);
    if(dup) {
      new_item->next = NULL;
      new_item->data = dup;
    }
    else {
      free(new_item);
      return NULL;
    }
  }
  else
    return NULL;

  if (list) {
    last = slist_get_last(list);
    last->next = new_item;
    return list;
  }

  /* if this is the first item, then new_item *is* the list */
  return new_item;
}