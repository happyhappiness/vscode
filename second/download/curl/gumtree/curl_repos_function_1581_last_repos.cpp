void
Curl_hash_clean(struct curl_hash *h)
{
  Curl_hash_clean_with_criterium(h, NULL, NULL);
}