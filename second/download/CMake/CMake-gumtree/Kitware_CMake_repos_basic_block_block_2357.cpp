{
    long t;
    char* endptr;
    t = strtol(columns.c_str(), &endptr, 0);
    if (endptr && !*endptr && (t > 0) && (t < 1000)) {
      width = static_cast<int>(t);
    }
  }