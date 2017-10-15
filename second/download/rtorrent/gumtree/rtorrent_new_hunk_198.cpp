
#include "globals.h"
#include "text_element_value.h"

namespace display {

// Should be in text_element.cc.
void
TextElement::push_attribute(Canvas::attributes_list* attributes, Attributes value) {
  Attributes base = attributes->back();
  
  if (value.colors() == Attributes::color_invalid)
    value.set_colors(base.colors());

  if (value.attributes() == Attributes::a_invalid)
    value.set_attributes(base.attributes());

  if (base.position() == value.position())
    attributes->back() = value;
  else if (base.colors() != value.colors() || base.attributes() != value.attributes())
    attributes->push_back(value);
}

char*
TextElementValueBase::print(char* first, char* last, Canvas::attributes_list* attributes, void* object) {
  Attributes baseAttribute = attributes->back();
  push_attribute(attributes, Attributes(first, m_attributes, Attributes::color_invalid));

  int64_t val = value(object);

  // Transform the value if needed.
  if (m_flags & flag_elapsed)
    val = cachedTime.seconds() - val;
