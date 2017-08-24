{
  std::cerr << "Testing: " << libname << std::endl;
  kwsys::DynamicLoader::LibraryHandle l =
    kwsys::DynamicLoader::OpenLibrary(libname);
  // If result is incompatible with expectation just fails (xor):
  if ((r1 && !l) || (!r1 && l)) {
    std::cerr << kwsys::DynamicLoader::LastError() << std::endl;
    return 1;
  }
  kwsys::DynamicLoader::SymbolPointer f =
    kwsys::DynamicLoader::GetSymbolAddress(l, symbol);
  if ((r2 && !f) || (!r2 && f)) {
    std::cerr << kwsys::DynamicLoader::LastError() << std::endl;
    return 1;
  }
#ifndef __APPLE__
  int s = kwsys::DynamicLoader::CloseLibrary(l);
  if ((r3 && !s) || (!r3 && s)) {
    std::cerr << kwsys::DynamicLoader::LastError() << std::endl;
    return 1;
  }
#else
  (void)r3;
#endif
  return 0;
}