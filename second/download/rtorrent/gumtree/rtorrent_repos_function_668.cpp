char
WindowDownloadTransferList::key_id(torrent::BlockTransfer::key_type key) {
  uint32_t oldestTime = cachedTime.seconds();
  assigned_vector::iterator oldestItr = m_assigned.begin();

  for (assigned_vector::iterator itr = m_assigned.begin(), last = m_assigned.end(); itr != last; ++itr) {
    if (itr->m_key == key) {
      itr->m_last = cachedTime.seconds();
      return itr->m_id;
    }

    if (itr->m_last < oldestTime) {
      oldestTime = itr->m_last;
      oldestItr = itr;
    }
  }

  if (oldestItr == m_assigned.end() || cachedTime.seconds() - oldestTime <= 60) {
    // We didn't find any previously used id's to take over.

    // Return 'f' when we run out of characters.
    if (m_assigned.size() >= ('Z' - 'A'))
      return 'Z';

    char id = 'A' + m_assigned.size();

    m_assigned.push_back(assigned_type(key, cachedTime.seconds(), id));
    return id;

  } else {
    return oldestItr->m_id;
  }
}