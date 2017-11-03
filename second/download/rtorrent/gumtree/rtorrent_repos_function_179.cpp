std::string
convert_list_to_string(const torrent::Object& src) {
  if (!src.is_list())
    throw torrent::internal_error("convert_list_to_string(...) !src->is_list().");

  return convert_list_to_string(src.as_list().begin(), src.as_list().end());
}