void curl_perform(uv_poll_t *req, int status, int events)
{
  int running_handles;
  int flags = 0;
  curl_context_t *context;
  char *done_url;
  CURLMsg *message;
  int pending;

  uv_timer_stop(&timeout);

  if (events & UV_READABLE)
    flags |= CURL_CSELECT_IN;
  if (events & UV_WRITABLE)
    flags |= CURL_CSELECT_OUT;

  context = (curl_context_t*)req;

  curl_multi_socket_action(curl_handle, context->sockfd, flags,
                           &running_handles);

  while ((message = curl_multi_info_read(curl_handle, &pending))) {
    switch (message->msg) {
    case CURLMSG_DONE:
      curl_easy_getinfo(message->easy_handle, CURLINFO_EFFECTIVE_URL,
                        &done_url);
      printf("%s DONE\n", done_url);

      curl_multi_remove_handle(curl_handle, message->easy_handle);
      curl_easy_cleanup(message->easy_handle);

      break;
    default:
      fprintf(stderr, "CURLMSG default\n");
      abort();
    }
  }
}