void Curl_http2_init_state(struct UrlState *state)
{
  state->stream_weight = NGHTTP2_DEFAULT_WEIGHT;
}