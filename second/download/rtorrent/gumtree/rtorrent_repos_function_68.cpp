torrent::Object
apply_f_path(torrent::File* file) {
  if (file->path()->empty())
    return std::string();

  torrent::Object resultRaw(*file->path()->begin());
  torrent::Object::string_type& result = resultRaw.as_string();

  for (torrent::Path::const_iterator itr = ++file->path()->begin(), last = file->path()->end(); itr != last; itr++)
    result += '/' + *itr;

  return resultRaw;
}