struct curl_hash *
Curl_hash_alloc(int slots, curl_hash_dtor dtor)
{
  struct curl_hash *h;

  h = (struct curl_hash *) malloc(sizeof(struct curl_hash));
  if (h) {
    if(Curl_hash_init(h, slots, dtor)) {
      /* failure */
      free(h);
      h = NULL;
    }
  }

  return h;
}