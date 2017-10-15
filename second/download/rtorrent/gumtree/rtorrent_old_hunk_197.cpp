#include "text_element_string.h"

namespace display {

char*
TextElementStringBase::print(char* first, char* last, Canvas::attributes_list* attributes, void* object) {
  // Move this stuff into a function in TextElement.
  Attributes base = attributes->back();
  Attributes current(NULL, m_attributes, Attributes::color_invalid);

  if (current.attributes() == Attributes::a_invalid)
    current.set_attributes(base.attributes());
  else if (current.attributes() != base.attributes())
    current.set_position(first);

  if (current.colors() == Attributes::color_invalid)
    current.set_colors(base.colors());
  else if (current.colors() != base.colors())
    current.set_position(first);

  if (first == last) {
    // Do nothing, but ensure that the last attributes are set.

  } else if (m_flags & flag_escape_hex) {
    char buffer[last - first];
    char* bufferLast = copy_string(buffer, buffer + (last - first), object);

    first = rak::transform_hex(buffer, bufferLast, first, last);

  } else if (m_flags & flag_escape_html) {
