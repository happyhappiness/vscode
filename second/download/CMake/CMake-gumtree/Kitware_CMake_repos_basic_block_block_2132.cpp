{
      std::string::size_type idx = path.find_first_of("/\0");
      std::string user = path.substr(1, idx - 1);
      passwd* pw = getpwnam(user.c_str());
      if (pw) {
        path.replace(0, idx, pw->pw_dir);
      }
    }