{
        snprintf(buf + len, sizeof(buf) - len,
                 ": %s", (char*) status_string.value);
      len += status_string.length;
    }