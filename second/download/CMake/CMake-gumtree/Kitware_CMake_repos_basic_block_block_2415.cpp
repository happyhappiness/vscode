{
        // The current pair of paths is a working logical mapping.
        cwd_changed = cwd_str;
        pwd_changed = pwd_str;

        // Strip off one directory level and see if the logical
        // mapping still works.
        pwd_str = SystemTools::GetFilenamePath(pwd_str);
        cwd_str = SystemTools::GetFilenamePath(cwd_str);
        Realpath(pwd_str.c_str(), pwd_path);
      }