{
  std::string libName = EXAMPLE_EXE_PLUGIN_DIR CONFIG_DIR "/";
  libName += kwsys::DynamicLoader::LibPrefix();
  libName += "example_mod_1";
  libName += kwsys::DynamicLoader::LibExtension();
  kwsys::DynamicLoader::LibraryHandle handle =
    kwsys::DynamicLoader::OpenLibrary(libName.c_str());
  if (!handle) {
    // Leave the .c_str() on this one.  It is needed on OpenWatcom.
    std::cerr << "Could not open plugin \"" << libName.c_str() << "\"!"
              << std::endl;
    return 1;
  }
  kwsys::DynamicLoader::SymbolPointer sym =
    kwsys::DynamicLoader::GetSymbolAddress(handle, "example_mod_1_function");
  if (!sym) {
    std::cerr << "Could not get plugin symbol \"example_mod_1_function\"!"
              << std::endl;
    return 1;
  }
#ifdef __WATCOMC__
  int(__cdecl * f)(int) = (int(__cdecl*)(int))(sym);
#else
  int (*f)(int) = reinterpret_cast<int (*)(int)>(sym);
#endif
  if (f(456) != (123 + 456)) {
    std::cerr << "Incorrect return value from plugin!" << std::endl;
    return 1;
  }
  kwsys::DynamicLoader::CloseLibrary(handle);
  return 0;
}