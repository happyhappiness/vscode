static void unit_stop(void)
{
  if(hnd)
    curl_easy_cleanup(hnd);
  curl_global_cleanup();
}