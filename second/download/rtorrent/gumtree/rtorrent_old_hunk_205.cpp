  if (m_interval != 0)
    m_slotSchedule(this, (cachedTime + rak::timer::from_seconds(m_interval)).round_seconds());

  m_canvas->erase();

  unsigned int position = 0;
  Canvas::attributes_list attributes;

  for (iterator itr = begin(); itr != end() && position < m_canvas->height(); ++itr, ++position) {
    if (*itr == NULL)
      continue;

    char buffer[m_canvas->width() + 1];

    // Add a print function that sets up attributes etc?
    attributes.clear();
    attributes.push_back(Attributes(buffer, Attributes::a_normal, Attributes::color_default));

    char* last = (*itr)->print(buffer, buffer + m_canvas->width(), &attributes, m_object);

    m_canvas->print_attributes(0, position, buffer, last, &attributes);
  }
