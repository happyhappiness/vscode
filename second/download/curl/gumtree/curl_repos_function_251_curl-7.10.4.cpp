curl_hash *
Curl_hash_alloc (int slots, curl_hash_dtor dtor)
{
  curl_hash *h;

  h = (curl_hash *) malloc(sizeof(curl_hash));
  if (NULL == h)
    return NULL;

  Curl_hash_init(h, slots, dtor);

  return h;
}