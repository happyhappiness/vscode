@@ -32,33 +32,33 @@ int cmGlobalGenerator::s_TryCompileTimeout = 0;
 cmGlobalGenerator::cmGlobalGenerator()
 {
   // by default use the native paths
-  m_ForceUnixPaths = false;
+  this->ForceUnixPaths = false;
 }
 
 cmGlobalGenerator::~cmGlobalGenerator()
 { 
   // Delete any existing cmLocalGenerators
   unsigned int i;
-  for (i = 0; i < m_LocalGenerators.size(); ++i)
+  for (i = 0; i < this->LocalGenerators.size(); ++i)
     {
-    delete m_LocalGenerators[i];
+    delete this->LocalGenerators[i];
     }
-  m_LocalGenerators.clear();
+  this->LocalGenerators.clear();
 }
 
 // Find the make program for the generator, required for try compiles
 void cmGlobalGenerator::FindMakeProgram(cmMakefile* mf)
 {
-  if(m_FindMakeProgramFile.size() == 0)
+  if(this->FindMakeProgramFile.size() == 0)
     {
     cmSystemTools::Error(
       "Generator implementation error, "
-      "all generators must specify m_FindMakeProgramFile");
+      "all generators must specify this->FindMakeProgramFile");
     }
   if(!mf->GetDefinition("CMAKE_MAKE_PROGRAM")
      || cmSystemTools::IsOff(mf->GetDefinition("CMAKE_MAKE_PROGRAM")))
     {
-    std::string setMakeProgram = mf->GetModulesFile(m_FindMakeProgramFile.c_str());
+    std::string setMakeProgram = mf->GetModulesFile(this->FindMakeProgramFile.c_str());
     if(setMakeProgram.size())
       {
       mf->ReadListFile(0, setMakeProgram.c_str());
@@ -146,9 +146,9 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
   // If the configuration files path has been set,
   // then we are in a try compile and need to copy the enable language
   // files from the parent cmake bin dir, into the try compile bin dir
-  if(m_ConfiguredFilesPath.size())
+  if(this->ConfiguredFilesPath.size())
     {
-    std::string src = m_ConfiguredFilesPath;
+    std::string src = this->ConfiguredFilesPath;
     src += "/CMakeSystem.cmake";
     std::string dst = rootBin;
     dst += "/CMakeSystem.cmake";
@@ -162,7 +162,7 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
         continue;
         }
       const char* lang = l->c_str();
-      std::string src2 = m_ConfiguredFilesPath;
+      std::string src2 = this->ConfiguredFilesPath;
       src2 += "/CMake";
       src2 += lang;
       src2 += "Compiler.cmake";
@@ -171,7 +171,7 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
       dst2 += lang;
       dst2 += "Compiler.cmake";
       cmSystemTools::CopyFileIfDifferent(src2.c_str(), dst2.c_str()); 
-      src2 = m_ConfiguredFilesPath;
+      src2 = this->ConfiguredFilesPath;
       src2 += "/CMake";
       src2 += lang;
       src2 += "Platform.cmake";
@@ -181,7 +181,7 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
       dst2 += "Platform.cmake";
       cmSystemTools::CopyFileIfDifferent(src2.c_str(), dst2.c_str());
       }
-    rootBin = m_ConfiguredFilesPath;
+    rootBin = this->ConfiguredFilesPath;
     }
 
   // find and make sure CMAKE_MAKE_PROGRAM is defined
@@ -246,7 +246,7 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
     unsigned int cacheMinor = mf->GetCacheMinorVersion();
     unsigned int selfMajor = cmMakefile::GetMajorVersion();
     unsigned int selfMinor = cmMakefile::GetMinorVersion();
