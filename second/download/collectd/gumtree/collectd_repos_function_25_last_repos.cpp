static size_t apache_header_callback(void *buf, size_t size, size_t nmemb,
                                     void *user_data) {
  size_t len = size * nmemb;
  apache_t *st;

  st = user_data;
  if (st == NULL) {
    ERROR("apache plugin: apache_header_callback: "
          "user_data pointer is NULL.");
    return 0;
  }

  if (len == 0)
    return len;

  /* look for the Server header */
  if (strncasecmp(buf, "Server: ", strlen("Server: ")) != 0)
    return len;

  if (strstr(buf, "Apache") != NULL)
    st->server_type = APACHE;
  else if (strstr(buf, "lighttpd") != NULL)
    st->server_type = LIGHTTPD;
  else if (strstr(buf, "IBM_HTTP_Server") != NULL)
    st->server_type = APACHE;
  else {
    const char *hdr = buf;

    hdr += strlen("Server: ");
    NOTICE("apache plugin: Unknown server software: %s", hdr);
  }

  return len;
}