@@ -14,6 +14,20 @@
 #if defined(_MSC_VER) && _MSC_VER >= 1800
 # define KWSYS_WINDOWS_DEPRECATED_GetVersionEx
 #endif
+typedef struct {
+  ULONG  dwOSVersionInfoSize;
+  ULONG  dwMajorVersion;
+  ULONG  dwMinorVersion;
+  ULONG  dwBuildNumber;
+  ULONG  dwPlatformId;
+  WCHAR  szCSDVersion[128];
+  USHORT wServicePackMajor;
+  USHORT wServicePackMinor;
+  USHORT wSuiteMask;
+  UCHAR  wProductType;
+  UCHAR  wReserved;
+} CMRTL_OSVERSIONINFOEXW;
+
 #endif
 
 #include "cmGlobalGenerator.h"
@@ -30,10 +44,10 @@
 #include "cmGeneratedFileStream.h"
 #include "cmGeneratorTarget.h"
 #include "cmGeneratorExpression.h"
-#include "cmGeneratorExpressionEvaluationFile.h"
 #include "cmExportBuildFileGenerator.h"
 #include "cmCPackPropertiesGenerator.h"
 #include "cmAlgorithms.h"
+#include "cmInstallGenerator.h"
 
 #include <cmsys/Directory.hxx>
 #include <cmsys/FStream.hxx>
@@ -432,23 +446,45 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
   if (!mf->GetDefinition("CMAKE_SYSTEM"))
     {
 #if defined(_WIN32) && !defined(__CYGWIN__)
-    /* Windows version number data.  */
-    OSVERSIONINFO osvi;
-    ZeroMemory(&osvi, sizeof(osvi));
-    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
+    CMRTL_OSVERSIONINFOEXW osviex;
+    ZeroMemory(&osviex, sizeof(osviex));
+    osviex.dwOSVersionInfoSize = sizeof(osviex);
+
+    typedef LONG (FAR WINAPI *cmRtlGetVersion)(CMRTL_OSVERSIONINFOEXW*);
+    cmRtlGetVersion rtlGetVersion = reinterpret_cast<cmRtlGetVersion>(
+      GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "RtlGetVersion"));
+    if (rtlGetVersion && rtlGetVersion(&osviex) == 0)
+      {
+      std::ostringstream windowsVersionString;
+      windowsVersionString << osviex.dwMajorVersion << "."
+                           << osviex.dwMinorVersion << "."
+                           << osviex.dwBuildNumber;
+      windowsVersionString.str();
+      mf->AddDefinition("CMAKE_HOST_SYSTEM_VERSION",
+                        windowsVersionString.str().c_str());
+      }
+    else
+      {
+      // RtlGetVersion failed, so use the deprecated GetVersionEx function.
+      /* Windows version number data.  */
+      OSVERSIONINFO osvi;
+      ZeroMemory(&osvi, sizeof(osvi));
+      osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
 #ifdef KWSYS_WINDOWS_DEPRECATED_GetVersionEx
 # pragma warning (push)
 # pragma warning (disable:4996)
 #endif
-    GetVersionEx (&osvi);
+      GetVersionEx (&osvi);
 #ifdef KWSYS_WINDOWS_DEPRECATED_GetVersionEx
 # pragma warning (pop)
 #endif
-    std::ostringstream windowsVersionString;
-    windowsVersionString << osvi.dwMajorVersion << "." << osvi.dwMinorVersion;
-    windowsVersionString.str();
-    mf->AddDefinition("CMAKE_HOST_SYSTEM_VERSION",
-                      windowsVersionString.str().c_str());
+      std::ostringstream windowsVersionString;
+      windowsVersionString << osvi.dwMajorVersion << "."
+                           << osvi.dwMinorVersion;
+      windowsVersionString.str();
+      mf->AddDefinition("CMAKE_HOST_SYSTEM_VERSION",
+                        windowsVersionString.str().c_str());
+      }
 #endif
     // Read the DetermineSystem file
     std::string systemFile = mf->GetModulesFile("CMakeDetermineSystem.cmake");
@@ -1093,6 +1129,7 @@ void cmGlobalGenerator::Configure()
 
   // start with this directory
   cmLocalGenerator *lg = this->MakeLocalGenerator();
