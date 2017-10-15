char*
print_client_version(char* first, char* last, const torrent::ClientInfo& clientInfo) {
  switch (torrent::ClientInfo::version_size(clientInfo.type())) {
  case 4:
    return print_buffer(first, last, "%s %hhu.%hhu.%hhu.%hhu",
                        clientInfo.short_description(),
                        clientInfo.version()[0], clientInfo.version()[1],
                        clientInfo.version()[2], clientInfo.version()[3]);
  case 3:
    return print_buffer(first, last, "%s %hhu.%hhu.%hhu",
                        clientInfo.short_description(),
                        clientInfo.version()[0], clientInfo.version()[1],
                        clientInfo.version()[2]);
  default:
    return print_buffer(first, last, "%s", clientInfo.short_description());
  }
}