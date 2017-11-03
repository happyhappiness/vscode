char*
print_address(char* first, char* last, const rak::socket_address* sa) {
  if (!sa->address_c_str(first, last - first))
    return first;

  return std::find(first, last, '\0');
}