+  this->Makefiles.push_back(lg->GetMakefile());
   this->LocalGenerators.push_back(lg);
 
   // set the Start directories
@@ -1111,9 +1148,9 @@ void cmGlobalGenerator::Configure()
   // update the cache entry for the number of local generators, this is used
   // for progress
   char num[100];
-  sprintf(num,"%d",static_cast<int>(this->LocalGenerators.size()));
+  sprintf(num,"%d",static_cast<int>(this->Makefiles.size()));
   this->GetCMakeInstance()->AddCacheEntry
-    ("CMAKE_NUMBER_OF_LOCAL_GENERATORS", num,
+    ("CMAKE_NUMBER_OF_MAKEFILES", num,
      "number of local generators", cmState::INTERNAL);
 
   // check for link libraries and include directories containing "NOTFOUND"
@@ -1156,9 +1193,9 @@ void cmGlobalGenerator::Configure()
   cmTargets globalTargets;
   this->CreateDefaultGlobalTargets(&globalTargets);
 
-  for (i = 0; i < this->LocalGenerators.size(); ++i)
+  for (i = 0; i < this->Makefiles.size(); ++i)
     {
-    cmMakefile* mf = this->LocalGenerators[i]->GetMakefile();
+    cmMakefile* mf = this->Makefiles[i];
     cmTargets* targets = &(mf->GetTargets());
     cmTargets::iterator tit;
     for ( tit = globalTargets.begin(); tit != globalTargets.end(); ++ tit )
@@ -1212,7 +1249,7 @@ bool cmGlobalGenerator::CheckALLOW_DUPLICATE_CUSTOM_TARGETS() const
   return false;
 }
 
-void cmGlobalGenerator::DoGenerate()
+bool cmGlobalGenerator::Compute()
 {
   // Some generators track files replaced during the Generate.
   // Start with an empty vector:
@@ -1221,17 +1258,11 @@ void cmGlobalGenerator::DoGenerate()
   // clear targets to issue warning CMP0042 for
   this->CMP0042WarnTargets.clear();
 
-  this->Generate();
-}
-
-void cmGlobalGenerator::Generate()
-{
   // Check whether this generator is allowed to run.
   if(!this->CheckALLOW_DUPLICATE_CUSTOM_TARGETS())
     {
-    return;
+    return false;
     }
-
   this->FinalizeTargetCompileInfo();
 
   this->CreateGenerationObjects();
@@ -1266,6 +1297,24 @@ void cmGlobalGenerator::Generate()
     }
 #endif
 
+  for (i = 0; i < this->LocalGenerators.size(); ++i)
+    {
+    cmMakefile* mf = this->LocalGenerators[i]->GetMakefile();
+    std::vector<cmInstallGenerator*>& gens = mf->GetInstallGenerators();
+    for (std::vector<cmInstallGenerator*>::const_iterator git = gens.begin();
+         git != gens.end(); ++git)
+      {
+      (*git)->Compute(this->LocalGenerators[i]);
+      }
+    }
+
+  return true;
+}
+
+void cmGlobalGenerator::Generate()
+{
+  unsigned int i;
+
   // Trace the dependencies, after that no custom commands should be added
   // because their dependencies might not be handled correctly
   for (i = 0; i < this->LocalGenerators.size(); ++i)
@@ -1433,9 +1482,9 @@ void cmGlobalGenerator::CreateQtAutoGeneratorsTargets(AutogensType &autogens)
 void cmGlobalGenerator::FinalizeTargetCompileInfo()
 {
   // Construct per-target generator information.
-  for(unsigned int i=0; i < this->LocalGenerators.size(); ++i)
+  for(unsigned int i=0; i < this->Makefiles.size(); ++i)
     {
-    cmMakefile *mf = this->LocalGenerators[i]->GetMakefile();
+    cmMakefile *mf = this->Makefiles[i];
 
     const cmStringRange noconfig_compile_definitions =
                                 mf->GetCompileDefinitionsEntries();
@@ -1501,6 +1550,7 @@ void cmGlobalGenerator::CreateGeneratorTargets(TargetTypes targetTypes,
         ti != targets.end(); ++ti)
       {
       cmTarget* t = &ti->second;
+      t->Compute();
       cmGeneratorTarget* gt = new cmGeneratorTarget(t, lg);
       this->GeneratorTargets[t] = gt;
       generatorTargets[t] = gt;
@@ -1548,12 +1598,11 @@ void cmGlobalGenerator::ClearGeneratorMembers()
   cmDeleteAll(this->GeneratorTargets);
   this->GeneratorTargets.clear();
 
-  cmDeleteAll(this->EvaluationFiles);
-  this->EvaluationFiles.clear();
-
   cmDeleteAll(this->BuildExportSets);
   this->BuildExportSets.clear();
 
+  this->Makefiles.clear();
+
   cmDeleteAll(this->LocalGenerators);
   this->LocalGenerators.clear();
 
@@ -1593,11 +1642,11 @@ void cmGlobalGenerator::CheckLocalGenerators()
 //  std::set<std::string> notFoundMap;
   // after it is all done do a ConfigureFinalPass
   cmState* state = this->GetCMakeInstance()->GetState();
-  for (unsigned int i = 0; i < this->LocalGenerators.size(); ++i)
+  for (unsigned int i = 0; i < this->Makefiles.size(); ++i)
     {
-    this->LocalGenerators[i]->GetMakefile()->ConfigureFinalPass();
+    this->Makefiles[i]->ConfigureFinalPass();
     cmTargets &targets =
-      this->LocalGenerators[i]->GetMakefile()->GetTargets();
+      this->Makefiles[i]->GetTargets();
     for (cmTargets::iterator l = targets.begin();
          l != targets.end(); l++)
       {
@@ -1652,15 +1701,14 @@ void cmGlobalGenerator::CheckLocalGenerators()
             }
           std::string text = notFoundMap[varName];
           text += "\n   used as include directory in directory ";
-          text += this->LocalGenerators[i]
-                      ->GetMakefile()->GetCurrentSourceDirectory();
+          text += this->Makefiles[i]->GetCurrentSourceDirectory();
           notFoundMap[varName] = text;
           }
         }
       }
     this->CMakeInstance->UpdateProgress
       ("Configuring", 0.9f+0.1f*(static_cast<float>(i)+1.0f)/
-        static_cast<float>(this->LocalGenerators.size()));
+        static_cast<float>(this->Makefiles.size()));
     }
 
   if(!notFoundMap.empty())
