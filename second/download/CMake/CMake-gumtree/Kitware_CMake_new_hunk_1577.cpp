  // declare varuiables for ARGV ARGN but do not compute until needed
  std::string argvDef;
  std::string argnDef;
  bool argvDefInitialized = false;

  // save the current definitions of all vars that we will be setting
  std::string oldARGC;
  if (m_Makefile->GetDefinition("ARGC"))
    {
    oldARGC = m_Makefile->GetDefinition("ARGC");
    }
  m_Makefile->AddDefinition("ARGC",argcDef.c_str());

  // store ARGN, ARGV
  std::vector<std::string> oldARGVArgs;
  std::vector<std::string>::const_iterator eit;
  std::vector<std::string>::size_type cnt = 0;
  char argvName[60];
  for ( eit = expandedArgs.begin(); eit != expandedArgs.end(); ++eit )
    {
    if ( cnt >= m_Args.size()-1 )
      {
      if ( argnDef.size() > 0 )
        {
        argnDef += ";";
        }
      argnDef += *eit;
      }
    if ( argvDef.size() > 0 )
      {
      argvDef += ";";
      }
    argvDef += *eit;
    oldARGVArgs.push_back(std::string());
    sprintf(argvName,"ARGV%i",cnt);
    if (m_Makefile->GetDefinition(argvName))
      {
      oldARGVArgs[cnt] = m_Makefile->GetDefinition(argvName);
      }
    m_Makefile->AddDefinition(argvName,eit->c_str());
    cnt++;
    }
  std::string oldARGN;
  if (m_Makefile->GetDefinition("ARGN"))
    {
    oldARGN = m_Makefile->GetDefinition("ARGN");
    }
  m_Makefile->AddDefinition("ARGN",argnDef.c_str());
  std::string oldARGV;
  if (m_Makefile->GetDefinition("ARGV"))
    {
    oldARGV = m_Makefile->GetDefinition("ARGV");
    }
  m_Makefile->AddDefinition("ARGV",argvDef.c_str());

  // store old defs for formal args
  std::vector<std::string> oldFormalArgs;
  for (unsigned int j = 1; j < m_Args.size(); ++j)
    {
    oldFormalArgs.push_back(std::string());
    if (m_Makefile->GetDefinition(m_Args[j].c_str()))
      {
      oldFormalArgs[j-1] = m_Makefile->GetDefinition(m_Args[j].c_str());
      }
    m_Makefile->AddDefinition(m_Args[j].c_str(),expandedArgs[j-1].c_str());
    }
  
  // Invoke all the functions that were collected in the block.
  for(unsigned int c = 0; c < m_Functions.size(); ++c)
    {
    if(!m_Makefile->ExecuteCommand(m_Functions[c]))
      {
      cmOStringStream error;
      error << "Error in cmake code at\n"
            << args[0].FilePath << ":" << args[0].Line << "\n"
            << "A command failed during the invocation of macro \""
            << this->m_Args[0].c_str() << "\".\nThe failing line "
            << "in the macro definition was at\n" 
            << m_Functions[c].m_FilePath << ":"
            << m_Functions[c].m_Line << "\n";
      cmSystemTools::Error(error.str().c_str());
      return false;
      }
    }
  
  // restore all args
  m_Makefile->AddDefinition("ARGC",oldARGC.c_str());
  m_Makefile->AddDefinition("ARGN",oldARGN.c_str());
  m_Makefile->AddDefinition("ARGV",oldARGV.c_str());
  // restore old defs for formal args
  for (unsigned int j = 1; j < m_Args.size(); ++j)
    {
    m_Makefile->AddDefinition(m_Args[j].c_str(),oldFormalArgs[j-1].c_str());
    }
  // restore old defs for formal args
  for (unsigned int j = 0; j < oldARGVArgs.size(); ++j)
    {
    sprintf(argvName,"ARGV%i",j);
    m_Makefile->AddDefinition(argvName,oldARGVArgs[j].c_str());
    }
  
  return true;
}

