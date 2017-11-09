static void curl_perform(uv_poll_t *req, int status, int events)
{
  int running_handles;
  int flags = 0;
  curl_context_t *context;

  if(events & UV_READABLE)
    flags |= CURL_CSELECT_IN;
  if(events & UV_WRITABLE)
    flags |= CURL_CSELECT_OUT;

  context = (curl_context_t *) req->data;

  curl_multi_socket_action(curl_handle, context->sockfd, flags,
                           &running_handles);

  check_multi_info();
}