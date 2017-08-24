{
    std::string str = kwsys::Encoding::ToNarrow(std::wstring(
      UnicodeTestString, sizeof(UnicodeTestString) / sizeof(wchar_t) - 1));
    std::cout << str << std::endl;
    std::cerr << str << std::endl;
  }