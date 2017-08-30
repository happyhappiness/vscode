{
    std::string tmps;
    cmListFileArgument arg;
    std::string variable;
    // Expand the argument list to the macro.
    std::vector<std::string> expandedArguments;
    mf.ExpandArguments(lff.m_Arguments, expandedArguments);

    // make sure the number of arguments passed is at least the number
    // required by the signature
    if (expandedArguments.size() < m_Args.size() - 1)
      {
      cmOStringStream error;
      error << "Error in cmake code at\n"
            << lff.m_FilePath << ":" << lff.m_Line << ":\n"
            << "Invocation of macro \""
            << lff.m_Name.c_str() << "\" with incorrect number of arguments.";
      cmSystemTools::Error(error.str().c_str());
      return true;
      }
    
    // now set the new argcDef
    char argcDef[64];
    sprintf(argcDef,"%i",expandedArguments.size());    
    
    // Invoke all the functions that were collected in the block.
    cmListFileFunction newLFF;
    for(unsigned int c = 0; c < m_Functions.size(); ++c)
      {
      // Replace the formal arguments and then invoke the command.
      newLFF.m_Arguments.clear();
      newLFF.m_Arguments.reserve(m_Functions[c].m_Arguments.size());
      newLFF.m_Name = m_Functions[c].m_Name;
      newLFF.m_FilePath = m_Functions[c].m_FilePath;
      newLFF.m_Line = m_Functions[c].m_Line;
      for (std::vector<cmListFileArgument>::const_iterator k = 
             m_Functions[c].m_Arguments.begin();
           k != m_Functions[c].m_Arguments.end(); ++k)
        {
        tmps = k->Value;
        // replace formal arguments
        for (unsigned int j = 1; j < m_Args.size(); ++j)
          {
          variable = "${";
          variable += m_Args[j];
          variable += "}"; 
          cmSystemTools::ReplaceString(tmps, variable.c_str(),
                                       expandedArguments[j-1].c_str());
          }
        // replace argc, argv arguments
        for (unsigned int j = 1; j < m_Args.size(); ++j)
          {
          variable = "${ARGC}";
          cmSystemTools::ReplaceString(tmps, variable.c_str(),argcDef);
          }
        for (unsigned int j = 1; j < m_Args.size(); ++j)
          {
          // since this could be slow, first check if there is an ARGV
          // only then do the inner loop. PS std::string sucks
          char argvName[60];
          if (tmps.find("${ARGV") != std::string::npos)
            {
            for (unsigned int t = 0; t < expandedArguments.size(); ++t)
              {
              sprintf(argvName,"${ARGV%i}",t);
              cmSystemTools::ReplaceString(tmps, argvName,
                                           expandedArguments[t].c_str());
              }
            }
          }
        
        arg.Value = tmps;
        arg.Quoted = k->Quoted;
        newLFF.m_Arguments.push_back(arg);
        }
      if(!mf.ExecuteCommand(newLFF))
        {
        cmOStringStream error;
        error << "Error in cmake code at\n"
              << lff.m_FilePath << ":" << lff.m_Line << ":\n"
              << "A command failed during the invocation of macro \""
              << lff.m_Name.c_str() << "\".";
        cmSystemTools::Error(error.str().c_str());
        }
      }
    return true;
    }