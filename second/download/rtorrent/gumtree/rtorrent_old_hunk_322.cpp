    ++range.second;

  int pos = 1;

  while (range.first != range.second) {
    char buffer[m_canvas->width() + 1];
    char* position;
    char* last = buffer + m_canvas->width() - 2 + 1;

    position = print_download_title(buffer, last, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_view->focus() ? '*' : ' ', buffer);
    
    position = print_download_info(buffer, last, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_view->focus() ? '*' : ' ', buffer);

    position = print_download_status(buffer, last, *range.first);
    m_canvas->print(0, pos++, "%c %s", range.first == m_view->focus() ? '*' : ' ', buffer);

    ++range.first;
  }    
}

