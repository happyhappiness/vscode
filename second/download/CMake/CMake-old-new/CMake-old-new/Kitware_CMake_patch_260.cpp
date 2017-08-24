@@ -16,7 +16,6 @@
 #include "cmake.h"
 #include "cmFunctionBlocker.h"
 #include "cmMakefile.h"
-#include "cmLocalGenerator.h"
 #include "cmGlobalGenerator.h"
 #include "cmGeneratedFileStream.h"
 
@@ -86,7 +85,6 @@ cmCTestScriptHandler::cmCTestScriptHandler()
   this->EmptyBinDir = false;
   this->EmptyBinDirOnce = false;
   this->Makefile = 0;
-  this->LocalGenerator = 0;
   this->CMake = 0;
   this->GlobalGenerator = 0;
 
@@ -128,9 +126,6 @@ void cmCTestScriptHandler::Initialize()
   delete this->Makefile;
   this->Makefile = 0;
 
-  delete this->LocalGenerator;
-  this->LocalGenerator = 0;
-
   delete this->GlobalGenerator;
   this->GlobalGenerator = 0;
 
@@ -141,7 +136,6 @@ void cmCTestScriptHandler::Initialize()
 cmCTestScriptHandler::~cmCTestScriptHandler()
 {
   delete this->Makefile;
-  delete this->LocalGenerator;
   delete this->GlobalGenerator;
   delete this->CMake;
 }
@@ -179,15 +173,14 @@ int cmCTestScriptHandler::ProcessHandler()
 
 void cmCTestScriptHandler::UpdateElapsedTime()
 {
-  if (this->LocalGenerator)
+  if (this->Makefile)
     {
     // set the current elapsed time
     char timeString[20];
     int itime = static_cast<unsigned int>(cmSystemTools::GetTime()
                                           - this->ScriptStartTime);
     sprintf(timeString,"%i",itime);
-    this->LocalGenerator->GetMakefile()->AddDefinition("CTEST_ELAPSED_TIME",
-                                                   timeString);
+    this->Makefile->AddDefinition("CTEST_ELAPSED_TIME", timeString);
     }
 }
 
@@ -316,7 +309,6 @@ void cmCTestScriptHandler::CreateCMake()
     {
     delete this->CMake;
     delete this->GlobalGenerator;
-    delete this->LocalGenerator;
     delete this->Makefile;
     }
   this->CMake = new cmake;
@@ -327,8 +319,6 @@ void cmCTestScriptHandler::CreateCMake()
 
   cmState::Snapshot snapshot = this->CMake->GetCurrentSnapshot();
   this->Makefile = new cmMakefile(this->GlobalGenerator, snapshot);
-  this->LocalGenerator =
-      this->GlobalGenerator->CreateLocalGenerator(this->Makefile);
 
   this->CMake->SetProgressCallback(ctestScriptProgressCallback, this->CTest);
 