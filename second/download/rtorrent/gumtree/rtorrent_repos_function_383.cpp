void
ElementText::push_column(text_element_wrapper entry1, text_element_wrapper entry2,
                         text_element_wrapper entry3, text_element_wrapper entry4,
                         text_element_wrapper entry5) {
  m_columnWidth = std::max(entry1.m_element->max_length(), m_columnWidth);

  display::TextElementList* list = new display::TextElementList;
  list->set_column(m_column);
  list->set_column_width(&m_columnWidth);

  list->push_back(entry1.m_element);
  list->push_back(entry2.m_element);
  list->push_back(entry3.m_element);
  list->push_back(entry4.m_element);
  list->push_back(entry5.m_element);

  push_back(list);
}