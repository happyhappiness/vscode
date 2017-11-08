static void init(CURLM *cm, const char* url, const char* userpwd,
                struct curl_slist *headers)
{
  CURL *eh = curl_easy_init();

  curl_easy_setopt(eh, CURLOPT_URL, url);
  curl_easy_setopt(eh, CURLOPT_PROXY, PROXY);
  curl_easy_setopt(eh, CURLOPT_PROXYUSERPWD, userpwd);
  curl_easy_setopt(eh, CURLOPT_PROXYAUTH, CURLAUTH_ANY);
  curl_easy_setopt(eh, CURLOPT_VERBOSE, 1);
  curl_easy_setopt(eh, CURLOPT_HEADER, 1);
  curl_easy_setopt(eh, CURLOPT_HTTPHEADER, headers); /* custom Host: */

  curl_multi_add_handle(cm, eh);
}