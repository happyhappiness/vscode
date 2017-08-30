      {
      func_name = cmSystemTools::GetFilenameWithoutLastExtension(*i);
      }
    functionMapCode += "  {\n"
      "    \"";
    functionMapCode += func_name;
    functionMapCode += "\",\n"
      "    ";
    functionMapCode +=  *j;
    functionMapCode += "\n"
      "  },\n";
    numTests++;
    }
  if(extraInclude.size())
    {
    m_Makefile->AddDefinition("CMAKE_TESTDRIVER_EXTRA_INCLUDES", extraInclude.c_str());
    }
  if(function.size())
    {
    m_Makefile->AddDefinition("CMAKE_TESTDRIVER_ARGVC_FUNCTION", function.c_str());
    }
  m_Makefile->AddDefinition("CMAKE_FORWARD_DECLARE_TESTS", forwardDeclareCode.c_str());
  m_Makefile->AddDefinition("CMAKE_FUNCTION_TABLE_ENTIRES", functionMapCode.c_str());
  m_Makefile->ConfigureFile(configFile.c_str(), driver.c_str(), false, true, false);

  // Create the source list
  cmSourceFile cfile;