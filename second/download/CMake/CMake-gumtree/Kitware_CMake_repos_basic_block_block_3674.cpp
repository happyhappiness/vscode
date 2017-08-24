{
    tsd->done = 1;
    Curl_mutex_release(tsd->mtx);
  }