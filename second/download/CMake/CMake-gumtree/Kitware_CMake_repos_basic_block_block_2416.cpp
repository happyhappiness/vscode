{
      // The current working directory may be a logical path.  Find
      // the shortest logical path that still produces the correct
      // physical path.
      std::string cwd_changed;
      std::string pwd_changed;

      // Test progressively shorter logical-to-physical mappings.
      std::string cwd_str = cwd;
      std::string pwd_path;
      Realpath(pwd_str.c_str(), pwd_path);
      while (cwd_str == pwd_path && cwd_str != pwd_str) {
        // The current pair of paths is a working logical mapping.
        cwd_changed = cwd_str;
        pwd_changed = pwd_str;

        // Strip off one directory level and see if the logical
        // mapping still works.
        pwd_str = SystemTools::GetFilenamePath(pwd_str);
        cwd_str = SystemTools::GetFilenamePath(cwd_str);
        Realpath(pwd_str.c_str(), pwd_path);
      }

      // Add the translation to keep the logical path name.
      if (!cwd_changed.empty() && !pwd_changed.empty()) {
        SystemTools::AddTranslationPath(cwd_changed, pwd_changed);
      }
    }