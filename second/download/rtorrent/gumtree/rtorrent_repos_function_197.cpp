void
CommandMap::insert_peer(key_type key, Command* variable, peer_slot targetSlot, int flags, const char* parm, const char* doc) {
  iterator itr = insert(key, variable, flags, parm, doc);

  itr->second.m_target   = target_peer;
  itr->second.m_peerSlot = targetSlot;
}