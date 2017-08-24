(line.find("/bin/sh: bad interpreter: Text file busy") !=
        std::string::npos) {
      hitbug = true;
      std::cerr << "Hit xcodebuild bug : " << line << "\n";
    }