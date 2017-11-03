ViewManager::iterator
ViewManager::find(const std::string& name) {
  return std::find_if(begin(), end(), rak::equal(name, std::mem_fun(&View::name)));
}