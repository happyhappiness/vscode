void SyncTime_CURL_Init(CURL *curl, char *proxy_port,
                        char *proxy_user_password)
{
  if(strlen(proxy_port) > 0)
    curl_easy_setopt(curl, CURLOPT_PROXY, proxy_port);

  if(strlen(proxy_user_password) > 0)
    curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD, proxy_user_password);

#ifdef SYNCTIME_UA
  curl_easy_setopt(curl, CURLOPT_USERAGENT, SYNCTIME_UA);
#endif
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, *SyncTime_CURL_WriteOutput);
  curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, *SyncTime_CURL_WriteHeader);
}