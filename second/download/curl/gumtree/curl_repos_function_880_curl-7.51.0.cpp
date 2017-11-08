void slist_wc_free_all(struct slist_wc *list)
{
  if(!list)
    return;

  curl_slist_free_all(list->first);
  free(list);
}