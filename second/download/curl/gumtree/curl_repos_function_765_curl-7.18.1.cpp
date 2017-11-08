bool Curl_multi_canPipeline(const struct Curl_multi* multi)
{
  return multi->pipelining_enabled;
}