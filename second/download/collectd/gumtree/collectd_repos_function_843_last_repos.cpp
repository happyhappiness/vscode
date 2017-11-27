static int bind_init(void) /* {{{ */
{
  if (curl != NULL)
    return 0;

  curl = curl_easy_init();
  if (curl == NULL) {
    ERROR("bind plugin: bind_init: curl_easy_init failed.");
    return -1;
  }

  curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, bind_curl_callback);
  curl_easy_setopt(curl, CURLOPT_USERAGENT, COLLECTD_USERAGENT);
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, bind_curl_error);
  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
  curl_easy_setopt(curl, CURLOPT_MAXREDIRS, 50L);
#ifdef HAVE_CURLOPT_TIMEOUT_MS
  curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS,
                   (timeout >= 0) ? (long)timeout : (long)CDTIME_T_TO_MS(
                                                        plugin_get_interval()));
#endif

  return 0;
}