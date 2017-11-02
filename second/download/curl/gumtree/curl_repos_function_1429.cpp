struct curl_hash *
Curl_hash_alloc(int slots,
                hash_function hfunc,
                comp_function comparator,
                curl_hash_dtor dtor)
{
  struct curl_hash *h;

  if(!slots || !hfunc || !comparator ||!dtor) {
    return NULL; /* failure */
  }

  h = malloc(sizeof(struct curl_hash));
  if(h) {
    if(Curl_hash_init(h, slots, hfunc, comparator, dtor)) {
      /* failure */
      free(h);
      h = NULL;
    }
  }

  return h;
}