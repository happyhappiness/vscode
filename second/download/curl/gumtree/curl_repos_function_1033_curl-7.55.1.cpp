void Curl_http2_init_userset(struct UserDefined *set)
{
  set->stream_weight = NGHTTP2_DEFAULT_WEIGHT;
}