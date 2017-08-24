{
    const char* exception_str = cmsysProcess_GetExceptionString(cp);
    std::cerr << exception_str << std::endl;
    result = false;
  }