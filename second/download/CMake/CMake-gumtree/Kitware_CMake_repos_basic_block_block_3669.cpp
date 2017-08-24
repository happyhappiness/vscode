{
    Curl_mutex_destroy(tsd->mtx);
    free(tsd->mtx);
  }