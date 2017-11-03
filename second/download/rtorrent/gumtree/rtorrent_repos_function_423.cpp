void
ViewManager::set_sort_new(const std::string& name, const sort_args& sort) {
  iterator viewItr = find_throw(name);

  (*viewItr)->set_sort_new(build_sort_list(sort));
}