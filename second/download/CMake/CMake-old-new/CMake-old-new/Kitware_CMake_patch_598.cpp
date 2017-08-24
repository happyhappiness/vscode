@@ -9,8 +9,8 @@
   Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
   See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
-     This software is distributed WITHOUT ANY WARRANTY; without even 
-     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+     This software is distributed WITHOUT ANY WARRANTY; without even
+     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
      PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
@@ -78,20 +78,22 @@
 
 #include <memory> // auto_ptr
 
-void cmNeedBackwardsCompatibility(const std::string& variable, 
+void cmNeedBackwardsCompatibility(const std::string& variable,
                                   int access_type, void* )
 {
 #ifdef CMAKE_BUILD_WITH_CMAKE
   if (access_type == cmVariableWatch::UNKNOWN_VARIABLE_READ_ACCESS)
     {
     std::string message = "An attempt was made to access a variable: ";
     message += variable;
-    message += " that has not been defined. Some variables were always defined "
-      "by CMake in versions prior to 1.6. To fix this you might need to set the "
-      "cache value of CMAKE_BACKWARDS_COMPATIBILITY to 1.4 or less. If you are "
-      "writing a CMakeList file, (or have already set "
-      "CMAKE_BACKWARDS_COMPATABILITY to 1.4 or less) then you probably need to "
-      "include a CMake module to test for the feature this variable defines.";
+    message +=
+      " that has not been defined. Some variables were always defined "
+      "by CMake in versions prior to 1.6. To fix this you might need to set "
+      "the cache value of CMAKE_BACKWARDS_COMPATIBILITY to 1.4 or less. If "
+      "you are writing a CMakeList file, (or have already set "
+      "CMAKE_BACKWARDS_COMPATABILITY to 1.4 or less) then you probably need "
+      "to include a CMake module to test for the feature this variable "
+      "defines.";
     cmSystemTools::Error(message.c_str());
     }
 #else
@@ -105,7 +107,7 @@ cmake::cmake()
   m_DebugTryCompile = false;
   m_ClearBuildSystem = false;
   m_FileComparison = new cmFileTimeComparison;
-  
+
 #ifdef __APPLE__
   struct rlimit rlp;
   if(!getrlimit(RLIMIT_STACK, &rlp))
@@ -126,8 +128,8 @@ cmake::cmake()
   if(getenv("MAKEFLAGS"))
     {
     cmSystemTools::PutEnv("MAKEFLAGS=");
-    }  
-  
+    }
+
   m_Verbose = false;
   m_InTryCompile = false;
   m_CacheManager = new cmCacheManager;
@@ -202,7 +204,7 @@ bool cmake::CommandExists(const char* name) const
   return (m_Commands.find(sName) != m_Commands.end());
 }
 
