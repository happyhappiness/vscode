bool Curl_if_is_interface_name(const char *interf)
{
  bool result = FALSE;

  struct ifaddrs *iface, *head;

  if(getifaddrs(&head) >= 0) {
    for(iface=head; iface != NULL; iface=iface->ifa_next) {
      if(curl_strequal(iface->ifa_name, interf)) {
        result = TRUE;
        break;
      }
    }
    freeifaddrs(head);
  }
  return result;
}