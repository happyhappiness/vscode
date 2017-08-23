static int process(const std::string& srcfilename, const std::string& dfile,
                   const std::string& objfile, const std::string& prefix,
                   const std::string& cmd, const std::string& dir = "",
                   bool quiet = false)
{
  std::string output;
  // break up command line into a vector
  std::vector<std::string> args;
  cmSystemTools::ParseWindowsCommandLine(cmd.c_str(), args);
  // convert to correct vector type for RunSingleCommand
  std::vector<std::string> command;
  for (std::vector<std::string>::iterator i = args.begin(); i != args.end();
       ++i) {
    command.push_back(*i);
  }
  // run the command
  int exit_code = 0;
  bool run =
    cmSystemTools::RunSingleCommand(command, &output, &output, &exit_code,
                                    dir.c_str(), cmSystemTools::OUTPUT_NONE);

  // process the include directives and output everything else
  std::istringstream ss(output);
  std::string line;
  std::vector<std::string> includes;
  bool isFirstLine = true; // cl prints always first the source filename
  while (std::getline(ss, line)) {
    if (startsWith(line, prefix)) {
      std::string inc = trimLeadingSpace(line.substr(prefix.size()).c_str());
      if (inc[inc.size() - 1] == '\r') // blech, stupid \r\n
        inc = inc.substr(0, inc.size() - 1);
      includes.push_back(inc);
    } else {
      if (!isFirstLine || !startsWith(line, srcfilename)) {
        if (!quiet || exit_code != 0) {
          fprintf(stdout, "%s\n", line.c_str());
        }
      } else {
        isFirstLine = false;
      }
    }
  }

  // don't update .d until/unless we succeed compilation
  if (run && exit_code == 0)
    outputDepFile(dfile, objfile, includes);

  return exit_code;
}