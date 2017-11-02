int handle_socket(CURL *easy, curl_socket_t s, int action, void *userp,
                  void *socketp)
{
  curl_context_t *curl_context;
  if(action == CURL_POLL_IN || action == CURL_POLL_OUT) {
    if(socketp) {
      curl_context = (curl_context_t *) socketp;
    }
    else {
      curl_context = create_curl_context(s);
    }
    curl_multi_assign(curl_handle, s, (void *) curl_context);
  }

  switch(action) {
  case CURL_POLL_IN:
    uv_poll_start(&curl_context->poll_handle, UV_READABLE, curl_perform);
    break;
  case CURL_POLL_OUT:
    uv_poll_start(&curl_context->poll_handle, UV_WRITABLE, curl_perform);
    break;
  case CURL_POLL_REMOVE:
    if(socketp) {
      uv_poll_stop(&((curl_context_t*)socketp)->poll_handle);
      destroy_curl_context((curl_context_t*) socketp);
      curl_multi_assign(curl_handle, s, NULL);
    }
    break;
  default:
    abort();
  }

  return 0;
}