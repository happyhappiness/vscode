void cmGlobalGenerator::Configure()
{
  // Delete any existing cmLocalGenerators
  unsigned int i;
  for (i = 0; i < m_LocalGenerators.size(); ++i)
    {
    delete m_LocalGenerators[i];
    }
  m_LocalGenerators.clear();

  // Setup relative path generation.
  this->ConfigureRelativePaths();

  // start with this directory
  cmLocalGenerator *lg = this->CreateLocalGenerator();
  m_LocalGenerators.push_back(lg);

  // set the Start directories
  lg->GetMakefile()->SetStartDirectory
    (m_CMakeInstance->GetStartDirectory());
  lg->GetMakefile()->SetStartOutputDirectory
    (m_CMakeInstance->GetStartOutputDirectory());
  lg->GetMakefile()->MakeStartDirectoriesCurrent();
  
  // now do it
  lg->Configure();
  
  // update the cache entry for the number of local generators, this is used
  // for progress
  char num[100];
  sprintf(num,"%d",static_cast<int>(m_LocalGenerators.size()));
  this->GetCMakeInstance()->AddCacheEntry
    ("CMAKE_NUMBER_OF_LOCAL_GENERATORS", num,
     "number of local generators", cmCacheManager::INTERNAL);
  
  std::set<cmStdString> notFoundMap;
  // after it is all done do a ConfigureFinalPass
  cmCacheManager* manager = 0;
  for (i = 0; i < m_LocalGenerators.size(); ++i)
    {
    manager = m_LocalGenerators[i]->GetMakefile()->GetCacheManager();
    m_LocalGenerators[i]->ConfigureFinalPass();
    cmTargets & targets = 
      m_LocalGenerators[i]->GetMakefile()->GetTargets(); 
    for (cmTargets::iterator l = targets.begin();
         l != targets.end(); l++)
      {
      cmTarget::LinkLibraries libs = l->second.GetLinkLibraries();
      for(cmTarget::LinkLibraries::iterator lib = libs.begin();
          lib != libs.end(); ++lib)
        {
        if(lib->first.size() > 9 && 
           cmSystemTools::IsNOTFOUND(lib->first.c_str()))
          {
          std::string varName = lib->first.substr(0, lib->first.size()-9);
          notFoundMap.insert(varName);
          }
        }
      std::vector<std::string>& incs = 
        m_LocalGenerators[i]->GetMakefile()->GetIncludeDirectories();
      
      for( std::vector<std::string>::iterator lib = incs.begin();
           lib != incs.end(); ++lib)
        {
        if(lib->size() > 9 && 
           cmSystemTools::IsNOTFOUND(lib->c_str()))
          {
          std::string varName = lib->substr(0, lib->size()-9); 
          notFoundMap.insert(varName);
          }
        }
      m_CMakeInstance->UpdateProgress("Configuring", 
                                      0.9f+0.1f*(i+1.0f)/m_LocalGenerators.size());
      m_LocalGenerators[i]->GetMakefile()->CheckInfiniteLoops();
      }
    }

  if(notFoundMap.size())
    {
    std::string notFoundVars;
    for(std::set<cmStdString>::iterator ii = notFoundMap.begin();
        ii != notFoundMap.end(); ++ii)
      { 
      notFoundVars += *ii;
      if(manager)
        {
        cmCacheManager::CacheIterator it = 
          manager->GetCacheIterator(ii->c_str());
        if(it.GetPropertyAsBool("ADVANCED"))
          {
          notFoundVars += " (ADVANCED)";
          }
        }
      notFoundVars += "\n";
      }
    cmSystemTools::Error("This project requires some variables to be set,\n"
                         "and cmake can not find them.\n"
                         "Please set the following variables:\n",
                         notFoundVars.c_str());
    }
  // at this point m_LocalGenerators has been filled,
  // so create the map from project name to vector of local generators
  this->FillProjectMap();
  if ( !m_CMakeInstance->GetScriptMode() )
    {
    m_CMakeInstance->UpdateProgress("Configuring done", -1);
    }
}