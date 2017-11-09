static size_t write_callback(char *ptr, size_t size, size_t nmemb,
                             void *userdata)
{
  struct cb_data *data = (struct cb_data *)userdata;
  size_t totalsize = nmemb * size;

  /* unused parameter */
  (void)ptr;

  /* all response headers have been received */
  data->response_received = 1;

  if(data->paused) {
    /* continue to send request body data */
    data->paused = 0;
    curl_easy_pause(data->easy_handle, CURLPAUSE_CONT);
  }

  return totalsize;
}