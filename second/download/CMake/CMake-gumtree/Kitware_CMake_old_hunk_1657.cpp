      cmSystemTools::Error(error.str().c_str());

      return true;

      }

    

    // now set the new argcDef

    char argcDef[64];

    sprintf(argcDef,"%i",expandedArguments.size());    

    

    // Invoke all the functions that were collected in the block.

    cmListFileFunction newLFF;

