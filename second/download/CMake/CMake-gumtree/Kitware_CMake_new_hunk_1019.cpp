    const std::string &absFilename = *it;
    if (this->Verbose)
      {
      std::cout << "AUTOMOC: Checking " << absFilename << std::endl;
      }
    if (includedMocs.find(absFilename) == includedMocs.end()
              && notIncludedMocs.find(absFilename) == notIncludedMocs.end())
