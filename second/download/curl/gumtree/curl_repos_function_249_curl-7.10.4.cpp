static void 
_hash_element_dtor (void *user, void *element)
{
  curl_hash         *h = (curl_hash *) user;
  curl_hash_element *e = (curl_hash_element *) element;

  if (e->key) {
    free(e->key);
  }

  h->dtor(e->ptr);

  free(e);
}