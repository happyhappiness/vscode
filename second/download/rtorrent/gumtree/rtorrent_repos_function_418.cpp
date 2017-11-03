ViewManager::iterator
ViewManager::insert(const std::string& name) {
  if (find(name) != end())
    throw torrent::internal_error("ViewManager::insert(...) name already inserted.");

  View* view = new View();
  view->initialize(name, m_list);

  return base_type::insert(end(), view);
}