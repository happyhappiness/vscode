    return rtrim(line, CRLF);
  }

  template <typename T>
  T value_from_string(const string & data)
  {
    T value;

    istringstream iss(data);
    iss >> value;
    if (iss.fail()) 
      throw redis::value_error("invalid number");

    return value;
  }
