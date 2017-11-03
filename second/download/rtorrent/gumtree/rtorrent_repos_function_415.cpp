virtual bool operator () (Download* d1, Download* d2) const {
    return (*m_sort)(d2, d1);
  }