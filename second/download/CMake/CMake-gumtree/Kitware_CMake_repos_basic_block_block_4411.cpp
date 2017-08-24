r(iface=head; iface != NULL; iface=iface->ifa_next) {
      if(strcasecompare(iface->ifa_name, interf)) {
        result = TRUE;
        break;
      }
    }