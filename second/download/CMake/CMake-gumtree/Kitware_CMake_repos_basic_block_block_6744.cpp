{
  struct ptr_list_wrap *wrap = malloc(sizeof *wrap);
  if(!wrap)
    return CURLE_OUT_OF_MEMORY;

  wrap->ptr = ptr;
  Curl_llist_insert_next(list, list->tail, wrap, &wrap->node);
  return CURLE_OK;
}