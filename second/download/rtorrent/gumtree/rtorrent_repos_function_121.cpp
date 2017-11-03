void
OptionParser::insert_option(char c, SlotString s) {
  m_container[c].m_slot = s;
  m_container[c].m_useOption = true;
}