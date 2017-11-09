curl_socket_t curlx_sitosk(int i)
{
  return (curl_socket_t)((ssize_t) i);
}