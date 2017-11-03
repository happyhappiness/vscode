inline void
View::insert_visible(Download* d) {
  iterator itr = std::find_if(begin_visible(), end_visible(), std::bind1st(view_downloads_compare(m_sortNew), d));

  m_size++;
  m_focus += (m_focus >= position(itr));

  base_type::insert(itr, d);
}