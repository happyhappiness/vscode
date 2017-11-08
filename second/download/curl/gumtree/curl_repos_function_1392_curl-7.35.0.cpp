CURLMcode curl_multi_assign(CURLM *multi_handle,
                            curl_socket_t s, void *hashp)
{
  struct Curl_sh_entry *there = NULL;
  struct Curl_multi *multi = (struct Curl_multi *)multi_handle;

  if(s != CURL_SOCKET_BAD)
    there = Curl_hash_pick(multi->sockhash, (char *)&s, sizeof(curl_socket_t));

  if(!there)
    return CURLM_BAD_SOCKET;

  there->socketp = hashp;

  return CURLM_OK;
}