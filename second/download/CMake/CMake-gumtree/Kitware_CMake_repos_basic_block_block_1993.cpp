{
    std::string& menv = (*SystemTools::EnvMap)[key];
    menv = env;
    v = menv.c_str();
  }