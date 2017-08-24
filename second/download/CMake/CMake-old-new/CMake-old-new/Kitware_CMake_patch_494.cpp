@@ -16,7 +16,6 @@
 =========================================================================*/
 #include "cmLocalUnixMakefileGenerator3.h"
 
-#include "cmDepends.h"
 #include "cmGeneratedFileStream.h"
 #include "cmGlobalUnixMakefileGenerator3.h"
 #include "cmMakefile.h"
@@ -1387,9 +1386,9 @@ bool cmLocalUnixMakefileGenerator3::UpdateDependencies(const char* tgtInfo,
     if(verbose)
       {
       cmOStringStream msg;
-      msg << "Dependee \"" << internalDependFile
+      msg << "Dependee \"" << dirInfoFile
           << "\" is newer than depender \""
-          << dirInfoFile << "\"." << std::endl;
+          << internalDependFile << "\"." << std::endl;
       cmSystemTools::Stdout(msg.str().c_str());
       }
     needRescanDirInfo = true;
@@ -1400,14 +1399,26 @@ bool cmLocalUnixMakefileGenerator3::UpdateDependencies(const char* tgtInfo,
   // The build.make file may have explicit dependencies for the object
   // files but these will not affect the scanning process so they need
   // not be considered.
+  std::map<std::string, cmDepends::DependencyVector> validDependencies;
   bool needRescanDependencies = false;
   if (needRescanDirInfo == false)
     {
     cmDependsC checker;
     checker.SetVerbose(verbose);
     checker.SetFileComparison(ftc);
+    // cmDependsC::Check() fills the vector validDependencies() with the
+    // dependencies for those files where they are still valid, i.e. neither
+    // the files themselves nor any files they depend on have changed.
+    // We don't do that if the CMakeDirectoryInformation.cmake file has 
+    // changed, because then potentially all dependencies have changed.
+    // This information is given later on to cmDependsC, which then only
+    // rescans the files where it did not get valid dependencies via this
+    // dependency vector. This means that in the normal case, when only 
+    // few or one file have been edited, then also only this one file is
+    // actually scanned again, instead of all files for this target.
     needRescanDependencies = !checker.Check(dependFile.c_str(),
-                                            internalDependFile.c_str());
+                                            internalDependFile.c_str(),
+                                            validDependencies);
     }
 
   if(needRescanDependInfo || needRescanDirInfo || needRescanDependencies)
@@ -1426,7 +1437,7 @@ bool cmLocalUnixMakefileGenerator3::UpdateDependencies(const char* tgtInfo,
     fprintf(stdout, "%s\n", message.c_str());
 #endif
 
-    return this->ScanDependencies(dir.c_str());
+    return this->ScanDependencies(dir.c_str(), validDependencies);
     }
   else
     {
@@ -1438,7 +1449,8 @@ bool cmLocalUnixMakefileGenerator3::UpdateDependencies(const char* tgtInfo,
 //----------------------------------------------------------------------------
 bool
 cmLocalUnixMakefileGenerator3
-::ScanDependencies(const char* targetDir)
+::ScanDependencies(const char* targetDir,
+                 std::map<std::string, cmDepends::DependencyVector>& validDeps)
 {
   // Read the directory information file.
   cmMakefile* mf = this->Makefile;
@@ -1526,7 +1538,7 @@ ::ScanDependencies(const char* targetDir)
     if(lang == "C" || lang == "CXX" || lang == "RC")
       {
       // TODO: Handle RC (resource files) dependencies correctly.
-      scanner = new cmDependsC(this, targetDir, lang.c_str());
+      scanner = new cmDependsC(this, targetDir, lang.c_str(), &validDeps);
       }
 #ifdef CMAKE_BUILD_WITH_CMAKE
     else if(lang == "Fortran")