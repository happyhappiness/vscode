int curlx_sktosi(curl_socket_t s)
{
  return (int)((ssize_t) s);
}