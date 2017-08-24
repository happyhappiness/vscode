{
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