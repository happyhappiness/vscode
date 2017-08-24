return prefix_address_data[i] ==
      (address_data[i] & (0xff << (8 - prefix_len % 8)));