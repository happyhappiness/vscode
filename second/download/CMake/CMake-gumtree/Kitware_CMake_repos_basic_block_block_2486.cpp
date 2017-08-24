{
    DWORD lastError = GetLastError();
    std::cerr << "CreateProcess(" << kwsys::Encoding::ToNarrow(cmd) << ")"
              << std::endl;
    displayError(lastError);
  }