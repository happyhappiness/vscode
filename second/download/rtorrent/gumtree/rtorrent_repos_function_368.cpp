inline void
ElementMenu::focus_entry(size_type idx) {
  if (idx >= size())
    return;

  if (m_focus)
    base_type::operator[](idx).m_element->set_attributes(display::Attributes::a_reverse);
  else
    base_type::operator[](idx).m_element->set_attributes(display::Attributes::a_bold);
}