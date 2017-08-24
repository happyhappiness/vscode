{
      std::replace(str.begin(), str.end(), '\0', ' ');
      std::cout << "string with null was different: '" << str << "' ("
                << str.size() << ")" << std::endl;
      ret++;
    }