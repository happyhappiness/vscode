CURLcode curl_easy_perform_ev(struct Curl_easy *data)
{
  return easy_perform(data, TRUE);
}