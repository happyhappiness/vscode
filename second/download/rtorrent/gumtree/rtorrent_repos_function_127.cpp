void
OptionParser::call(char c, const std::string& arg) {
  Container::iterator itr = m_container.find(c);

  if (itr == m_container.end())
    throw std::logic_error("OptionParser::call_flag(...) could not find the flag");

  itr->second.m_slot(arg);
}