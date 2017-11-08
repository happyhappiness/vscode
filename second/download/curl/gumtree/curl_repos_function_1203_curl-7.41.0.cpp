void Curl_thread_destroy(curl_thread_t hnd)
{
  if(hnd != curl_thread_t_null) {
    pthread_detach(*hnd);
    free(hnd);
  }
}