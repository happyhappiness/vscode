static int Curl_schannel_init(void)
{
  return (Curl_sspi_global_init() == CURLE_OK ? 1 : 0);
}