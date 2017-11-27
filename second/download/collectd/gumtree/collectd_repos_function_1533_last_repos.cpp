static int http_handler(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **connection_state) {
  if (strcmp(method, MHD_HTTP_METHOD_GET) != 0) {
    return MHD_NO;
  }

  /* On the first call for each connection, return without anything further.
   * Apparently not everything has been initialized yet or so; the docs are not
   * very specific on the issue. */
  if (*connection_state == NULL) {
    /* set to a random non-NULL pointer. */
    *connection_state = &(int){42};
    return MHD_YES;
  }

  char const *accept = MHD_lookup_connection_value(connection, MHD_HEADER_KIND,
                                                   MHD_HTTP_HEADER_ACCEPT);
  _Bool want_proto =
      (accept != NULL) &&
      (strstr(accept, "application/vnd.google.protobuf") != NULL);

  uint8_t scratch[4096] = {0};
  ProtobufCBufferSimple simple = PROTOBUF_C_BUFFER_SIMPLE_INIT(scratch);
  ProtobufCBuffer *buffer = (ProtobufCBuffer *)&simple;

  if (want_proto)
    format_protobuf(buffer);
  else
    format_text(buffer);

#if defined(MHD_VERSION) && MHD_VERSION >= 0x00090500
  struct MHD_Response *res = MHD_create_response_from_buffer(
      simple.len, simple.data, MHD_RESPMEM_MUST_COPY);
#else
  struct MHD_Response *res = MHD_create_response_from_data(
      simple.len, simple.data, /* must_free = */ 0, /* must_copy = */ 1);
#endif
  MHD_add_response_header(res, MHD_HTTP_HEADER_CONTENT_TYPE,
                          want_proto ? CONTENT_TYPE_PROTO : CONTENT_TYPE_TEXT);

  int status = MHD_queue_response(connection, MHD_HTTP_OK, res);

  MHD_destroy_response(res);
  PROTOBUF_C_BUFFER_SIMPLE_CLEAR(&simple);
  return status;
}