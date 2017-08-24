(!wstr.empty() && (str != str2 || strcmp(c_str2, str.c_str()))) {
      std::cout << "converted string was different: " << str2 << std::endl;
      std::cout << "converted string was different: " << c_str2 << std::endl;
      ret++;
    }