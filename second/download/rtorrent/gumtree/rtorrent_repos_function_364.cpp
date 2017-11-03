void
ElementPeerList::update_itr() {
  m_windowList->mark_dirty();
  m_elementInfo->set_object(m_listItr != m_list.end() ? &*m_listItr : NULL);
}