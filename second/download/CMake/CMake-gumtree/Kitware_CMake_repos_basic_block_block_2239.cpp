(!SystemTools::FileExists(self)) {
      failures.push_back(self);
      self = installPrefix;
      self += "/bin/";
      self += exeName;
    }