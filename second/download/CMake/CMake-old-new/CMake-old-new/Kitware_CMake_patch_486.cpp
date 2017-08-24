@@ -67,6 +67,7 @@
 #    include "cmGlobalVisualStudio8Win64Generator.h"
 #    include "cmGlobalBorlandMakefileGenerator.h"
 #    include "cmGlobalNMakeMakefileGenerator.h"
+#    include "cmGlobalJOMMakefileGenerator.h"
 #    include "cmGlobalWatcomWMakeGenerator.h"
 #    define CMAKE_HAVE_VS_GENERATORS
 #  endif
@@ -81,7 +82,7 @@
 #include "cmCallVisualStudioMacro.h"
 #endif
 
-#if !defined(__CYGWIN__) && !defined(CMAKE_BOOT_MINGW)
+#if !defined(CMAKE_BOOT_MINGW)
 # include "cmExtraCodeBlocksGenerator.h"
 #endif
 
@@ -1378,61 +1379,12 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
     // Internal CMake shared library support.
     else if (args[1] == "cmake_symlink_library" && args.size() == 5)
       {
-      int result = 0;
-      std::string realName = args[2];
-      std::string soName = args[3];
-      std::string name = args[4];
-      if(soName != realName)
-        {
-        std::string fname = cmSystemTools::GetFilenameName(realName);
-        if(cmSystemTools::FileExists(soName.c_str()) ||
-           cmSystemTools::FileIsSymlink(soName.c_str()))
-          {
-          cmSystemTools::RemoveFile(soName.c_str());
-          }
-        if(!cmSystemTools::CreateSymlink(fname.c_str(), soName.c_str()))
-          {
-          cmSystemTools::ReportLastSystemError("cmake_symlink_library");
-          result = 1;
-          }
-        }
-      if(name != soName)
-        {
-        std::string fname = cmSystemTools::GetFilenameName(soName);
-        if(cmSystemTools::FileExists(name.c_str()) ||
-           cmSystemTools::FileIsSymlink(name.c_str()))
-          {
-          cmSystemTools::RemoveFile(name.c_str());
-          }
-        if(!cmSystemTools::CreateSymlink(fname.c_str(), name.c_str()))
-          {
-          cmSystemTools::ReportLastSystemError("cmake_symlink_library");
-          result = 1;
-          }
-        }
-      return result;
+      return cmake::SymlinkLibrary(args);
       }
     // Internal CMake versioned executable support.
     else if (args[1] == "cmake_symlink_executable" && args.size() == 4)
       {
-      int result = 0;
-      std::string realName = args[2];
-      std::string name = args[3];
-      if(name != realName)
-        {
-        std::string fname = cmSystemTools::GetFilenameName(realName);
-        if(cmSystemTools::FileExists(name.c_str()) ||
-           cmSystemTools::FileIsSymlink(name.c_str()))
-          {
-          cmSystemTools::RemoveFile(name.c_str());
-          }
-        if(!cmSystemTools::CreateSymlink(fname.c_str(), name.c_str()))
-          {
-          cmSystemTools::ReportLastSystemError("cmake_symlink_executable");
-          result = 1;
-          }
-        }
-      return result;
+      return cmake::SymlinkExecutable(args);
       }
 
 #if defined(CMAKE_HAVE_VS_GENERATORS)
