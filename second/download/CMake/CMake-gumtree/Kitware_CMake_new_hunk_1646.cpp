
    if ( m_ShowOnly )
      {
      std::cerr.width(3);
      std::cerr.setf(std::ios_base::right);
      std::cerr << cnt << "/";
      std::cerr.width(3);
      std::cerr << tmsize << " Testing ";
      std::string outname = testname;
      outname.resize(30, ' ');
      std::cerr << outname.c_str() << "\n";
     }
    else
      {
      std::cerr.width(3);
      std::cerr << cnt << "/";
      std::cerr.width(3);
      std::cerr << tmsize << " Testing ";
      std::string outname = testname;
      outname.resize(30, ' ');
      std::cerr << outname.c_str();
      std::cerr.flush();
      }
    
    //std::cerr << "Testing " << args[0] << " ... ";
    // find the test executable
    std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());