-cmCommand *cmake::GetCommand(const char *name) 
+cmCommand *cmake::GetCommand(const char *name)
 {
   cmCommand* rm = 0;
   std::string sName = cmSystemTools::LowerCase(name);
@@ -252,7 +254,7 @@ void cmake::AddCommand(cmCommand* wg)
 
 // Parse the args
 bool cmake::SetCacheArgs(const std::vector<std::string>& args)
-{ 
+{
   for(unsigned int i=1; i < args.size(); ++i)
     {
     std::string arg = args[i];
@@ -278,7 +280,7 @@ bool cmake::SetCacheArgs(const std::vector<std::string>& args)
                   << "Should be: VAR:type=value\n";
         cmSystemTools::Error("No cmake scrpt provided.");
         return false;
-        }        
+        }
       }
     else if(arg.find("-C",0) == 0)
       {
@@ -311,7 +313,7 @@ void cmake::ReadListFile(const char *path)
   // if a generator was not yet created, temporarily create one
   cmGlobalGenerator *gg = this->GetGlobalGenerator();
   bool created = false;
-  
+
   // if a generator was not specified use a generic one
   if (!gg)
     {
@@ -338,7 +340,7 @@ void cmake::ReadListFile(const char *path)
       std::cerr << "Error processing file:" << path << "\n";
       }
     }
-  
+
   // free generic one if generated
   if (created)
     {
@@ -422,7 +424,7 @@ void cmake::SetArgs(const std::vector<std::string>& args)
         {
         value = args[++i];
         }
-      cmGlobalGenerator* gen = 
+      cmGlobalGenerator* gen =
         this->CreateGlobalGenerator(value.c_str());
       if(!gen)
         {
@@ -520,40 +522,41 @@ void cmake::SetDirectoriesFromFile(const char* arg)
     {
     cmCacheManager* cachem = this->GetCacheManager();
     cmCacheManager::CacheIterator it = cachem->NewIterator();
-    if(cachem->LoadCache(cachePath.c_str()) && it.Find("CMAKE_HOME_DIRECTORY"))
+    if(cachem->LoadCache(cachePath.c_str()) &&
+      it.Find("CMAKE_HOME_DIRECTORY"))
       {
-      this->SetHomeOutputDirectory(cachePath.c_str());      
-      this->SetStartOutputDirectory(cachePath.c_str());      
+      this->SetHomeOutputDirectory(cachePath.c_str());
+      this->SetStartOutputDirectory(cachePath.c_str());
       this->SetHomeDirectory(it.GetValue());
       this->SetStartDirectory(it.GetValue());
       return;
       }
     }
-  
+
   // If there is a CMakeLists.txt file, use it as the source tree.
   if(listPath.length() > 0)
     {
     this->SetHomeDirectory(listPath.c_str());
     this->SetStartDirectory(listPath.c_str());
-    
+
     if(argIsFile)
       {
       // Source CMakeLists.txt file given.  It was probably dropped
       // onto the executable in a GUI.  Default to an in-source build.
-      this->SetHomeOutputDirectory(listPath.c_str());      
-      this->SetStartOutputDirectory(listPath.c_str());      
+      this->SetHomeOutputDirectory(listPath.c_str());
+      this->SetStartOutputDirectory(listPath.c_str());
       }
     else
       {
       // Source directory given on command line.  Use current working
       // directory as build tree.
       std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
       this->SetHomeOutputDirectory(cwd.c_str());
-      this->SetStartOutputDirectory(cwd.c_str());      
+      this->SetStartOutputDirectory(cwd.c_str());
       }
     return;
     }
-  
+
   // We didn't find a CMakeLists.txt or CMakeCache.txt file from the
   // argument.  Assume it is the path to the source tree, and use the
   // current working directory as the build tree.
@@ -562,10 +565,11 @@ void cmake::SetDirectoriesFromFile(const char* arg)
   this->SetHomeDirectory(full.c_str());
   this->SetStartDirectory(full.c_str());
   this->SetHomeOutputDirectory(cwd.c_str());
-  this->SetStartOutputDirectory(cwd.c_str());      
+  this->SetStartOutputDirectory(cwd.c_str());
 }
 
-// at the end of this CMAKE_ROOT and CMAKE_COMMAND should be added to the cache
+// at the end of this CMAKE_ROOT and CMAKE_COMMAND should be added to the
+// cache
 int cmake::AddCMakePaths(const char *arg0)
 {
   // Find our own executable.
@@ -638,7 +642,7 @@ int cmake::AddCMakePaths(const char *arg0)
       ("CMAKE_EDIT_COMMAND", editCacheCommand.c_str(),
        "Path to cache edit program executable.", cmCacheManager::INTERNAL);
     }
-  
+
   // do CMAKE_ROOT, look for the environment variable first
   std::string cMakeRoot;
   std::string modules;
@@ -652,14 +656,14 @@ int cmake::AddCMakePaths(const char *arg0)
     // next try exe/..
     cMakeRoot  = cmSystemTools::GetProgramPath(cMakeSelf.c_str());
     std::string::size_type slashPos = cMakeRoot.rfind("/");
-    if(slashPos != std::string::npos)      
+    if(slashPos != std::string::npos)
       {
       cMakeRoot = cMakeRoot.substr(0, slashPos);
       }
     // is there no Modules direcory there?
-    modules = cMakeRoot + "/Modules/CMake.cmake"; 
+    modules = cMakeRoot + "/Modules/CMake.cmake";
     }
-  
+
   if (!cmSystemTools::FileExists(modules.c_str()))
     {
     // try exe/../share/cmake
@@ -684,7 +688,7 @@ int cmake::AddCMakePaths(const char *arg0)
 #endif
   if (!cmSystemTools::FileExists(modules.c_str()))
     {
-    // try 
+    // try
     cMakeRoot  = cmSystemTools::GetProgramPath(cMakeSelf.c_str());
     cMakeRoot += CMAKE_DATA_DIR;
     modules = cMakeRoot +  "/Modules/CMake.cmake";
@@ -694,15 +698,15 @@ int cmake::AddCMakePaths(const char *arg0)
     // next try exe
     cMakeRoot  = cmSystemTools::GetProgramPath(cMakeSelf.c_str());
     // is there no Modules direcory there?
-    modules = cMakeRoot + "/Modules/CMake.cmake"; 
+    modules = cMakeRoot + "/Modules/CMake.cmake";
     }
   if (!cmSystemTools::FileExists(modules.c_str()))
     {
     // couldn't find modules
     cmSystemTools::Error("Could not find CMAKE_ROOT !!!\n"
-                         "CMake has most likely not been installed correctly.\n"
-                         "Modules directory not found in\n",
-                         cMakeRoot.c_str());
+      "CMake has most likely not been installed correctly.\n"
+      "Modules directory not found in\n",
+      cMakeRoot.c_str());
     return 0;
     }
   this->m_CacheManager->AddCacheEntry
@@ -723,20 +727,23 @@ void CMakeCommandUsage(const char* program)
   cmOStringStream errorStream;
 
 #ifdef CMAKE_BUILD_WITH_CMAKE
-  errorStream 
+  errorStream
     << "cmake version " << cmVersion::GetCMakeVersion() << "\n";
 #else
-  errorStream 
+  errorStream
     << "cmake bootstrap\n";
 #endif
 
-  errorStream 
+  errorStream
     << "Usage: " << program << " -E [command] [arguments ...]\n"
     << "Available commands: \n"
     << "  chdir dir cmd [args]... - run command in a given directory\n"
-    << "  copy file destination   - copy file to destination (either file or directory)\n"
-    << "  copy_if_different in-file out-file   - copy file if input has changed\n"
-    << "  copy_directory source destination    - copy directory 'source' content to directory 'destination'\n"
+    << "  copy file destination   - copy file to destination (either file or "
+    "directory)\n"
+    << "  copy_if_different in-file out-file   - copy file if input has "
+    "changed\n"
+    << "  copy_directory source destination    - copy directory 'source' "
+    "content to directory 'destination'\n"
     << "  compare_files file1 file2 - check if file1 is same as file2\n"
     << "  echo [string]...        - displays arguments as text\n"
     << "  remove file1 file2 ...  - remove the file(s)\n"
@@ -774,7 +781,8 @@ int cmake::CMakeCommand(std::vector<std::string>& args)
     // Copy file if different.
     if (args[1] == "copy_if_different" && args.size() == 4)
       {
-      if(!cmSystemTools::CopyFileIfDifferent(args[2].c_str(), args[3].c_str()))
+      if(!cmSystemTools::CopyFileIfDifferent(args[2].c_str(),
+          args[3].c_str()))
         {
         std::cerr << "Error copying file (if different) from \""
                   << args[2].c_str() << "\" to \"" << args[3].c_str()
@@ -856,17 +864,17 @@ int cmake::CMakeCommand(std::vector<std::string>& args)
 
       time(&time_start);
       clock_start = clock();
-      
+
       cmSystemTools::RunSingleCommand(command.c_str());
 
       clock_finish = clock();
       time(&time_finish);
 
       double clocks_per_sec = (double)CLOCKS_PER_SEC;
-      std::cout << "Elapsed time: " 
+      std::cout << "Elapsed time: "
                 << (long)(time_finish - time_start) << " s. (time)"
-                << ", " 
-                << (double)(clock_finish - clock_start) / clocks_per_sec 
+                << ", "
+                << (double)(clock_finish - clock_start) / clocks_per_sec
                 << " s. (clock)"
                 << "\n";
       return 0;
@@ -894,11 +902,11 @@ int cmake::CMakeCommand(std::vector<std::string>& args)
         }
       int retval = 0;
       int timeout = 0;
-      if ( cmSystemTools::RunSingleCommand(command.c_str(), 0, &retval, 
+      if ( cmSystemTools::RunSingleCommand(command.c_str(), 0, &retval,
                                            directory.c_str(), true, timeout) )
         {
         return retval;
-        }        
+        }
 
       return 1;
       }
@@ -1011,15 +1019,17 @@ int cmake::CMakeCommand(std::vector<std::string>& args)
         }
       else if ( flags.find_first_of('c') != flags.npos )
         {
-        if ( !cmSystemTools::CreateTar(outFile.c_str(), files, gzip, verbose) )
+        if ( !cmSystemTools::CreateTar(
+            outFile.c_str(), files, gzip, verbose) )
           {
           cmSystemTools::Error("Problem creating tar: ", outFile.c_str());
           return 1;
           }
         }
       else if ( flags.find_first_of('x') != flags.npos )
         {
-        if ( !cmSystemTools::ExtractTar(outFile.c_str(), files, gzip, verbose) )
+        if ( !cmSystemTools::ExtractTar(
+            outFile.c_str(), files, gzip, verbose) )
           {
           cmSystemTools::Error("Problem extracting tar: ", outFile.c_str());
           return 1;
@@ -1040,7 +1050,7 @@ int cmake::CMakeCommand(std::vector<std::string>& args)
     // Write registry value
     else if (args[1] == "write_regv" && args.size() > 3)
       {
-      return cmSystemTools::WriteRegistryValue(args[2].c_str(), 
+      return cmSystemTools::WriteRegistryValue(args[2].c_str(),
                                                args[3].c_str()) ? 0 : 1;
       }
 
@@ -1091,7 +1101,7 @@ cmGlobalGenerator* cmake::CreateGlobalGenerator(const char* name)
     }
 }
 
-void cmake::SetHomeDirectory(const char* dir) 
+void cmake::SetHomeDirectory(const char* dir)
 {
   m_cmHomeDirectory = dir;
   cmSystemTools::ConvertToUnixSlashes(m_cmHomeDirectory);
@@ -1127,7 +1137,7 @@ void cmake::SetGlobalGenerator(cmGlobalGenerator *gg)
 
   // set the new
   m_GlobalGenerator = gg;
-  // set the global flag for unix style paths on cmSystemTools as 
+  // set the global flag for unix style paths on cmSystemTools as
   // soon as the generator is set.  This allows gmake to be used
   // on windows.
   cmSystemTools::SetForceUnixPaths(m_GlobalGenerator->GetForceUnixPaths());
@@ -1177,15 +1187,16 @@ int cmake::DoPreConfigureChecks()
       err << "The source directory \"" << this->GetHomeDirectory()
           << "\" does not exist.\n";
       }
-    err << "Specify --help for usage, or press the help button on the CMake GUI.";
+    err << "Specify --help for usage, or press the help button on the CMake "
+      "GUI.";
     cmSystemTools::Error(err.str().c_str());
     return -2;
     }
-  
+
   // do a sanity check on some values
   if(m_CacheManager->GetCacheValue("CMAKE_HOME_DIRECTORY"))
     {
-    std::string cacheStart = 
+    std::string cacheStart =
       m_CacheManager->GetCacheValue("CMAKE_HOME_DIRECTORY");
     cacheStart += "/CMakeLists.txt";
     std::string currentStart = this->GetHomeDirectory();
@@ -1226,24 +1237,26 @@ int cmake::Configure()
     }
   if ( !res )
     {
-    m_CacheManager->AddCacheEntry("CMAKE_HOME_DIRECTORY", 
-                                  this->GetHomeDirectory(),
-                                  "Start directory with the top level CMakeLists.txt file for this project",
-                                  cmCacheManager::INTERNAL);
+    m_CacheManager->AddCacheEntry("CMAKE_HOME_DIRECTORY",
+      this->GetHomeDirectory(),
+      "Start directory with the top level CMakeLists.txt file for this "
+      "project",
+      cmCacheManager::INTERNAL);
     }
-  
+
   // set the default BACKWARDS compatibility to the current version
   if(!m_CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
     {
     char ver[256];
     sprintf(ver,"%i.%i",cmMakefile::GetMajorVersion(),
             cmMakefile::GetMinorVersion());
     this->m_CacheManager->AddCacheEntry
-      ("CMAKE_BACKWARDS_COMPATIBILITY",ver, 
-       "For backwards compatibility, what version of CMake commands and syntax should this version of CMake allow.",
+      ("CMAKE_BACKWARDS_COMPATIBILITY",ver,
+       "For backwards compatibility, what version of CMake commands and "
+       "syntax should this version of CMake allow.",
        cmCacheManager::STRING);
-    }  
-  
+    }
+
   // no generator specified on the command line
   if(!m_GlobalGenerator)
     {
@@ -1254,34 +1267,38 @@ int cmake::Configure()
       }
     if(m_GlobalGenerator)
       {
-      // set the global flag for unix style paths on cmSystemTools as 
+      // set the global flag for unix style paths on cmSystemTools as
       // soon as the generator is set.  This allows gmake to be used
       // on windows.
-      cmSystemTools::SetForceUnixPaths(m_GlobalGenerator->GetForceUnixPaths());
+      cmSystemTools::SetForceUnixPaths(
+        m_GlobalGenerator->GetForceUnixPaths());
       }
     else
       {
 #if defined(__BORLANDC__) && defined(_WIN32)
       this->SetGlobalGenerator(new cmGlobalBorlandMakefileGenerator);
 #elif defined(_WIN32) && !defined(__CYGWIN__) && !defined(CMAKE_BOOT_MINGW)
       std::string installedCompiler;
-      std::string mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\8.0\\Setup;Dbghelp_path]";
+      std::string mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft"
+        "\\VisualStudio\\8.0\\Setup;Dbghelp_path]";
       cmSystemTools::ExpandRegistryValues(mp);
       if (!(mp == "/registry"))
         {
         installedCompiler = "Visual Studio 8 2005";
         }
       else
         {
-        mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\7.1;InstallDir]";
+        mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft"
+          "\\VisualStudio\\7.1;InstallDir]";
         cmSystemTools::ExpandRegistryValues(mp);
         if (!(mp == "/registry"))
           {
           installedCompiler = "Visual Studio 7 .NET 2003";
           }
         else
           {
-          mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\VisualStudio\\7.0;InstallDir]";
+          mp = "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft"
+            "\\VisualStudio\\7.0;InstallDir]";
           cmSystemTools::ExpandRegistryValues(mp);
           if (!(mp == "/registry"))
             {
@@ -1293,7 +1310,8 @@ int cmake::Configure()
             }
           }
         }
