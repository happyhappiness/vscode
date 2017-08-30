  const char* ret = getcwd(buf, len);
  if(!ret)
    {
    std::cerr << "No current working directory" << std::endl;
    abort();
    }
  return ret;
