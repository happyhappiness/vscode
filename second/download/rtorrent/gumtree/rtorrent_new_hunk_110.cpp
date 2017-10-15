#include "curl_stack.h"

namespace core {

size_t
curl_get_receive_write(void* data, size_t size, size_t nmemb, void* handle) {
  if (!((CurlGet*)handle)->stream()->write((const char*)data, size * nmemb).fail())
    return size * nmemb;
  else
    return 0;
}

CurlGet::CurlGet(CurlStack* s) :
