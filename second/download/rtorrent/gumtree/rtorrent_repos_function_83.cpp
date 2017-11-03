torrent::Object
apply_download_list(const torrent::Object& rawArgs) {
  const torrent::Object::list_type&          args    = rawArgs.as_list();
  torrent::Object::list_type::const_iterator argsItr = args.begin();

  core::ViewManager* viewManager = control->view_manager();
  core::ViewManager::iterator viewItr;

  if (argsItr != args.end() && !argsItr->as_string().empty())
    viewItr = viewManager->find((argsItr++)->as_string());
  else
    viewItr = viewManager->find("default");

  if (viewItr == viewManager->end())
    throw torrent::input_error("Could not find view.");

  torrent::Object result(torrent::Object::TYPE_LIST);
  torrent::Object::list_type& resultList = result.as_list();

  for (core::View::const_iterator itr = (*viewItr)->begin_visible(), last = (*viewItr)->end_visible(); itr != last; itr++) {
    const torrent::HashString* hashString = &(*itr)->download()->info_hash();

    resultList.push_back(rak::transform_hex(hashString->begin(), hashString->end()));
  }

  return result;
}