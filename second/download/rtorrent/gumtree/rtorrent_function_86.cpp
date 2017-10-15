size_t
curl_get_receive_write(void* data, size_t size, size_t nmemb, void* handle) {
  return ((CurlGet*)handle)->m_stream->write((char*)data, size * nmemb).fail() ? 0 : size * nmemb;
}