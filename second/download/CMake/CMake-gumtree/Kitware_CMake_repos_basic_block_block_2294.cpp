{
      std::string homedir;
      root = root.substr(0, root.size() - 1);
      if (root.size() == 1) {
#if defined(_WIN32) && !defined(__CYGWIN__)
        if (!SystemTools::GetEnv("USERPROFILE", homedir))
#endif
          SystemTools::GetEnv("HOME", homedir);
      }
#ifdef HAVE_GETPWNAM
      else if (passwd* pw = getpwnam(root.c_str() + 1)) {
        if (pw->pw_dir) {
          homedir = pw->pw_dir;
        }
      }
#endif
      if (!homedir.empty() &&
          (*homedir.rbegin() == '/' || *homedir.rbegin() == '\\')) {
        homedir.resize(homedir.size() - 1);
      }
      SystemTools::SplitPath(homedir, components);
    }