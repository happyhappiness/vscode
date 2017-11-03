extent_type result_length(const char** result) {
    if (m_flags & flag_fixed_width)
      return m_length;
    else
      return std::min<extent_type>(std::strlen(*result), m_length);
  }