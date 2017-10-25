void Curl_digest_cleanup(struct SessionHandle *data)
{
  Curl_digest_cleanup_one(&data->state.digest);
  Curl_digest_cleanup_one(&data->state.proxydigest);
}