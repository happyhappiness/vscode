(i = 0; i < sizeof(address->phys_addr); i++) {
    if (address->phys_addr[i] != 0)
      return 0;
  }