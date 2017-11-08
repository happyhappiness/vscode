void Curl_nss_cleanup(void)
{
  NSS_Shutdown();
  initialized = 0;
}