static CURLcode unit_setup(void)
{
  return Curl_hash_init(&hash_static, slots, Curl_hash_str,
                        Curl_str_key_compare, mydtor);
}