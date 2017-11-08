static curl_socket_t opensocket(void *clientp,
                                curlsocktype purpose,
                                struct curl_sockaddr *address)
{
  (void)purpose;
  (void)address;
  (void)clientp;
  fprintf(stderr, "opensocket() returns CURL_SOCKET_BAD\n");
  return CURL_SOCKET_BAD;
}