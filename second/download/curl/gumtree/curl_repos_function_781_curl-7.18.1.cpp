CURLMcode curl_multi_socket_all(CURLM *multi_handle, int *running_handles)

{
  CURLMcode result = multi_socket((struct Curl_multi *)multi_handle,
                                  TRUE, CURL_SOCKET_BAD, 0, running_handles);
  if(CURLM_OK >= result)
    update_timer((struct Curl_multi *)multi_handle);
  return result;
}