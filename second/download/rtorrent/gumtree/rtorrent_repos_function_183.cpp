bool
convert_to_value_nothrow(const torrent::Object& src, int64_t* value, int base, int unit) {
  const torrent::Object& unpacked = (src.is_list() && src.as_list().size() == 1) ? src.as_list().front() : src;

  switch (unpacked.type()) {
  case torrent::Object::TYPE_VALUE:
    *value = unpacked.as_value();
    break;

  case torrent::Object::TYPE_STRING:
    if (parse_skip_wspace(parse_value(unpacked.as_string().c_str(), value, base, unit),
                          unpacked.as_string().c_str() + unpacked.as_string().size()) != unpacked.as_string().c_str() + unpacked.as_string().size())
      return false;

    break;

  case torrent::Object::TYPE_NONE:
    *value = 0;
    break;

  default:
    return false;
  }
  
  return true;
}