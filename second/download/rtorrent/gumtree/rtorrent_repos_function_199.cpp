void
CommandMap::insert(key_type key, const command_map_data_type src) {
  iterator itr = base_type::find(key);

  if (itr != base_type::end())
    throw torrent::internal_error("CommandMap::insert(...) tried to insert an already existing key.");

  itr = base_type::insert(itr, value_type(key, command_map_data_type(src.m_variable, src.m_flags | flag_dont_delete, src.m_parm, src.m_doc)));

  itr->second.m_target       = src.m_target;

  // This _should_ be optimized int just one assignment.
  switch (itr->second.m_target) {
  case target_generic:  itr->second.m_genericSlot  = src.m_genericSlot; break;
  case target_download: itr->second.m_downloadSlot = src.m_downloadSlot; break;
  case target_file:     itr->second.m_fileSlot     = src.m_fileSlot; break;
  case target_peer:     itr->second.m_peerSlot     = src.m_peerSlot; break;
  case target_tracker:  itr->second.m_trackerSlot  = src.m_trackerSlot; break;
  default: throw torrent::internal_error("CommandMap::insert(...) Invalid target.");
  }
}