{
      std::string intdir = ".";
#ifdef CMAKE_INTDIR
      intdir = CMAKE_INTDIR;
#endif
      self = buildDir;
      self += "/bin/";
      self += intdir;
      self += "/";
      self += exeName;
      self += SystemTools::GetExecutableExtension();
    }