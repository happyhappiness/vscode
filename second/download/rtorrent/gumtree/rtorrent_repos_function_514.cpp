void
View::filter() {
  iterator split = std::stable_partition(base_type::begin(), base_type::end(), view_downloads_filter(m_filter));

  m_size = position(split);

  // Fix focus
  m_focus = std::min(m_focus, m_size);
}