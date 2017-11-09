static void destroy_curl_context(curl_context_t *context)
{
  uv_close((uv_handle_t *) &context->poll_handle, curl_close_cb);
}