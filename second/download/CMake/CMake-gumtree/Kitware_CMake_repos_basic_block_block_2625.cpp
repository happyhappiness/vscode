{
#ifdef _WIN32
  cmsys::ConsoleBuf::Manager consoleOut(std::cout);
#endif
  if (argc <= 2) {
    std::cout << "Usage: testEncoding <encoding> <file>" << std::endl;
    return 1;
  }
  const std::string encoding(argv[1]);
#ifdef _WIN32
  if (encoding == "UTF8") {
    setEncoding(consoleOut, CP_UTF8);
  } else if (encoding == "ANSI") {
    setEncoding(consoleOut, CP_ACP);
  } else if (encoding == "OEM") {
    setEncoding(consoleOut, CP_OEMCP);
  } // else AUTO
#endif
  cmsys::ifstream file(argv[2]);
  if (!file.is_open()) {
    std::cout << "Failed to open file: " << argv[2] << std::endl;
    return 2;
  }
  std::string text((std::istreambuf_iterator<char>(file)),
                   std::istreambuf_iterator<char>());
  std::cout << text;
  return 0;
}