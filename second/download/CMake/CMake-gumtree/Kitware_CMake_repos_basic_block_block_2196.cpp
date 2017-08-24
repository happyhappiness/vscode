{
    tryPath = *p;
    tryPath += name;
    if (SystemTools::FileExists(tryPath)) {
      return tryPath;
    }
  }