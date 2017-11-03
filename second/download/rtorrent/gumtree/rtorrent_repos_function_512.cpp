bool operator () (Download* d1) const {
    for (View::filter_list::const_iterator itr = m_filter.begin(), last = m_filter.end(); itr != last; ++itr)
      if (!(**itr)(d1))
        return false;

    // The default filter action is to return true, to not filter the
    // download out.
    return true;
  }