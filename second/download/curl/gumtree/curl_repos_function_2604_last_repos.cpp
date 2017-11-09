static int Curl_multissl_init(void)
{
  if(multissl_init(NULL))
    return 1;
  return Curl_ssl->init();
}