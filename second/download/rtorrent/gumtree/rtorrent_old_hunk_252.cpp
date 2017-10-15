  m_connPeerDisconnected.disconnect();

  delete m_windowList;
  delete m_elementInfo;
}

std::string
te_client_version(const torrent::PeerInfo* info) {
  char buf[128];
  display::print_client_version(buf, buf + 128, info->client_info());

  return buf;
}

inline ElementText*
ElementPeerList::create_info() {
  using namespace display::helpers;

  ElementText* element = new ElementText(rpc::make_target());

  element->set_column(1);
  element->set_interval(1);

  // Get these bindings with some kind of string map.

  element->push_back("Peer info:");

  element->push_back("");
  element->push_column("Address:",
                       display::text_element_string_slot(rak::on(std::mem_fun(&torrent::Peer::address), std::ptr_fun(&te_address))), ":",
                       display::text_element_value_slot(rak::on(std::mem_fun(&torrent::Peer::address), std::ptr_fun(&te_port))));

  element->push_column("Id:",        display::text_element_string_slot(std::mem_fun(&torrent::Peer::id), string_base::flag_escape_html));
//   element->push_column("Client:",    display::text_element_string_slot(rak::on(std::mem_fun(&torrent::Peer::id), rak::make_mem_fun(control->client_info(), &display::ClientInfo::hash_str))));
  element->push_column("Client:",    display::text_element_string_slot(rak::on(std::mem_fun(&torrent::Peer::info), std::ptr_fun(&te_client_version))));
  element->push_column("Options:",   display::text_element_string_slot(std::mem_fun(&torrent::Peer::options), string_base::flag_escape_hex | string_base::flag_fixed_width, 0, 8));
  element->push_column("Connected:", display::text_element_branch(std::mem_fun(&torrent::Peer::is_incoming), te_string("incoming"), te_string("outgoing")));
  element->push_column("Encrypted:", display::text_element_branch3(std::mem_fun(&torrent::Peer::is_encrypted), te_string("yes"), std::mem_fun(&torrent::Peer::is_obfuscated), te_string("handshake"), te_string("no")));

  element->push_back("");
  element->push_column("Snubbed:", display::text_element_branch(std::mem_fun(&torrent::Peer::is_snubbed), te_string("yes"), te_string("no")));
  element->push_column("Done:",    display::text_element_value_slot(rak::on(std::mem_fun(&torrent::Peer::bitfield), std::ptr_fun(&te_bitfield_percentage))));
  element->push_column("Rate:",
                       display::text_element_value_slot(rak::on(std::mem_fun(&torrent::Peer::up_rate), std::mem_fun(&torrent::Rate::rate)), value_base::flag_kb), " KB / ",
                       display::text_element_value_slot(rak::on(std::mem_fun(&torrent::Peer::down_rate), std::mem_fun(&torrent::Rate::rate)), value_base::flag_kb), " KB");
  element->push_column("Total:",
                       display::text_element_value_slot(rak::on(std::mem_fun(&torrent::Peer::up_rate), std::mem_fun(&torrent::Rate::total)), value_base::flag_xb), " / ",
                       display::text_element_value_slot(rak::on(std::mem_fun(&torrent::Peer::down_rate), std::mem_fun(&torrent::Rate::total)), value_base::flag_xb));

  element->set_column_width(element->column_width() + 1);

  return element;
}

void
ElementPeerList::activate(display::Frame* frame, bool focus) {
