{
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