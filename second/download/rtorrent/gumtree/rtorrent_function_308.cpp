void
WindowText::redraw() {
  if (m_interval != 0)
    m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(m_interval)).round_seconds());

  m_canvas->erase();

  unsigned int position = 0;

  if (m_canvas->height() == 0)
    return;

  if (m_errorHandler != NULL && m_target.second == NULL) {
    char buffer[m_canvas->width() + 1];

    Canvas::attributes_list attributes;
    attributes.push_back(Attributes(buffer, Attributes::a_normal, Attributes::color_default));

    char* last = m_errorHandler->print(buffer, buffer + m_canvas->width(), &attributes, m_target);

    m_canvas->print_attributes(0, position, buffer, last, &attributes);
    return;
  }

  for (iterator itr = begin(); itr != end() && position < m_canvas->height(); ++itr, ++position) {
    if (*itr == NULL)
      continue;

    char buffer[m_canvas->width() + 1];

    Canvas::attributes_list attributes;
    attributes.push_back(Attributes(buffer, Attributes::a_normal, Attributes::color_default));

    char* last = (*itr)->print(buffer, buffer + m_canvas->width(), &attributes, m_target);

    m_canvas->print_attributes(0, position, buffer, last, &attributes);
  }
}