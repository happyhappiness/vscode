CURLcode curl_easy_perform_ev(CURL *easy)
{
  return easy_perform(easy, TRUE);
}