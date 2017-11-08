void Curl_digest_cleanup(struct SessionHandle *data)
{
  digest_cleanup_one(&data->state.digest);
  digest_cleanup_one(&data->state.proxydigest);
}