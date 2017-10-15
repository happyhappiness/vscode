 
   (*m_view->focus())->set_priority((*m_view->focus())->priority() - 1);
   m_window->mark_dirty();
 }
 
 void
+ElementDownloadList::receive_cycle_throttle() {
+  if (m_view->focus() == m_view->end_visible())
+    return;
+
+  core::Download* download = *m_view->focus();
+  if (download->is_active()) {
+    control->core()->push_log("Cannot change throttle on active download.");
+    return;
+  }
+
+  core::ThrottleMap::const_iterator itr = control->core()->throttles().find(download->bencode()->get_key("rtorrent").get_key_string("throttle_name"));
+  if (itr == control->core()->throttles().end())
+    itr = control->core()->throttles().begin();
+  else
+    ++itr;
+
+  download->set_throttle_name(itr == control->core()->throttles().end() ? std::string() : itr->first);
+  m_window->mark_dirty();
+}
+
+void
 ElementDownloadList::receive_change_view(const std::string& name) {
   core::ViewManager::iterator itr = control->view_manager()->find(name);
 
   if (itr == control->view_manager()->end()) {
     control->core()->push_log_std("Could not find view \"" + name + "\".");
     return;
