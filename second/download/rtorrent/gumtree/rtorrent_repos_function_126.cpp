std::string
OptionParser::create_optstring() {
  std::string s;

  for (Container::iterator itr = m_container.begin(); itr != m_container.end(); ++itr) {
    s += itr->first;

    if (itr->second.m_useOption)
      s += ':';
  }

  return s;
}