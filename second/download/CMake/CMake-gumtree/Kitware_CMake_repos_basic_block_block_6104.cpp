f(rest[0]) {
      failf(data, "Port number ended with '%c'", rest[0]);
      return CURLE_URL_MALFORMAT;
    }