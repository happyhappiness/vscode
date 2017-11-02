CURLcode curl_easy_perform(CURL *easy)
{
  return easy_perform(easy, FALSE);
}