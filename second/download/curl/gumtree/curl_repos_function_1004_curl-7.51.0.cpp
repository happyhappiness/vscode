void Curl_http2_setup_conn(struct connectdata *conn)
{
  conn->proto.httpc.settings.max_concurrent_streams =
    DEFAULT_MAX_CONCURRENT_STREAMS;
}