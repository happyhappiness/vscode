void
CommandMap::insert_download(key_type key, Command* variable, download_slot targetSlot, int flags, const char* parm, const char* doc) {
  iterator itr = insert(key, variable, flags, parm, doc);

  itr->second.m_target       = target_download;
  itr->second.m_downloadSlot = targetSlot;
}