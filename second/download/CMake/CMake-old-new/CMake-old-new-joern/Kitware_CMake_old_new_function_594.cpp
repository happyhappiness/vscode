void cmGlobalGenerator::Configure()
{
  this->FirstTimeProgress = 0.0f;
  this->ClearGeneratorMembers();

  // start with this directory
  cmLocalGenerator *lg = this->MakeLocalGenerator();
  this->Makefiles.push_back(lg->GetMakefile());
  this->LocalGenerators.push_back(lg);

  // set the Start directories
  lg->GetMakefile()->SetCurrentSourceDirectory
    (this->CMakeInstance->GetHomeDirectory());
  lg->GetMakefile()->SetCurrentBinaryDirectory
    (this->CMakeInstance->GetHomeOutputDirectory());

  this->BinaryDirectories.insert(
      this->CMakeInstance->GetHomeOutputDirectory());

  // now do it
  lg->GetMakefile()->Configure();
  lg->GetMakefile()->EnforceDirectoryLevelRules();

  // update the cache entry for the number of local generators, this is used
  // for progress
  char num[100];
  sprintf(num,"%d",static_cast<int>(this->LocalGenerators.size()));
  this->GetCMakeInstance()->AddCacheEntry
    ("CMAKE_NUMBER_OF_LOCAL_GENERATORS", num,
     "number of local generators", cmState::INTERNAL);

  // check for link libraries and include directories containing "NOTFOUND"
  // and for infinite loops
  this->CheckLocalGenerators();

  // at this point this->LocalGenerators has been filled,
  // so create the map from project name to vector of local generators
  this->FillProjectMap();

  if ( this->CMakeInstance->GetWorkingMode() == cmake::NORMAL_MODE)
    {
    std::ostringstream msg;
    if(cmSystemTools::GetErrorOccuredFlag())
      {
      msg << "Configuring incomplete, errors occurred!";
      const char* logs[] = {"CMakeOutput.log", "CMakeError.log", 0};
      for(const char** log = logs; *log; ++log)
        {
        std::string f = this->CMakeInstance->GetHomeOutputDirectory();
        f += this->CMakeInstance->GetCMakeFilesDirectory();
        f += "/";
        f += *log;
        if(cmSystemTools::FileExists(f.c_str()))
          {
          msg << "\nSee also \"" << f << "\".";
          }
        }
      }
    else
      {
      msg << "Configuring done";
      }
    this->CMakeInstance->UpdateProgress(msg.str().c_str(), -1);
    }

  unsigned int i;

  // Put a copy of each global target in every directory.
  cmTargets globalTargets;
  this->CreateDefaultGlobalTargets(&globalTargets);

  for (i = 0; i < this->LocalGenerators.size(); ++i)
    {
    cmMakefile* mf = this->LocalGenerators[i]->GetMakefile();
    cmTargets* targets = &(mf->GetTargets());
    cmTargets::iterator tit;
    for ( tit = globalTargets.begin(); tit != globalTargets.end(); ++ tit )
      {
      (*targets)[tit->first] = tit->second;
      (*targets)[tit->first].SetMakefile(mf);
      }
    }

}