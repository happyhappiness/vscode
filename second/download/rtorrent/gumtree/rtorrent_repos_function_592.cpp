char*
TextElementString::copy_string(char* first, char* last, void* object) {
  extent_type length = std::min<extent_type>(last - first, m_string.size());
  
  std::memcpy(first, m_string.c_str(), length);

  return first + length;
}