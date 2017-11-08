CURLcode Curl_http2_request(Curl_send_buffer *req,
                            struct connectdata *conn)
{
  uint8_t binsettings[80];
  CURLcode result;
  ssize_t binlen;
  char *base64;
  size_t blen;

  if(!conn->proto.httpc.h2) {
    /* The nghttp2 session is not yet setup, do it */
    int rc = nghttp2_session_client_new(&conn->proto.httpc.h2,
                                        &callbacks, &conn);
    if(rc) {
      failf(conn->data, "Couldn't initialize nghttp2!");
      return CURLE_OUT_OF_MEMORY; /* most likely at least */
    }
  }

  /* As long as we have a fixed set of settings, we don't have to dynamically
   * figure out the base64 strings since it'll always be the same. However,
   * the settings will likely not be fixed every time in the future.
   */

  /* this returns number of bytes it wrote */
  binlen = nghttp2_pack_settings_payload(binsettings,
                                         sizeof(binsettings),
                                         settings,
                                         sizeof(settings)/sizeof(settings[0]));
  if(!binlen) {
    failf(conn->data, "nghttp2 unexpectedly failed on pack_settings_payload");
    return CURLE_FAILED_INIT;
  }

  result = Curl_base64_encode(conn->data, (const char *)binsettings, binlen,
                              &base64, &blen);
  if(result)
    return result;

  result = Curl_add_bufferf(req,
                            "Connection: Upgrade, HTTP2-Settings\r\n"
                            "Upgrade: %s\r\n"
                            "HTTP2-Settings: %s\r\n",
                            NGHTTP2_PROTO_VERSION_ID, base64);
  free(base64);

  return result;
}