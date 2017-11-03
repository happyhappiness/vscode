void
OptionParser::call_option_list(SlotStringPair slot, const std::string& arg) {
  std::string::const_iterator itr = arg.begin();

  while (itr != arg.end()) {
    std::string::const_iterator last = std::find(itr, arg.end(), ',');
    std::string::const_iterator opt = std::find(itr, last, '=');

    if (opt == itr || opt == last)
      throw std::logic_error("Invalid argument, \"" + arg + "\" should be \"key1=opt1,key2=opt2,...\"");

    slot(std::string(itr, opt), std::string(opt + 1, last));

    if (last == arg.end())
      break;

    itr = ++last;
  }
}