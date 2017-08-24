    const std::string &absFilename = *it;
    if (this->Verbose)
      {
      printf("Checking -%s-\n", absFilename.c_str());
      }
    if (includedMocs.find(absFilename) == includedMocs.end()
              && notIncludedMocs.find(absFilename) == notIncludedMocs.end())
