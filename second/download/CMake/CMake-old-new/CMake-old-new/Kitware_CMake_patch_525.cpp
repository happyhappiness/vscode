@@ -1229,6 +1229,16 @@ bool cmLocalUnixMakefileGenerator3::UpdateDependencies(const char* tgtInfo,
                                                        bool verbose,
                                                        bool color)
 {
+  // read in the target info file
+  if(!this->Makefile->ReadListFile(0, tgtInfo) ||
+     cmSystemTools::GetErrorOccuredFlag())
+    {
+    cmSystemTools::Error("Target DependInfo.cmake file not found");
+    }
+
+  // Check if any multiple output pairs have a missing file.
+  this->CheckMultipleOutputs(verbose);
+
   std::string dir = cmSystemTools::GetFilenamePath(tgtInfo);
   std::string internalDependFile = dir + "/depend.internal";
   std::string dependFile = dir + "/depend.make";
@@ -1257,7 +1267,7 @@ bool cmLocalUnixMakefileGenerator3::UpdateDependencies(const char* tgtInfo,
     fprintf(stdout, "%s\n", message.c_str());
 #endif
 
-    return this->ScanDependencies(tgtInfo);
+    return this->ScanDependencies(dir.c_str());
     }
   else
     {
@@ -1267,11 +1277,10 @@ bool cmLocalUnixMakefileGenerator3::UpdateDependencies(const char* tgtInfo,
 }
 
 //----------------------------------------------------------------------------
-bool cmLocalUnixMakefileGenerator3::ScanDependencies(const char* tgtInfo)
+bool
+cmLocalUnixMakefileGenerator3
+::ScanDependencies(const char* targetDir)
 {
-  // The info file for this target
-  std::string infoFile = tgtInfo;
-
   // Read the directory information file.
   cmMakefile* mf = this->Makefile;
   bool haveDirectoryInfo = false;
@@ -1284,13 +1293,6 @@ bool cmLocalUnixMakefileGenerator3::ScanDependencies(const char* tgtInfo)
     haveDirectoryInfo = true;
     }
   
-  // read in the target info file
-  if(!mf->ReadListFile(0, infoFile.c_str()) ||
-     cmSystemTools::GetErrorOccuredFlag())
-    {
-    cmSystemTools::Error("Target DependInfo.cmake file not found");    
-    }
-
   // Lookup useful directory information.
   if(haveDirectoryInfo)
     {
@@ -1322,7 +1324,7 @@ bool cmLocalUnixMakefileGenerator3::ScanDependencies(const char* tgtInfo)
     }
 
   // create the file stream for the depends file
-  std::string dir = cmSystemTools::GetFilenamePath(infoFile);
+  std::string dir = targetDir;
   
   // Open the rule file.  This should be copy-if-different because the
   // rules may depend on this file itself.
@@ -1450,6 +1452,48 @@ bool cmLocalUnixMakefileGenerator3::ScanDependencies(const char* tgtInfo)
 }
 
 //----------------------------------------------------------------------------
+void cmLocalUnixMakefileGenerator3::CheckMultipleOutputs(bool verbose)
+{
+  cmMakefile* mf = this->Makefile;
+
+  // Get the string listing the multiple output pairs.
+  const char* pairs_string = mf->GetDefinition("CMAKE_MULTIPLE_OUTPUT_PAIRS");
+  if(!pairs_string)
+    {
+    return;
+    }
+
+  // Convert the string to a list and preserve empty entries.
+  std::vector<std::string> pairs;
+  cmSystemTools::ExpandListArgument(pairs_string, pairs, true);
+  for(std::vector<std::string>::const_iterator i = pairs.begin();
+      i != pairs.end(); ++i)
+    {
+    const std::string& depender = *i;
+    if(++i != pairs.end())
+      {
+      const std::string& dependee = *i;
+
+      // If the depender is missing then delete the dependee to make
+      // sure both will be regenerated.
+      if(cmSystemTools::FileExists(dependee.c_str()) &&
+         !cmSystemTools::FileExists(depender.c_str()))
+        {
+        if(verbose)
+          {
+          cmOStringStream msg;
+          msg << "Deleting primary custom command output \"" << dependee
+              << "\" because another output \""
+              << depender << "\" does not exist." << std::endl;
+          cmSystemTools::Stdout(msg.str().c_str());
+          }
+        cmSystemTools::RemoveFile(dependee.c_str());
+        }
+      }
+    }
+}
+
+//----------------------------------------------------------------------------
 void cmLocalUnixMakefileGenerator3
 ::WriteLocalAllRules(std::ostream& ruleFileStream)
 {