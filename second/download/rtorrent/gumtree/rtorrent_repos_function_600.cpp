inline char*
print_buffer(char* first, char* last, const char* format) {
  if (first >= last)
    return first;

  int s = snprintf(first, last - first, format);

  if (s < 0)
    return first;
  else
    return std::min(first + s, last);
}