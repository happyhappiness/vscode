void
OptionParser::insert_flag(char c, Slot s) {
  m_container[c].m_slot = sigc::hide(s);
  m_container[c].m_useOption = false;
}