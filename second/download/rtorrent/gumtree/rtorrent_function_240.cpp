char*
TextElementList::print(char* first, char* last, Canvas::attributes_list* attributes, void* object) {
  int column = m_columnWidth != NULL ? m_column : 0;

  // Call print for each element even if first == last so that any
  // attributes gets added to the list.
  for (iterator itr = begin(); itr != end(); ++itr)
    if (column-- > 0) {
      char* columnEnd = std::min(last, first + *m_columnWidth);

      if (columnEnd < first || columnEnd > last)
        throw torrent::client_error("TextElementList::print(...) columnEnd < first || columnEnd > last.");

      first = (*itr)->print(first, columnEnd, attributes, object);

      if (first > columnEnd)
        throw torrent::client_error("TextElementList::print(...) first > columnEnd.");

      std::memset(first, ' ', columnEnd - first);
      first = columnEnd;

    } else {
      first = (*itr)->print(first, last, attributes, object);
    }

  return first;
}