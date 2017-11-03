void
OptionParser::insert_option_list(char c, SlotStringPair s) {
  m_container[c].m_slot = sigc::bind<0>(sigc::ptr_fun(&OptionParser::call_option_list), s);
  m_container[c].m_useOption = true;
}