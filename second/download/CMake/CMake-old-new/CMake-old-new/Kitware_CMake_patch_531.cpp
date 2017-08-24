@@ -9,20 +9,21 @@
   Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
   See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
-     This software is distributed WITHOUT ANY WARRANTY; without even 
-     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+     This software is distributed WITHOUT ANY WARRANTY; without even
+     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
      PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
 #include "cmGlobalGenerator.h"
 #include "cmLocalGenerator.h"
+#include "cmExternalMakefileProjectGenerator.h"
 #include "cmake.h"
 #include "cmMakefile.h"
 #include "cmVersion.h"
 
 #include <stdlib.h> // required for atof
 
-#if defined(_WIN32) && !defined(__CYGWIN__) 
+#if defined(_WIN32) && !defined(__CYGWIN__)
 #include <windows.h>
 #endif
 
@@ -47,17 +48,24 @@ cmGlobalGenerator::cmGlobalGenerator()
 
   // how long to let try compiles run
   this->TryCompileTimeout = 0;
+
+  this->ExtraGenerator = 0;
 }
 
 cmGlobalGenerator::~cmGlobalGenerator()
-{ 
+{
   // Delete any existing cmLocalGenerators
   unsigned int i;
   for (i = 0; i < this->LocalGenerators.size(); ++i)
     {
     delete this->LocalGenerators[i];
     }
   this->LocalGenerators.clear();
+
+  if (this->ExtraGenerator)
+    {
+    delete this->ExtraGenerator;
+    }
 }
 
 // Find the make program for the generator, required for try compiles
@@ -72,13 +80,13 @@ void cmGlobalGenerator::FindMakeProgram(cmMakefile* mf)
   if(!mf->GetDefinition("CMAKE_MAKE_PROGRAM")
      || cmSystemTools::IsOff(mf->GetDefinition("CMAKE_MAKE_PROGRAM")))
     {
-    std::string setMakeProgram = 
+    std::string setMakeProgram =
       mf->GetModulesFile(this->FindMakeProgramFile.c_str());
     if(setMakeProgram.size())
       {
       mf->ReadListFile(0, setMakeProgram.c_str());
       }
-    } 
+    }
   if(!mf->GetDefinition("CMAKE_MAKE_PROGRAM")
      || cmSystemTools::IsOff(mf->GetDefinition("CMAKE_MAKE_PROGRAM")))
     {
@@ -120,12 +128,12 @@ void cmGlobalGenerator::FindMakeProgram(cmMakefile* mf)
     // it will stop forwarding output, and let the build finish.
     // Then it will retry the build.  It will continue this
     // untill no text file busy errors occur.
-    std::string cmakexbuild = 
+    std::string cmakexbuild =
       this->CMakeInstance->GetCacheManager()->GetCacheValue("CMAKE_COMMAND");
     cmakexbuild = cmakexbuild.substr(0, cmakexbuild.length()-5);
     cmakexbuild += "cmakexbuild";
-    
-    mf->AddCacheDefinition("CMAKE_MAKE_PROGRAM", 
+
+    mf->AddCacheDefinition("CMAKE_MAKE_PROGRAM",
                            cmakexbuild.c_str(),
                            "make program",
                            cmCacheManager::FILEPATH);
@@ -135,49 +143,49 @@ void cmGlobalGenerator::FindMakeProgram(cmMakefile* mf)
 // enable the given language
 //
 // The following files are loaded in this order:
-// 
+//
 // First figure out what OS we are running on:
-// 
+//
 // CMakeSystem.cmake - configured file created by CMakeDetermineSystem.cmake
-//   CMakeDetermineSystem.cmake - figure out os info and create 
-//                                CMakeSystem.cmake IFF CMAKE_SYSTEM_NAME 
+//   CMakeDetermineSystem.cmake - figure out os info and create
+//                                CMakeSystem.cmake IFF CMAKE_SYSTEM_NAME
 //                                not set
-//   CMakeSystem.cmake - configured file created by 
-//                       CMakeDetermineSystem.cmake IFF CMAKE_SYSTEM_LOADED 
+//   CMakeSystem.cmake - configured file created by
+//                       CMakeDetermineSystem.cmake IFF CMAKE_SYSTEM_LOADED
 
 // Next try and enable all languages found in the languages vector
-// 
+//
 // FOREACH LANG in languages
-//   CMake(LANG)Compiler.cmake - configured file create by 
+//   CMake(LANG)Compiler.cmake - configured file create by
 //                               CMakeDetermine(LANG)Compiler.cmake
-//     CMakeDetermine(LANG)Compiler.cmake - Finds compiler for LANG and 
+//     CMakeDetermine(LANG)Compiler.cmake - Finds compiler for LANG and
 //                                          creates CMake(LANG)Compiler.cmake
-//     CMake(LANG)Compiler.cmake - configured file created by 
-//                                 CMakeDetermine(LANG)Compiler.cmake       
+//     CMake(LANG)Compiler.cmake - configured file created by
+//                                 CMakeDetermine(LANG)Compiler.cmake
 //
-// CMakeSystemSpecificInformation.cmake 
+// CMakeSystemSpecificInformation.cmake
 //   - includes Platform/${CMAKE_SYSTEM_NAME}.cmake
 //     may use compiler stuff
 
 // FOREACH LANG in languages
-//   CMake(LANG)Information.cmake 
+//   CMake(LANG)Information.cmake
 //     - loads Platform/${CMAKE_SYSTEM_NAME}-${COMPILER}.cmake
 //   CMakeTest(LANG)Compiler.cmake
-//     - Make sure the compiler works with a try compile if 
+//     - Make sure the compiler works with a try compile if
 //       CMakeDetermine(LANG) was loaded
-// 
+//
 // Now load a few files that can override values set in any of the above
 // CMake(PROJECTNAME)Compatibility.cmake
 //   - load any backwards compatibility stuff for current project
 // ${CMAKE_USER_MAKE_RULES_OVERRIDE}
-//   - allow users a chance to override system variables 
+//   - allow users a chance to override system variables
 //
 //
 
-void 
+void
 cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
                                   cmMakefile *mf)
-{  
+{
   if(languages.size() == 0)
     {
     cmSystemTools::Error("EnableLanguage must have a lang specified!");
@@ -187,7 +195,7 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
   mf->AddDefinition("RUN_CONFIGURE", true);
   std::string rootBin = mf->GetHomeOutputDirectory();
   rootBin += cmake::GetCMakeFilesDirectory();
-  
+
   // If the configuration files path has been set,
   // then we are in a try compile and need to copy the enable language
   // files from the parent cmake bin dir, into the try compile bin dir
@@ -206,8 +214,8 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
     }
 
   // set the dir for parent files so they can be used by modules
-  mf->AddDefinition("CMAKE_PLATFORM_ROOT_BIN",rootBin.c_str());  
-                    
+  mf->AddDefinition("CMAKE_PLATFORM_ROOT_BIN",rootBin.c_str());
+
   // find and make sure CMAKE_MAKE_PROGRAM is defined
   this->FindMakeProgram(mf);
 
@@ -225,7 +233,7 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
   // what platform we are running on
   if (!mf->GetDefinition("CMAKE_SYSTEM_NAME"))
     {
-#if defined(_WIN32) && !defined(__CYGWIN__) 
+#if defined(_WIN32) && !defined(__CYGWIN__)
     /* Windows version number data.  */
     OSVERSIONINFO osvi;
     ZeroMemory(&osvi, sizeof(osvi));
@@ -247,9 +255,9 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
     mf->ReadListFile(0,fpath.c_str());
     }
   std::map<cmStdString, bool> needTestLanguage;
-  // foreach language 
+  // foreach language
   // load the CMakeDetermine(LANG)Compiler.cmake file to find
-  // the compiler 
+  // the compiler
 
   for(std::vector<std::string>::const_iterator l = languages.begin();
       l != languages.end(); ++l)
@@ -283,38 +291,38 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
         {
         if(!mf->ReadListFile(0,fpath.c_str()))
           {
-          cmSystemTools::Error("Could not find cmake module file:", 
+          cmSystemTools::Error("Could not find cmake module file:",
                                fpath.c_str());
           }
         // if this file was found then the language was already determined
         // to be working
         needTestLanguage[lang] = false;
-        this->SetLanguageEnabled(lang, mf); 
+        this->SetLanguageEnabled(lang, mf);
         // this can only be called after loading CMake(LANG)Compiler.cmake
         }
       }
-      
+
     if(!this->GetLanguageEnabled(lang) )
-      {  
+      {
       if (this->CMakeInstance->GetIsInTryCompile())
         {
         cmSystemTools::Error("This should not have happen. "
                              "If you see this message, you are probably "
                              "using a broken CMakeLists.txt file or a "
                              "problematic release of CMake");
         }
-      // if the CMake(LANG)Compiler.cmake file was not found then 
+      // if the CMake(LANG)Compiler.cmake file was not found then
       // load CMakeDetermine(LANG)Compiler.cmake
       std::string determineCompiler = "CMakeDetermine";
       determineCompiler += lang;
       determineCompiler += "Compiler.cmake";
-      std::string determineFile = 
+      std::string determineFile =
         mf->GetModulesFile(determineCompiler.c_str());
       if(!mf->ReadListFile(0,determineFile.c_str()))
         {
-        cmSystemTools::Error("Could not find cmake module file:", 
+        cmSystemTools::Error("Could not find cmake module file:",
                              determineFile.c_str());
-        }      
+        }
       needTestLanguage[lang] = true;
       determineLanguageCalled = true;
       // Some generators like visual studio should not use the env variables
@@ -331,15 +339,15 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
         compilerEnv += lang;
         compilerEnv += "_COMPILER_ENV_VAR";
         std::string envVar = mf->GetRequiredDefinition(compilerEnv.c_str());
-        std::string envVarValue = 
+        std::string envVarValue =
           mf->GetRequiredDefinition(compilerName.c_str());
         std::string env = envVar;
         env += "=";
         env += envVarValue;
         cmSystemTools::PutEnv(env.c_str());
         }
-      } // end if(!this->GetLanguageEnabled(lang) )  
-    // if determineLanguage was called then load the file it 
+      } // end if(!this->GetLanguageEnabled(lang) )
+    // if determineLanguage was called then load the file it
     // configures CMake(LANG)Compiler.cmake
     if(determineLanguageCalled)
       {
@@ -349,25 +357,25 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
       fpath += "Compiler.cmake";
       if(!mf->ReadListFile(0,fpath.c_str()))
         {
-        cmSystemTools::Error("Could not find cmake module file:", 
+        cmSystemTools::Error("Could not find cmake module file:",
                              fpath.c_str());
         }
-      this->SetLanguageEnabled(lang, mf); 
+      this->SetLanguageEnabled(lang, mf);
       // this can only be called after loading CMake(LANG)Compiler.cmake
       // the language must be enabled for try compile to work, but we do
       // not know if it is a working compiler yet so set the test language
       // flag
       needTestLanguage[lang] = true;
       }
     }  // end loop over languages
-  
+
   // **** Load the system specific information if not yet loaded
   if (!mf->GetDefinition("CMAKE_SYSTEM_SPECIFIC_INFORMATION_LOADED"))
     {
     fpath = mf->GetModulesFile("CMakeSystemSpecificInformation.cmake");
     if(!mf->ReadListFile(0,fpath.c_str()))
       {
-      cmSystemTools::Error("Could not find cmake module file:", 
+      cmSystemTools::Error("Could not find cmake module file:",
                            fpath.c_str());
       }
     }
@@ -386,14 +394,14 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
     langLoadedVar += lang;
     langLoadedVar += "_INFORMATION_LOADED";
     if (!mf->GetDefinition(langLoadedVar.c_str()))
-      { 
+      {
       fpath = "CMake";
       fpath +=  lang;
       fpath += "Information.cmake";
       fpath = mf->GetModulesFile(fpath.c_str());
       if(!mf->ReadListFile(0,fpath.c_str()))
         {
-        cmSystemTools::Error("Could not find cmake module file:", 
+        cmSystemTools::Error("Could not find cmake module file:",
                              fpath.c_str());
         }
       }
@@ -411,7 +419,7 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
         std::string ifpath = mf->GetModulesFile(testLang.c_str());
         if(!mf->ReadListFile(0,ifpath.c_str()))
           {
-          cmSystemTools::Error("Could not find cmake module file:", 
+          cmSystemTools::Error("Could not find cmake module file:",
                                ifpath.c_str());
           }
         std::string compilerWorks = "CMAKE_";
@@ -421,7 +429,7 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
         // CMake(LANG)Compiler.cmake file so that it will get tested the
         // next time cmake is run
         if(!mf->IsOn(compilerWorks.c_str()))
-          { 
+          {
           fpath = rootBin;
           fpath += "/CMake";
           fpath += lang;
@@ -441,22 +449,22 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
             {
             if(strcmp(lang, "C") == 0)
               {
-              ifpath =  
+              ifpath =
                 mf->GetModulesFile("CMakeBackwardCompatibilityC.cmake");
-              mf->ReadListFile(0,ifpath.c_str()); 
+              mf->ReadListFile(0,ifpath.c_str());
               }
             if(strcmp(lang, "CXX") == 0)
               {
               ifpath =
                 mf->GetModulesFile("CMakeBackwardCompatibilityCXX.cmake");
-              mf->ReadListFile(0,ifpath.c_str()); 
+              mf->ReadListFile(0,ifpath.c_str());
               }
             }
           }
         } // end if in try compile
       } // end need test language
     } // end for each language
-  
+
   // Now load files that can override any settings on the platform or for
   // the project First load the project compatibility file if it is in
   // cmake
@@ -466,14 +474,14 @@ cmGlobalGenerator::EnableLanguage(std::vector<std::string>const& languages,
   projectCompatibility += "Compatibility.cmake";
   if(cmSystemTools::FileExists(projectCompatibility.c_str()))
     {
-    mf->ReadListFile(0,projectCompatibility.c_str()); 
+    mf->ReadListFile(0,projectCompatibility.c_str());
     }
 }
 
 const char* cmGlobalGenerator
 ::GetLanguageOutputExtensionForLanguage(const char* lang)
 {
-  if(!lang) 
+  if(!lang)
     {
     return "";
     }
@@ -527,7 +535,7 @@ void cmGlobalGenerator::SetLanguageEnabled(const char* l, cmMakefile* mf)
     {
     return;
     }
-  std::string outputExtensionVar = std::string("CMAKE_") + 
+  std::string outputExtensionVar = std::string("CMAKE_") +
     std::string(l) + std::string("_OUTPUT_EXTENSION");
   const char* outputExtension = mf->GetDefinition(outputExtensionVar.c_str());
   if(outputExtension)
@@ -539,19 +547,19 @@ void cmGlobalGenerator::SetLanguageEnabled(const char* l, cmMakefile* mf)
       this->OutputExtensions[outputExtension+1] = outputExtension+1;
       }
     }
-  
-  std::string linkerPrefVar = std::string("CMAKE_") + 
+
+  std::string linkerPrefVar = std::string("CMAKE_") +
     std::string(l) + std::string("_LINKER_PREFERENCE");
   const char* linkerPref = mf->GetDefinition(linkerPrefVar.c_str());
   if(!linkerPref)
     {
     linkerPref = "None";
     }
   this->LanguageToLinkerPreference[l] = linkerPref;
-  
-  std::string extensionsVar = std::string("CMAKE_") + 
+
+  std::string extensionsVar = std::string("CMAKE_") +
     std::string(l) + std::string("_SOURCE_FILE_EXTENSIONS");
-  std::string ignoreExtensionsVar = std::string("CMAKE_") + 
+  std::string ignoreExtensionsVar = std::string("CMAKE_") +
     std::string(l) + std::string("_IGNORE_EXTENSIONS");
   std::string ignoreExts = mf->GetSafeDefinition(ignoreExtensionsVar.c_str());
   std::string exts = mf->GetSafeDefinition(extensionsVar.c_str());
@@ -598,20 +606,20 @@ bool cmGlobalGenerator::IsDependedOn(const char* project,
   // loop over local gens and get the targets for each one
   for(unsigned int i = 0; i < gens->size(); ++i)
     {
-    cmTargets& targets = (*gens)[i]->GetMakefile()->GetTargets(); 
+    cmTargets& targets = (*gens)[i]->GetMakefile()->GetTargets();
     for (cmTargets::iterator l = targets.begin();
          l != targets.end(); l++)
-      { 
+      {
       cmTarget& target = l->second;
-      std::set<cmStdString>::const_iterator pos = 
+      std::set<cmStdString>::const_iterator pos =
         target.GetUtilities().find(targetIn->GetName());
       if(pos != target.GetUtilities().end())
         {
         return true;
         }
       }
     }
-  return false; 
+  return false;
 }
 
 void cmGlobalGenerator::Configure()
@@ -639,51 +647,51 @@ void cmGlobalGenerator::Configure()
   lg->GetMakefile()->SetStartOutputDirectory
     (this->CMakeInstance->GetStartOutputDirectory());
   lg->GetMakefile()->MakeStartDirectoriesCurrent();
-  
+
   // now do it
   lg->Configure();
-  
+
   // update the cache entry for the number of local generators, this is used
   // for progress
   char num[100];
   sprintf(num,"%d",static_cast<int>(this->LocalGenerators.size()));
   this->GetCMakeInstance()->AddCacheEntry
     ("CMAKE_NUMBER_OF_LOCAL_GENERATORS", num,
      "number of local generators", cmCacheManager::INTERNAL);
-  
+
   std::set<cmStdString> notFoundMap;
   // after it is all done do a ConfigureFinalPass
   cmCacheManager* manager = 0;
   for (i = 0; i < this->LocalGenerators.size(); ++i)
     {
     manager = this->LocalGenerators[i]->GetMakefile()->GetCacheManager();
     this->LocalGenerators[i]->ConfigureFinalPass();
-    cmTargets & targets = 
-      this->LocalGenerators[i]->GetMakefile()->GetTargets(); 
+    cmTargets & targets =
+      this->LocalGenerators[i]->GetMakefile()->GetTargets();
     for (cmTargets::iterator l = targets.begin();
          l != targets.end(); l++)
       {
       cmTarget::LinkLibraryVectorType libs = l->second.GetLinkLibraries();
       for(cmTarget::LinkLibraryVectorType::iterator lib = libs.begin();
           lib != libs.end(); ++lib)
         {
-        if(lib->first.size() > 9 && 
+        if(lib->first.size() > 9 &&
            cmSystemTools::IsNOTFOUND(lib->first.c_str()))
           {
           std::string varName = lib->first.substr(0, lib->first.size()-9);
           notFoundMap.insert(varName);
           }
         }
-      std::vector<std::string>& incs = 
+      std::vector<std::string>& incs =
         this->LocalGenerators[i]->GetMakefile()->GetIncludeDirectories();
-      
+
       for( std::vector<std::string>::iterator lib = incs.begin();
            lib != incs.end(); ++lib)
         {
-        if(lib->size() > 9 && 
+        if(lib->size() > 9 &&
            cmSystemTools::IsNOTFOUND(lib->c_str()))
           {
-          std::string varName = lib->substr(0, lib->size()-9); 
+          std::string varName = lib->substr(0, lib->size()-9);
           notFoundMap.insert(varName);
           }
         }
@@ -698,11 +706,11 @@ void cmGlobalGenerator::Configure()
     std::string notFoundVars;
     for(std::set<cmStdString>::iterator ii = notFoundMap.begin();
         ii != notFoundMap.end(); ++ii)
-      { 
+      {
       notFoundVars += *ii;
       if(manager)
         {
-        cmCacheManager::CacheIterator it = 
+        cmCacheManager::CacheIterator it =
           manager->GetCacheIterator(ii->c_str());
         if(it.GetPropertyAsBool("ADVANCED"))
           {
@@ -719,8 +727,8 @@ void cmGlobalGenerator::Configure()
   // at this point this->LocalGenerators has been filled,
   // so create the map from project name to vector of local generators
     this->FillProjectMap();
-  // now create project to target map 
-  // This will make sure that targets have all the 
+  // now create project to target map
+  // This will make sure that targets have all the
   // targets they depend on as part of the build.
     this->FillProjectToTargetMap();
 
@@ -740,7 +748,7 @@ void cmGlobalGenerator::Generate()
   this->CreateDefaultGlobalTargets(&globalTargets);
   for (i = 0; i < this->LocalGenerators.size(); ++i)
     {
-    cmTargets* targets = 
+    cmTargets* targets =
       &(this->LocalGenerators[i]->GetMakefile()->GetTargets());
     cmTargets::iterator tarIt;
     for ( tarIt = targets->begin(); tarIt != targets->end(); ++ tarIt )
@@ -762,7 +770,7 @@ void cmGlobalGenerator::Generate()
       (*targets)[tit->first].SetMakefile(mf);
       }
     }
- 
+
   // Add generator specific helper commands
   for (i = 0; i < this->LocalGenerators.size(); ++i)
     {
@@ -788,14 +796,20 @@ void cmGlobalGenerator::Generate()
     this->LocalGenerators[i]->Generate();
     this->LocalGenerators[i]->GenerateInstallRules();
     this->LocalGenerators[i]->GenerateTestFiles();
-    this->CMakeInstance->UpdateProgress("Generating", 
+    this->CMakeInstance->UpdateProgress("Generating",
                                     (i+1.0f)/this->LocalGenerators.size());
     }
+
+  if (this->ExtraGenerator != 0)
+    {
+    this->ExtraGenerator->Generate();
+    }
+
   this->CMakeInstance->UpdateProgress("Generating done", -1);
 }
 
-int cmGlobalGenerator::TryCompile(const char *srcdir, const char *bindir, 
-                                  const char *projectName, 
+int cmGlobalGenerator::TryCompile(const char *srcdir, const char *bindir,
+                                  const char *projectName,
                                   const char *target,
                                   std::string *output, cmMakefile *mf)
 {
@@ -815,7 +829,7 @@ int cmGlobalGenerator::TryCompile(const char *srcdir, const char *bindir,
 #if 0
 #if defined(_WIN32) || defined(__CYGWIN__)
     std::string tmp = target;
-    // if the target does not already end in . something 
+    // if the target does not already end in . something
     // then assume .exe
     if(tmp.size() < 4 || tmp[tmp.size()-4] != '.')
       {
@@ -827,20 +841,20 @@ int cmGlobalGenerator::TryCompile(const char *srcdir, const char *bindir,
   const char* config = mf->GetDefinition("CMAKE_TRY_COMPILE_CONFIGURATION");
   return this->Build(srcdir,bindir,projectName,
                      newTarget.c_str(),
-                     output,makeCommand.c_str(),config,false,true, 
+                     output,makeCommand.c_str(),config,false,true,
                      this->TryCompileTimeout);
 }
 
 std::string cmGlobalGenerator
-::GenerateBuildCommand(const char* makeProgram, const char *projectName, 
+::GenerateBuildCommand(const char* makeProgram, const char *projectName,
                        const char* additionalOptions, const char *targetName,
                        const char* config, bool ignoreErrors, bool)
 {
   // Project name and config are not used yet.
   (void)projectName;
   (void)config;
 
-  std::string makeCommand = 
+  std::string makeCommand =
     cmSystemTools::ConvertToUnixOutputPath(makeProgram);
 
   // Since we have full control over the invocation of nmake, let us
@@ -865,18 +879,18 @@ ::GenerateBuildCommand(const char* makeProgram, const char *projectName,
     }
   return makeCommand;
 }
-  
+
 int cmGlobalGenerator::Build(
-  const char *, const char *bindir, 
+  const char *, const char *bindir,
   const char *projectName, const char *target,
-  std::string *output, 
+  std::string *output,
   const char *makeCommandCSTR,
   const char *config,
   bool clean, bool fast,
   double timeout)
 {
   *output += "\nTesting TryCompileWithoutMakefile\n";
-  
+
   /**
    * Run an executable command and put the stdout in output.
    */
@@ -890,10 +904,10 @@ int cmGlobalGenerator::Build(
   // should we do a clean first?
   if (clean)
     {
-    std::string cleanCommand = 
+    std::string cleanCommand =
       this->GenerateBuildCommand(makeCommandCSTR, projectName,
       0, "clean", config, false, fast);
-    if (!cmSystemTools::RunSingleCommand(cleanCommand.c_str(), output, 
+    if (!cmSystemTools::RunSingleCommand(cleanCommand.c_str(), output,
                                          &retVal, 0, false, timeout))
       {
       cmSystemTools::SetRunCommandHideConsole(hideconsole);
@@ -902,19 +916,19 @@ int cmGlobalGenerator::Build(
         {
         *output += "\nGenerator: execution of make clean failed.\n";
         }
-      
+
       // return to the original directory
       cmSystemTools::ChangeDirectory(cwd.c_str());
       return 1;
       }
     }
-  
+
   // now build
-  std::string makeCommand = 
+  std::string makeCommand =
     this->GenerateBuildCommand(makeCommandCSTR, projectName,
                                0, target, config, false, fast);
-  
-  if (!cmSystemTools::RunSingleCommand(makeCommand.c_str(), output, 
+
+  if (!cmSystemTools::RunSingleCommand(makeCommand.c_str(), output,
                                        &retVal, 0, false, timeout))
     {
     cmSystemTools::SetRunCommandHideConsole(hideconsole);
@@ -923,44 +937,44 @@ int cmGlobalGenerator::Build(
        makeCommand.c_str());
     if (output)
       {
-      *output += "\nGenerator: execution of make failed. Make command was: " 
+      *output += "\nGenerator: execution of make failed. Make command was: "
         + makeCommand + "\n";
       }
-    
+
     // return to the original directory
     cmSystemTools::ChangeDirectory(cwd.c_str());
     return 1;
     }
 
   cmSystemTools::SetRunCommandHideConsole(hideconsole);
-  
+
   // The SGI MipsPro 7.3 compiler does not return an error code when
   // the source has a #error in it!  This is a work-around for such
   // compilers.
   if((retVal == 0) && (output->find("#error") != std::string::npos))
     {
     retVal = 1;
     }
-  
+
   cmSystemTools::ChangeDirectory(cwd.c_str());
   return retVal;
 }
 
 void cmGlobalGenerator::AddLocalGenerator(cmLocalGenerator *lg)
 {
-  this->LocalGenerators.push_back(lg); 
+  this->LocalGenerators.push_back(lg);
 
   // update progress
   // estimate how many lg there will be
-  const char *numGenC = 
+  const char *numGenC =
     this->CMakeInstance->GetCacheManager()->GetCacheValue
     ("CMAKE_NUMBER_OF_LOCAL_GENERATORS");
-  
+
   if (!numGenC)
     {
     return;
     }
-  
+
   int numGen = atoi(numGenC);
   float prog = 0.9f*this->LocalGenerators.size()/numGen;
   if (prog > 0.9f)
@@ -1017,7 +1031,7 @@ void cmGlobalGenerator::GetDocumentation(cmDocumentationEntry& entry) const
   entry.full = "";
 }
 
-bool cmGlobalGenerator::IsExcluded(cmLocalGenerator* root, 
+bool cmGlobalGenerator::IsExcluded(cmLocalGenerator* root,
                                    cmLocalGenerator* gen)
 {
   if(gen == root)
@@ -1039,7 +1053,7 @@ bool cmGlobalGenerator::IsExcluded(cmLocalGenerator* root,
 
 void cmGlobalGenerator::GetEnabledLanguages(std::vector<std::string>& lang)
 {
-  for(std::map<cmStdString, bool>::iterator i = 
+  for(std::map<cmStdString, bool>::iterator i =
         this->LanguageEnabled.begin(); i != this->LanguageEnabled.end(); ++i)
     {
     lang.push_back(i->first);
@@ -1056,15 +1070,15 @@ const char* cmGlobalGenerator::GetLinkerPreference(const char* lang)
 }
 
 void cmGlobalGenerator::FillProjectMap()
-{ 
+{
   this->ProjectMap.clear(); // make sure we start with a clean map
   unsigned int i;
   for(i = 0; i < this->LocalGenerators.size(); ++i)
     {
-    // for each local generator add all projects 
+    // for each local generator add all projects
     cmLocalGenerator *lg = this->LocalGenerators[i];
     std::string name;
-    do 
+    do
       {
       if (name != lg->GetMakefile()->GetProjectName())
         {
@@ -1082,8 +1096,8 @@ void cmGlobalGenerator::FillProjectMap()
 void cmGlobalGenerator::FillProjectToTargetMap()
 {
   // loop over each project in the build
-  for(std::map<cmStdString, 
-        std::vector<cmLocalGenerator*> >::iterator m = 
+  for(std::map<cmStdString,
+        std::vector<cmLocalGenerator*> >::iterator m =
         this->ProjectMap.begin();
       m != this->ProjectMap.end(); ++m)
     {
@@ -1098,9 +1112,9 @@ void cmGlobalGenerator::FillProjectToTargetMap()
     const char* exclude = 0;
     std::string excludeSave;
     bool chain = false;
-    exclude = 
+    exclude =
       projectMakefile->GetProperties().
-      GetPropertyValue("EXCLUDE_FROM_ALL", 
+      GetPropertyValue("EXCLUDE_FROM_ALL",
                        cmProperty::DIRECTORY, chain);
     if(exclude)
       {
@@ -1112,7 +1126,7 @@ void cmGlobalGenerator::FillProjectToTargetMap()
     // now loop over all cmLocalGenerators in this project and pull
     // out all the targets that depend on each other, even if those
     // targets come from a target that is excluded.
-    for(std::vector<cmLocalGenerator*>::iterator lg = 
+    for(std::vector<cmLocalGenerator*>::iterator lg =
           lgs.begin(); lg != lgs.end(); ++lg)
       {
       cmMakefile* mf = (*lg)->GetMakefile();
@@ -1121,7 +1135,7 @@ void cmGlobalGenerator::FillProjectToTargetMap()
           t != targets.end(); ++t)
         {
         cmTarget& target = t->second;
-        // if the target is in all then add it to the project 
+        // if the target is in all then add it to the project
         if(!target.GetPropertyAsBool("EXCLUDE_FROM_ALL"))
           {
           // add this target to the project
@@ -1131,23 +1145,23 @@ void cmGlobalGenerator::FillProjectToTargetMap()
           this->ProjectToTargetMap[projectName].insert(tgtdeps.begin(),
                                                        tgtdeps.end());
           }
-        } 
+        }
       }
-    // Now restore the EXCLUDE_FROM_ALL property on the project top 
+    // Now restore the EXCLUDE_FROM_ALL property on the project top
     // makefile
     if(exclude)
       {
       exclude = excludeSave.c_str();
       }
     projectMakefile->SetProperty("EXCLUDE_FROM_ALL", exclude);
     }
-  // dump the map for debug purposes 
-  // right now this map is not being used, but it was 
-  // checked in to avoid constant conflicts.  
+  // dump the map for debug purposes
+  // right now this map is not being used, but it was
+  // checked in to avoid constant conflicts.
   // It is also the first step to creating sub projects
   // that contain all of the targets they need.
 #if 0
-  std::map<cmStdString, std::set<cmTarget*> >::iterator i = 
+  std::map<cmStdString, std::set<cmTarget*> >::iterator i =
     this->ProjectToTargetMap.begin();
   for(; i != this->ProjectToTargetMap.end(); ++i)
     {
@@ -1179,7 +1193,7 @@ cmLocalGenerator* cmGlobalGenerator::FindLocalGenerator(const char* start_dir)
 }
 
 
-cmTarget* cmGlobalGenerator::FindTarget(const char* project, 
+cmTarget* cmGlobalGenerator::FindTarget(const char* project,
                                         const char* name,
                                         bool useImportedTargets)
 {
@@ -1189,7 +1203,7 @@ cmTarget* cmGlobalGenerator::FindTarget(const char* project,
     std::vector<cmLocalGenerator*>* gens = &this->ProjectMap[project];
     for(unsigned int i = 0; i < gens->size(); ++i)
       {
-      cmTarget* ret = (*gens)[i]->GetMakefile()->FindTarget(name, 
+      cmTarget* ret = (*gens)[i]->GetMakefile()->FindTarget(name,
                                                             useImportedTargets);
       if(ret)
         {
@@ -1206,7 +1220,7 @@ cmTarget* cmGlobalGenerator::FindTarget(const char* project,
       {
       return i->second;
       }
-    
+
     if ( useImportedTargets )
       {
       std::map<cmStdString,cmTarget *>::iterator importedTarget =
@@ -1271,7 +1285,7 @@ void cmGlobalGenerator::CreateDefaultGlobalTargets(cmTargets* targets)
   const char* packageSourceTargetName = this->GetPackageSourceTargetName();
   if ( packageSourceTargetName )
     {
-    cpackCommandLines.erase(cpackCommandLines.begin(), 
+    cpackCommandLines.erase(cpackCommandLines.begin(),
                             cpackCommandLines.end());
     singleLine.erase(singleLine.begin(), singleLine.end());
     depends.erase(depends.begin(), depends.end());
@@ -1293,7 +1307,7 @@ void cmGlobalGenerator::CreateDefaultGlobalTargets(cmTargets* targets)
   // Test
   if(mf->IsOn("CMAKE_TESTING_ENABLED"))
     {
-    cpackCommandLines.erase(cpackCommandLines.begin(), 
+    cpackCommandLines.erase(cpackCommandLines.begin(),
                             cpackCommandLines.end());
     singleLine.erase(singleLine.begin(), singleLine.end());
     depends.erase(depends.begin(), depends.end());
@@ -1318,7 +1332,7 @@ void cmGlobalGenerator::CreateDefaultGlobalTargets(cmTargets* targets)
   const char* editCacheTargetName = this->GetEditCacheTargetName();
   if ( editCacheTargetName )
     {
-    cpackCommandLines.erase(cpackCommandLines.begin(), 
+    cpackCommandLines.erase(cpackCommandLines.begin(),
                             cpackCommandLines.end());
     singleLine.erase(singleLine.begin(), singleLine.end());
     depends.erase(depends.begin(), depends.end());
@@ -1344,7 +1358,7 @@ void cmGlobalGenerator::CreateDefaultGlobalTargets(cmTargets* targets)
       cpackCommandLines.push_back(singleLine);
       (*targets)[editCacheTargetName] =
         this->CreateGlobalTarget(
-          editCacheTargetName, 
+          editCacheTargetName,
           "Running interactive CMake command-line interface...",
           &cpackCommandLines, depends);
       }
@@ -1354,7 +1368,7 @@ void cmGlobalGenerator::CreateDefaultGlobalTargets(cmTargets* targets)
   const char* rebuildCacheTargetName = this->GetRebuildCacheTargetName();
   if ( rebuildCacheTargetName )
     {
-    cpackCommandLines.erase(cpackCommandLines.begin(), 
+    cpackCommandLines.erase(cpackCommandLines.begin(),
                             cpackCommandLines.end());
     singleLine.erase(singleLine.begin(), singleLine.end());
     depends.erase(depends.begin(), depends.end());
@@ -1374,7 +1388,7 @@ void cmGlobalGenerator::CreateDefaultGlobalTargets(cmTargets* targets)
     if(!cmakeCfgIntDir || !*cmakeCfgIntDir || cmakeCfgIntDir[0] == '.')
       {
       std::set<cmStdString>* componentsSet = &this->InstallComponents;
-      cpackCommandLines.erase(cpackCommandLines.begin(), 
+      cpackCommandLines.erase(cpackCommandLines.begin(),
         cpackCommandLines.end());
       depends.erase(depends.begin(), depends.end());
       cmOStringStream ostr;
@@ -1535,21 +1549,21 @@ std::vector<cmTarget *>& cmGlobalGenerator
 ::GetTargetDepends(cmTarget& target)
 {
   // if the depends are already in the map then return
-  std::map<cmStdString, std::vector<cmTarget *> >::iterator tgtI = 
+  std::map<cmStdString, std::vector<cmTarget *> >::iterator tgtI =
     this->TargetDependencies.find(target.GetName());
   if (tgtI != this->TargetDependencies.end())
     {
     return tgtI->second;
     }
-  
+
   // A target should not depend on itself.
   std::set<cmStdString> emitted;
   emitted.insert(target.GetName());
-  
+
   // the vector of results
-  std::vector<cmTarget *>& result = 
+  std::vector<cmTarget *>& result =
     this->TargetDependencies[target.GetName()];
-  
+
   // Loop over all library dependencies but not for static libs
   if (target.GetType() != cmTarget::STATIC_LIBRARY)
     {
@@ -1560,15 +1574,15 @@ ::GetTargetDepends(cmTarget& target)
       // Don't emit the same library twice for this target.
       if(emitted.insert(lib->first).second)
         {
-        cmTarget *target2 = 
+        cmTarget *target2 =
           target.GetMakefile()->FindTarget(lib->first.c_str(), false);
 
         // search each local generator until a match is found
         if (!target2)
           {
           target2 = this->FindTarget(0,lib->first.c_str(), false);
           }
-        
+
         // if a match was found then ...
         if (target2)
           {
@@ -1578,7 +1592,7 @@ ::GetTargetDepends(cmTarget& target)
         }
       }
     }
-  
+
   // Loop over all utility dependencies.
   const std::set<cmStdString>& tutils = target.GetUtilities();
   for(std::set<cmStdString>::const_iterator util = tutils.begin();
@@ -1588,13 +1602,13 @@ ::GetTargetDepends(cmTarget& target)
     if(emitted.insert(*util).second)
       {
       cmTarget *target2 = target.GetMakefile()->FindTarget(util->c_str(), false);
-      
+
       // search each local generator until a match is found
       if (!target2)
         {
         target2 = this->FindTarget(0,util->c_str(), false);
         }
-      
+
       // if a match was found then ...
       if (target2)
         {
@@ -1617,3 +1631,14 @@ void cmGlobalGenerator::AddTarget(cmTargets::value_type &v)
     this->TotalTargets[v.first] = &v.second;
     }
 }
+
+void cmGlobalGenerator::SetExternalMakefileProjectGenerator(
+                            cmExternalMakefileProjectGenerator *extraGenerator)
+{
+  this->ExtraGenerator = extraGenerator;
+  if (this->ExtraGenerator!=0)
+    {
+    this->ExtraGenerator->SetGlobalGenerator(this);
+    }
+}
+