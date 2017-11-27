static size_t cx_curl_callback(void *buf, /* {{{ */
                               size_t size, size_t nmemb, void *user_data) {
  size_t len = size * nmemb;
  cx_t *db;

  db = user_data;
  if (db == NULL) {
    ERROR("curl_xml plugin: cx_curl_callback: "
          "user_data pointer is NULL.");
    return (0);
  }

  if (len == 0)
    return (len);

  if ((db->buffer_fill + len) >= db->buffer_size) {
    char *temp;

    temp = realloc(db->buffer, db->buffer_fill + len + 1);
    if (temp == NULL) {
      ERROR("curl_xml plugin: realloc failed.");
      return (0);
    }
    db->buffer = temp;
    db->buffer_size = db->buffer_fill + len + 1;
  }

  memcpy(db->buffer + db->buffer_fill, (char *)buf, len);
  db->buffer_fill += len;
  db->buffer[db->buffer_fill] = 0;

  return (len);
}