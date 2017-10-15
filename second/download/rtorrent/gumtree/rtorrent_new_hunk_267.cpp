}

void
Canvas::print_attributes(unsigned int x, unsigned int y, const char* first, const char* last, const attributes_list* attributes) {
  move(x, y);

  attr_t org_attr;
  short org_pair;
  wattr_get(m_window, &org_attr, &org_pair, NULL);

  attributes_list::const_iterator attrItr = attributes->begin();
  wattr_set(m_window, Attributes::a_normal, Attributes::color_default, NULL);

  while (first != last) {
    const char* next = last;

    if (attrItr != attributes->end()) {
      next = attrItr->position();

      if (first >= next) {
        wattr_set(m_window, attrItr->attributes(), attrItr->colors(), NULL);
        ++attrItr;
      }
    }

    print("%.*s", next - first, first);
    first = next;
  }

  // Reset the color.
  wattr_set(m_window, org_attr, org_pair, NULL);
}

void
Canvas::initialize() {
  if (m_isInitialized)
    return;
