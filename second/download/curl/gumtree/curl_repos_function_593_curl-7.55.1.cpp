int test(char *URL)
{
  CURLM *handle = curl_multi_init();
  const char *bl_servers[] = {"Microsoft-IIS/6.0", "nginx/0.8.54", NULL};
  const char *bl_sites[] = {"curl.haxx.se:443", "example.com:80", NULL};
  (void)URL; /* unused */

  curl_multi_setopt(handle, CURLMOPT_PIPELINING_SERVER_BL, bl_servers);
  curl_multi_setopt(handle, CURLMOPT_PIPELINING_SITE_BL, bl_sites);
  curl_multi_cleanup(handle);
  return 0;
}