Directory::Base
Directory::make_list() {
  Base l;

  for (Base::iterator itr = begin(); itr != end(); ++itr)
    l.push_back(m_path + *itr);

  return l;
}