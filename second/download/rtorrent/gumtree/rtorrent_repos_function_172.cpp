const char*
parse_value(const char* src, int64_t* value, int base, int unit) {
  const char* last = parse_value_nothrow(src, value, base, unit);

  if (last == src)
    throw torrent::input_error("Could not convert string to value.");

  return last;
}