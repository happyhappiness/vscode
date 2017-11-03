virtual int64_t value(void* object) {
    if (object == NULL)
      return 0;

    return m_slot(reinterpret_cast<arg1_type>(object));
  }