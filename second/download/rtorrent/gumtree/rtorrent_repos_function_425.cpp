inline ViewManager::filter_list
ViewManager::build_filter_list(const filter_args& args) {
  View::filter_list filterList;
  filterList.reserve(args.size());

  for (filter_args::const_iterator itr = args.begin(), last = args.end(); itr != last; ++itr) {
    filter_map::const_iterator filterItr = m_filter.find(itr->c_str());

    if (filterItr == m_filter.end())
      throw torrent::input_error("Invalid filtering identifier.");

    filterList.push_back(filterItr->second);
  }

  return filterList;
}