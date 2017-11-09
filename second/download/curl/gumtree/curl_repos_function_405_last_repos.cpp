static void notifyCurl(CURLM *curl, curl_socket_t s, int evBitmask,
                       const char *info)
{
  int numhandles = 0;
  CURLMcode result = curl_multi_socket_action(curl, s, evBitmask, &numhandles);
  if(result != CURLM_OK) {
    fprintf(stderr, "Curl error on %s: %i (%s)\n",
            info, result, curl_multi_strerror(result));
  }
}