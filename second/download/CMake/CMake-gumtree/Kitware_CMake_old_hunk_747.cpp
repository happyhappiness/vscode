    sprintf(argvName,"${ARGV%i}",j);

    argVs.push_back(argvName);

    }

  if(!this->Functions.empty())

    {

    this->FilePath = this->Functions[0].FilePath;

    }

  // Invoke all the functions that were collected in the block.

  cmListFileFunction newLFF;

  // for each function

