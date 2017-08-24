{
  hitbug = false;
  cmsysProcess* cp = cmsysProcess_New();
  cmsysProcess_SetCommand(cp, &*argv.begin());
  cmsysProcess_SetTimeout(cp, 0);
  cmsysProcess_Execute(cp);
  std::vector<char> out;
  std::vector<char> err;
  std::string line;
  int pipe = cmSystemTools::WaitForLine(cp, line, 100.0, out, err);
  while (pipe != cmsysProcess_Pipe_None) {
    if (line.find("/bin/sh: bad interpreter: Text file busy") !=
        std::string::npos) {
      hitbug = true;
      std::cerr << "Hit xcodebuild bug : " << line << "\n";
    }
    // if the bug is hit, no more output should be generated
    // because it may contain bogus errors
    // also remove all output with setenv in it to tone down
    // the verbosity of xcodebuild
    if (!hitbug && (line.find("setenv") == std::string::npos)) {
      if (pipe == cmsysProcess_Pipe_STDERR) {
        std::cerr << line << "\n";
      } else if (pipe == cmsysProcess_Pipe_STDOUT) {
        std::cout << line << "\n";
      }
    }
    pipe = cmSystemTools::WaitForLine(cp, line, 100, out, err);
  }
  cmsysProcess_WaitForExit(cp, 0);
  if (cmsysProcess_GetState(cp) == cmsysProcess_State_Exited) {
    return cmsysProcess_GetExitValue(cp);
  }
  if (cmsysProcess_GetState(cp) == cmsysProcess_State_Error) {
    return -1;
  }
  return -1;
}