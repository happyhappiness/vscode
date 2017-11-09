static void unit_stop(void)
{
  curl_easy_cleanup(easy);
  curl_global_cleanup();
}