{
    std::string name = env.substr(0, pos);
    return setenv(name.c_str(), env.c_str() + pos + 1, 1) == 0;
  }