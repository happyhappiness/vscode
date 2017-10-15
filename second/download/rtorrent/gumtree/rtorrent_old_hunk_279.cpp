
  (*m_view->focus())->set_priority((*m_view->focus())->priority() - 1);
  m_window->mark_dirty();
}

void
ElementDownloadList::receive_change_view(const std::string& name) {
  core::ViewManager::iterator itr = control->view_manager()->find(name);

  if (itr == control->view_manager()->end()) {
    control->core()->push_log_std("Could not find view \"" + name + "\".");
    return;
