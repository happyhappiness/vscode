void push(const value_type& value) {
    base_type::push_back(value);
    std::push_heap(begin(), end(), m_compare);
  }