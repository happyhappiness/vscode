int
OptionParser::process(int argc, char** argv) {
  int c;
  std::string optString = create_optstring();

  while ((c = getopt(argc, argv, optString.c_str())) != -1)
    if (c == '?')
      throw std::runtime_error("Invalid/unknown option flag \"-" + std::string(1, (char)optopt) + "\". See rtorrent -h for more information.");
    else
      call(c, optarg ? optarg : "");

  return optind;
}