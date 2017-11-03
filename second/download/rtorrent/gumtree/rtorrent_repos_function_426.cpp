void
ViewManager::set_filter(const std::string& name, const filter_args& args) {
  iterator viewItr = find_throw(name);

  (*viewItr)->set_filter(build_filter_list(args));
  (*viewItr)->filter();
}