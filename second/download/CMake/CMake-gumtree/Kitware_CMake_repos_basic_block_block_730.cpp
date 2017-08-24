(cmSystemTools::FileExists(fullName.c_str(), true)) {
    fileName = fullName;
    return true;
  }