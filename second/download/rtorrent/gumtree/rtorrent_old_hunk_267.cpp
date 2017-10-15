}

void
Canvas::print_attributes(unsigned int x, unsigned int y, const char* first, const char* last, const attributes_list* attributes) {
  move(x, y);

  attributes_list::const_iterator attrItr = attributes->begin();
  Attributes current = Attributes(first, Attributes::a_normal, Attributes::color_default);

  while (first != last) {
    if (attrItr != attributes->end() && first >= attrItr->position())
      current = *attrItr++;

    waddch(m_window, *first++ | current.attributes());
  }

  // Reset the color.
}

void
Canvas::initialize() {
  if (m_isInitialized)
    return;
