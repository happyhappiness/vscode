static void unit_stop(void)
{
  Curl_hash_destroy(&hash_static);
}