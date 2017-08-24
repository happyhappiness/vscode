(std::vector<std::string>::iterator i = path.begin() + old_size;
       i != path.end(); ++i) {
    SystemTools::ConvertToUnixSlashes(*i);
  }