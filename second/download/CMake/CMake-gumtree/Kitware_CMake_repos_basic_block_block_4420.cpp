f((res == IF2IP_NOT_FOUND) &&
                strcasecompare(iface->ifa_name, interf)) {
          res = IF2IP_AF_NOT_SUPPORTED;
        }