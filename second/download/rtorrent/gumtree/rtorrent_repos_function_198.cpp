void
CommandMap::insert_tracker(key_type key, Command* variable, tracker_slot targetSlot, int flags, const char* parm, const char* doc) {
  iterator itr = insert(key, variable, flags, parm, doc);

  itr->second.m_target      = target_tracker;
  itr->second.m_trackerSlot = targetSlot;
}