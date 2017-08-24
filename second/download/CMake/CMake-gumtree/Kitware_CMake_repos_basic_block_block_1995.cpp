{
    std::string name = env.substr(0, pos);
    unsetenv(name.c_str());
  }