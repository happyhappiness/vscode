static int dispatch_gauge(CURL *curl, CURLINFO info, value_list_t *vl) {
  CURLcode code;
  value_t v;

  code = curl_easy_getinfo(curl, info, &v.gauge);
  if (code != CURLE_OK)
    return -1;

  vl->values = &v;
  vl->values_len = 1;

  return plugin_dispatch_values(vl);
}