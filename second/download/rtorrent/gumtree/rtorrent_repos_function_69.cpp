torrent::Object
apply_f_path_components(torrent::File* file) {
  torrent::Object resultRaw(torrent::Object::TYPE_LIST);
  torrent::Object::list_type& result = resultRaw.as_list();

  for (torrent::Path::const_iterator itr = file->path()->begin(), last = file->path()->end(); itr != last; itr++)
    result.push_back(*itr);

  return resultRaw;
}