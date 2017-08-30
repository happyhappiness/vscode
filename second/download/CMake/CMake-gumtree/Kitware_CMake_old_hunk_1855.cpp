        // return to the original directory
        cmSystemTools::ChangeDirectory(cwd.c_str());
        }

      if (name == "ADD_TEST")
        {
        fprintf(stderr,"Testing %-30s ",args[0].c_str());
        //std::cerr << "Testing " << args[0] << " ... ";
        // find the test executable
