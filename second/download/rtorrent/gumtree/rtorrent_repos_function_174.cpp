bool
parse_whole_value_nothrow(const char* src, int64_t* value, int base, int unit) {
  const char* last = parse_value_nothrow(src, value, base, unit);

  if (last == src || *parse_skip_wspace(last) != '\0')
    return false;

  return true;
}