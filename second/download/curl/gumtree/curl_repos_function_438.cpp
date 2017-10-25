static void
hash_element_dtor(void *user, void *element)
{
  struct curl_hash *h = (struct curl_hash *) user;
  struct curl_hash_element *e = (struct curl_hash_element *) element;

  if (e->key)
    free(e->key);

  h->dtor(e->ptr);

  free(e);
}