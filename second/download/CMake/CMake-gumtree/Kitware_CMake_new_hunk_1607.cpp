        // Add the translation to keep the logical path name.
        if(!cwd_changed.empty() && !pwd_changed.empty())
          {
          SystemTools::AddTranslationPath(cwd_changed.c_str(),
                                          pwd_changed.c_str());
          }