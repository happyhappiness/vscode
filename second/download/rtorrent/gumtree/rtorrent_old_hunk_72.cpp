
#include "curl_get.h"
#include "curl_stack.h"

namespace core {

CurlGet::CurlGet(CurlStack* s) :
  m_handle(NULL),
  m_stack(s) {

  if (m_stack == NULL)
    throw std::logic_error("Tried to create CurlGet without a valid CurlStack");
