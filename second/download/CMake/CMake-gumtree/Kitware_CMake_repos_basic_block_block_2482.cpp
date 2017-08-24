{
    std::cerr << "Error message: " << kwsys::Encoding::ToNarrow(message)
              << std::endl;
    HeapFree(GetProcessHeap(), 0, message);
  }