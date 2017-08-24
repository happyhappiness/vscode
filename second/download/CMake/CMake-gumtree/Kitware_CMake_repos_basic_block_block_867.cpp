(dir = search_path; *dir; ++dir) {
      /* Add separator between path components.  */
      if (dir != search_path) {
        strcat(ldpath, kwsys_shared_forward_path_sep);
      }

      /* Add this path component.  */
      if (!kwsys_shared_forward_fullpath(self_path_logical, *dir,
                                         ldpath + strlen(ldpath),
                                         "runtime path entry")) {
        return 0;
      }
    }