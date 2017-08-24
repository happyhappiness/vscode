{
#if defined(_WIN32)
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
#elif defined(__BEOS__) || defined(__HAIKU__)
  disable_debugger(1);
#endif
  int res = 0;
  if (argc == 3) {
    // User specify a libname and symbol to check.
    res = TestDynamicLoader(argv[1], argv[2], 1, 1, 1);
    return res;
  }

// dlopen() on Syllable before 11/22/2007 doesn't return 0 on error
#ifndef __SYLLABLE__
  // Make sure that inexistent lib is giving correct result
  res += TestDynamicLoader("azerty_", "foo_bar", 0, 0, 0);
  // Make sure that random binary file cannot be assimilated as dylib
  res += TestDynamicLoader(TEST_SYSTEMTOOLS_SOURCE_DIR "/testSystemTools.bin",
                           "wp", 0, 0, 0);
#endif

#ifdef __linux__
  // This one is actually fun to test, since dlopen is by default
  // loaded...wonder why :)
  res += TestDynamicLoader("foobar.lib", "dlopen", 0, 1, 0);
  res += TestDynamicLoader("libdl.so", "dlopen", 1, 1, 1);
  res += TestDynamicLoader("libdl.so", "TestDynamicLoader", 1, 0, 1);
#endif
  // Now try on the generated library
  std::string libname = GetLibName(KWSYS_NAMESPACE_STRING "TestDynload");
  res += TestDynamicLoader(libname.c_str(), "dummy", 1, 0, 1);
  res += TestDynamicLoader(libname.c_str(), "TestDynamicLoaderSymbolPointer",
                           1, 1, 1);
  res += TestDynamicLoader(libname.c_str(), "_TestDynamicLoaderSymbolPointer",
                           1, 0, 1);
  res += TestDynamicLoader(libname.c_str(), "TestDynamicLoaderData", 1, 1, 1);
  res += TestDynamicLoader(libname.c_str(), "_TestDynamicLoaderData", 1, 0, 1);

  return res;
}