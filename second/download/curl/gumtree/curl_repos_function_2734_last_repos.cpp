static bool Curl_gtls_cert_status_request(void)
{
#ifdef HAS_OCSP
  return TRUE;
#else
  return FALSE;
#endif
}