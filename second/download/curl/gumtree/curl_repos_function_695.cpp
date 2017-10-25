int Curl_gtls_cleanup(void)
{
  gnutls_global_deinit();
  return 1;
}