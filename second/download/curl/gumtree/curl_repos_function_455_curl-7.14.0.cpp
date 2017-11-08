void Curl_multi_rmeasy(void *multi_handle, CURL *easy_handle)
{
  curl_multi_remove_handle(multi_handle, easy_handle);
}