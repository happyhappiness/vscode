CURLcode curl_easy_perform(CURL *curl)
{
  return curl_transfer(curl);
}