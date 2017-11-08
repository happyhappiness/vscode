static void setupcallbacks(CURL *curl)
{
  curl_easy_setopt(curl, CURLOPT_OPENSOCKETFUNCTION, tst_opensocket);
  curl_easy_setopt(curl, CURLOPT_CLOSESOCKETFUNCTION, tst_closesocket);
  counter = 0;
}