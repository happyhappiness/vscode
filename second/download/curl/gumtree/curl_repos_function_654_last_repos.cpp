static void unit_stop(void)
{
  curl_easy_cleanup(data);
  curl_global_cleanup();
}