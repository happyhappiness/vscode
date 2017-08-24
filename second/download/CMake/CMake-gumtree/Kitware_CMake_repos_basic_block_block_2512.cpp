{
    std::wstring wstr = kwsys::Encoding::ToWide(*it);
    std::string str = kwsys::Encoding::ToNarrow(wstr);
    std::string s(*it);
    std::replace(s.begin(), s.end(), '\0', ' ');
    std::cout << "'" << s << "' (" << it->size() << ")" << std::endl;
    if (str != *it) {
      std::replace(str.begin(), str.end(), '\0', ' ');
      std::cout << "string with null was different: '" << str << "' ("
                << str.size() << ")" << std::endl;
      ret++;
    }
  }