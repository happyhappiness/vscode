bool Curl_multi_pipeline_enabled(const struct Curl_multi *multi)
{
  return (multi && multi->pipelining_enabled) ? TRUE : FALSE;
}