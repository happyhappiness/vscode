void Curl_resolver_cleanup(void *resolver)
{
  ares_destroy((ares_channel)resolver);
}