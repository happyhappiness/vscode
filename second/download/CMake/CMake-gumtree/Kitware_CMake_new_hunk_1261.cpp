      return;

      }



    std::cout << "Writing " << currentFilename << "..." << std::endl;

    this->WriteHeader(str);



    this->WriteConnections(ptrIt->first.c_str(),

