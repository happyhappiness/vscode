      {

      for(int i=0; i<command.size(); i++)

        {

        printf("%s ", command[i].c_str());

        }

      printf("\n");

      }



    std::string output;

    int retVal = 0;

    bool result = cmSystemTools::RunSingleCommand(command, &output, &retVal);

    if (!result || retVal)

      {

      std::cerr << "automoc4: process for " << mocFilePath << " failed:\n"

                << output << std::endl;

      this->RunMocFailed = true;

      cmSystemTools::RemoveFile(mocFilePath.c_str());
