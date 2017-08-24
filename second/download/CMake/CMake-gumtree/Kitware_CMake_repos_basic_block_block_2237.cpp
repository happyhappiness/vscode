{
    failures.push_back(self);
    std::ostringstream msg;
    msg << "Can not find the command line program ";
    if (exeName) {
      msg << exeName;
    }
    msg << "\n";
    if (argv0) {
      msg << "  argv[0] = \"" << argv0 << "\"\n";
    }
    msg << "  Attempted paths:\n";
    std::vector<std::string>::iterator i;
    for (i = failures.begin(); i != failures.end(); ++i) {
      msg << "    \"" << *i << "\"\n";
    }
    errorMsg = msg.str();
    return false;
  }