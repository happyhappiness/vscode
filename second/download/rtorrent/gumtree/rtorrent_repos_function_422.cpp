void
ViewManager::sort(const std::string& name, uint32_t timeout) {
  iterator viewItr = find_throw(name);

  if ((*viewItr)->last_changed() + rak::timer::from_seconds(timeout) > cachedTime)
    return;

  // Should we rename sort, or add a seperate function?
  (*viewItr)->filter();

  (*viewItr)->sort();
}