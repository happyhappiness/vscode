  // attributes gets added to the list.
  for (iterator itr = begin(); itr != end(); ++itr)
    if (column-- > 0) {
      char* columnEnd = std::min(last, first + *m_columnWidth);

      if (columnEnd < first || columnEnd > last)
        throw torrent::internal_error("TextElementList::print(...) columnEnd < first || columnEnd > last.");

      first = (*itr)->print(first, columnEnd, attributes, object);

      if (first > columnEnd)
        throw torrent::internal_error("TextElementList::print(...) first > columnEnd.");

      std::memset(first, ' ', columnEnd - first);
      first = columnEnd;

    } else {
      first = (*itr)->print(first, last, attributes, object);
