
    if ( m_ShowOnly )
      {
      fprintf(stderr,"%3d/%3d Testing %-30s\n", cnt, (int)tmsize, testname.c_str());
      }
    else
      {
      fprintf(stderr,"%3d/%3d Testing %-30s ", cnt, (int)tmsize, testname.c_str());
      fflush(stderr);
      }
    //std::cerr << "Testing " << args[0] << " ... ";
    // find the test executable
    std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());
