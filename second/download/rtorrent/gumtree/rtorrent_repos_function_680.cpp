TextElementList::extent_type
TextElementList::max_length() {
  extent_type length = 0;
  int column = m_columnWidth != NULL ? m_column : 0;

  for (iterator itr = begin(); itr != end(); ++itr) {
    extent_type l = column-- > 0 ? std::min((*itr)->max_length(), *m_columnWidth) : (*itr)->max_length();

    if (l == extent_full)
      return extent_full;
    
    length += l;
  }
  
  return length;
}