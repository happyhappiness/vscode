f((port < 0) || (port > 0xffff)) {
      /* Single unix standard says port numbers are 16 bits long */
      failf(data, "Port number out of range");
      return CURLE_URL_MALFORMAT;
    }