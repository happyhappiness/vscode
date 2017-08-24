{
    IP_ADAPTER_UNICAST_ADDRESS* unicast_address;
    int name_size;

    /* Interfaces that are not 'up' should not be reported. Also skip */
    /* interfaces that have no associated unicast address, as to avoid */
    /* allocating space for the name for this interface. */
    if (adapter->OperStatus != IfOperStatusUp ||
        adapter->FirstUnicastAddress == NULL)
      continue;

    /* Compute the size of the interface name. */
    name_size = WideCharToMultiByte(CP_UTF8,
                                    0,
                                    adapter->FriendlyName,
                                    -1,
                                    NULL,
                                    0,
                                    NULL,
                                    FALSE);
    if (name_size <= 0) {
      uv__free(win_address_buf);
      return uv_translate_sys_error(GetLastError());
    }
    uv_address_buf_size += name_size;

    /* Count the number of addresses associated with this interface, and */
    /* compute the size. */
    for (unicast_address = (IP_ADAPTER_UNICAST_ADDRESS*)
                           adapter->FirstUnicastAddress;
         unicast_address != NULL;
         unicast_address = unicast_address->Next) {
      count++;
      uv_address_buf_size += sizeof(uv_interface_address_t);
    }
  }