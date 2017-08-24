{
    ret.insert(static_cast<std::string::size_type>(0),
               static_cast<std::string::size_type>(1), '\"');
    ret.append(1, '\"');
  }