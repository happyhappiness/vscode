      cmSystemTools::Error(error.str().c_str());
      return true;
      }
    cmOStringStream argcDefStream;
    argcDefStream << expandedArguments.size();
    std::string argcDef = argcDefStream.str();
    
    // Invoke all the functions that were collected in the block.
    cmListFileFunction newLFF;
