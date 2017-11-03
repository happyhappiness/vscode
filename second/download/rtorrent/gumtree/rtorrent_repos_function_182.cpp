int64_t
convert_to_value(const torrent::Object& src, int base, int unit) {
  int64_t value;

  if (!convert_to_value_nothrow(src, &value, base, unit))
    throw torrent::input_error("Not convertible to a value.");

  return value;
}