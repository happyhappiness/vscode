(!cmSystemTools::RunSingleCommand(command, CM_NULLPTR, CM_NULLPTR,
                                         CM_NULLPTR,
                                         it->at("directory").c_str())) {
      std::cout << "ERROR: Failed to run command \"" << command[0] << "\""
                << std::endl;
      exit(1);
    }