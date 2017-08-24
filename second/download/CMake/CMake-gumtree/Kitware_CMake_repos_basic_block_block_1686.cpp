{
    size_t at = file.rfind("/");
    if (at != std::string::npos) {
      file = file.substr(at + 1);
    }
  }