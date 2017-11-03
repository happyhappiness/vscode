torrent::Object
apply_view_list(const torrent::Object&) {
  torrent::Object rawResult(torrent::Object::TYPE_LIST);
  torrent::Object::list_type& result = rawResult.as_list();

  for (core::ViewManager::const_iterator itr = control->view_manager()->begin(), last = control->view_manager()->end(); itr != last; itr++)
    result.push_back((*itr)->name());

  return rawResult;
}