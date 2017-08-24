@@ -1148,9 +1148,9 @@ void cmGlobalGenerator::Configure()
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
@@ -1742,9 +1742,9 @@ int cmGlobalGenerator::TryCompile(const std::string& srcdir,
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
@@ -1935,22 +1935,16 @@ std::string cmGlobalGenerator::GenerateCMakeBuildCommand(
 void cmGlobalGenerator::AddMakefile(cmMakefile *mf)
 {
   this->Makefiles.push_back(mf);
-}
-
-//----------------------------------------------------------------------------
-void cmGlobalGenerator::AddLocalGenerator(cmLocalGenerator *lg)
-{
-  this->LocalGenerators.push_back(lg);
 
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
@@ -1965,7 +1959,7 @@ void cmGlobalGenerator::AddLocalGenerator(cmLocalGenerator *lg)
     }
 
   int numGen = atoi(numGenC);
-  float prog = 0.9f*static_cast<float>(this->LocalGenerators.size())/
+  float prog = 0.9f*static_cast<float>(this->Makefiles.size())/
     static_cast<float>(numGen);
   if (prog > 0.9f)
     {
@@ -1974,6 +1968,12 @@ void cmGlobalGenerator::AddLocalGenerator(cmLocalGenerator *lg)
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