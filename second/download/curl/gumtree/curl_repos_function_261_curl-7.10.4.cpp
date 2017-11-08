void 
Curl_hash_destroy(curl_hash *h)
{
  if (!h)
    return;

  Curl_hash_clean(h);
  free(h);
}