void
OptionParser::call_int_pair(SlotIntPair slot, const std::string& arg) {
  int a, b;

  if (std::sscanf(arg.c_str(), "%u-%u", &a, &b) != 2)
    throw std::runtime_error("Invalid argument, \"" + arg + "\" should be \"a-b\"");

  slot(a, b);
}