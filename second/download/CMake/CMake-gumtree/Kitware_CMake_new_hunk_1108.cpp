  lg->GetMakefile()->SetStartOutputDirectory
    (this->CMakeInstance->GetStartOutputDirectory());
  lg->GetMakefile()->MakeStartDirectoriesCurrent();

  // now do it
  lg->Configure();

  // update the cache entry for the number of local generators, this is used
  // for progress
  char num[100];
  sprintf(num,"%d",static_cast<int>(this->LocalGenerators.size()));
  this->GetCMakeInstance()->AddCacheEntry
    ("CMAKE_NUMBER_OF_LOCAL_GENERATORS", num,
     "number of local generators", cmCacheManager::INTERNAL);

  std::set<cmStdString> notFoundMap;
  // after it is all done do a ConfigureFinalPass
  cmCacheManager* manager = 0;
  for (i = 0; i < this->LocalGenerators.size(); ++i)
    {
    manager = this->LocalGenerators[i]->GetMakefile()->GetCacheManager();
    this->LocalGenerators[i]->ConfigureFinalPass();
    cmTargets & targets =
      this->LocalGenerators[i]->GetMakefile()->GetTargets();
    for (cmTargets::iterator l = targets.begin();
         l != targets.end(); l++)
      {
      cmTarget::LinkLibraryVectorType libs = l->second.GetLinkLibraries();
      for(cmTarget::LinkLibraryVectorType::iterator lib = libs.begin();
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
        this->LocalGenerators[i]->GetMakefile()->GetIncludeDirectories();

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
