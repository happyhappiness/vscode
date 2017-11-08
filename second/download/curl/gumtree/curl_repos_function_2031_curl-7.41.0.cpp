void Curl_digest_cleanup(struct SessionHandle *data)
{
  Curl_sasl_digest_cleanup(&data->state.digest);
  Curl_sasl_digest_cleanup(&data->state.proxydigest);
}