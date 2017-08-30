    const std::string &absFilename = *it;

    if (this->Verbose)

      {

      std::cout << "AUTOMOC: Checking " << absFilename << std::endl;

      }

    this->ParseCppFile(absFilename, includedMocs, notIncludedMocs);

    }

