static bool Curl_darwinssl_false_start(void)
{
#if CURL_BUILD_MAC_10_9 || CURL_BUILD_IOS_7
  if(SSLSetSessionOption != NULL)
    return TRUE;
#endif
  return FALSE;
}