virtual char* copy_string(char* first, char* last, void* object) {
    if (object == NULL)
      return first;

    result_type result = m_slot(reinterpret_cast<arg1_type>(object));
    extent_type length = std::min<extent_type>(result_length(&result), last - first);

    std::memcpy(first, result_buffer(&result), length);

    return first + length;
  }