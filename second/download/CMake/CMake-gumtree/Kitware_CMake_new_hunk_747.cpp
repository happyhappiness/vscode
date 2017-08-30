    sprintf(argvName,"${ARGV%i}",j);

    argVs.push_back(argvName);

    }

  // Invoke all the functions that were collected in the block.

  cmListFileFunction newLFF;

  // for each function

