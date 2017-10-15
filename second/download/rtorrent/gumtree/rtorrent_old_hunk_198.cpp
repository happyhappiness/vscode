
#include "globals.h"
#include "text_element_value.h"

namespace display {

char*
TextElementValueBase::print(char* first, char* last, Canvas::attributes_list* attributes, void* object) {
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

  int64_t val = value(object);

  // Transform the value if needed.
  if (m_flags & flag_elapsed)
    val = cachedTime.seconds() - val;
