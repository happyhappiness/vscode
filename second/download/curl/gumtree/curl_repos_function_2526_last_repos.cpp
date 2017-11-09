static void Curl_cyassl_session_free(void *ptr)
{
  (void)ptr;
  /* CyaSSL reuses sessions on own, no free */
}