@@ -1465,8 +1417,10 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
     else if (args[1] == "cmake_depends" && args.size() >= 6)
       {
       // Use the make system's VERBOSE environment variable to enable
-      // verbose output.
-      bool verbose = cmSystemTools::GetEnv("VERBOSE") != 0;
+      // verbose output. This can be skipped by also setting CMAKE_NO_VERBOSE
+      // (which is set by the Eclipse and KDevelop generators).
+      bool verbose = ((cmSystemTools::GetEnv("VERBOSE") != 0) 
+                       && (cmSystemTools::GetEnv("CMAKE_NO_VERBOSE") == 0));
 
       // Create a cmake object instance to process dependencies.
       cmake cm;
@@ -1693,10 +1647,8 @@ void cmake::AddDefaultExtraGenerators()
   // e.g. kdevelop4 ?
 #endif
 
-#if !defined(__CYGWIN__)
   this->AddExtraGenerator(cmExtraCodeBlocksGenerator::GetActualName(),
                           &cmExtraCodeBlocksGenerator::New);
-#endif
 
 #ifdef CMAKE_USE_ECLIPSE
   this->AddExtraGenerator(cmExtraEclipseCDT4Generator::GetActualName(),
@@ -2364,34 +2316,6 @@ const char* cmake::GetCacheDefinition(const char* name) const
   return this->CacheManager->GetCacheValue(name);
 }
 
-int cmake::DumpDocumentationToFile(std::ostream& f)
-{
-#ifdef CMAKE_BUILD_WITH_CMAKE
-  // Loop over all registered commands and print out documentation
-  const char *name;
-  const char *terse;
-  const char *full;
-  char tmp[1024];
-  sprintf(tmp,"Version %s", cmVersion::GetCMakeVersion());
-  f << "<html>\n";
-  f << "<h1>Documentation for commands of CMake " << tmp << "</h1>\n";
-  f << "<ul>\n";
-  for(RegisteredCommandsMap::iterator j = this->Commands.begin();
-      j != this->Commands.end(); ++j)
-    {
-    name = (*j).second->GetName();
-    terse = (*j).second->GetTerseDocumentation();
-    full = (*j).second->GetFullDocumentation();
-    f << "<li><b>" << name << "</b> - " << terse << std::endl
-      << "<br><i>Usage:</i> " << full << "</li>" << std::endl << std::endl;
-    }
-  f << "</ul></html>\n";
-#else
-  (void)f;
-#endif
-  return 1;
-}
-
 void cmake::AddDefaultCommands()
 {
   std::list<cmCommand*> commands;
@@ -2430,6 +2354,8 @@ void cmake::AddDefaultGenerators()
     &cmGlobalBorlandMakefileGenerator::New;
   this->Generators[cmGlobalNMakeMakefileGenerator::GetActualName()] =
     &cmGlobalNMakeMakefileGenerator::New;
+  this->Generators[cmGlobalJOMMakefileGenerator::GetActualName()] =
+    &cmGlobalJOMMakefileGenerator::New;
   this->Generators[cmGlobalWatcomWMakeGenerator::GetActualName()] =
     &cmGlobalWatcomWMakeGenerator::New;
 # endif
@@ -2588,9 +2514,11 @@ int cmake::CheckBuildSystem()
 {
   // We do not need to rerun CMake.  Check dependency integrity.  Use
   // the make system's VERBOSE environment variable to enable verbose
-  // output.
-  bool verbose = cmSystemTools::GetEnv("VERBOSE") != 0;
-  
+  // output. This can be skipped by setting CMAKE_NO_VERBOSE (which is set
+  // by the Eclipse and KDevelop generators).
+  bool verbose = ((cmSystemTools::GetEnv("VERBOSE") != 0) 
+                   && (cmSystemTools::GetEnv("CMAKE_NO_VERBOSE") == 0));
+
   // This method will check the integrity of the build system if the
   // option was given on the command line.  It reads the given file to
   // determine whether CMake should rerun.
@@ -3131,6 +3059,65 @@ void cmake::GenerateGraphViz(const char* fileName) const
 }
 
 //----------------------------------------------------------------------------
+int cmake::SymlinkLibrary(std::vector<std::string>& args)
+{
+  int result = 0;
+  std::string realName = args[2];
+  std::string soName = args[3];
+  std::string name = args[4];
+  if(soName != realName)
+    {
+    if(!cmake::SymlinkInternal(realName, soName))
+      {
+      cmSystemTools::ReportLastSystemError("cmake_symlink_library");
+      result = 1;
+      }
+    }
+  if(name != soName)
+    {
+    if(!cmake::SymlinkInternal(soName, name))
+      {
+      cmSystemTools::ReportLastSystemError("cmake_symlink_library");
+      result = 1;
+      }
+    }
+  return result;
+}
+
+//----------------------------------------------------------------------------
+int cmake::SymlinkExecutable(std::vector<std::string>& args)
+{
+  int result = 0;
+  std::string realName = args[2];
+  std::string name = args[3];
+  if(name != realName)
+    {
+    if(!cmake::SymlinkInternal(realName, name))
+      {
+      cmSystemTools::ReportLastSystemError("cmake_symlink_executable");
+      result = 1;
+      }
+    }
+  return result;
+}
+
+//----------------------------------------------------------------------------
+bool cmake::SymlinkInternal(std::string const& file, std::string const& link)
+{
+  if(cmSystemTools::FileExists(link.c_str()) ||
+     cmSystemTools::FileIsSymlink(link.c_str()))
+    {
+    cmSystemTools::RemoveFile(link.c_str());
+    }
+#if defined(_WIN32) && !defined(__CYGWIN__)
+  return cmSystemTools::CopyFileAlways(file.c_str(), link.c_str());
+#else
+  std::string linktext = cmSystemTools::GetFilenameName(file);
+  return cmSystemTools::CreateSymlink(linktext.c_str(), link.c_str());
+#endif
+}
+
+//----------------------------------------------------------------------------
 #ifdef CMAKE_BUILD_WITH_CMAKE
 int cmake::ExecuteEchoColor(std::vector<std::string>& args)
 {
@@ -4402,7 +4389,7 @@ int cmake::Build(const std::string& dir,
                  const std::string& config,
                  const std::vector<std::string>& nativeOptions,
                  bool clean)
-{ 
+{
   if(!cmSystemTools::FileIsDirectory(dir.c_str()))
     {
     std::cerr << "Error: " << dir << " is not a directory\n";
@@ -4422,8 +4409,8 @@ int cmake::Build(const std::string& dir,
     std::cerr << "Error: could find generator in Cache\n";
     return 1;
     }
-  cmGlobalGenerator* gen =
-    this->CreateGlobalGenerator(it.GetValue());
+  std::auto_ptr<cmGlobalGenerator> gen(
+    this->CreateGlobalGenerator(it.GetValue()));
   std::string output;
   std::string projName;
   std::string makeProgram;