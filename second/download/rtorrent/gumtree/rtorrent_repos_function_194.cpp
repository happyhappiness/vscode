void
CommandMap::insert_generic(key_type key, Command* variable, generic_slot targetSlot, int flags, const char* parm, const char* doc) {
  iterator itr = insert(key, variable, flags, parm, doc);

  itr->second.m_target      = target_generic;
  itr->second.m_genericSlot = targetSlot;
}