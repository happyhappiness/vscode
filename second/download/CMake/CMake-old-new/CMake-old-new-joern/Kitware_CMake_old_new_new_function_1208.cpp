int cmake::Configure()
{
  // Construct right now our path conversion table before it's too late:
  this->UpdateConversionPathTable();
  this->CleanupCommandsAndMacros();

  int res = 0;
  if ( !this->ScriptMode )
    {
    res = this->DoPreConfigureChecks();
    }
  if ( res < 0 )
    {
    return -2;
    }
  if ( !res )
    {
    this->CacheManager->AddCacheEntry
      ("CMAKE_HOME_DIRECTORY", 
       this->GetHomeDirectory(),
       "Start directory with the top level CMakeLists.txt file for this "
       "project",
       cmCacheManager::INTERNAL);
    }

  // set the default BACKWARDS compatibility to the current version
  if(!this->CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
    {
    char ver[256];
    sprintf(ver,"%i.%i",cmVersion::GetMajorVersion(),
            cmVersion::GetMinorVersion());
    this->CacheManager->AddCacheEntry
      ("CMAKE_BACKWARDS_COMPATIBILITY",ver, 
       "For backwards compatibility, what version of CMake commands and "
       "syntax should this version of CMake allow.",
       cmCacheManager::STRING);
    }

  // no generator specified on the command line
  if(!this->GlobalGenerator)
    {
    const char* genName = 
      this->CacheManager->GetCacheValue("CMAKE_GENERATOR");
    if(genName)
      {
      this->GlobalGenerator = this->CreateGlobalGenerator(genName);
      }
    if(this->GlobalGenerator)
      {
      // set the global flag for unix style paths on cmSystemTools as
      // soon as the generator is set.  This allows gmake to be used
      // on windows.
      cmSystemTools::SetForceUnixPaths
        (this->GlobalGenerator->GetForceUnixPaths());
      }
    else
      {
#if defined(__BORLANDC__) && defined(_WIN32)
      this->SetGlobalGenerator(new cmGlobalBorlandMakefileGenerator);
#elif defined(_WIN32) && !defined(__CYGWIN__) && !defined(CMAKE_BOOT_MINGW)
      std::string installedCompiler;
      std::string mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft"
        "\\VisualStudio\\8.0\\Setup;Dbghelp_path]";
      cmSystemTools::ExpandRegistryValues(mp);
      if (!(mp == "/registry"))
        {
        installedCompiler = "Visual Studio 8 2005";
        }
      else
        {
        mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft"
          "\\VisualStudio\\7.1;InstallDir]";
        cmSystemTools::ExpandRegistryValues(mp);
        if (!(mp == "/registry"))
          {
          installedCompiler = "Visual Studio 7 .NET 2003";
          }
        else
          {
          mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft"
            "\\VisualStudio\\7.0;InstallDir]";
          cmSystemTools::ExpandRegistryValues(mp);
          if (!(mp == "/registry"))
            {
            installedCompiler = "Visual Studio 7";
            }
          else
            {
            installedCompiler = "Visual Studio 6";
            }
          }
        }
      cmGlobalGenerator* gen
        = this->CreateGlobalGenerator(installedCompiler.c_str());
      if(!gen)
        {
        gen = new cmGlobalNMakeMakefileGenerator;
        }
      this->SetGlobalGenerator(gen);
#else
      this->SetGlobalGenerator(new cmGlobalUnixMakefileGenerator3);
#endif
      }
    if(!this->GlobalGenerator)
      {
      cmSystemTools::Error("Could not create generator");
      return -1;
      }
    }

  const char* genName = this->CacheManager->GetCacheValue("CMAKE_GENERATOR");
  if(genName)
    {
    if(strcmp(this->GlobalGenerator->GetName(), genName) != 0)
      {
      std::string message = "Error: generator : ";
      message += this->GlobalGenerator->GetName();
      message += "\nDoes not match the generator used previously: ";
      message += genName;
      message +=
        "\nEither remove the CMakeCache.txt file or choose a different"
        " binary directory.";
      cmSystemTools::Error(message.c_str());
      return -2;
      }
    }
  if(!this->CacheManager->GetCacheValue("CMAKE_GENERATOR"))
    {
    this->CacheManager->AddCacheEntry("CMAKE_GENERATOR", 
                                      this->GlobalGenerator->GetName(),
                                      "Name of generator.",
                                      cmCacheManager::INTERNAL);
    }

  // reset any system configuration information, except for when we are
  // InTryCompile. With TryCompile the system info is taken from the parent's
  // info to save time
  if (!this->InTryCompile)
    {
    this->GlobalGenerator->ClearEnabledLanguages();
    }

  this->CleanupWrittenFiles();

  // Truncate log files
  if (!this->InTryCompile)
    {
    this->TruncateOutputLog("CMakeOutput.log");
    this->TruncateOutputLog("CMakeError.log");
    }

  // actually do the configure
  this->GlobalGenerator->Configure();
  
  // Before saving the cache
  // if the project did not define one of the entries below, add them now
  // so users can edit the values in the cache:
  // LIBRARY_OUTPUT_PATH
  // EXECUTABLE_OUTPUT_PATH
  if(!this->CacheManager->GetCacheValue("LIBRARY_OUTPUT_PATH"))
    {
    this->CacheManager->AddCacheEntry
      ("LIBRARY_OUTPUT_PATH", "",
       "Single output directory for building all libraries.",
       cmCacheManager::PATH);
    } 
  if(!this->CacheManager->GetCacheValue("EXECUTABLE_OUTPUT_PATH"))
    {
    this->CacheManager->AddCacheEntry
      ("EXECUTABLE_OUTPUT_PATH", "",
       "Single output directory for building all executables.",
       cmCacheManager::PATH);
    }  
  if(!this->CacheManager->GetCacheValue("CMAKE_USE_RELATIVE_PATHS"))
    {
    this->CacheManager->AddCacheEntry
      ("CMAKE_USE_RELATIVE_PATHS", false,
       "If true, cmake will use relative paths in makefiles and projects.");
    cmCacheManager::CacheIterator it =
      this->CacheManager->GetCacheIterator("CMAKE_USE_RELATIVE_PATHS");
    if ( !it.PropertyExists("ADVANCED") )
      {
      it.SetProperty("ADVANCED", "1");
      }
    }

  if(cmSystemTools::GetFatalErrorOccured() &&
     (!this->CacheManager->GetCacheValue("CMAKE_MAKE_PROGRAM") ||
      cmSystemTools::IsOff(this->CacheManager->
                           GetCacheValue("CMAKE_MAKE_PROGRAM"))))
    {
    // We must have a bad generator selection.  Wipe the cache entry so the
    // user can select another.
    this->CacheManager->RemoveCacheEntry("CMAKE_GENERATOR");
    }
  // only save the cache if there were no fatal errors
  if ( !this->ScriptMode )
    {
    this->CacheManager->SaveCache(this->GetHomeOutputDirectory());
    }
  if ( !this->GraphVizFile.empty() )
    {
    std::cout << "Generate graphviz: " << this->GraphVizFile << std::endl;
    this->GenerateGraphViz(this->GraphVizFile.c_str());
    }
  if(cmSystemTools::GetErrorOccuredFlag())
    {
    return -1;
    }
  return 0;
}