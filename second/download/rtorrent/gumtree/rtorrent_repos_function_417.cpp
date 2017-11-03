void
ViewManager::clear() {
  std::for_each(begin(), end(), rak::call_delete<View>());
  std::for_each(m_sort.begin(), m_sort.end(), rak::on(rak::mem_ref(&sort_map::value_type::second), rak::call_delete<ViewSort>()));
  std::for_each(m_filter.begin(), m_filter.end(), rak::on(rak::mem_ref(&filter_map::value_type::second), rak::call_delete<ViewFilter>()));

  base_type::clear();
}