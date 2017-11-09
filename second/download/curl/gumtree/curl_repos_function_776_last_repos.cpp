static int fuzz_sockopt_callback(void *ptr,
                                 curl_socket_t curlfd,
                                 curlsocktype purpose)
{
  (void)ptr;
  (void)curlfd;
  (void)purpose;

  return CURL_SOCKOPT_ALREADY_CONNECTED;
}