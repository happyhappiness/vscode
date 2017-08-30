    const std::string &absFilename = *it;

    if (this->Verbose)

      {

      printf("Checking -%s-\n", absFilename.c_str());

      }

    this->ParseCppFile(absFilename, includedMocs, notIncludedMocs);

    }

