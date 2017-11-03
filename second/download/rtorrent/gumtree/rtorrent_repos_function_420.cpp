ViewManager::iterator
ViewManager::find_throw(const std::string& name) {
  iterator itr = std::find_if(begin(), end(), rak::equal(name, std::mem_fun(&View::name)));

  if (itr == end())
    throw torrent::input_error("Could not find view: " + name);

  return itr;
}