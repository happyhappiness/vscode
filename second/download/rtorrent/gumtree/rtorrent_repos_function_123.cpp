void
OptionParser::insert_int_pair(char c, SlotIntPair s) {
  m_container[c].m_slot = sigc::bind<0>(sigc::ptr_fun(&OptionParser::call_int_pair), s);
  m_container[c].m_useOption = true;
}