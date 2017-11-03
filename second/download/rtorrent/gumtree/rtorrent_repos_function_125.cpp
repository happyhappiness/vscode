bool
OptionParser::has_flag(char flag, int argc, char** argv) {
  char options[3] = { '-', flag, '\0' };

  return std::find_if(argv, argv + argc, std::not1(std::bind1st(std::ptr_fun(&std::strcmp), options))) != argv + argc;
}