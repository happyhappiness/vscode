      {

      for(int i=0; i<command.size(); i++)

        {

        std::cout << command[i] << " ";

        }

      std::cout << std::endl;

      }



    std::string output;

    int retVal = 0;

    bool result = cmSystemTools::RunSingleCommand(command, &output, &retVal);

    if (!result || retVal)

      {

      std::cerr << "AUTOMOC: process for " << mocFilePath << " failed:\n"

                << output << std::endl;

      this->RunMocFailed = true;

      cmSystemTools::RemoveFile(mocFilePath.c_str());