-      cmGlobalGenerator* gen = this->CreateGlobalGenerator(installedCompiler.c_str());
+      cmGlobalGenerator* gen
+        = this->CreateGlobalGenerator(installedCompiler.c_str());
       if(!gen)
         {
         gen = new cmGlobalNMakeMakefileGenerator;
@@ -1328,7 +1346,8 @@ int cmake::Configure()
     }
   if(!m_CacheManager->GetCacheValue("CMAKE_GENERATOR"))
     {
-    m_CacheManager->AddCacheEntry("CMAKE_GENERATOR", m_GlobalGenerator->GetName(),
+    m_CacheManager->AddCacheEntry("CMAKE_GENERATOR",
+                                  m_GlobalGenerator->GetName(),
                                   "Name of generator.",
                                   cmCacheManager::INTERNAL);
     }
@@ -1340,7 +1359,7 @@ int cmake::Configure()
     {
     m_GlobalGenerator->ClearEnabledLanguages();
     }
-  
+
   this->CleanupWrittenFiles();
 
   // Truncate log files
@@ -1352,7 +1371,7 @@ int cmake::Configure()
 
   // actually do the configure
   m_GlobalGenerator->Configure();
-  
+
   // Before saving the cache
   // if the project did not define one of the entries below, add them now
   // so users can edit the values in the cache:
@@ -1361,30 +1380,31 @@ int cmake::Configure()
   if(!m_CacheManager->GetCacheValue("LIBRARY_OUTPUT_PATH"))
     {
     m_CacheManager->AddCacheEntry("LIBRARY_OUTPUT_PATH", "",
-                                  "Single output directory for building all libraries.",
-                                  cmCacheManager::PATH);
-    } 
+      "Single output directory for building all libraries.",
+      cmCacheManager::PATH);
+    }
   if(!m_CacheManager->GetCacheValue("EXECUTABLE_OUTPUT_PATH"))
     {
     m_CacheManager->AddCacheEntry("EXECUTABLE_OUTPUT_PATH", "",
-                                  "Single output directory for building all executables.",
-                                  cmCacheManager::PATH);
-    }  
+      "Single output directory for building all executables.",
+      cmCacheManager::PATH);
+    }
   if(!m_CacheManager->GetCacheValue("CMAKE_USE_RELATIVE_PATHS"))
     {
     m_CacheManager->AddCacheEntry("CMAKE_USE_RELATIVE_PATHS", false,
-                                  "If true, cmake will use relative paths in makefiles and projects.");
+      "If true, cmake will use relative paths in makefiles and projects.");
     cmCacheManager::CacheIterator it =
       m_CacheManager->GetCacheIterator("CMAKE_USE_RELATIVE_PATHS");
     if ( !it.PropertyExists("ADVANCED") )
       {
       it.SetProperty("ADVANCED", "1");
       }
