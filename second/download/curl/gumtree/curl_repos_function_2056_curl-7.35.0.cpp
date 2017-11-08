int Curl_cyassl_init(void)
{
  if(CyaSSL_Init() == 0)
    return 1;

  return -1;
}