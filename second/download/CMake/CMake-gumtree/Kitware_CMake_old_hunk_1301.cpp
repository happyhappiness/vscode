      Realpath(pwd, pwd_path);
      if(cwd == pwd_path && strcmp(cwd, pwd) != 0)
        {
#if defined(__HP_aCC)
        fprintf(stderr, "cwd=[%s]\npwd=[%s]\npwd_path=[%s]\n",
                cwd, pwd, pwd_path.c_str());
#endif
        // The current working directory is a logical path.  Split
        // both the logical and physical paths into their components.
        kwsys_stl::vector<kwsys_stl::string> cwd_components;
