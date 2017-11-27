static size_t cj_curl_callback(void *buf, /* {{{ */
                               size_t size, size_t nmemb, void *user_data) {
  cj_t *db;
  size_t len;
  yajl_status status;

  len = size * nmemb;

  if (len == 0)
    return (len);

  db = user_data;
  if (db == NULL)
    return (0);

  status = yajl_parse(db->yajl, (unsigned char *)buf, len);
  if (status == yajl_status_ok)
    return (len);
#if !HAVE_YAJL_V2
  else if (status == yajl_status_insufficient_data)
    return (len);
#endif

  unsigned char *msg =
      yajl_get_error(db->yajl, /* verbose = */ 1,
                     /* jsonText = */ (unsigned char *)buf, (unsigned int)len);
  ERROR("curl_json plugin: yajl_parse failed: %s", msg);
  yajl_free_error(db->yajl, msg);
  return (0); /* abort write callback */
}