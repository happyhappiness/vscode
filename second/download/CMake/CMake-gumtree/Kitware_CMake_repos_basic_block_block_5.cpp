(cmsysProcess_GetState(cp) == cmsysProcess_State_Expired) {
    const char* error_str = "Process terminated due to timeout\n";
    std::cerr << error_str << std::endl;
    result = false;
  }