void
initialize_xmlrpc() {
  rpc::xmlrpc.initialize();
  rpc::xmlrpc.set_slot_find_download(rak::mem_fn(control->core()->download_list(), &core::DownloadList::find_hex_ptr));
  rpc::xmlrpc.set_slot_find_file(rak::ptr_fn(&xmlrpc_find_file));
  rpc::xmlrpc.set_slot_find_tracker(rak::ptr_fn(&xmlrpc_find_tracker));

  unsigned int count = 0;

  for (rpc::CommandMap::const_iterator itr = rpc::commands.begin(), last = rpc::commands.end(); itr != last; itr++) {
    if (!(itr->second.m_flags & rpc::CommandMap::flag_public_xmlrpc))
      continue;

    switch (itr->second.m_target) {
    case rpc::CommandMap::target_generic:  rpc::xmlrpc.insert_command(itr->first, itr->second.m_parm, itr->second.m_doc, rpc::XmlRpc::call_generic); break;
    case rpc::CommandMap::target_download: rpc::xmlrpc.insert_command(itr->first, itr->second.m_parm, itr->second.m_doc, rpc::XmlRpc::call_download); break;
    case rpc::CommandMap::target_file:     rpc::xmlrpc.insert_command(itr->first, itr->second.m_parm, itr->second.m_doc, rpc::XmlRpc::call_file); break;
    case rpc::CommandMap::target_tracker:  rpc::xmlrpc.insert_command(itr->first, itr->second.m_parm, itr->second.m_doc, rpc::XmlRpc::call_tracker); break;
    default: throw torrent::internal_error("XMLRPC: Bad entry.");
    }

    count++;
  }

  char buffer[128];
  sprintf(buffer, "XMLRPC initialized with %u functions.", count);

  control->core()->push_log(buffer);
}