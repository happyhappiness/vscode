#include "text_element_string.h"

namespace display {

char*
TextElementStringBase::print(char* first, char* last, Canvas::attributes_list* attributes, void* object) {
  Attributes baseAttribute = attributes->back();
  push_attribute(attributes, Attributes(first, m_attributes, Attributes::color_invalid));

  if (first == last)
    return first;

  if (m_flags & flag_escape_hex) {
    char buffer[last - first];
    char* bufferLast = copy_string(buffer, buffer + (last - first), object);

    first = rak::transform_hex(buffer, bufferLast, first, last);

  } else if (m_flags & flag_escape_html) {
