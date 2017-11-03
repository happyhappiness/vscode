void
CommandMap::insert_file(key_type key, Command* variable, file_slot targetSlot, int flags, const char* parm, const char* doc) {
  iterator itr = insert(key, variable, flags, parm, doc);

  itr->second.m_target   = target_file;
  itr->second.m_fileSlot = targetSlot;
}