void Curl_thread_destroy(curl_thread_t hnd)
{
  CloseHandle(hnd);
}