-    if((m_CMakeInstance->GetIsInTryCompile() ||
+    if((this->CMakeInstance->GetIsInTryCompile() ||
         (selfMajor == cacheMajor && selfMinor == cacheMinor))
        && !mf->GetDefinition(loadedLang.c_str()))
       {
@@ -268,7 +268,7 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
       
     if(!this->GetLanguageEnabled(lang) )
       {  
-      if (m_CMakeInstance->GetIsInTryCompile())
+      if (this->CMakeInstance->GetIsInTryCompile())
         {
         cmSystemTools::Error("This should not have happen. "
                              "If you see this message, you are probably using a "
@@ -368,7 +368,7 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
     // If the language is untested then test it now with a try compile.
     if(needTestLanguage[lang])
       {
-      if (!m_CMakeInstance->GetIsInTryCompile())
+      if (!this->CMakeInstance->GetIsInTryCompile())
         {
         std::string testLang = "CMakeTest";
         testLang += lang;
@@ -438,9 +438,9 @@ const char* cmGlobalGenerator::GetLanguageOutputExtensionForLanguage(const char*
     {
     return "";
     }
-  if(m_LanguageToOutputExtension.count(lang) > 0)
+  if(this->LanguageToOutputExtension.count(lang) > 0)
     {
-    return m_LanguageToOutputExtension[lang].c_str();
+    return this->LanguageToOutputExtension[lang].c_str();
     }
   return "";
 }
@@ -457,7 +457,7 @@ const char* cmGlobalGenerator::GetLanguageOutputExtensionFromExtension(const cha
     // if no language is found then check to see if it is already an
     // ouput extension for some language.  In that case it should be ignored
     // and in this map, so it will not be compiled but will just be used.
-    if(m_OutputExtensions.count(ext))
+    if(this->OutputExtensions.count(ext))
       {
       return ext;
       }
@@ -475,16 +475,16 @@ const char* cmGlobalGenerator::GetLanguageFromExtension(const char* ext)
     {
     ++ext;
     }
-  if(m_ExtensionToLanguage.count(ext) > 0)
+  if(this->ExtensionToLanguage.count(ext) > 0)
     {
-    return m_ExtensionToLanguage[ext].c_str();
+    return this->ExtensionToLanguage[ext].c_str();
     }
   return 0;
 }
 
 void cmGlobalGenerator::SetLanguageEnabled(const char* l, cmMakefile* mf)
 {
-  if(m_LanguageEnabled.count(l) > 0)
+  if(this->LanguageEnabled.count(l) > 0)
     {
     return;
     }
@@ -493,11 +493,11 @@ void cmGlobalGenerator::SetLanguageEnabled(const char* l, cmMakefile* mf)
   const char* outputExtension = mf->GetDefinition(outputExtensionVar.c_str());
   if(outputExtension)
     {
-    m_LanguageToOutputExtension[l] = outputExtension;
-    m_OutputExtensions[outputExtension] = outputExtension;
+    this->LanguageToOutputExtension[l] = outputExtension;
+    this->OutputExtensions[outputExtension] = outputExtension;
     if(outputExtension[0] == '.')
       {
-      m_OutputExtensions[outputExtension+1] = outputExtension+1;
+      this->OutputExtensions[outputExtension+1] = outputExtension+1;
       }
     }
   
@@ -508,7 +508,7 @@ void cmGlobalGenerator::SetLanguageEnabled(const char* l, cmMakefile* mf)
     {
     linkerPref = "None";
     }
-  m_LanguageToLinkerPreference[l] = linkerPref;
+  this->LanguageToLinkerPreference[l] = linkerPref;
   
   std::string extensionsVar = std::string("CMAKE_") + 
     std::string(l) + std::string("_SOURCE_FILE_EXTENSIONS");
@@ -521,15 +521,15 @@ void cmGlobalGenerator::SetLanguageEnabled(const char* l, cmMakefile* mf)
   for(std::vector<std::string>::iterator i = extensionList.begin();
       i != extensionList.end(); ++i)
     {
-    m_ExtensionToLanguage[*i] = l;
+    this->ExtensionToLanguage[*i] = l;
     }
   cmSystemTools::ExpandListArgument(ignoreExts, extensionList);
   for(std::vector<std::string>::iterator i = extensionList.begin();
       i != extensionList.end(); ++i)
     {
-    m_IgnoreExtensions[*i] = true;
+    this->IgnoreExtensions[*i] = true;
     }
-  m_LanguageEnabled[l] = true;
+  this->LanguageEnabled[l] = true;
 
 }
 bool cmGlobalGenerator::IgnoreFile(const char* l)
@@ -538,41 +538,41 @@ bool cmGlobalGenerator::IgnoreFile(const char* l)
     {
     return false;
     }
-  return (m_IgnoreExtensions.count(l) > 0);
+  return (this->IgnoreExtensions.count(l) > 0);
 }
 
 bool cmGlobalGenerator::GetLanguageEnabled(const char* l)
 {
-  return (m_LanguageEnabled.count(l) > 0);
+  return (this->LanguageEnabled.count(l) > 0);
 }
 
 void cmGlobalGenerator::ClearEnabledLanguages()
 {
-  m_LanguageEnabled.clear();
+  this->LanguageEnabled.clear();
 }
 
 void cmGlobalGenerator::Configure()
 {
   // Delete any existing cmLocalGenerators
   unsigned int i;
-  for (i = 0; i < m_LocalGenerators.size(); ++i)
+  for (i = 0; i < this->LocalGenerators.size(); ++i)
     {
-    delete m_LocalGenerators[i];
+    delete this->LocalGenerators[i];
     }
-  m_LocalGenerators.clear();
+  this->LocalGenerators.clear();
 
   // Setup relative path generation.
   this->ConfigureRelativePaths();
 
   // start with this directory
   cmLocalGenerator *lg = this->CreateLocalGenerator();
-  m_LocalGenerators.push_back(lg);
+  this->LocalGenerators.push_back(lg);
 
   // set the Start directories
   lg->GetMakefile()->SetStartDirectory
-    (m_CMakeInstance->GetStartDirectory());
+    (this->CMakeInstance->GetStartDirectory());
   lg->GetMakefile()->SetStartOutputDirectory
-    (m_CMakeInstance->GetStartOutputDirectory());
+    (this->CMakeInstance->GetStartOutputDirectory());
   lg->GetMakefile()->MakeStartDirectoriesCurrent();
   
   // now do it
@@ -581,25 +581,25 @@ void cmGlobalGenerator::Configure()
   // update the cache entry for the number of local generators, this is used
   // for progress
   char num[100];
-  sprintf(num,"%d",static_cast<int>(m_LocalGenerators.size()));
+  sprintf(num,"%d",static_cast<int>(this->LocalGenerators.size()));
   this->GetCMakeInstance()->AddCacheEntry
     ("CMAKE_NUMBER_OF_LOCAL_GENERATORS", num,
      "number of local generators", cmCacheManager::INTERNAL);
   
   std::set<cmStdString> notFoundMap;
   // after it is all done do a ConfigureFinalPass
   cmCacheManager* manager = 0;
-  for (i = 0; i < m_LocalGenerators.size(); ++i)
+  for (i = 0; i < this->LocalGenerators.size(); ++i)
     {
-    manager = m_LocalGenerators[i]->GetMakefile()->GetCacheManager();
-    m_LocalGenerators[i]->ConfigureFinalPass();
+    manager = this->LocalGenerators[i]->GetMakefile()->GetCacheManager();
+    this->LocalGenerators[i]->ConfigureFinalPass();
     cmTargets & targets = 
-      m_LocalGenerators[i]->GetMakefile()->GetTargets(); 
+      this->LocalGenerators[i]->GetMakefile()->GetTargets(); 
     for (cmTargets::iterator l = targets.begin();
          l != targets.end(); l++)
       {
-      cmTarget::LinkLibraries libs = l->second.GetLinkLibraries();
-      for(cmTarget::LinkLibraries::iterator lib = libs.begin();
+      cmTarget::LinkLibraryVectorType libs = l->second.GetLinkLibraries();
+      for(cmTarget::LinkLibraryVectorType::iterator lib = libs.begin();
           lib != libs.end(); ++lib)
         {
         if(lib->first.size() > 9 && 
@@ -610,7 +610,7 @@ void cmGlobalGenerator::Configure()
           }
         }
       std::vector<std::string>& incs = 
-        m_LocalGenerators[i]->GetMakefile()->GetIncludeDirectories();
+        this->LocalGenerators[i]->GetMakefile()->GetIncludeDirectories();
       
       for( std::vector<std::string>::iterator lib = incs.begin();
            lib != incs.end(); ++lib)
@@ -622,9 +622,9 @@ void cmGlobalGenerator::Configure()
           notFoundMap.insert(varName);
           }
         }
-      m_CMakeInstance->UpdateProgress("Configuring", 
-                                      0.9f+0.1f*(i+1.0f)/m_LocalGenerators.size());
-      m_LocalGenerators[i]->GetMakefile()->CheckInfiniteLoops();
+      this->CMakeInstance->UpdateProgress("Configuring", 
+                                      0.9f+0.1f*(i+1.0f)/this->LocalGenerators.size());
+      this->LocalGenerators[i]->GetMakefile()->CheckInfiniteLoops();
       }
     }
 
@@ -651,12 +651,12 @@ void cmGlobalGenerator::Configure()
                          "Please set the following variables:\n",
                          notFoundVars.c_str());
     }
-  // at this point m_LocalGenerators has been filled,
+  // at this point this->LocalGenerators has been filled,
   // so create the map from project name to vector of local generators
   this->FillProjectMap();
-  if ( !m_CMakeInstance->GetScriptMode() )
+  if ( !this->CMakeInstance->GetScriptMode() )
     {
-    m_CMakeInstance->UpdateProgress("Configuring done", -1);
+    this->CMakeInstance->UpdateProgress("Configuring done", -1);
     }
 }
 
@@ -668,9 +668,9 @@ void cmGlobalGenerator::Generate()
   // Consolidate global targets
   cmTargets globalTargets;
   this->CreateDefaultGlobalTargets(&globalTargets);
-  for (i = 0; i < m_LocalGenerators.size(); ++i)
+  for (i = 0; i < this->LocalGenerators.size(); ++i)
     {
-    cmTargets* targets = &(m_LocalGenerators[i]->GetMakefile()->GetTargets());
+    cmTargets* targets = &(this->LocalGenerators[i]->GetMakefile()->GetTargets());
     cmTargets::iterator tarIt;
     for ( tarIt = targets->begin(); tarIt != targets->end(); ++ tarIt )
       {
@@ -682,21 +682,21 @@ void cmGlobalGenerator::Generate()
     }
   
   // Generate project files
-  for (i = 0; i < m_LocalGenerators.size(); ++i)
+  for (i = 0; i < this->LocalGenerators.size(); ++i)
     {
-    cmTargets* targets = &(m_LocalGenerators[i]->GetMakefile()->GetTargets());
+    cmTargets* targets = &(this->LocalGenerators[i]->GetMakefile()->GetTargets());
     cmTargets::iterator tit;
     for ( tit = globalTargets.begin(); tit != globalTargets.end(); ++ tit )
       {
       (*targets)[tit->first] = tit->second;
       }
-    m_LocalGenerators[i]->Generate();
-    m_LocalGenerators[i]->GenerateInstallRules();
-    m_LocalGenerators[i]->GenerateTestFiles();
-    m_CMakeInstance->UpdateProgress("Generating", 
-                                    (i+1.0f)/m_LocalGenerators.size());
+    this->LocalGenerators[i]->Generate();
+    this->LocalGenerators[i]->GenerateInstallRules();
+    this->LocalGenerators[i]->GenerateTestFiles();
+    this->CMakeInstance->UpdateProgress("Generating", 
+                                    (i+1.0f)/this->LocalGenerators.size());
     }
-  m_CMakeInstance->UpdateProgress("Generating done", -1);
+  this->CMakeInstance->UpdateProgress("Generating done", -1);
 }
 
 int cmGlobalGenerator::TryCompile(const char *srcdir, const char *bindir, 
@@ -705,7 +705,7 @@ int cmGlobalGenerator::TryCompile(const char *srcdir, const char *bindir,
                                   std::string *output, cmMakefile *mf)
 {
   std::string makeCommand = 
-    m_CMakeInstance->GetCacheManager()->GetCacheValue("CMAKE_MAKE_PROGRAM");
+    this->CMakeInstance->GetCacheManager()->GetCacheValue("CMAKE_MAKE_PROGRAM");
   if(makeCommand.size() == 0)
     {
     cmSystemTools::Error(
@@ -847,12 +847,12 @@ int cmGlobalGenerator::Build(
 
 void cmGlobalGenerator::AddLocalGenerator(cmLocalGenerator *lg)
 {
-  m_LocalGenerators.push_back(lg); 
+  this->LocalGenerators.push_back(lg); 
 
   // update progress
   // estimate how many lg there will be
   const char *numGenC = 
-    m_CMakeInstance->GetCacheManager()->GetCacheValue
+    this->CMakeInstance->GetCacheManager()->GetCacheValue
     ("CMAKE_NUMBER_OF_LOCAL_GENERATORS");
   
   if (!numGenC)
@@ -861,12 +861,12 @@ void cmGlobalGenerator::AddLocalGenerator(cmLocalGenerator *lg)
     }
   
   int numGen = atoi(numGenC);
-  float prog = 0.9f*m_LocalGenerators.size()/numGen;
+  float prog = 0.9f*this->LocalGenerators.size()/numGen;
   if (prog > 0.9f)
     {
     prog = 0.9f;
     }
-  m_CMakeInstance->UpdateProgress("Configuring", prog);
+  this->CMakeInstance->UpdateProgress("Configuring", prog);
 }
 
 cmLocalGenerator *cmGlobalGenerator::CreateLocalGenerator()
@@ -887,12 +887,12 @@ void cmGlobalGenerator::EnableLanguagesFromGenerator(cmGlobalGenerator *gen )
                                           "make program",
                                           cmCacheManager::FILEPATH);
   // copy the enabled languages
-  this->m_LanguageEnabled = gen->m_LanguageEnabled;
-  this->m_ExtensionToLanguage = gen->m_ExtensionToLanguage;
-  this->m_IgnoreExtensions = gen->m_IgnoreExtensions;
-  this->m_LanguageToOutputExtension = gen->m_LanguageToOutputExtension;
-  this->m_LanguageToLinkerPreference = gen->m_LanguageToLinkerPreference;
-  this->m_OutputExtensions = gen->m_OutputExtensions;
+  this->LanguageEnabled = gen->LanguageEnabled;
+  this->ExtensionToLanguage = gen->ExtensionToLanguage;
+  this->IgnoreExtensions = gen->IgnoreExtensions;
+  this->LanguageToOutputExtension = gen->LanguageToOutputExtension;
+  this->LanguageToLinkerPreference = gen->LanguageToLinkerPreference;
+  this->OutputExtensions = gen->OutputExtensions;
 }
 
 //----------------------------------------------------------------------------
@@ -921,38 +921,38 @@ bool cmGlobalGenerator::IsExcluded(cmLocalGenerator* root,
 
 void cmGlobalGenerator::GetEnabledLanguages(std::vector<std::string>& lang)
 {
-  for(std::map<cmStdString, bool>::iterator i = m_LanguageEnabled.begin(); 
-      i != m_LanguageEnabled.end(); ++i)
+  for(std::map<cmStdString, bool>::iterator i = this->LanguageEnabled.begin(); 
+      i != this->LanguageEnabled.end(); ++i)
     {
     lang.push_back(i->first);
     }
 }
 
 const char* cmGlobalGenerator::GetLinkerPreference(const char* lang)
 {
-  if(m_LanguageToLinkerPreference.count(lang))
+  if(this->LanguageToLinkerPreference.count(lang))
     {
-    return m_LanguageToLinkerPreference[lang].c_str();
+    return this->LanguageToLinkerPreference[lang].c_str();
     }
   return "None";
 }
 
 
 void cmGlobalGenerator::FillProjectMap()
 { 
-  m_ProjectMap.clear(); // make sure we start with a clean map
+  this->ProjectMap.clear(); // make sure we start with a clean map
   unsigned int i;
-  for(i = 0; i < m_LocalGenerators.size(); ++i)
+  for(i = 0; i < this->LocalGenerators.size(); ++i)
     {
     // for each local generator add all projects 
-    cmLocalGenerator *lg = m_LocalGenerators[i];
+    cmLocalGenerator *lg = this->LocalGenerators[i];
     std::string name;
     do 
       {
       if (name != lg->GetMakefile()->GetProjectName())
         {
         name = lg->GetMakefile()->GetProjectName();
-        m_ProjectMap[name].push_back(m_LocalGenerators[i]);
+        this->ProjectMap[name].push_back(this->LocalGenerators[i]);
         }
       lg = lg->GetParent();
       }
@@ -964,7 +964,7 @@ void cmGlobalGenerator::FillProjectMap()
 ///! Find a local generator by its startdirectory
 cmLocalGenerator* cmGlobalGenerator::FindLocalGenerator(const char* start_dir)
 {
-  std::vector<cmLocalGenerator*>* gens = &m_LocalGenerators;
+  std::vector<cmLocalGenerator*>* gens = &this->LocalGenerators;
   for(unsigned int i = 0; i < gens->size(); ++i)
     {
     std::string sd = (*gens)[i]->GetMakefile()->GetStartDirectory();
@@ -980,10 +980,10 @@ cmLocalGenerator* cmGlobalGenerator::FindLocalGenerator(const char* start_dir)
 cmTarget* cmGlobalGenerator::FindTarget(const char* project, 
                                         const char* name)
 {
-  std::vector<cmLocalGenerator*>* gens = &m_LocalGenerators;
+  std::vector<cmLocalGenerator*>* gens = &this->LocalGenerators;
   if(project)
     {
-    gens = &m_ProjectMap[project];
+    gens = &this->ProjectMap[project];
     }
   for(unsigned int i = 0; i < gens->size(); ++i)
     {
@@ -1002,17 +1002,17 @@ void cmGlobalGenerator::ConfigureRelativePaths()
   // The current working directory on Windows cannot be a network
   // path.  Therefore relative paths cannot work when the build tree
   // is a network path.
-  std::string source = m_CMakeInstance->GetHomeDirectory();
-  std::string binary = m_CMakeInstance->GetHomeOutputDirectory();
+  std::string source = this->CMakeInstance->GetHomeDirectory();
+  std::string binary = this->CMakeInstance->GetHomeOutputDirectory();
   if(binary.size() < 2 || binary.substr(0, 2) != "//")
     {
-    m_RelativePathTopSource = source;
-    m_RelativePathTopBinary = binary;
+    this->RelativePathTopSource = source;
+    this->RelativePathTopBinary = binary;
     }
   else
     {
-    m_RelativePathTopSource = "";
-    m_RelativePathTopBinary = "";
+    this->RelativePathTopSource = "";
+    this->RelativePathTopBinary = "";
     }
 }
 
@@ -1035,14 +1035,14 @@ cmGlobalGenerator::ConvertToRelativePath(const std::vector<std::string>& local,
 
   // Skip conversion if the path is not in the source or binary tree.
   std::string original = in_remote;
-  if((original.size() < m_RelativePathTopSource.size() ||
+  if((original.size() < this->RelativePathTopSource.size() ||
       !cmSystemTools::ComparePath(
-        original.substr(0, m_RelativePathTopSource.size()).c_str(),
-        m_RelativePathTopSource.c_str())) &&
-     (original.size() < m_RelativePathTopBinary.size() ||
+        original.substr(0, this->RelativePathTopSource.size()).c_str(),
+        this->RelativePathTopSource.c_str())) &&
+     (original.size() < this->RelativePathTopBinary.size() ||
       !cmSystemTools::ComparePath(
-        original.substr(0, m_RelativePathTopBinary.size()).c_str(),
-        m_RelativePathTopBinary.c_str())))
+        original.substr(0, this->RelativePathTopBinary.size()).c_str(),
+        this->RelativePathTopBinary.c_str())))
     {
     return in_remote;
     }
@@ -1129,7 +1129,7 @@ inline std::string removeQuotes(const std::string& s)
 void cmGlobalGenerator::SetupTests()
 {
   std::string ctest = 
-    m_LocalGenerators[0]->GetMakefile()->GetRequiredDefinition("CMAKE_COMMAND");
+    this->LocalGenerators[0]->GetMakefile()->GetRequiredDefinition("CMAKE_COMMAND");
   ctest = removeQuotes(ctest);
   ctest = cmSystemTools::GetFilenamePath(ctest.c_str());
   ctest += "/";
@@ -1138,7 +1138,7 @@ void cmGlobalGenerator::SetupTests()
   if(!cmSystemTools::FileExists(ctest.c_str()))
     {
     ctest =     
-      m_LocalGenerators[0]->GetMakefile()->GetRequiredDefinition("CMAKE_COMMAND");
+      this->LocalGenerators[0]->GetMakefile()->GetRequiredDefinition("CMAKE_COMMAND");
     ctest = cmSystemTools::GetFilenamePath(ctest.c_str());
     ctest += "/Debug/";
     ctest += "ctest";
@@ -1147,7 +1147,7 @@ void cmGlobalGenerator::SetupTests()
   if(!cmSystemTools::FileExists(ctest.c_str()))
     {
     ctest =     
-      m_LocalGenerators[0]->GetMakefile()->GetRequiredDefinition("CMAKE_COMMAND");
+      this->LocalGenerators[0]->GetMakefile()->GetRequiredDefinition("CMAKE_COMMAND");
     ctest = cmSystemTools::GetFilenamePath(ctest.c_str());
     ctest += "/Release/";
     ctest += "ctest";
@@ -1158,9 +1158,9 @@ void cmGlobalGenerator::SetupTests()
     {
     // Create a full path filename for output Testfile
     std::string fname;
-    fname = m_CMakeInstance->GetStartOutputDirectory();
+    fname = this->CMakeInstance->GetStartOutputDirectory();
     fname += "/";
-    if ( m_LocalGenerators[0]->GetMakefile()->IsSet("CTEST_NEW_FORMAT") )
+    if ( this->LocalGenerators[0]->GetMakefile()->IsSet("CTEST_NEW_FORMAT") )
       {
       fname += "CTestTestfile.txt";
       }
@@ -1172,9 +1172,9 @@ void cmGlobalGenerator::SetupTests()
     // Add run_test only if any tests are foun
     long total_tests = 0;
     unsigned int i;
-    for (i = 0; i < m_LocalGenerators.size(); ++i)
+    for (i = 0; i < this->LocalGenerators.size(); ++i)
       {
-      total_tests += m_LocalGenerators[i]->GetMakefile()->GetTests()->size();
+      total_tests += this->LocalGenerators[i]->GetMakefile()->GetTests()->size();
       }
 
     // If the file doesn't exist, then ENABLE_TESTING hasn't been run
@@ -1184,7 +1184,7 @@ void cmGlobalGenerator::SetupTests()
       const char* no_working_dir = 0;
       std::vector<std::string> no_depends;
       std::map<cmStdString, std::vector<cmLocalGenerator*> >::iterator it;
-      for(it = m_ProjectMap.begin(); it!= m_ProjectMap.end(); ++it)
+      for(it = this->ProjectMap.begin(); it!= this->ProjectMap.end(); ++it)
         {
         std::vector<cmLocalGenerator*>& gen = it->second;
         // add the RUN_TESTS to the first local generator of each project
@@ -1205,7 +1205,7 @@ void cmGlobalGenerator::SetupTests()
 
 void cmGlobalGenerator::CreateDefaultGlobalTargets(cmTargets* targets)
 {
-  cmMakefile* mf = m_LocalGenerators[0]->GetMakefile();
+  cmMakefile* mf = this->LocalGenerators[0]->GetMakefile();
   const char* cmakeCfgIntDir = this->GetCMakeCFGInitDirectory();
   const char* cmakeCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
 