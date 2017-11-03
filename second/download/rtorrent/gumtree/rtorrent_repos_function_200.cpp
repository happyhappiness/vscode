const CommandMap::mapped_type
CommandMap::call_command(key_type key, const mapped_type& arg, target_type target) {
  const_iterator itr = base_type::find(key);

  if (itr == base_type::end())
    throw torrent::input_error("Command \"" + std::string(key) + "\" does not exist.");

  if ((itr->second.m_target != target.first && itr->second.m_target != target_generic) ||
      (itr->second.m_target != target_generic && target.second == NULL))
    throw torrent::input_error("Command type mis-match.");

  // This _should_ be optimized int just two calls.
  switch (itr->second.m_target) {
  case target_generic:  return itr->second.m_genericSlot(itr->second.m_variable, arg);
  case target_download: return itr->second.m_downloadSlot(itr->second.m_variable, (core::Download*)target.second, arg);
  case target_file:     return itr->second.m_fileSlot(itr->second.m_variable, (torrent::File*)target.second, arg);
  case target_peer:     return itr->second.m_peerSlot(itr->second.m_variable, (torrent::Peer*)target.second, arg);
  case target_tracker:  return itr->second.m_trackerSlot(itr->second.m_variable, (torrent::Tracker*)target.second, arg);
  default: throw torrent::internal_error("CommandMap::call_command(...) Invalid target.");
  }
}