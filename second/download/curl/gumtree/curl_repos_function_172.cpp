void curl_easy_cleanup(CURL *curl)
{
  curl_close(curl);
  curl_free();
}