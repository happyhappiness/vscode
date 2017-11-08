static void populate_settings(struct connectdata *conn,
                              struct http_conn *httpc)
{
  nghttp2_settings_entry *iv = httpc->local_settings;

  iv[0].settings_id = NGHTTP2_SETTINGS_MAX_CONCURRENT_STREAMS;
  iv[0].value = 100;

  iv[1].settings_id = NGHTTP2_SETTINGS_INITIAL_WINDOW_SIZE;
  iv[1].value = HTTP2_HUGE_WINDOW_SIZE;

  iv[2].settings_id = NGHTTP2_SETTINGS_ENABLE_PUSH;
  iv[2].value = conn->data->multi->push_cb != NULL;

  httpc->local_settings_num = 3;
}