void pop() {
    std::pop_heap(begin(), end(), m_compare);
    base_type::pop_back();
  }