@@ -1694,9 +1742,9 @@ int cmGlobalGenerator::TryCompile(const std::string& srcdir,
   // take the bulk of the time, so try and guess some progress
   // by getting closer and closer to 100 without actually getting there.
   if (!this->CMakeInstance->GetState()->GetInitializedCacheValue
-      ("CMAKE_NUMBER_OF_LOCAL_GENERATORS"))
+      ("CMAKE_NUMBER_OF_MAKEFILES"))
     {
-    // If CMAKE_NUMBER_OF_LOCAL_GENERATORS is not set
+    // If CMAKE_NUMBER_OF_MAKEFILES is not set
     // we are in the first time progress and we have no
     // idea how long it will be.  So, just move 1/10th of the way
     // there each time, and don't go over 95%
@@ -1884,19 +1932,19 @@ std::string cmGlobalGenerator::GenerateCMakeBuildCommand(
 }
 
 //----------------------------------------------------------------------------
-void cmGlobalGenerator::AddLocalGenerator(cmLocalGenerator *lg)
+void cmGlobalGenerator::AddMakefile(cmMakefile *mf)
 {
-  this->LocalGenerators.push_back(lg);
+  this->Makefiles.push_back(mf);
 
   // update progress
   // estimate how many lg there will be
   const char *numGenC =
     this->CMakeInstance->GetState()->GetInitializedCacheValue
-    ("CMAKE_NUMBER_OF_LOCAL_GENERATORS");
+    ("CMAKE_NUMBER_OF_MAKEFILES");
 
   if (!numGenC)
     {
-    // If CMAKE_NUMBER_OF_LOCAL_GENERATORS is not set
+    // If CMAKE_NUMBER_OF_MAKEFILES is not set
     // we are in the first time progress and we have no
     // idea how long it will be.  So, just move half way
     // there each time, and don't go over 95%
@@ -1911,7 +1959,7 @@ void cmGlobalGenerator::AddLocalGenerator(cmLocalGenerator *lg)
     }
 
   int numGen = atoi(numGenC);
-  float prog = 0.9f*static_cast<float>(this->LocalGenerators.size())/
+  float prog = 0.9f*static_cast<float>(this->Makefiles.size())/
     static_cast<float>(numGen);
   if (prog > 0.9f)
     {
@@ -1920,6 +1968,12 @@ void cmGlobalGenerator::AddLocalGenerator(cmLocalGenerator *lg)
   this->CMakeInstance->UpdateProgress("Configuring", prog);
 }
 
+//----------------------------------------------------------------------------
+void cmGlobalGenerator::AddLocalGenerator(cmLocalGenerator *lg)
+{
+  this->LocalGenerators.push_back(lg);
+}
+
 void cmGlobalGenerator::AddInstallComponent(const char* component)
 {
   if(component && *component)
@@ -2009,10 +2063,10 @@ bool cmGlobalGenerator::IsExcluded(cmLocalGenerator* root,
 }
 
 bool cmGlobalGenerator::IsExcluded(cmLocalGenerator* root,
-                                   cmTarget const& target) const
+                                   cmGeneratorTarget* target) const
 {
-  if(target.GetType() == cmTarget::INTERFACE_LIBRARY
-      || target.GetPropertyAsBool("EXCLUDE_FROM_ALL"))
+  if(target->GetType() == cmTarget::INTERFACE_LIBRARY
+      || target->Target->GetPropertyAsBool("EXCLUDE_FROM_ALL"))
     {
     // This target is excluded from its directory.
     return true;
@@ -2021,7 +2075,7 @@ bool cmGlobalGenerator::IsExcluded(cmLocalGenerator* root,
     {
     // This target is included in its directory.  Check whether the
     // directory is excluded.
-    return this->IsExcluded(root, target.GetMakefile()->GetLocalGenerator());
+    return this->IsExcluded(root, target->GetLocalGenerator());
     }
 }
 
@@ -2082,15 +2136,16 @@ void cmGlobalGenerator::FillLocalGeneratorToTargetMap()
       {
       cmTarget const& target = t->second;
 
+      cmGeneratorTarget* gt = this->GetGeneratorTarget(&target);
+
       // Consider the directory containing the target and all its
       // parents until something excludes the target.
-      for(cmLocalGenerator* clg = lg; clg && !this->IsExcluded(clg, target);
+      for(cmLocalGenerator* clg = lg; clg && !this->IsExcluded(clg, gt);
           clg = clg->GetParent())
         {
         // This local generator includes the target.
         std::set<cmGeneratorTarget const*>& targetSet =
           this->LocalGeneratorToTargetMap[clg];
-        cmGeneratorTarget* gt = this->GetGeneratorTarget(&target);
         targetSet.insert(gt);
 
         // Add dependencies of the included target.  An excluded
@@ -2107,6 +2162,20 @@ void cmGlobalGenerator::FillLocalGeneratorToTargetMap()
     }
 }
 
+cmMakefile*
+cmGlobalGenerator::FindMakefile(const std::string& start_dir) const
+{
+  for(std::vector<cmMakefile*>::const_iterator it =
+      this->Makefiles.begin(); it != this->Makefiles.end(); ++it)
+    {
+    std::string sd = (*it)->GetCurrentSourceDirectory();
+    if (sd == start_dir)
+      {
+      return *it;
+      }
+    }
+  return 0;
+}
 
 ///! Find a local generator by its startdirectory
 cmLocalGenerator*
@@ -2194,7 +2263,7 @@ inline std::string removeQuotes(const std::string& s)
 
 void cmGlobalGenerator::CreateDefaultGlobalTargets(cmTargets* targets)
 {
-  cmMakefile* mf = this->LocalGenerators[0]->GetMakefile();
+  cmMakefile* mf = this->Makefiles[0];
   const char* cmakeCfgIntDir = this->GetCMakeCFGIntDir();
 
   // CPack
@@ -2698,12 +2767,8 @@ void cmGlobalGenerator::AddTargetDepends(cmGeneratorTarget const* target,
 
 
 //----------------------------------------------------------------------------
-void cmGlobalGenerator::AddToManifest(const std::string& config,
-                                      std::string const& f)
+void cmGlobalGenerator::AddToManifest(std::string const& f)
 {
-  // Add to the main manifest for this configuration.
-  this->TargetManifest[config].insert(f);
-
   // Add to the content listing for the file's directory.
   std::string dir = cmSystemTools::GetFilenamePath(f);
   std::string file = cmSystemTools::GetFilenameName(f);
@@ -2771,9 +2836,9 @@ cmGlobalGenerator::AddRuleHash(const std::vector<std::string>& outputs,
   }
 
   // Shorten the output name (in expected use case).
-  cmLocalGenerator* lg = this->GetLocalGenerators()[0];
-  std::string fname = lg->Convert(outputs[0],
-                                  cmLocalGenerator::HOME_OUTPUT);
+  cmOutputConverter converter(this->GetMakefiles()[0]->GetStateSnapshot());
+  std::string fname = converter.Convert(
+        outputs[0], cmLocalGenerator::HOME_OUTPUT);
 
   // Associate the hash with this output.
   this->RuleHashes[fname] = hash;
@@ -3023,61 +3088,21 @@ cmGlobalGenerator::GetFilenameTargetDepends(cmSourceFile* sf) const {
 void cmGlobalGenerator::CreateEvaluationSourceFiles(
                                               std::string const& config) const
 {
-  for(std::vector<cmGeneratorExpressionEvaluationFile*>::const_iterator
-      li = this->EvaluationFiles.begin();
-      li != this->EvaluationFiles.end();
-      ++li)
+  unsigned int i;
+  for (i = 0; i < this->LocalGenerators.size(); ++i)
     {
-    (*li)->CreateOutputFile(config);
+    this->LocalGenerators[i]->CreateEvaluationFileOutputs(config);
     }
 }
 
 //----------------------------------------------------------------------------
-void cmGlobalGenerator::AddEvaluationFile(const std::string &inputFile,
-                    cmsys::auto_ptr<cmCompiledGeneratorExpression> outputExpr,
-                    cmMakefile *makefile,
-                    cmsys::auto_ptr<cmCompiledGeneratorExpression> condition,
-                    bool inputIsContent)
-{
-  this->EvaluationFiles.push_back(
-              new cmGeneratorExpressionEvaluationFile(inputFile, outputExpr,
-                                                      makefile, condition,
-                                                      inputIsContent));
-}
-
-//----------------------------------------------------------------------------
 void cmGlobalGenerator::ProcessEvaluationFiles()
 {
   std::vector<std::string> generatedFiles;
-  for(std::vector<cmGeneratorExpressionEvaluationFile*>::const_iterator
-      li = this->EvaluationFiles.begin();
-      li != this->EvaluationFiles.end();
-      ++li)
+  unsigned int i;
+  for (i = 0; i < this->LocalGenerators.size(); ++i)
     {
-    (*li)->Generate();
-    if (cmSystemTools::GetFatalErrorOccured())
-      {
-      return;
-      }
-    std::vector<std::string> files = (*li)->GetFiles();
-    std::sort(files.begin(), files.end());
-
-    std::vector<std::string> intersection;
-    std::set_intersection(files.begin(), files.end(),
-                          generatedFiles.begin(), generatedFiles.end(),
-                          std::back_inserter(intersection));
-    if (!intersection.empty())
-      {
-      cmSystemTools::Error("Files to be generated by multiple different "
-        "commands: ", cmWrap('"', intersection, '"', " ").c_str());
-      return;
-      }
-
-        generatedFiles.insert(generatedFiles.end(),
-                              files.begin(), files.end());
-    std::vector<std::string>::iterator newIt =
-        generatedFiles.end() - files.size();
-    std::inplace_merge(generatedFiles.begin(), newIt, generatedFiles.end());
+    this->LocalGenerators[i]->ProcessEvaluationFiles(generatedFiles);
     }
 }
 