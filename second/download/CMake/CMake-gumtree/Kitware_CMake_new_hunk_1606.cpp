      Realpath(pwd, pwd_path);

      if(cwd == pwd_path && strcmp(cwd, pwd) != 0)

        {

        // The current working directory is a logical path.  Split

        // both the logical and physical paths into their components.

        kwsys_stl::vector<kwsys_stl::string> cwd_components;

