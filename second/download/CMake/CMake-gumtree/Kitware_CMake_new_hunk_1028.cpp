  const char* ret = _getcwd(buf, len);
  if(!ret)
    {
    std::cerr << "No current working directory." << std::endl;
    abort();
    }
  // make sure the drive letter is capital
