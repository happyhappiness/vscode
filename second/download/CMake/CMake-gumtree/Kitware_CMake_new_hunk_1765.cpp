          firstTest = 0;

          }

        cres.m_Name = args[0].Value;

        if ( m_ShowOnly )

          {

          std::cout << args[0].Value << std::endl;

          }

        else

          {

          fprintf(stderr,"Testing %-30s ",args[0].Value.c_str());

          fflush(stderr);

          }

        //std::cerr << "Testing " << args[0] << " ... ";

        // find the test executable

        std::string testCommand = this->FindExecutable(args[1].Value.c_str());

