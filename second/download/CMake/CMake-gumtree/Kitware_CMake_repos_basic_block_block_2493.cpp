{
    DWORD lastError = GetLastError();
    std::cerr << "CreateFile(" << kwsys::Encoding::ToNarrow(fileName) << ")"
              << std::endl;
    displayError(lastError);
  }