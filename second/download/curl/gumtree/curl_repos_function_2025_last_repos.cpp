static CURLcode getinfo_socket(struct Curl_easy *data, CURLINFO info,
                               curl_socket_t *param_socketp)
{
  switch(info) {
  case CURLINFO_ACTIVESOCKET:
    *param_socketp = Curl_getconnectinfo(data, NULL);
    break;
  default:
    return CURLE_UNKNOWN_OPTION;
  }

  return CURLE_OK;
}