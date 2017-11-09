CURLcode curl_easy_perform(struct Curl_easy *data)
{
  return easy_perform(data, FALSE);
}