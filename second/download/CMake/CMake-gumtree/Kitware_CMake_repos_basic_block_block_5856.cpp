{
    Curl_conncache_foreach(data->state.conn_cache, data,
                           call_disconnect_if_dead);
    data->state.conn_cache->last_cleanup = now;
  }