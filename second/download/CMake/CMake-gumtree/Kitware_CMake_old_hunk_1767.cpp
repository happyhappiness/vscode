          firstTest = 0;
          }
        cres.m_Name = args[0].Value;
        fprintf(stderr,"Testing %-30s ",args[0].Value.c_str());
        fflush(stderr);
        //std::cerr << "Testing " << args[0] << " ... ";
        // find the test executable
        std::string testCommand = this->FindExecutable(args[1].Value.c_str());
