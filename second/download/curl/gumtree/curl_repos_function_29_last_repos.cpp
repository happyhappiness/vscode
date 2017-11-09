static void on_timeout(uv_timer_t *req)
{
  int running_handles;
  curl_multi_socket_action(curl_handle, CURL_SOCKET_TIMEOUT, 0,
                           &running_handles);
  check_multi_info();
}