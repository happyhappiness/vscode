@@ -104,17 +104,17 @@ void cmNeedBackwardsCompatibility(const std::string& variable,
 
 cmake::cmake()
 {
-  m_DebugTryCompile = false;
-  m_ClearBuildSystem = false;
-  m_FileComparison = new cmFileTimeComparison;
+  this->DebugTryCompile = false;
+  this->ClearBuildSystem = false;
+  this->FileComparison = new cmFileTimeComparison;
 
 #ifdef __APPLE__
   struct rlimit rlp;
   if(!getrlimit(RLIMIT_STACK, &rlp))
     {
-    if(rlp.rlim_cur != rlp.rlim_max)
+    if(rlp.rlithis->cur != rlp.rlithis->max)
       {
-        rlp.rlim_cur = rlp.rlim_max;
+        rlp.rlithis->cur = rlp.rlithis->max;
          setrlimit(RLIMIT_STACK, &rlp);
       }
     }
@@ -130,21 +130,21 @@ cmake::cmake()
     cmSystemTools::PutEnv("MAKEFLAGS=");
     }
 
-  m_Verbose = false;
-  m_InTryCompile = false;
-  m_CacheManager = new cmCacheManager;
-  m_GlobalGenerator = 0;
-  m_ProgressCallback = 0;
-  m_ProgressCallbackClientData = 0;
-  m_ScriptMode = false;
+  this->Verbose = false;
+  this->InTryCompile = false;
+  this->CacheManager = new cmCacheManager;
+  this->GlobalGenerator = 0;
+  this->ProgressCallback = 0;
+  this->ProgressCallbackClientData = 0;
+  this->ScriptMode = false;
 
 #ifdef CMAKE_BUILD_WITH_CMAKE
-  m_VariableWatch = new cmVariableWatch;
-  m_VariableWatch->AddWatch("CMAKE_WORDS_BIGENDIAN",
+  this->VariableWatch = new cmVariableWatch;
+  this->VariableWatch->AddWatch("CMAKE_WORDS_BIGENDIAN",
                             cmNeedBackwardsCompatibility);
-  m_VariableWatch->AddWatch("CMAKE_SIZEOF_INT",
+  this->VariableWatch->AddWatch("CMAKE_SIZEOF_INT",
                             cmNeedBackwardsCompatibility);
-  m_VariableWatch->AddWatch("CMAKE_X_LIBS",
+  this->VariableWatch->AddWatch("CMAKE_X_LIBS",
                             cmNeedBackwardsCompatibility);
 #endif
 
@@ -157,28 +157,28 @@ cmake::cmake()
 
 cmake::~cmake()
 {
-  delete m_CacheManager;
-  if (m_GlobalGenerator)
+  delete this->CacheManager;
+  if (this->GlobalGenerator)
     {
-    delete m_GlobalGenerator;
-    m_GlobalGenerator = 0;
+    delete this->GlobalGenerator;
+    this->GlobalGenerator = 0;
     }
-  for(RegisteredCommandsMap::iterator j = m_Commands.begin();
-      j != m_Commands.end(); ++j)
+  for(RegisteredCommandsMap::iterator j = this->Commands.begin();
+      j != this->Commands.end(); ++j)
     {
     delete (*j).second;
     }
 #ifdef CMAKE_BUILD_WITH_CMAKE
-  delete m_VariableWatch;
+  delete this->VariableWatch;
 #endif
-  delete m_FileComparison;
+  delete this->FileComparison;
 }
 
 void cmake::CleanupCommandsAndMacros()
 {
   std::vector<cmCommand*> commands;
-  for(RegisteredCommandsMap::iterator j = m_Commands.begin();
-      j != m_Commands.end(); ++j)
+  for(RegisteredCommandsMap::iterator j = this->Commands.begin();
+      j != this->Commands.end(); ++j)
     {
     if ( !j->second->IsA("cmMacroHelperCommand") )
       {
@@ -189,27 +189,27 @@ void cmake::CleanupCommandsAndMacros()
       delete j->second;
       }
     }
-  m_Commands.erase(m_Commands.begin(), m_Commands.end());
+  this->Commands.erase(this->Commands.begin(), this->Commands.end());
   std::vector<cmCommand*>::iterator it;
   for ( it = commands.begin(); it != commands.end();
     ++ it )
     {
-    m_Commands[cmSystemTools::LowerCase((*it)->GetName())] = *it;
+    this->Commands[cmSystemTools::LowerCase((*it)->GetName())] = *it;
     }
 }
 
 bool cmake::CommandExists(const char* name) const
 {
   std::string sName = cmSystemTools::LowerCase(name);
-  return (m_Commands.find(sName) != m_Commands.end());
+  return (this->Commands.find(sName) != this->Commands.end());
 }
 
 cmCommand *cmake::GetCommand(const char *name)
 {
   cmCommand* rm = 0;
   std::string sName = cmSystemTools::LowerCase(name);
-  RegisteredCommandsMap::iterator pos = m_Commands.find(sName);
-  if (pos != m_Commands.end())
+  RegisteredCommandsMap::iterator pos = this->Commands.find(sName);
+  if (pos != this->Commands.end())
     {
     rm = (*pos).second;
     }
@@ -221,35 +221,35 @@ void cmake::RenameCommand(const char*oldName, const char* newName)
   // if the command already exists, free the old one
   std::string sOldName = cmSystemTools::LowerCase(oldName);
   std::string sNewName = cmSystemTools::LowerCase(newName);
-  RegisteredCommandsMap::iterator pos = m_Commands.find(sOldName);
-  if ( pos == m_Commands.end() )
+  RegisteredCommandsMap::iterator pos = this->Commands.find(sOldName);
+  if ( pos == this->Commands.end() )
     {
     return;
     }
   cmCommand* cmd = pos->second;
 
-  pos = m_Commands.find(sNewName);
-  if (pos != m_Commands.end())
+  pos = this->Commands.find(sNewName);
+  if (pos != this->Commands.end())
     {
     delete pos->second;
-    m_Commands.erase(pos);
+    this->Commands.erase(pos);
     }
-  m_Commands.insert(RegisteredCommandsMap::value_type(sNewName, cmd));
-  pos = m_Commands.find(sOldName);
-  m_Commands.erase(pos);
+  this->Commands.insert(RegisteredCommandsMap::value_type(sNewName, cmd));
+  pos = this->Commands.find(sOldName);
+  this->Commands.erase(pos);
 }
 
 void cmake::AddCommand(cmCommand* wg)
 {
   std::string name = cmSystemTools::LowerCase(wg->GetName());
   // if the command already exists, free the old one
-  RegisteredCommandsMap::iterator pos = m_Commands.find(name);
-  if (pos != m_Commands.end())
+  RegisteredCommandsMap::iterator pos = this->Commands.find(name);
+  if (pos != this->Commands.end())
     {
     delete pos->second;
-    m_Commands.erase(pos);
+    this->Commands.erase(pos);
     }
-  m_Commands.insert( RegisteredCommandsMap::value_type(name, wg));
+  this->Commands.insert( RegisteredCommandsMap::value_type(name, wg));
 }
 
 // Parse the args
@@ -270,7 +270,7 @@ bool cmake::SetCacheArgs(const std::vector<std::string>& args)
       if(cmCacheManager::ParseEntry(entry.c_str(), var, value, type) ||
         cmCacheManager::ParseEntry(entry.c_str(), var, value))
         {
-        this->m_CacheManager->AddCacheEntry(var.c_str(), value.c_str(),
+        this->CacheManager->AddCacheEntry(var.c_str(), value.c_str(),
           "No help, variable specified on the command line.",
           type);
         }
@@ -380,12 +380,12 @@ void cmake::SetArgs(const std::vector<std::string>& args)
       }
     else if((i < args.size()-1) && (arg.find("--check-build-system",0) == 0))
       {
-      m_CheckBuildSystem = args[++i];
-      m_ClearBuildSystem = (atoi(args[++i].c_str()) > 0);
+      this->CheckBuildSystemArgument = args[++i];
+      this->ClearBuildSystem = (atoi(args[++i].c_str()) > 0);
       }
     else if(arg.find("-V",0) == 0)
       {
-        m_Verbose = true;
+        this->Verbose = true;
       }
     else if(arg.find("-D",0) == 0)
       {
@@ -405,8 +405,8 @@ void cmake::SetArgs(const std::vector<std::string>& args)
       std::string path = arg.substr(strlen("--graphviz="));
       path = cmSystemTools::CollapseFullPath(path.c_str());
       cmSystemTools::ConvertToUnixSlashes(path);
-      m_GraphVizFile = path;
-      if ( m_GraphVizFile.empty() )
+      this->GraphVizFile = path;
+      if ( this->GraphVizFile.empty() )
         {
         cmSystemTools::Error("No file specified for --graphviz");
         }
@@ -615,7 +615,7 @@ int cmake::AddCMakePaths(const char *arg0)
     return 0;
     }
   // Save the value in the cache
-  this->m_CacheManager->AddCacheEntry
+  this->CacheManager->AddCacheEntry
     ("CMAKE_COMMAND",cMakeSelf.c_str(), "Path to CMake executable.",
      cmCacheManager::INTERNAL);
 
@@ -631,13 +631,13 @@ int cmake::AddCMakePaths(const char *arg0)
     "/ctest" + cmSystemTools::GetFilenameExtension(cMakeSelf);
   if(cmSystemTools::FileExists(ctestCommand.c_str()))
     {
-    this->m_CacheManager->AddCacheEntry
+    this->CacheManager->AddCacheEntry
       ("CMAKE_CTEST_COMMAND", ctestCommand.c_str(),
        "Path to ctest program executable.", cmCacheManager::INTERNAL);
     }
   if(cmSystemTools::FileExists(editCacheCommand.c_str()))
     {
-    this->m_CacheManager->AddCacheEntry
+    this->CacheManager->AddCacheEntry
       ("CMAKE_EDIT_COMMAND", editCacheCommand.c_str(),
        "Path to cache edit program executable.", cmCacheManager::INTERNAL);
     }
@@ -708,7 +708,7 @@ int cmake::AddCMakePaths(const char *arg0)
       cMakeRoot.c_str());
     return 0;
     }
-  this->m_CacheManager->AddCacheEntry
+  this->CacheManager->AddCacheEntry
     ("CMAKE_ROOT", cMakeRoot.c_str(),
      "Path to CMake installation.", cmCacheManager::INTERNAL);
 
@@ -761,7 +761,7 @@ void CMakeCommandUsage(const char* program)
   cmSystemTools::Error(errorStream.str().c_str());
 }
 
-int cmake::CMakeCommand(std::vector<std::string>& args)
+int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
 {
   if (args.size() > 1)
     {
@@ -1078,17 +1078,17 @@ int cmake::CMakeCommand(std::vector<std::string>& args)
 
 void cmake::GetRegisteredGenerators(std::vector<std::string>& names)
 {
-  for(RegisteredGeneratorsMap::const_iterator i = m_Generators.begin();
-      i != m_Generators.end(); ++i)
+  for(RegisteredGeneratorsMap::const_iterator i = this->Generators.begin();
+      i != this->Generators.end(); ++i)
     {
     names.push_back(i->first);
     }
 }
 
 cmGlobalGenerator* cmake::CreateGlobalGenerator(const char* name)
 {
-  RegisteredGeneratorsMap::const_iterator i = m_Generators.find(name);
-  if(i != m_Generators.end())
+  RegisteredGeneratorsMap::const_iterator i = this->Generators.find(name);
+  if(i != this->Generators.end())
     {
     cmGlobalGenerator* generator = (i->second)();
     generator->SetCMakeInstance(this);
@@ -1102,62 +1102,62 @@ cmGlobalGenerator* cmake::CreateGlobalGenerator(const char* name)
 
 void cmake::SetHomeDirectory(const char* dir)
 {
-  m_cmHomeDirectory = dir;
-  cmSystemTools::ConvertToUnixSlashes(m_cmHomeDirectory);
+  this->cmHomeDirectory = dir;
+  cmSystemTools::ConvertToUnixSlashes(this->cmHomeDirectory);
 }
 
 void cmake::SetHomeOutputDirectory(const char* lib)
 {
-  m_HomeOutputDirectory = lib;
-  cmSystemTools::ConvertToUnixSlashes(m_HomeOutputDirectory);
+  this->HomeOutputDirectory = lib;
+  cmSystemTools::ConvertToUnixSlashes(this->HomeOutputDirectory);
 }
 
 void cmake::SetGlobalGenerator(cmGlobalGenerator *gg)
 {
   // delete the old generator
-  if (m_GlobalGenerator)
+  if (this->GlobalGenerator)
     {
-    delete m_GlobalGenerator;
+    delete this->GlobalGenerator;
     // restore the original environment variables CXX and CC
     // Restor CC
     std::string env = "CC=";
-    if(m_CCEnvironment.size())
+    if(this->CCEnvironment.size())
       {
-      env += m_CCEnvironment;
+      env += this->CCEnvironment;
       }
     cmSystemTools::PutEnv(env.c_str());
     env = "CXX=";
-    if(m_CXXEnvironment.size())
+    if(this->CXXEnvironment.size())
       {
-      env += m_CXXEnvironment;
+      env += this->CXXEnvironment;
       }
     cmSystemTools::PutEnv(env.c_str());
     }
 
   // set the new
-  m_GlobalGenerator = gg;
-  // set the global flag for unix style paths on cmSystemTools as
+  this->GlobalGenerator = gg;
+  // set the global flag for unix style paths on cmSystemTools as 
   // soon as the generator is set.  This allows gmake to be used
   // on windows.
-  cmSystemTools::SetForceUnixPaths(m_GlobalGenerator->GetForceUnixPaths());
+  cmSystemTools::SetForceUnixPaths(this->GlobalGenerator->GetForceUnixPaths());
   // Save the environment variables CXX and CC
   const char* cxx = getenv("CXX");
   const char* cc = getenv("CC");
   if(cxx)
     {
-    m_CXXEnvironment = cxx;
+    this->CXXEnvironment = cxx;
     }
   else
     {
-    m_CXXEnvironment = "";
+    this->CXXEnvironment = "";
     }
   if(cc)
     {
-    m_CCEnvironment = cc;
+    this->CCEnvironment = cc;
     }
   else
     {
-    m_CCEnvironment = "";
+    this->CCEnvironment = "";
     }
   // set the cmake instance just to be sure
   gg->SetCMakeInstance(this);
@@ -1193,10 +1193,10 @@ int cmake::DoPreConfigureChecks()
     }
 
   // do a sanity check on some values
-  if(m_CacheManager->GetCacheValue("CMAKE_HOME_DIRECTORY"))
+  if(this->CacheManager->GetCacheValue("CMAKE_HOME_DIRECTORY"))
     {
-    std::string cacheStart =
-      m_CacheManager->GetCacheValue("CMAKE_HOME_DIRECTORY");
+    std::string cacheStart = 
+      this->CacheManager->GetCacheValue("CMAKE_HOME_DIRECTORY");
     cacheStart += "/CMakeLists.txt";
     std::string currentStart = this->GetHomeDirectory();
     currentStart += "/CMakeLists.txt";
@@ -1226,7 +1226,7 @@ int cmake::Configure()
   this->CleanupCommandsAndMacros();
 
   int res = 0;
-  if ( !m_ScriptMode )
+  if ( !this->ScriptMode )
     {
     res = this->DoPreConfigureChecks();
     }
@@ -1236,41 +1236,42 @@ int cmake::Configure()
     }
   if ( !res )
     {
-    m_CacheManager->AddCacheEntry("CMAKE_HOME_DIRECTORY",
-      this->GetHomeDirectory(),
-      "Start directory with the top level CMakeLists.txt file for this "
-      "project",
-      cmCacheManager::INTERNAL);
+    this->CacheManager->AddCacheEntry
+      ("CMAKE_HOME_DIRECTORY", 
+       this->GetHomeDirectory(),
+       "Start directory with the top level CMakeLists.txt file for this "
+       "project",
+       cmCacheManager::INTERNAL);
     }
 
   // set the default BACKWARDS compatibility to the current version
-  if(!m_CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
+  if(!this->CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
     {
     char ver[256];
     sprintf(ver,"%i.%i",cmMakefile::GetMajorVersion(),
             cmMakefile::GetMinorVersion());
-    this->m_CacheManager->AddCacheEntry
-      ("CMAKE_BACKWARDS_COMPATIBILITY",ver,
+    this->CacheManager->AddCacheEntry
+      ("CMAKE_BACKWARDS_COMPATIBILITY",ver, 
        "For backwards compatibility, what version of CMake commands and "
        "syntax should this version of CMake allow.",
        cmCacheManager::STRING);
     }
 
   // no generator specified on the command line
-  if(!m_GlobalGenerator)
+  if(!this->GlobalGenerator)
     {
-    const char* genName = m_CacheManager->GetCacheValue("CMAKE_GENERATOR");
+    const char* genName = this->CacheManager->GetCacheValue("CMAKE_GENERATOR");
     if(genName)
       {
-      m_GlobalGenerator = this->CreateGlobalGenerator(genName);
+      this->GlobalGenerator = this->CreateGlobalGenerator(genName);
       }
-    if(m_GlobalGenerator)
+    if(this->GlobalGenerator)
       {
       // set the global flag for unix style paths on cmSystemTools as
       // soon as the generator is set.  This allows gmake to be used
       // on windows.
-      cmSystemTools::SetForceUnixPaths(
-        m_GlobalGenerator->GetForceUnixPaths());
+      cmSystemTools::SetForceUnixPaths
+        (this->GlobalGenerator->GetForceUnixPaths());
       }
     else
       {
@@ -1320,20 +1321,20 @@ int cmake::Configure()
       this->SetGlobalGenerator(new cmGlobalUnixMakefileGenerator3);
 #endif
       }
-    if(!m_GlobalGenerator)
+    if(!this->GlobalGenerator)
       {
       cmSystemTools::Error("Could not create generator");
       return -1;
       }
     }
 
-  const char* genName = m_CacheManager->GetCacheValue("CMAKE_GENERATOR");
+  const char* genName = this->CacheManager->GetCacheValue("CMAKE_GENERATOR");
   if(genName)
     {
-    if(strcmp(m_GlobalGenerator->GetName(), genName) != 0)
+    if(strcmp(this->GlobalGenerator->GetName(), genName) != 0)
       {
       std::string message = "Error: generator : ";
-      message += m_GlobalGenerator->GetName();
+      message += this->GlobalGenerator->GetName();
       message += "\nDoes not match the generator used previously: ";
       message += genName;
       message +=
@@ -1343,81 +1344,84 @@ int cmake::Configure()
       return -2;
       }
     }
-  if(!m_CacheManager->GetCacheValue("CMAKE_GENERATOR"))
+  if(!this->CacheManager->GetCacheValue("CMAKE_GENERATOR"))
     {
-    m_CacheManager->AddCacheEntry("CMAKE_GENERATOR",
-                                  m_GlobalGenerator->GetName(),
-                                  "Name of generator.",
-                                  cmCacheManager::INTERNAL);
+    this->CacheManager->AddCacheEntry("CMAKE_GENERATOR", 
+                                      this->GlobalGenerator->GetName(),
+                                      "Name of generator.",
+                                      cmCacheManager::INTERNAL);
     }
 
   // reset any system configuration information, except for when we are
   // InTryCompile. With TryCompile the system info is taken from the parent's
   // info to save time
-  if (!m_InTryCompile)
+  if (!this->InTryCompile)
     {
-    m_GlobalGenerator->ClearEnabledLanguages();
+    this->GlobalGenerator->ClearEnabledLanguages();
     }
 
   this->CleanupWrittenFiles();
 
   // Truncate log files
-  if (!m_InTryCompile)
+  if (!this->InTryCompile)
     {
     this->TruncateOutputLog("CMakeOutput.log");
     this->TruncateOutputLog("CMakeError.log");
     }
 
   // actually do the configure
-  m_GlobalGenerator->Configure();
-
+  this->GlobalGenerator->Configure();
+  
   // Before saving the cache
   // if the project did not define one of the entries below, add them now
   // so users can edit the values in the cache:
   // LIBRARY_OUTPUT_PATH
   // EXECUTABLE_OUTPUT_PATH
-  if(!m_CacheManager->GetCacheValue("LIBRARY_OUTPUT_PATH"))
-    {
-    m_CacheManager->AddCacheEntry("LIBRARY_OUTPUT_PATH", "",
-      "Single output directory for building all libraries.",
-      cmCacheManager::PATH);
-    }
-  if(!m_CacheManager->GetCacheValue("EXECUTABLE_OUTPUT_PATH"))
-    {
-    m_CacheManager->AddCacheEntry("EXECUTABLE_OUTPUT_PATH", "",
-      "Single output directory for building all executables.",
-      cmCacheManager::PATH);
-    }
-  if(!m_CacheManager->GetCacheValue("CMAKE_USE_RELATIVE_PATHS"))
-    {
-    m_CacheManager->AddCacheEntry("CMAKE_USE_RELATIVE_PATHS", false,
-      "If true, cmake will use relative paths in makefiles and projects.");
+  if(!this->CacheManager->GetCacheValue("LIBRARY_OUTPUT_PATH"))
+    {
+    this->CacheManager->AddCacheEntry
+      ("LIBRARY_OUTPUT_PATH", "",
+       "Single output directory for building all libraries.",
+       cmCacheManager::PATH);
+    } 
+  if(!this->CacheManager->GetCacheValue("EXECUTABLE_OUTPUT_PATH"))
+    {
+    this->CacheManager->AddCacheEntry
+      ("EXECUTABLE_OUTPUT_PATH", "",
+       "Single output directory for building all executables.",
+       cmCacheManager::PATH);
+    }  
+  if(!this->CacheManager->GetCacheValue("CMAKE_USE_RELATIVE_PATHS"))
+    {
+    this->CacheManager->AddCacheEntry
+      ("CMAKE_USE_RELATIVE_PATHS", false,
+       "If true, cmake will use relative paths in makefiles and projects.");
     cmCacheManager::CacheIterator it =
-      m_CacheManager->GetCacheIterator("CMAKE_USE_RELATIVE_PATHS");
+      this->CacheManager->GetCacheIterator("CMAKE_USE_RELATIVE_PATHS");
     if ( !it.PropertyExists("ADVANCED") )
       {
       it.SetProperty("ADVANCED", "1");
       }
     }
 
   if(cmSystemTools::GetFatalErrorOccured() &&
-     (!this->m_CacheManager->GetCacheValue("CMAKE_MAKE_PROGRAM") ||
-      cmSystemTools::IsOff(
-        this->m_CacheManager->GetCacheValue("CMAKE_MAKE_PROGRAM"))))
+     (!this->CacheManager->GetCacheValue("CMAKE_MAKE_PROGRAM") ||
+      cmSystemTools::IsOff(this->CacheManager->
+                           GetCacheValue("CMAKE_MAKE_PROGRAM"))))
     {
     // We must have a bad generator selection.  Wipe the cache entry so the
     // user can select another.
-    m_CacheManager->RemoveCacheEntry("CMAKE_GENERATOR");
+    this->CacheManager->RemoveCacheEntry("CMAKE_GENERATOR");
     }
   // only save the cache if there were no fatal errors
-  if ( !m_ScriptMode && !cmSystemTools::GetFatalErrorOccured() )
+  if ( !this->ScriptMode && !cmSystemTools::GetFatalErrorOccured() )
     {
-    this->m_CacheManager->SaveCache(this->GetHomeOutputDirectory());
+    this->CacheManager->SaveCache(this->GetHomeOutputDirectory());
     }
-  if ( !m_GraphVizFile.empty() )
+  if ( !this->GraphVizFile.empty() )
     {
-    std::cout << "Generate graphviz: " << m_GraphVizFile << std::endl;
-    this->GenerateGraphViz(m_GraphVizFile.c_str());
+    std::cout << "Generate graphviz: " << this->GraphVizFile << std::endl;
+    this->GenerateGraphViz(this->GraphVizFile.c_str());
     }
   if(cmSystemTools::GetErrorOccuredFlag())
     {
@@ -1428,12 +1432,12 @@ int cmake::Configure()
 
 bool cmake::CacheVersionMatches()
 {
-  const char* majv
-    = m_CacheManager->GetCacheValue("CMAKE_CACHE_MAJOR_VERSION");
-  const char* minv
-    = m_CacheManager->GetCacheValue("CMAKE_CACHE_MINOR_VERSION");
-  const char* relv
-    = m_CacheManager->GetCacheValue("CMAKE_CACHE_RELEASE_VERSION");
+  const char* majv = 
+    this->CacheManager->GetCacheValue("CMAKE_CACHE_MAJOR_VERSION");
+  const char* minv = 
+    this->CacheManager->GetCacheValue("CMAKE_CACHE_MINOR_VERSION");
+  const char* relv = 
+    this->CacheManager->GetCacheValue("CMAKE_CACHE_RELEASE_VERSION");
   bool cacheSameCMake = false;
   if(majv &&
      atoi(majv) == static_cast<int>(cmMakefile::GetMajorVersion())
@@ -1480,9 +1484,9 @@ int cmake::Run(const std::vector<std::string>& args, bool noconfigure)
     }
 
   // set the cmake command
-  m_CMakeCommand = args[0];
-
-  if ( !m_ScriptMode )
+  this->CMakeCommand = args[0];
+  
+  if ( !this->ScriptMode )
     {
     // load the cache
     if(this->LoadCache() < 0)
@@ -1493,7 +1497,7 @@ int cmake::Run(const std::vector<std::string>& args, bool noconfigure)
     }
   else
     {
-    this->AddCMakePaths(m_CMakeCommand.c_str());
+    this->AddCMakePaths(this->CMakeCommand.c_str());
     }
 
   // Add any cache args
@@ -1504,7 +1508,7 @@ int cmake::Run(const std::vector<std::string>& args, bool noconfigure)
     }
 
   // In script mode we terminate after running the script.
-  if(m_ScriptMode)
+  if(this->ScriptMode)
     {
     if(cmSystemTools::GetErrorOccuredFlag())
       {
@@ -1540,7 +1544,7 @@ int cmake::Run(const std::vector<std::string>& args, bool noconfigure)
   this->SetStartDirectory(this->GetHomeDirectory());
   this->SetStartOutputDirectory(this->GetHomeOutputDirectory());
   int ret = this->Configure();
-  if (ret || m_ScriptMode)
+  if (ret || this->ScriptMode)
     {
     return ret;
     }
@@ -1560,11 +1564,11 @@ int cmake::Run(const std::vector<std::string>& args, bool noconfigure)
 
 int cmake::Generate()
 {
-  if(!m_GlobalGenerator)
+  if(!this->GlobalGenerator)
     {
     return -1;
     }
-  m_GlobalGenerator->Generate();
+  this->GlobalGenerator->Generate();
   if(cmSystemTools::GetErrorOccuredFlag())
     {
     return -1;
@@ -1591,14 +1595,14 @@ void cmake::AddCacheEntry(const char* key, const char* value,
                           const char* helpString,
                           int type)
 {
-  m_CacheManager->AddCacheEntry(key, value,
-                                helpString,
-                                cmCacheManager::CacheEntryType(type));
+  this->CacheManager->AddCacheEntry(key, value, 
+                                    helpString,
+                                    cmCacheManager::CacheEntryType(type));
 }
 
 const char* cmake::GetCacheDefinition(const char* name) const
 {
-  return m_CacheManager->GetCacheValue(name);
+  return this->CacheManager->GetCacheValue(name);
 }
 
 int cmake::DumpDocumentationToFile(std::ostream& f)
@@ -1614,8 +1618,8 @@ int cmake::DumpDocumentationToFile(std::ostream& f)
   f << "<html>\n";
   f << "<h1>Documentation for commands of CMake " << tmp << "</h1>\n";
   f << "<ul>\n";
-  for(RegisteredCommandsMap::iterator j = m_Commands.begin();
-      j != m_Commands.end(); ++j)
+  for(RegisteredCommandsMap::iterator j = this->Commands.begin();
+      j != this->Commands.end(); ++j)
     {
     name = (*j).second->GetName();
     terse = (*j).second->GetTerseDocumentation();
@@ -1646,42 +1650,42 @@ void cmake::AddDefaultGenerators()
 {
 #if defined(_WIN32) && !defined(__CYGWIN__)
 # if !defined(CMAKE_BOOT_MINGW)
-  m_Generators[cmGlobalVisualStudio6Generator::GetActualName()] =
+  this->Generators[cmGlobalVisualStudio6Generator::GetActualName()] =
     &cmGlobalVisualStudio6Generator::New;
-  m_Generators[cmGlobalVisualStudio7Generator::GetActualName()] =
+  this->Generators[cmGlobalVisualStudio7Generator::GetActualName()] =
     &cmGlobalVisualStudio7Generator::New;
-  m_Generators[cmGlobalVisualStudio71Generator::GetActualName()] =
+  this->Generators[cmGlobalVisualStudio71Generator::GetActualName()] =
     &cmGlobalVisualStudio71Generator::New;
-  m_Generators[cmGlobalVisualStudio8Generator::GetActualName()] =
+  this->Generators[cmGlobalVisualStudio8Generator::GetActualName()] =
     &cmGlobalVisualStudio8Generator::New;
-  m_Generators[cmGlobalBorlandMakefileGenerator::GetActualName()] =
+  this->Generators[cmGlobalBorlandMakefileGenerator::GetActualName()] =
     &cmGlobalBorlandMakefileGenerator::New;
-  m_Generators[cmGlobalNMakeMakefileGenerator::GetActualName()] =
+  this->Generators[cmGlobalNMakeMakefileGenerator::GetActualName()] =
     &cmGlobalNMakeMakefileGenerator::New;
-  m_Generators[cmGlobalWatcomWMakeGenerator::GetActualName()] =
+  this->Generators[cmGlobalWatcomWMakeGenerator::GetActualName()] =
     &cmGlobalWatcomWMakeGenerator::New;
 # endif
-  m_Generators[cmGlobalMSYSMakefileGenerator::GetActualName()] =
+  this->Generators[cmGlobalMSYSMakefileGenerator::GetActualName()] =
     &cmGlobalMSYSMakefileGenerator::New;
-  m_Generators[cmGlobalMinGWMakefileGenerator::GetActualName()] =
+  this->Generators[cmGlobalMinGWMakefileGenerator::GetActualName()] =
     &cmGlobalMinGWMakefileGenerator::New;
 #endif
-  m_Generators[cmGlobalUnixMakefileGenerator3::GetActualName()] =
+  this->Generators[cmGlobalUnixMakefileGenerator3::GetActualName()] =
     &cmGlobalUnixMakefileGenerator3::New;
 #ifdef CMAKE_USE_XCODE
-  m_Generators[cmGlobalXCodeGenerator::GetActualName()] =
+  this->Generators[cmGlobalXCodeGenerator::GetActualName()] =
     &cmGlobalXCodeGenerator::New;
 #endif
 #ifdef CMAKE_USE_KDEVELOP
-  m_Generators[cmGlobalKdevelopGenerator::GetActualName()] =
+  this->Generators[cmGlobalKdevelopGenerator::GetActualName()] =
      &cmGlobalKdevelopGenerator::New;
 #endif
 }
 
 int cmake::LoadCache()
 {
   // could we not read the cache
-  if (!m_CacheManager->LoadCache(this->GetHomeOutputDirectory()))
+  if (!this->CacheManager->LoadCache(this->GetHomeOutputDirectory()))
     {
     // if it does exist, but isn;t readable then warn the user
     std::string cacheFile = this->GetHomeOutputDirectory();
@@ -1696,7 +1700,7 @@ int cmake::LoadCache()
       }
     }
 
-  if (m_CMakeCommand.size() < 2)
+  if (this->CMakeCommand.size() < 2)
     {
     cmSystemTools::Error(
       "cmake command was not specified prior to loading the cache in "
@@ -1705,19 +1709,19 @@ int cmake::LoadCache()
     }
 
   // setup CMAKE_ROOT and CMAKE_COMMAND
-  if(!this->AddCMakePaths(m_CMakeCommand.c_str()))
+  if(!this->AddCMakePaths(this->CMakeCommand.c_str()))
     {
     return -3;
     }
 
   // set the default BACKWARDS compatibility to the current version
-  if(!m_CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
+  if(!this->CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
     {
     char ver[256];
     sprintf(ver,"%i.%i",cmMakefile::GetMajorVersion(),
             cmMakefile::GetMinorVersion());
-    this->m_CacheManager->AddCacheEntry
-      ("CMAKE_BACKWARDS_COMPATIBILITY",ver,
+    this->CacheManager->AddCacheEntry
+      ("CMAKE_BACKWARDS_COMPATIBILITY",ver, 
        "For backwards compatibility, what version of CMake commands and "
        "syntax should this version of CMake allow.",
        cmCacheManager::STRING);
@@ -1726,26 +1730,26 @@ int cmake::LoadCache()
   return 0;
 }
 
-void cmake::SetProgressCallback(ProgressCallback f, void *cd)
+void cmake::SetProgressCallback(ProgressCallbackType f, void *cd)
 {
-  m_ProgressCallback = f;
-  m_ProgressCallbackClientData = cd;
+  this->ProgressCallback = f;
+  this->ProgressCallbackClientData = cd;
 }
 
 void cmake::UpdateProgress(const char *msg, float prog)
 {
-  if(m_ProgressCallback && !m_InTryCompile)
+  if(this->ProgressCallback && !this->InTryCompile)
     {
-    (*m_ProgressCallback)(msg, prog, m_ProgressCallbackClientData);
+    (*this->ProgressCallback)(msg, prog, this->ProgressCallbackClientData);
     return;
     }
 }
 
 void cmake::GetCommandDocumentation(
   std::vector<cmDocumentationEntry>& v) const
 {
-  for(RegisteredCommandsMap::const_iterator j = m_Commands.begin();
-      j != m_Commands.end(); ++j)
+  for(RegisteredCommandsMap::const_iterator j = this->Commands.begin();
+      j != this->Commands.end(); ++j)
     {
     cmDocumentationEntry e =
       {
@@ -1761,8 +1765,8 @@ void cmake::GetCommandDocumentation(
 
 void cmake::GetGeneratorDocumentation(std::vector<cmDocumentationEntry>& v)
 {
-  for(RegisteredGeneratorsMap::const_iterator i = m_Generators.begin();
-      i != m_Generators.end(); ++i)
+  for(RegisteredGeneratorsMap::const_iterator i = this->Generators.begin();
+      i != this->Generators.end(); ++i)
     {
     cmDocumentationEntry e;
     cmGlobalGenerator* generator = (i->second)();
@@ -1776,24 +1780,24 @@ void cmake::GetGeneratorDocumentation(std::vector<cmDocumentationEntry>& v)
 
 void cmake::AddWrittenFile(const char* file)
 {
-  m_WrittenFiles.insert(file);
+  this->WrittenFiles.insert(file);
 }
 
 bool cmake::HasWrittenFile(const char* file)
 {
-  return m_WrittenFiles.find(file) != m_WrittenFiles.end();
+  return this->WrittenFiles.find(file) != this->WrittenFiles.end();
 }
 
 void cmake::CleanupWrittenFiles()
 {
-  m_WrittenFiles.clear();
+  this->WrittenFiles.clear();
 }
 
 void cmake::UpdateConversionPathTable()
 {
   // Update the path conversion table with any specified file:
-  const char* tablepath =
-    m_CacheManager->GetCacheValue("CMAKE_PATH_TRANSLATION_FILE");
+  const char* tablepath = 
+    this->CacheManager->GetCacheValue("CMAKE_PATH_TRANSLATION_FILE");
 
   if(tablepath)
     {
@@ -1827,13 +1831,13 @@ int cmake::CheckBuildSystem()
   // does not then we need to check the integrity here.
 
   // If no file is provided for the check, we have to rerun.
-  if(m_CheckBuildSystem.size() == 0)
+  if(this->CheckBuildSystemArgument.size() == 0)
     {
     return 1;
     }
 
   // If the file provided does not exist, we have to rerun.
-  if(!cmSystemTools::FileExists(m_CheckBuildSystem.c_str()))
+  if(!cmSystemTools::FileExists(this->CheckBuildSystemArgument.c_str()))
     {
     return 1;
     }
@@ -1846,7 +1850,7 @@ int cmake::CheckBuildSystem()
   std::auto_ptr<cmLocalGenerator> lg(gg.CreateLocalGenerator());
   lg->SetGlobalGenerator(&gg);
   cmMakefile* mf = lg->GetMakefile();
-  if(!mf->ReadListFile(0, m_CheckBuildSystem.c_str()) ||
+  if(!mf->ReadListFile(0, this->CheckBuildSystemArgument.c_str()) ||
      cmSystemTools::GetErrorOccuredFlag())
     {
     // There was an error reading the file.  Just rerun.
@@ -1874,8 +1878,8 @@ int cmake::CheckBuildSystem()
         out != outputs.end(); ++out)
       {
       int result = 0;
-      if(!m_FileComparison->FileTimeCompare(out->c_str(),
-                                            dep->c_str(), &result) ||
+      if(!this->FileComparison->FileTimeCompare(out->c_str(), 
+                                                dep->c_str(), &result) ||
          result < 0)
         {
         return 1;
@@ -1899,7 +1903,7 @@ int cmake::CheckBuildSystem()
     {
     std::auto_ptr<cmLocalGenerator> lgd(ggd->CreateLocalGenerator());
     lgd->SetGlobalGenerator(ggd);
-    lgd->CheckDependencies(mf, verbose, m_ClearBuildSystem);
+    lgd->CheckDependencies(mf, verbose, this->ClearBuildSystem);
     }
 
   // No need to rerun.
@@ -1917,7 +1921,7 @@ void cmake::TruncateOutputLog(const char* fname)
     {
     return;
     }
-  if ( !m_CacheManager->GetCacheValue("CMAKE_CACHEFILE_DIR") )
+  if ( !this->CacheManager->GetCacheValue("CMAKE_CACHEFILE_DIR") )
     {
     cmSystemTools::RemoveFile(fullPath.c_str());
     return;
@@ -1942,95 +1946,95 @@ inline std::string removeQuotes(const std::string& s)
 
 const char* cmake::GetCTestCommand()
 {
-  if ( !m_CTestCommand.empty() )
+  if ( !this->CTestCommand.empty() )
     {
-    return m_CTestCommand.c_str();
+    return this->CTestCommand.c_str();
     }
 
   cmMakefile* mf
     = this->GetGlobalGenerator()->GetLocalGenerator(0)->GetMakefile();
 #ifdef CMAKE_BUILD_WITH_CMAKE
-  m_CTestCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
-  m_CTestCommand = removeQuotes(m_CTestCommand);
-  m_CTestCommand = cmSystemTools::GetFilenamePath(m_CTestCommand.c_str());
-  m_CTestCommand += "/";
-  m_CTestCommand += "ctest";
-  m_CTestCommand += cmSystemTools::GetExecutableExtension();
-  if(!cmSystemTools::FileExists(m_CTestCommand.c_str()))
-    {
-    m_CTestCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
-    m_CTestCommand = cmSystemTools::GetFilenamePath(m_CTestCommand.c_str());
-    m_CTestCommand += "/Debug/";
-    m_CTestCommand += "ctest";
-    m_CTestCommand += cmSystemTools::GetExecutableExtension();
-    }
-  if(!cmSystemTools::FileExists(m_CTestCommand.c_str()))
-    {
-    m_CTestCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
-    m_CTestCommand = cmSystemTools::GetFilenamePath(m_CTestCommand.c_str());
-    m_CTestCommand += "/Release/";
-    m_CTestCommand += "ctest";
-    m_CTestCommand += cmSystemTools::GetExecutableExtension();
+  this->CTestCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
+  this->CTestCommand = removeQuotes(this->CTestCommand);
+  this->CTestCommand = cmSystemTools::GetFilenamePath(this->CTestCommand.c_str());
+  this->CTestCommand += "/";
+  this->CTestCommand += "ctest";
+  this->CTestCommand += cmSystemTools::GetExecutableExtension();
+  if(!cmSystemTools::FileExists(this->CTestCommand.c_str()))
+    {
+    this->CTestCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
+    this->CTestCommand = cmSystemTools::GetFilenamePath(this->CTestCommand.c_str());
+    this->CTestCommand += "/Debug/";
+    this->CTestCommand += "ctest";
+    this->CTestCommand += cmSystemTools::GetExecutableExtension();
+    }
+  if(!cmSystemTools::FileExists(this->CTestCommand.c_str()))
+    {
+    this->CTestCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
+    this->CTestCommand = cmSystemTools::GetFilenamePath(this->CTestCommand.c_str());
+    this->CTestCommand += "/Release/";
+    this->CTestCommand += "ctest";
+    this->CTestCommand += cmSystemTools::GetExecutableExtension();
     }
 #else
   // Only for bootstrap
-  m_CTestCommand += mf->GetSafeDefinition("EXECUTABLE_OUTPUT_PATH");
-  m_CTestCommand += "/ctest";
-  m_CTestCommand += cmSystemTools::GetExecutableExtension();
+  this->CTestCommand += mf->GetSafeDefinition("EXECUTABLE_OUTPUT_PATH");
+  this->CTestCommand += "/ctest";
+  this->CTestCommand += cmSystemTools::GetExecutableExtension();
 #endif
-  if ( m_CTestCommand.empty() )
+  if ( this->CTestCommand.empty() )
     {
     cmSystemTools::Error("Cannot find the CTest executable");
-    m_CTestCommand = "CTEST-COMMAND-NOT-FOUND";
+    this->CTestCommand = "CTEST-COMMAND-NOT-FOUND";
     }
-  return m_CTestCommand.c_str();
+  return this->CTestCommand.c_str();
 }
 
 const char* cmake::GetCPackCommand()
 {
-  if ( !m_CPackCommand.empty() )
+  if ( !this->CPackCommand.empty() )
     {
-    return m_CPackCommand.c_str();
+    return this->CPackCommand.c_str();
     }
 
   cmMakefile* mf
     = this->GetGlobalGenerator()->GetLocalGenerator(0)->GetMakefile();
 
 #ifdef CMAKE_BUILD_WITH_CMAKE
-  m_CPackCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
-  m_CPackCommand = removeQuotes(m_CPackCommand);
-  m_CPackCommand = cmSystemTools::GetFilenamePath(m_CPackCommand.c_str());
-  m_CPackCommand += "/";
-  m_CPackCommand += "cpack";
-  m_CPackCommand += cmSystemTools::GetExecutableExtension();
-  if(!cmSystemTools::FileExists(m_CPackCommand.c_str()))
-    {
-    m_CPackCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
-    m_CPackCommand = cmSystemTools::GetFilenamePath(m_CPackCommand.c_str());
-    m_CPackCommand += "/Debug/";
-    m_CPackCommand += "cpack";
-    m_CPackCommand += cmSystemTools::GetExecutableExtension();
-    }
-  if(!cmSystemTools::FileExists(m_CPackCommand.c_str()))
-    {
-    m_CPackCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
-    m_CPackCommand = cmSystemTools::GetFilenamePath(m_CPackCommand.c_str());
-    m_CPackCommand += "/Release/";
-    m_CPackCommand += "cpack";
-    m_CPackCommand += cmSystemTools::GetExecutableExtension();
-    }
-  if (!cmSystemTools::FileExists(m_CPackCommand.c_str()))
+  this->CPackCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
+  this->CPackCommand = removeQuotes(this->CPackCommand);
+  this->CPackCommand = cmSystemTools::GetFilenamePath(this->CPackCommand.c_str());
+  this->CPackCommand += "/";
+  this->CPackCommand += "cpack";
+  this->CPackCommand += cmSystemTools::GetExecutableExtension();
+  if(!cmSystemTools::FileExists(this->CPackCommand.c_str()))
+    {
+    this->CPackCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
+    this->CPackCommand = cmSystemTools::GetFilenamePath(this->CPackCommand.c_str());
+    this->CPackCommand += "/Debug/";
+    this->CPackCommand += "cpack";
+    this->CPackCommand += cmSystemTools::GetExecutableExtension();
+    }
+  if(!cmSystemTools::FileExists(this->CPackCommand.c_str()))
+    {
+    this->CPackCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
+    this->CPackCommand = cmSystemTools::GetFilenamePath(this->CPackCommand.c_str());
+    this->CPackCommand += "/Release/";
+    this->CPackCommand += "cpack";
+    this->CPackCommand += cmSystemTools::GetExecutableExtension();
+    }
+  if (!cmSystemTools::FileExists(this->CPackCommand.c_str()))
     {
     cmSystemTools::Error("Cannot find the CPack executable");
-    m_CPackCommand = "CPACK-COMMAND-NOT-FOUND";
+    this->CPackCommand = "CPACK-COMMAND-NOT-FOUND";
     }
 #else
   // Only for bootstrap
-  m_CPackCommand += mf->GetSafeDefinition("EXECUTABLE_OUTPUT_PATH");
-  m_CPackCommand += "/cpack";
-  m_CPackCommand += cmSystemTools::GetExecutableExtension();
+  this->CPackCommand += mf->GetSafeDefinition("EXECUTABLE_OUTPUT_PATH");
+  this->CPackCommand += "/cpack";
+  this->CPackCommand += cmSystemTools::GetExecutableExtension();
 #endif
-  return m_CPackCommand.c_str();
+  return this->CPackCommand.c_str();
 }
 
 void cmake::GenerateGraphViz(const char* fileName)
@@ -2141,9 +2145,9 @@ void cmake::GenerateGraphViz(const char* fileName)
     cmTargets::iterator tit;
     for ( tit = targets->begin(); tit != targets->end(); ++ tit )
       {
-      const cmTarget::LinkLibraries* ll
+      const cmTarget::LinkLibraryVectorType* ll
         = &(tit->second.GetOriginalLinkLibraries());
-      cmTarget::LinkLibraries::const_iterator llit;
+      cmTarget::LinkLibraryVectorType::const_iterator llit;
       const char* realTargetName = tit->first.c_str();
       if ( ignoreTargetsSet.find(realTargetName) != ignoreTargetsSet.end() )
         {
@@ -2254,9 +2258,9 @@ void cmake::GenerateGraphViz(const char* fileName)
         }
       std::map<cmStdString, cmStdString>::iterator cmakeTarIt
         = targetNamesNodes.find(tit->first.c_str());
-      const cmTarget::LinkLibraries* ll
+      const cmTarget::LinkLibraryVectorType* ll
         = &(tit->second.GetOriginalLinkLibraries());
-      cmTarget::LinkLibraries::const_iterator llit;
+      cmTarget::LinkLibraryVectorType::const_iterator llit;
       for ( llit = ll->begin(); llit != ll->end(); ++ llit )
         {
         const char* libName = llit->first.c_str();