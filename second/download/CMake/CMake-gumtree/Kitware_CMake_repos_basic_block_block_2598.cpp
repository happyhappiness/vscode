{
  cmsys::Encoding::CommandLineArguments args =
    cmsys::Encoding::CommandLineArguments::Main(ac, av);
  int argc = args.argc();
  const char* const* argv = args.argv();

  std::string exename = argv[0];
  std::string logarg;
  bool nextarg = false;

  if (exename.find("valgrind") != exename.npos) {
    logarg = "--log-file=";
  } else if (exename.find("purify") != exename.npos) {
#ifdef _WIN32
    logarg = "/SAVETEXTDATA=";
#else
    logarg = "-log-file=";
#endif
  } else if (exename.find("BC") != exename.npos) {
    nextarg = true;
    logarg = "/X";
  }

  if (!logarg.empty()) {
    std::string logfile;
    for (int i = 1; i < argc; i++) {
      std::string arg = argv[i];
      if (arg.find(logarg) == 0) {
        if (nextarg) {
          if (i == argc - 1) {
            return 1; // invalid command line
          }
          logfile = argv[i + 1];
        } else {
          logfile = arg.substr(logarg.length());
        }
        // keep searching, it may be overridden later to provoke an error
      }
    }

    if (!logfile.empty()) {
      cmSystemTools::Touch(logfile, true);
    }
  }

  return RETVAL;
}