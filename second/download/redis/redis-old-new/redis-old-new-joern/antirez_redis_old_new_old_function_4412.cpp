redis::client::int_type number_from_string(const string & data)
  {
    errno = 0;

    redis::client::int_type value = strtol(data.c_str(), NULL, 10);

    if ((value == LONG_MAX || value == LONG_MIN) && errno == ERANGE)
      throw redis::value_error("invalid number; out of range of long");

    if (value == 0 && errno == EINVAL)
      throw redis::value_error("invalid number; unrecognized format");

    return value;
  }