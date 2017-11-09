static void unit_stop(void)
{
  if(data_node) {
    Curl_freeaddrinfo(data_node->addr);
    free(data_node);
  }
  free(data_key);
  Curl_hash_destroy(&hp);

  curl_easy_cleanup(data);
  curl_global_cleanup();
}