char*
TextElementCString::copy_string(char* first, char* last, void* object) {
  extent_type length = std::min<extent_type>(last - first, m_length);

  std::memcpy(first, m_string, length);

  return first + length;
}