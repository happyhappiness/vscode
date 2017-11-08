int Curl_thread_join(curl_thread_t *hnd)
{
  int ret = (WaitForSingleObject(*hnd, INFINITE) == WAIT_OBJECT_0);

  Curl_thread_destroy(*hnd);

  *hnd = curl_thread_t_null;

  return ret;
}