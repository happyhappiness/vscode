			   rak::hexchar_to_value(id[5]), rak::hexchar_to_value(id[6]));

  } else if (std::isalpha(id[0]) && id[4] == '-' &&
	     std::isxdigit(id[1]) && std::isxdigit(id[2]) && std::isxdigit(id[3])) {
    // TYPE_THREE_COMPACT.

    const_iterator itr = std::find_if(m_containers[TYPE_COMPACT].begin(), m_containers[TYPE_COMPACT].end(),
                                      client_info_equal(id, sizeof_key(TYPE_COMPACT)));

    if (itr != m_containers[TYPE_COMPACT].end())
      first = print_buffer(first, last, "%s %hhu.%hhu.%hhu", itr->second,
			   rak::hexchar_to_value(id[1]), rak::hexchar_to_value(id[2]), rak::hexchar_to_value(id[3]));
    
    else
