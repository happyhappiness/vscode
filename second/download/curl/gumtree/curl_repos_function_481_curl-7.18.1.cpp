struct curl_slist *Curl_ossl_engines_list(struct SessionHandle *data)
{
  struct curl_slist *list = NULL;
#if defined(USE_SSLEAY) && defined(HAVE_OPENSSL_ENGINE_H)
  struct curl_slist *beg = NULL;
  ENGINE *e;

  for (e = ENGINE_get_first(); e; e = ENGINE_get_next(e)) {
    list = curl_slist_append(list, ENGINE_get_id(e));
    if(list == NULL) {
      curl_slist_free_all(beg);
      return NULL;
    }
    else if(beg == NULL) {
      beg = list;
    }
  }
#endif
  (void) data;
  return (list);
}