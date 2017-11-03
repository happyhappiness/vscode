void
WindowText::push_back(TextElement* element) {
  base_type::push_back(element);

//   m_minHeight = size();
  m_maxHeight = size();

  if (element != NULL) {
    extent_type width = element->max_length();

    if (width == extent_full)
      m_maxWidth = extent_full;
    else
      m_maxWidth = std::max(m_maxWidth, element->max_length() + m_margin);
  }

  // Check if active, if so do the update thingie. Or be lazy?
}