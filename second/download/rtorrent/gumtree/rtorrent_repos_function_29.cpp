void erase(iterator itr) {
//     std::push_heap(begin(), ++itr, m_compare);
//     pop();
    base_type::erase(itr);
    std::make_heap(begin(), end(), m_compare);
  }