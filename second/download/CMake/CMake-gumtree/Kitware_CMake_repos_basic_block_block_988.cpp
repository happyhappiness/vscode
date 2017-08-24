{
    wchar_t* wdata = new wchar_t[wlength];
    int r = MultiByteToWideChar(KWSYS_ENCODING_DEFAULT_CODEPAGE, 0, str.data(),
                                int(str.size()), wdata, wlength);
    if (r > 0) {
      wstr = std::wstring(wdata, wlength);
    }
    delete[] wdata;
  }