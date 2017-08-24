    this->SetError(err.c_str());
    return false;
    }
  std::string configFile = 
    m_Makefile->GetDefinition("CMAKE_ROOT");
  configFile += "/Templates/TestDriver.cxx.in";
  // Create the test driver file
  
  std::vector<std::string>::const_iterator testsBegin = i;
  std::vector<std::string> tests_func_name;

