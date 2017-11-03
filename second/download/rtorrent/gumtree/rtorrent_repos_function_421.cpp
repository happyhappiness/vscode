inline ViewManager::sort_list
ViewManager::build_sort_list(const sort_args& args) {
  View::sort_list sortList;
  sortList.reserve(args.size());

  for (sort_args::const_iterator itr = args.begin(), last = args.end(); itr != last; ++itr) {
    sort_map::const_iterator sortItr = m_sort.find(itr->c_str());

    if (sortItr == m_sort.end())
      throw torrent::input_error("Invalid sorting identifier.");

    sortList.push_back(sortItr->second);
  }

  return sortList;
}