-    }  
-  
+    }
+
   if(cmSystemTools::GetFatalErrorOccured() &&
      (!this->m_CacheManager->GetCacheValue("CMAKE_MAKE_PROGRAM") ||
-      cmSystemTools::IsOff(this->m_CacheManager->GetCacheValue("CMAKE_MAKE_PROGRAM"))))
+      cmSystemTools::IsOff(
+        this->m_CacheManager->GetCacheValue("CMAKE_MAKE_PROGRAM"))))
     {
     // We must have a bad generator selection.  Wipe the cache entry so the
     // user can select another.
@@ -1409,13 +1429,16 @@ int cmake::Configure()
 
 bool cmake::CacheVersionMatches()
 {
-  const char* majv = m_CacheManager->GetCacheValue("CMAKE_CACHE_MAJOR_VERSION");
-  const char* minv = m_CacheManager->GetCacheValue("CMAKE_CACHE_MINOR_VERSION");
-  const char* relv = m_CacheManager->GetCacheValue("CMAKE_CACHE_RELEASE_VERSION");
+  const char* majv
+    = m_CacheManager->GetCacheValue("CMAKE_CACHE_MAJOR_VERSION");
+  const char* minv
+    = m_CacheManager->GetCacheValue("CMAKE_CACHE_MINOR_VERSION");
+  const char* relv
+    = m_CacheManager->GetCacheValue("CMAKE_CACHE_RELEASE_VERSION");
   bool cacheSameCMake = false;
-  if(majv && 
+  if(majv &&
      atoi(majv) == static_cast<int>(cmMakefile::GetMajorVersion())
-     && minv && 
+     && minv &&
      atoi(minv) == static_cast<int>(cmMakefile::GetMinorVersion())
      && relv && (strcmp(relv, cmMakefile::GetReleaseVersion()) == 0))
     {
@@ -1456,16 +1479,16 @@ int cmake::Run(const std::vector<std::string>& args, bool noconfigure)
     CMakeCommandUsage(args[0].c_str());
     return -1;
     }
-  
+
   // set the cmake command
   m_CMakeCommand = args[0];
-  
+
   if ( !m_ScriptMode )
     {
     // load the cache
     if(this->LoadCache() < 0)
       {
-      cmSystemTools::Error("Error executing cmake::LoadCache().  Aborting.\n");
+      cmSystemTools::Error("Error executing cmake::LoadCache(). Aborting.\n");
       return -1;
       }
     }
@@ -1510,7 +1533,7 @@ int cmake::Run(const std::vector<std::string>& args, bool noconfigure)
     {
     return 0;
     }
-  
+
   // If we are doing global generate, we better set start and start
   // output directory to the root of the project.
   std::string oldstartdir = this->GetStartDirectory();
@@ -1550,26 +1573,26 @@ int cmake::Generate()
   return 0;
 }
 
-unsigned int cmake::GetMajorVersion() 
-{ 
+unsigned int cmake::GetMajorVersion()
+{
   return cmMakefile::GetMajorVersion();
 }
 
 unsigned int cmake::GetMinorVersion()
-{ 
+{
   return cmMakefile::GetMinorVersion();
 }
 
 const char *cmake::GetReleaseVersion()
-{ 
+{
   return cmMakefile::GetReleaseVersion();
 }
 
-void cmake::AddCacheEntry(const char* key, const char* value, 
-                          const char* helpString, 
+void cmake::AddCacheEntry(const char* key, const char* value,
+                          const char* helpString,
                           int type)
 {
-  m_CacheManager->AddCacheEntry(key, value, 
+  m_CacheManager->AddCacheEntry(key, value,
                                 helpString,
                                 cmCacheManager::CacheEntryType(type));
 }
@@ -1666,22 +1689,27 @@ int cmake::LoadCache()
     cacheFile += "/CMakeCache.txt";
     if(cmSystemTools::FileExists(cacheFile.c_str()))
       {
-      cmSystemTools::Error("There is a CMakeCache.txt file for the current binary tree but cmake does not have permission to read it. Please check the permissions of the directory you are trying to run CMake on.");
+      cmSystemTools::Error(
+        "There is a CMakeCache.txt file for the current binary tree but "
+        "cmake does not have permission to read it. Please check the "
+        "permissions of the directory you are trying to run CMake on.");
       return -1;
       }
     }
 
   if (m_CMakeCommand.size() < 2)
     {
-    cmSystemTools::Error("cmake command was not specified prior to loading the cache in cmake.cxx");
+    cmSystemTools::Error(
+      "cmake command was not specified prior to loading the cache in "
+      "cmake.cxx");
     return -1;
     }
-  
+
   // setup CMAKE_ROOT and CMAKE_COMMAND
   if(!this->AddCMakePaths(m_CMakeCommand.c_str()))
     {
     return -3;
-    }  
+    }
 
   // set the default BACKWARDS compatibility to the current version
   if(!m_CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
@@ -1690,11 +1718,12 @@ int cmake::LoadCache()
     sprintf(ver,"%i.%i",cmMakefile::GetMajorVersion(),
             cmMakefile::GetMinorVersion());
     this->m_CacheManager->AddCacheEntry
-      ("CMAKE_BACKWARDS_COMPATIBILITY",ver, 
-       "For backwards compatibility, what version of CMake commands and syntax should this version of CMake allow.",
+      ("CMAKE_BACKWARDS_COMPATIBILITY",ver,
+       "For backwards compatibility, what version of CMake commands and "
+       "syntax should this version of CMake allow.",
        cmCacheManager::STRING);
     }
-  
+
   return 0;
 }
 
@@ -1713,7 +1742,8 @@ void cmake::UpdateProgress(const char *msg, float prog)
     }
 }
 
-void cmake::GetCommandDocumentation(std::vector<cmDocumentationEntry>& v) const
+void cmake::GetCommandDocumentation(
+  std::vector<cmDocumentationEntry>& v) const
 {
   for(RegisteredCommandsMap::const_iterator j = m_Commands.begin();
       j != m_Commands.end(); ++j)
@@ -1763,15 +1793,16 @@ void cmake::CleanupWrittenFiles()
 void cmake::UpdateConversionPathTable()
 {
   // Update the path conversion table with any specified file:
-  const char* tablepath = 
+  const char* tablepath =
     m_CacheManager->GetCacheValue("CMAKE_PATH_TRANSLATION_FILE");
 
   if(tablepath)
     {
     std::ifstream table( tablepath );
     if(!table)
       {
-      cmSystemTools::Error("CMAKE_PATH_TRANSLATION_FILE set to ", tablepath, ". CMake can not open file.");
+      cmSystemTools::Error("CMAKE_PATH_TRANSLATION_FILE set to ", tablepath,
+        ". CMake can not open file.");
       cmSystemTools::ReportLastSystemError("CMake can not open file.");
       }
     else
@@ -1844,7 +1875,7 @@ int cmake::CheckBuildSystem()
         out != outputs.end(); ++out)
       {
       int result = 0;
-      if(!m_FileComparison->FileTimeCompare(out->c_str(), 
+      if(!m_FileComparison->FileTimeCompare(out->c_str(),
                                             dep->c_str(), &result) ||
          result < 0)
         {
@@ -1917,7 +1948,8 @@ const char* cmake::GetCTestCommand()
     return m_CTestCommand.c_str();
     }
 
-  cmMakefile* mf = this->GetGlobalGenerator()->GetLocalGenerator(0)->GetMakefile();
+  cmMakefile* mf
+    = this->GetGlobalGenerator()->GetLocalGenerator(0)->GetMakefile();
 #ifdef CMAKE_BUILD_WITH_CMAKE
   m_CTestCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
   m_CTestCommand = removeQuotes(m_CTestCommand);
@@ -1962,7 +1994,8 @@ const char* cmake::GetCPackCommand()
     return m_CPackCommand.c_str();
     }
 
-  cmMakefile* mf = this->GetGlobalGenerator()->GetLocalGenerator(0)->GetMakefile();
+  cmMakefile* mf
+    = this->GetGlobalGenerator()->GetLocalGenerator(0)->GetMakefile();
 
 #ifdef CMAKE_BUILD_WITH_CMAKE
   m_CPackCommand = mf->GetRequiredDefinition("CMAKE_COMMAND");
@@ -2031,10 +2064,12 @@ void cmake::GenerateGraphViz(const char* fileName)
     {
     if ( !mf->ReadListFile(0, infile.c_str()) )
       {
-      cmSystemTools::Error("Problem opening GraphViz options file: ", infile.c_str());
+      cmSystemTools::Error("Problem opening GraphViz options file: ",
+        infile.c_str());
       return;
       }
-    std::cout << "Read GraphViz options file: " << infile.c_str() << std::endl;
+    std::cout << "Read GraphViz options file: " << infile.c_str()
+      << std::endl;
     }
 
 #define __set_if_not_set(var, value, cmakeDefinition) \
@@ -2045,7 +2080,8 @@ void cmake::GenerateGraphViz(const char* fileName)
     }
   __set_if_not_set(graphType, "digraph", "GRAPHVIZ_GRAPH_TYPE");
   __set_if_not_set(graphName, "GG", "GRAPHVIZ_GRAPH_NAME");
-  __set_if_not_set(graphHeader, "node [\n  fontsize = \"12\"\n];", "GRAPHVIZ_GRAPH_HEADER");
+  __set_if_not_set(graphHeader, "node [\n  fontsize = \"12\"\n];",
+    "GRAPHVIZ_GRAPH_HEADER");
   __set_if_not_set(graphNodePrefix, "node", "GRAPHVIZ_NODE_PREFIX");
   const char* ignoreTargets = mf->GetDefinition("GRAPHVIZ_IGNORE_TARGETS");
   std::set<cmStdString> ignoreTargetsSet;
@@ -2054,12 +2090,14 @@ void cmake::GenerateGraphViz(const char* fileName)
     std::vector<std::string> ignoreTargetsVector;
     cmSystemTools::ExpandListArgument(ignoreTargets,ignoreTargetsVector);
     std::vector<std::string>::iterator itvIt;
-    for ( itvIt = ignoreTargetsVector.begin(); itvIt != ignoreTargetsVector.end(); ++ itvIt )
+    for ( itvIt = ignoreTargetsVector.begin();
+      itvIt != ignoreTargetsVector.end();
+      ++ itvIt )
       {
       ignoreTargetsSet.insert(itvIt->c_str());
       }
     }
- 
+
   str << graphType << " " << graphName << " {" << std::endl;
   str << graphHeader << std::endl;
 
@@ -2093,7 +2131,8 @@ void cmake::GenerateGraphViz(const char* fileName)
       sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);
       targetNamesNodes[realTargetName] = tgtName;
       targetPtrs[realTargetName] = &tit->second;
-      //str << "    \"" << tgtName << "\" [ label=\"" << tit->first.c_str() <<  "\" shape=\"box\"];" << std::endl;
+      //str << "    \"" << tgtName << "\" [ label=\"" << tit->first.c_str()
+      //<<  "\" shape=\"box\"];" << std::endl;
       }
     }
   // Ok, now find all the stuff we link to that is not in cmake
@@ -2103,7 +2142,8 @@ void cmake::GenerateGraphViz(const char* fileName)
     cmTargets::iterator tit;
     for ( tit = targets->begin(); tit != targets->end(); ++ tit )
       {
-      const cmTarget::LinkLibraries* ll = &(tit->second.GetOriginalLinkLibraries());
+      const cmTarget::LinkLibraries* ll
+        = &(tit->second.GetOriginalLinkLibraries());
       cmTarget::LinkLibraries::const_iterator llit;
       const char* realTargetName = tit->first.c_str();
       if ( ignoreTargetsSet.find(realTargetName) != ignoreTargetsSet.end() )
@@ -2118,7 +2158,8 @@ void cmake::GenerateGraphViz(const char* fileName)
       for ( llit = ll->begin(); llit != ll->end(); ++ llit )
         {
         const char* libName = llit->first.c_str();
-        std::map<cmStdString, cmStdString>::iterator tarIt = targetNamesNodes.find(libName);
+        std::map<cmStdString, cmStdString>::iterator tarIt
+          = targetNamesNodes.find(libName);
         if ( ignoreTargetsSet.find(libName) != ignoreTargetsSet.end() )
           {
           // Skip ignored targets
@@ -2129,11 +2170,13 @@ void cmake::GenerateGraphViz(const char* fileName)
           sprintf(tgtName, "%s%d", graphNodePrefix, cnt++);
           targetDeps[libName] = 2;
           targetNamesNodes[libName] = tgtName;
-          //str << "    \"" << tgtName << "\" [ label=\"" << libName <<  "\" shape=\"ellipse\"];" << std::endl;
+          //str << "    \"" << tgtName << "\" [ label=\"" << libName
+          //<<  "\" shape=\"ellipse\"];" << std::endl;
           }
         else
           {
-          std::map<cmStdString, int>::iterator depIt = targetDeps.find(libName);
+          std::map<cmStdString, int>::iterator depIt
+            = targetDeps.find(libName);
           if ( depIt == targetDeps.end() )
             {
             targetDeps[libName] = 1;
@@ -2148,22 +2191,27 @@ void cmake::GenerateGraphViz(const char* fileName)
   for ( depIt = targetDeps.begin(); depIt != targetDeps.end(); ++ depIt )
     {
     const char* newTargetName = depIt->first.c_str();
-    std::map<cmStdString, cmStdString>::iterator tarIt = targetNamesNodes.find(newTargetName);
+    std::map<cmStdString, cmStdString>::iterator tarIt
+      = targetNamesNodes.find(newTargetName);
     if ( tarIt == targetNamesNodes.end() )
       {
       // We should not be here.
-      std::cout << __LINE__ << " Cannot find library: " << newTargetName << " even though it was added in the previous pass" << std::endl;
+      std::cout << __LINE__ << " Cannot find library: " << newTargetName
+        << " even though it was added in the previous pass" << std::endl;
       abort();
       }
 
-    str << "    \"" << tarIt->second.c_str() << "\" [ label=\"" << newTargetName <<  "\" shape=\"";
+    str << "    \"" << tarIt->second.c_str() << "\" [ label=\""
+      << newTargetName <<  "\" shape=\"";
     if ( depIt->second == 1 )
       {
-      std::map<cmStdString, cmTarget*>::iterator tarTypeIt= targetPtrs.find(newTargetName);
+      std::map<cmStdString, cmTarget*>::iterator tarTypeIt= targetPtrs.find(
+        newTargetName);
       if ( tarTypeIt == targetPtrs.end() )
         {
         // We should not be here.
-        std::cout << __LINE__ << " Cannot find library: " << newTargetName << " even though it was added in the previous pass" << std::endl;
+        std::cout << __LINE__ << " Cannot find library: " << newTargetName
+          << " even though it was added in the previous pass" << std::endl;
         abort();
         }
       cmTarget* tg = tarTypeIt->second;
@@ -2199,31 +2247,38 @@ void cmake::GenerateGraphViz(const char* fileName)
     cmTargets::iterator tit;
     for ( tit = targets->begin(); tit != targets->end(); ++ tit )
       {
-      std::map<cmStdString, int>::iterator dependIt = targetDeps.find(tit->first.c_str());
+      std::map<cmStdString, int>::iterator dependIt
+        = targetDeps.find(tit->first.c_str());
       if ( dependIt == targetDeps.end() )
         {
         continue;
         }
-      std::map<cmStdString, cmStdString>::iterator cmakeTarIt = targetNamesNodes.find(tit->first.c_str());
-      const cmTarget::LinkLibraries* ll = &(tit->second.GetOriginalLinkLibraries());
+      std::map<cmStdString, cmStdString>::iterator cmakeTarIt
+        = targetNamesNodes.find(tit->first.c_str());
+      const cmTarget::LinkLibraries* ll
+        = &(tit->second.GetOriginalLinkLibraries());
       cmTarget::LinkLibraries::const_iterator llit;
       for ( llit = ll->begin(); llit != ll->end(); ++ llit )
         {
         const char* libName = llit->first.c_str();
-        std::map<cmStdString, cmStdString>::iterator tarIt = targetNamesNodes.find(libName);
+        std::map<cmStdString, cmStdString>::iterator tarIt
+          = targetNamesNodes.find(libName);
         if ( tarIt == targetNamesNodes.end() )
           {
           // We should not be here.
-          std::cout << __LINE__ << " Cannot find library: " << libName << " even though it was added in the previous pass" << std::endl;
+          std::cout << __LINE__ << " Cannot find library: " << libName
+            << " even though it was added in the previous pass" << std::endl;
           abort();
           }
-        str << "    \"" << cmakeTarIt->second.c_str() << "\" -> \"" << tarIt->second.c_str() << "\"" << std::endl;
+        str << "    \"" << cmakeTarIt->second.c_str() << "\" -> \""
+          << tarIt->second.c_str() << "\"" << std::endl;
         }
       }
     }
 
   // TODO: Use dotted or something for external libraries
-  //str << "    \"node0\":f4 -> \"node12\"[color=\"#0000ff\" style=dotted]" << std::endl;
+  //str << "    \"node0\":f4 -> \"node12\"[color=\"#0000ff\" style=dotted]"
+  //<< std::endl;
   //
   str << "}" << std::endl;
 }