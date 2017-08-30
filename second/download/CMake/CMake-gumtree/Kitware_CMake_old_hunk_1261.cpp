      return;
      }

    fprintf(stderr, "Writing %s...\n", currentFilename.c_str());
    this->WriteHeader(str);

    this->WriteConnections(ptrIt->first.c_str(),
