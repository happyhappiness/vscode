  // declare varuiables for ARGV ARGN but do not compute until needed

  std::string argvDef;

  std::string argnDef;

  bool argnDefInitialized = false;

  bool argvDefInitialized = false;

  

  // Invoke all the functions that were collected in the block.

  cmListFileFunction newLFF;

  // for each function

  for(unsigned int c = 0; c < m_Functions.size(); ++c)

    {

    // Replace the formal arguments and then invoke the command.

    newLFF.m_Arguments.clear();

    newLFF.m_Arguments.reserve(m_Functions[c].m_Arguments.size());

    newLFF.m_Name = m_Functions[c].m_Name;

    newLFF.m_FilePath = m_Functions[c].m_FilePath;

    newLFF.m_Line = m_Functions[c].m_Line;

    const char* def =

      m_Makefile->GetDefinition("CMAKE_MACRO_REPORT_DEFINITION_LOCATION"); 

    bool macroReportLocation = false;

    if(def && !cmSystemTools::IsOff(def))

      {

      macroReportLocation = true;

      }

    

    // for each argument of the current function

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

                                     expandedArgs[j-1].c_str());

        }

      // replace argc

      cmSystemTools::ReplaceString(tmps, "${ARGC}",argcDef.c_str());

      

      // repleace ARGN

      if (tmps.find("${ARGN}") != std::string::npos)

        {

        if (!argnDefInitialized)

          {

          std::vector<std::string>::const_iterator eit;

          std::vector<std::string>::size_type cnt = 0;

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

            cnt ++;

            }

          argnDefInitialized = true;

          }

        cmSystemTools::ReplaceString(tmps, "${ARGN}", argnDef.c_str());

        }

      

      // if the current argument of the current function has ${ARGV in it

      // then try replacing ARGV values

      if (tmps.find("${ARGV") != std::string::npos)

        {

        char argvName[60];

        

        // repleace ARGV, compute it only once

        if (!argvDefInitialized)

          {

          std::vector<std::string>::const_iterator eit;

          for ( eit = expandedArgs.begin(); eit != expandedArgs.end(); ++eit )

            {

            if ( argvDef.size() > 0 )

              {

              argvDef += ";";

              }

            argvDef += *eit;

            }

          argvDefInitialized = true;

          }

        cmSystemTools::ReplaceString(tmps, "${ARGV}", argvDef.c_str());

        

        // also replace the ARGV1 ARGV2 ... etc

        for (unsigned int t = 0; t < expandedArgs.size(); ++t)

          {

          sprintf(argvName,"${ARGV%i}",t);

          cmSystemTools::ReplaceString(tmps, argvName,

                                       expandedArgs[t].c_str());

          }

        }

      

      arg.Value = tmps;

      arg.Quoted = k->Quoted;

      if(macroReportLocation)

        {

        // Report the location of the argument where the macro was

        // defined.

        arg.FilePath = k->FilePath;

        arg.Line = k->Line;

        }

      else

        {

        // Report the location of the argument where the macro was

        // invoked.

        if (args.size())

          {

          arg.FilePath = args[0].FilePath;

          arg.Line = args[0].Line;

          }

        else

          {

          arg.FilePath = "Unknown";

          arg.Line = 0;

          }

        }

      newLFF.m_Arguments.push_back(arg);

      }

    if(!m_Makefile->ExecuteCommand(newLFF))

      {

      cmOStringStream error;

      error << "Error in cmake code at\n"

            << args[0].FilePath << ":" << args[0].Line << ":\n"

            << "A command failed during the invocation of macro \""

            << this->m_Args[0].c_str() << "\".";

      cmSystemTools::Error(error.str().c_str());

      return false;

      }

    }

  return true;

}



