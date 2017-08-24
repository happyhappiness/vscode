{
    char* data = new char[length];
    int r =
      WideCharToMultiByte(KWSYS_ENCODING_DEFAULT_CODEPAGE, 0, str.c_str(),
                          int(str.size()), data, length, NULL, NULL);
    if (r > 0) {
      nstr = std::string(data, length);
    }
    delete[] data;
  }