{
    address_data = (uint8_t*) &(((struct sockaddr_in6 *) address)->sin6_addr);
    prefix_address_data =
      (uint8_t*) &(((struct sockaddr_in6 *) prefix_address)->sin6_addr);
  }