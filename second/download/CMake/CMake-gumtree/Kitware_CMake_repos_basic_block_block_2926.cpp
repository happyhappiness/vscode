{
    std::vector<wchar_t> buffer(size + 1);
    MsiGetPropertyW(msi_handle, name.c_str(), &buffer[0], &size);
    return std::wstring(&buffer[0]);
  }