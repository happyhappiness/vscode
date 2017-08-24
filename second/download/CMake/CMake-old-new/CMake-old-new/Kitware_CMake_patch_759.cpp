@@ -57,14 +57,14 @@ bool cmTryRunCommand::InitialPass(std::vector<std::string> const& argv)
   int res = cmTryCompileCommand::CoreTryCompileCode(m_Makefile, tryCompile, false);
   
   // now try running the command if it compiled
-  std::string binaryDirectory = argv[1] + "/CMakeTmp";
+  std::string binaryDirectory = argv[2] + "/CMakeTmp";
   if (!res)
     {
     int retVal;
     std::string output;
     std::string command;
     command = binaryDirectory;
-    command += "/cmTryRunExec";
+    command += "/cmTryCompileExec";
     command += cmSystemTools::GetExecutableExtension();
     std::string fullPath;
     if(cmSystemTools::FileExists(command.c_str()))
@@ -74,14 +74,19 @@ bool cmTryRunCommand::InitialPass(std::vector<std::string> const& argv)
     else
       {
       command = binaryDirectory;
-      command += "/Debug/cmTryRunExec";
+      command += "/Debug/cmTryCompileExec";
       command += cmSystemTools::GetExecutableExtension();
       if(cmSystemTools::FileExists(command.c_str()))
         {
         fullPath = cmSystemTools::CollapseFullPath(command.c_str());
         }
+      else
+        {
+        cmSystemTools::Error("Unable to find executable for TRY_RUN",
+                             command.c_str());
+        }
       }
-    if (runArgs.size() > 1)
+    if (fullPath.size() > 1)
       {
       std::string finalCommand = fullPath;
       if(runArgs.size())
@@ -93,11 +98,7 @@ bool cmTryRunCommand::InitialPass(std::vector<std::string> const& argv)
       // set the run var
       char retChar[1000];
       sprintf(retChar,"%i",retVal);
-      m_Makefile->AddDefinition(argv[1].c_str(), retChar);
-      }
-    else
-      {
-      cmSystemTools::Error("Unable to find executable for TRY_RUN");
+      m_Makefile->AddDefinition(argv[0].c_str(), retChar);
       }
     }
   
@@ -116,6 +117,9 @@ bool cmTryRunCommand::InitialPass(std::vector<std::string> const& argv)
       cmSystemTools::RemoveFile(fullPath.c_str());
       }
     }
+  std::string cacheFile = binaryDirectory;
+  cacheFile += "/CMakeLists.txt";
+  cmListFileCache::GetInstance()->FlushCache(cacheFile.c_str());
   
   return true;
 }