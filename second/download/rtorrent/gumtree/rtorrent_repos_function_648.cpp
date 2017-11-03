inline char*
print_address(char* first, char* last, const sockaddr* sa) {
  return print_address(first, last, rak::socket_address::cast_from(sa));
}