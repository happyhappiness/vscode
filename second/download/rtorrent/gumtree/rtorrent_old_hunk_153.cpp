
  std::memcpy(itr->first, key, keySize);
  itr->second = name;
}

char*
ClientInfo::print(char* first, char* last, const char* id) {

  if (id[0] == '-' && id[7] == '-' &&
      std::isalpha(id[1]) && std::isalpha(id[2]) &&
      std::isxdigit(id[3]) && std::isxdigit(id[4]) && std::isxdigit(id[5]) && std::isxdigit(id[6])) {
    // TYPE_AZUREUS.

    iterator itr = std::find_if(m_containers[TYPE_AZUREUS].begin(), m_containers[TYPE_AZUREUS].end(),
				client_info_equal(id + 1, sizeof_key(TYPE_AZUREUS)));

    if (itr != m_containers[TYPE_AZUREUS].end())
      first = print_buffer(first, last, "%s %hhu.%hhu.%hhu.%hhu", itr->second,
			   rak::hexchar_to_value(id[3]), rak::hexchar_to_value(id[4]),
			   rak::hexchar_to_value(id[5]), rak::hexchar_to_value(id[6]));
    
