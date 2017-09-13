unsigned long unsigned_number_from_string(const string & data)
  {
    errno = 0;

    unsigned long value = strtoul(data.c_str(), NULL, 10);

    if (value == ULONG_MAX && errno == ERANGE)
      throw redis::value_error("invalid number; out of range of long");

    if (value == 0 && errno == EINVAL)
      throw redis::value_error("invalid number; unrecognized format");

    return value;
  }