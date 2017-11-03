inline ElementBase*
Download::create_menu() {
  ElementMenu* element = new ElementMenu;

  element->push_back("Peer list",
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_focus), DISPLAY_PEER_LIST),
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_menu), DISPLAY_PEER_LIST));
  element->push_back("Info",
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_focus), DISPLAY_INFO),
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_menu), DISPLAY_INFO));
  element->push_back("File list",
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_focus), DISPLAY_FILE_LIST),
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_menu), DISPLAY_FILE_LIST));
  element->push_back("Tracker list",
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_focus), DISPLAY_TRACKER_LIST),
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_menu), DISPLAY_TRACKER_LIST));
  element->push_back("Chunks seen",
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_focus), DISPLAY_CHUNKS_SEEN),
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_menu), DISPLAY_CHUNKS_SEEN));
  element->push_back("Transfer list",
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_focus), DISPLAY_TRANSFER_LIST),
                     sigc::bind(sigc::mem_fun(this, &Download::activate_display_menu), DISPLAY_TRANSFER_LIST));

  element->set_entry(0, false);

  m_bindings['p'] = sigc::bind(sigc::mem_fun(element, &ElementMenu::set_entry_trigger), 0);
  m_bindings['o'] = sigc::bind(sigc::mem_fun(element, &ElementMenu::set_entry_trigger), 1);
  m_bindings['i'] = sigc::bind(sigc::mem_fun(element, &ElementMenu::set_entry_trigger), 2);
  m_bindings['u'] = sigc::bind(sigc::mem_fun(element, &ElementMenu::set_entry_trigger), 3);

  return element;
}