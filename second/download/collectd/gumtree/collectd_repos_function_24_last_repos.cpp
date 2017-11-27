static size_t apache_curl_callback(void *buf, size_t size, size_t nmemb,
                                   void *user_data) {
  size_t len = size * nmemb;
  apache_t *st;

  st = user_data;
  if (st == NULL) {
    ERROR("apache plugin: apache_curl_callback: "
          "user_data pointer is NULL.");
    return 0;
  }

  if (len == 0)
    return len;

  if ((st->apache_buffer_fill + len) >= st->apache_buffer_size) {
    char *temp;

    temp = realloc(st->apache_buffer, st->apache_buffer_fill + len + 1);
    if (temp == NULL) {
      ERROR("apache plugin: realloc failed.");
      return 0;
    }
    st->apache_buffer = temp;
    st->apache_buffer_size = st->apache_buffer_fill + len + 1;
  }

  memcpy(st->apache_buffer + st->apache_buffer_fill, (char *)buf, len);
  st->apache_buffer_fill += len;
  st->apache_buffer[st->apache_buffer_fill] = 0;

  return len;
}