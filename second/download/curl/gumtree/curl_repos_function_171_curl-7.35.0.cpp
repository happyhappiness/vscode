void SyncTime_CURL_Init(CURL *curl, char *proxy_port,
                        char *proxy_user_password)
{
  if (strlen(proxy_port) > 0)
    curl_easy_setopt(curl, CURLOPT_PROXY, proxy_port);

  if (strlen(proxy_user_password) > 0)
    curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, proxy_user_password);

  /* Trick Webserver by claiming that you are using Microsoft WinXP SP2, IE6 */
  curl_easy_setopt(curl, CURLOPT_USERAGENT,
                   "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1)");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, *SyncTime_CURL_WriteOutput);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, *SyncTime_CURL_WriteHeader);
}