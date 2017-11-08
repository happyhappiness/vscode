size_t Curl_multi_max_pipeline_length(struct Curl_multi *multi)
{
  return multi ? multi->max_pipeline_length : 0;
}