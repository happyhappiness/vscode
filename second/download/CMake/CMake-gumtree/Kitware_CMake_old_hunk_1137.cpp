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
