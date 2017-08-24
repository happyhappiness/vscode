{
    // Leave the .c_str() on this one.  It is needed on OpenWatcom.
    std::cerr << "Could not open plugin \"" << libName.c_str() << "\"!"
              << std::endl;
    return 1;
  }