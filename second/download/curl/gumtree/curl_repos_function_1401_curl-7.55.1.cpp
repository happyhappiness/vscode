static const char *get_http_string(const struct Curl_easy *data,
                                   const struct connectdata *conn)
{
#ifdef USE_NGHTTP2
  if(conn->proto.httpc.h2)
    return "2";
#endif

  if(use_http_1_1plus(data, conn))
    return "1.1";

  return "1.0";
}