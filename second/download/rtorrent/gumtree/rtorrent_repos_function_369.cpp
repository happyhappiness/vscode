inline void
ElementMenu::unfocus_entry(size_type idx) {
  if (idx >= size())
    return;

  base_type::operator[](idx).m_element->set_attributes(display::Attributes::a_normal);
}