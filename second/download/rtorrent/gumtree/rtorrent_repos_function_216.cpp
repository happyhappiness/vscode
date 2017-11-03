int
parse_count_escaped(const char* first, const char* last) {
  int escaped = 0;

  while (last != first && *--last == '\\')
    escaped++;

  return escaped;
}