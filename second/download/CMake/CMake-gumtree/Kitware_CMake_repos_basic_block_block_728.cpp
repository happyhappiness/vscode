{
    fullName = *i;
    fullName += "/";
    fullName += includeName;
    if (cmSystemTools::FileExists(fullName.c_str(), true)) {
      fileName = fullName;
      return true;
    }
  }