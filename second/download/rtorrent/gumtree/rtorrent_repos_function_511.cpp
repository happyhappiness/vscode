bool operator () (Download* d1, Download* d2) const {
    for (View::sort_list::const_iterator itr = m_sort.begin(), last = m_sort.end(); itr != last; ++itr)
      if ((**itr)(d1, d2))
        return true;
      else if ((**itr)(d2, d1))
        return false;

    // Since we're testing equivalence, return false if we're
    // equal. This is a requirement for the stl sorting algorithms.
    return false;
  }