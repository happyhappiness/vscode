static int Curl_cyassl_init(void)
{
  return (CyaSSL_Init() == SSL_SUCCESS);
}