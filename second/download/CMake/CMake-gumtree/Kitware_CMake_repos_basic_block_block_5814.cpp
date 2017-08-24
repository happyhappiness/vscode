{
    Curl_resolver_cleanup(data->state.resolver);
    free(data->state.buffer);
    free(data->state.headerbuff);
    Curl_freeset(data);
    free(data);
    data = NULL;
  }