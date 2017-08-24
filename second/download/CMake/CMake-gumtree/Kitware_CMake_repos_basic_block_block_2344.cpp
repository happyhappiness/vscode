{
  // see if this is a full path to a program
  // if so then set program to path and args to nothing
  if (SystemTools::FileExists(path)) {
    program = path;
    args = "";
    return;
  }
  // Try to find the program in the path, note the program
  // may have spaces in its name so we have to look for it
  std::vector<std::string> e;
  std::string findProg = SystemTools::FindProgram(path, e);
  if (!findProg.empty()) {
    program = findProg;
    args = "";
    return;
  }

  // Now try and peel off space separated chunks from the end of the string
  // so the largest path possible is found allowing for spaces in the path
  std::string dir = path;
  std::string::size_type spacePos = dir.rfind(' ');
  while (spacePos != std::string::npos) {
    std::string tryProg = dir.substr(0, spacePos);
    // See if the file exists
    if (SystemTools::FileExists(tryProg)) {
      program = tryProg;
      // remove trailing spaces from program
      std::string::size_type pos = program.size() - 1;
      while (program[pos] == ' ') {
        program.erase(pos);
        pos--;
      }
      args = dir.substr(spacePos, dir.size() - spacePos);
      return;
    }
    // Now try and find the program in the path
    findProg = SystemTools::FindProgram(tryProg, e);
    if (!findProg.empty()) {
      program = findProg;
      // remove trailing spaces from program
      std::string::size_type pos = program.size() - 1;
      while (program[pos] == ' ') {
        program.erase(pos);
        pos--;
      }
      args = dir.substr(spacePos, dir.size() - spacePos);
      return;
    }
    // move past the space for the next search
    spacePos--;
    spacePos = dir.rfind(' ', spacePos);
  }

  program = "";
  args = "";
}