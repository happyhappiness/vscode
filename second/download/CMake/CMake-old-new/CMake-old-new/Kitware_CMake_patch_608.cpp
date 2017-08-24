@@ -41,6 +41,8 @@
 # include <unistd.h>
 #endif
 
+#define CTEST_INITIAL_CMAKE_OUTPUT_FILE_NAME "CTestInitialCMakeOutput.log"
+
 //----------------------------------------------------------------------
 cmCTestScriptHandler::cmCTestScriptHandler()
 {
@@ -125,7 +127,7 @@ int cmCTestScriptHandler::ReadInScript(const std::string& total_script_arg)
   // make sure the file exists
   if (!cmSystemTools::FileExists(script.c_str()))
     {
-    std::cerr << "Cannot find file: " << script.c_str() << std::endl;
+    cmSystemTools::Error("Cannot find file: ", script.c_str());
     return 1;
     }
 
@@ -198,7 +200,7 @@ int cmCTestScriptHandler::ExtractVariables()
     message += (!m_SourceDir.empty()) ? m_SourceDir.c_str() : "(Null)";
     message += "\nCTEST_BINARY_DIRECTORY = ";
     message += (!m_BinaryDir.empty()) ? m_BinaryDir.c_str() : "(Null)";
-    message += "\nCTEST_CMAKE_COMMAND = ";
+    message += "\nCTEST_COMMAND = ";
     message += (!m_CTestCmd.empty()) ? m_CTestCmd.c_str() : "(Null)";
     cmSystemTools::Error(
       "Some required settings in the configuration file were missing:\n",
@@ -394,40 +396,43 @@ int cmCTestScriptHandler::PerformExtraUpdates()
   bool res; 
 
   // do an initial cvs update as required
-  if (!m_CVSCmd.empty())
-    {
-    command = m_CVSCmd;
-    char updateVar[40];
-    int i;
-    for (i = 1; i < 10; ++i)
+  command = m_CVSCmd;
+  char updateVar[40];
+  int i;
+  for (i = 1; i < 10; ++i)
+    {
+    sprintf(updateVar,"CTEST_EXTRA_UPDATES_%i",i);
+    const char *updateVal = m_Makefile->GetDefinition(updateVar);
+    if (updateVal)
       {
-      sprintf(updateVar,"CTEST_EXTRA_UPDATES_%i",i);
-      const char *updateVal = m_Makefile->GetDefinition(updateVar);
-      if (updateVal)
+      if (m_CVSCmd.empty())
         {
-        std::vector<std::string> cvsArgs;
-        cmSystemTools::ExpandListArgument(updateVal,cvsArgs);
-        if (cvsArgs.size() == 2)
+        cmSystemTools::Error(updateVar, " specified without specifying CTEST_CVS_COMMAND.");
+        this->RestoreBackupDirectories();
+        return 12;
+        }
+      std::vector<std::string> cvsArgs;
+      cmSystemTools::ExpandListArgument(updateVal,cvsArgs);
+      if (cvsArgs.size() == 2)
+        {
+        std::string fullCommand = command;
+        fullCommand += " update ";
+        fullCommand += cvsArgs[1];
+        output = "";
+        retVal = 0;
+        if ( m_Verbose )
           {
-          std::string fullCommand = command;
-          fullCommand += " update ";
-          fullCommand += cvsArgs[1];
-          output = "";
-          retVal = 0;
-          if ( m_Verbose )
-            {
-            std::cerr << "Run CVS: " << fullCommand.c_str() << std::endl;
-            }
-          res = cmSystemTools::RunSingleCommand(fullCommand.c_str(), &output, 
-            &retVal, cvsArgs[0].c_str(),
-            m_Verbose, 0 /*m_TimeOut*/);
-          if (!res || retVal != 0)
-            {
-            cmSystemTools::Error("Unable to perform extra cvs updates:\n", 
-                                 output.c_str());
-            this->RestoreBackupDirectories();
-            return 8;
-            }
+          std::cerr << "Run CVS: " << fullCommand.c_str() << std::endl;
+          }
+        res = cmSystemTools::RunSingleCommand(fullCommand.c_str(), &output, 
+          &retVal, cvsArgs[0].c_str(),
+          m_Verbose, 0 /*m_TimeOut*/);
+        if (!res || retVal != 0)
+          {
+          cmSystemTools::Error("Unable to perform extra cvs updates:\n", 
+            output.c_str());
+          this->RestoreBackupDirectories();
+          return 8;
           }
         }
       }
@@ -556,6 +561,33 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
     res = cmSystemTools::RunSingleCommand(command.c_str(), &output, 
       &retVal, m_BinaryDir.c_str(),
       m_Verbose, 0 /*m_TimeOut*/);
+
+    const char* cmakeOutputFileName =
+      m_Makefile->GetDefinition("CTEST_CMAKE_OUTPUT_FILE_NAME");
+    if ( cmakeOutputFileName )
+      {
+      std::string cmakeOutputFile = cmakeOutputFileName;
+      if ( !cmSystemTools::FileIsFullPath(cmakeOutputFile.c_str()) )
+        {
+        cmakeOutputFile = m_BinaryDir + "/" + cmakeOutputFile;
+        }
+
+      if ( m_Verbose )
+        {
+        std::cerr << "Write CMake output to file: " << cmakeOutputFile.c_str()
+          << std::endl;
+        }
+      std::ofstream fout(cmakeOutputFile.c_str());
+      if ( fout )
+        {
+        fout << output.c_str();
+        }
+      else
+        {
+        cmSystemTools::Error("Cannot open CMake output file: ",
+          cmakeOutputFile.c_str(), " for writing");
+        }
+      }
     if (!res || retVal != 0)
       {
       // even if this fails continue to the next step