size_t
curl_get_receive_write(void* data, size_t size, size_t nmemb, void* handle) {
  if (!((CurlGet*)handle)->stream()->write((char*)data, size * nmemb).fail())
    return size * nmemb;
  else
    return 0;
}