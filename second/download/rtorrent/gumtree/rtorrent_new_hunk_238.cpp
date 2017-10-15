TextElementList::clear() {
  std::for_each(begin(), end(), rak::call_delete<TextElement>());
  base_type::clear();
}

char*
TextElementList::print(char* first, char* last, Canvas::attributes_list* attributes, rpc::target_type target) {
  int column = m_columnWidth != NULL ? m_column : 0;

  // Call print for each element even if first == last so that any
  // attributes gets added to the list.
  for (iterator itr = begin(); itr != end(); ++itr)
    if (column-- > 0) {
      char* columnEnd = std::min(last, first + *m_columnWidth);

      if (columnEnd < first || columnEnd > last)
        throw torrent::internal_error("TextElementList::print(...) columnEnd < first || columnEnd > last.");

      first = (*itr)->print(first, columnEnd, attributes, target);

      if (first > columnEnd)
        throw torrent::internal_error("TextElementList::print(...) first > columnEnd.");

      std::memset(first, ' ', columnEnd - first);
      first = columnEnd;

    } else {
      first = (*itr)->print(first, last, attributes, target);
    }

  return first;
}

TextElementList::extent_type
