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
  else if (m_flags & flag_remaining)
    val = val - cachedTime.seconds();
