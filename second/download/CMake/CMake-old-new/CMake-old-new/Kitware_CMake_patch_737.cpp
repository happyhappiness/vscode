@@ -172,6 +172,7 @@ ctest::ctest()
   m_UseExcludeRegExpFirst = false;
   m_Verbose               = false;
   m_DartMode              = false;
+  m_ShowOnly              = false;
   int cc; 
   for ( cc=0; cc < ctest::LAST_TEST; cc ++ )
     {
@@ -421,10 +422,18 @@ int ctest::UpdateDirectory()
   std::string command = cvsCommand + " update " + cvsOptions;
 
   std::string output;
-  int retVal;
-  bool res = cmSystemTools::RunCommand(command.c_str(), output, 
-                                       retVal, sourceDirectory.c_str(),
-                                       m_Verbose);
+  int retVal = 0;
+  bool res = true;
+  if ( !m_ShowOnly )
+    {
+    res = cmSystemTools::RunCommand(command.c_str(), output, 
+                                    retVal, sourceDirectory.c_str(),
+                                    m_Verbose);
+    }
+  else
+    {
+    std::cout << "Update with command: " << command << std::endl;
+    }
   if (! res || retVal )
     {
     std::cerr << "Error(s) when updating the project" << std::endl;
@@ -438,7 +447,8 @@ int ctest::ConfigureDirectory()
   std::string cCommand = m_DartConfiguration["ConfigureCommand"];
   if ( cCommand.size() == 0 )
     {
-    std::cerr << "Cannot find ConfigureCommand key in the DartConfiguration.tcl" << std::endl;
+    std::cerr << "Cannot find ConfigureCommand key in the DartConfiguration.tcl" 
+              << std::endl;
     return 1;
     }
 
@@ -450,10 +460,18 @@ int ctest::ConfigureDirectory()
     }
 
   std::string output;
-  int retVal;
-  bool res = cmSystemTools::RunCommand(cCommand.c_str(), output, 
-                                       retVal, buildDirectory.c_str(),
-                                       m_Verbose);
+  int retVal = 0;
+  bool res = true;
+  if ( !m_ShowOnly )
+    {
+    res = cmSystemTools::RunCommand(cCommand.c_str(), output, 
+                                    retVal, buildDirectory.c_str(),
+                                    m_Verbose);
+    }
+  else
+    {
+    std::cout << "Configure with command: " << cCommand << std::endl;
+    }
   if (! res || retVal )
     {
     std::cerr << "Error(s) when updating the project" << std::endl;
@@ -479,10 +497,18 @@ int ctest::BuildDirectory()
 
   m_StartBuild = ::CurrentTime();
   std::string output;
-  int retVal;
-  bool res = cmSystemTools::RunCommand(makeCommand.c_str(), output, 
-                                       retVal, buildDirectory.c_str(), 
-                                       m_Verbose);
+  int retVal = 0;
+  bool res = true;
+  if ( !m_ShowOnly )
+    {
+    res = cmSystemTools::RunCommand(makeCommand.c_str(), output, 
+                                    retVal, buildDirectory.c_str(), 
+                                    m_Verbose);
+    }
+  else
+    {
+    std::cout << "Build with command: " << makeCommand << std::endl;
+    }
   m_EndBuild = ::CurrentTime();
   if (! res || retVal )
     {
@@ -743,11 +769,15 @@ int ctest::CoverageDirectory()
     {
     std::string command = "gcov -l \"" + files[cc] + "\"";
     std::string output;
-    int retVal;
+    int retVal = 0;
     //std::cout << "Run gcov on " << files[cc] << std::flush;
-    bool res = cmSystemTools::RunCommand(command.c_str(), output, 
-                                         retVal, opath.c_str(),
-                                         m_Verbose);
+    bool res = true;
+    if ( !m_ShowOnly )
+      {
+      res = cmSystemTools::RunCommand(command.c_str(), output, 
+                                      retVal, opath.c_str(),
+                                      m_Verbose);
+      }
     if ( res && retVal == 0 )
       {
       //std::cout << " - done" << std::endl;
@@ -1163,8 +1193,15 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
           firstTest = 0;
           }
         cres.m_Name = args[0].Value;
-        fprintf(stderr,"Testing %-30s ",args[0].Value.c_str());
-        fflush(stderr);
+        if ( m_ShowOnly )
+          {
+          std::cout << args[0].Value << std::endl;
+          }
+        else
+          {
+          fprintf(stderr,"Testing %-30s ",args[0].Value.c_str());
+          fflush(stderr);
+          }
         //std::cerr << "Testing " << args[0] << " ... ";
         // find the test executable
         std::string testCommand = this->FindExecutable(args[1].Value.c_str());
@@ -1191,7 +1228,7 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
          * Run an executable command and put the stdout in output.
          */
         std::string output;
-        int retVal;
+        int retVal = 0;
 
         double clock_start, clock_finish;
         clock_start = cmSystemTools::GetTime();
@@ -1200,46 +1237,53 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
           {
           std::cout << std::endl << "Test command: " << testCommand << std::endl;
           }
-        bool res = cmSystemTools::RunCommand(testCommand.c_str(), output, 
-                                             retVal, 0, false);
+        bool res = true;
+        if ( !m_ShowOnly )
+          {
+          res = cmSystemTools::RunCommand(testCommand.c_str(), output, 
+                                          retVal, 0, false);
+          }
         clock_finish = cmSystemTools::GetTime();
 
         cres.m_ExecutionTime = (double)(clock_finish - clock_start);
         cres.m_FullCommandLine = testCommand;
 
-        if (!res || retVal != 0)
+        if ( !m_ShowOnly )
           {
-          fprintf(stderr,"***Failed\n");
-          if (output != "")
+          if (!res || retVal != 0)
             {
-            if (dartStuff.find(output.c_str()))
+            fprintf(stderr,"***Failed\n");
+            if (output != "")
               {
-              cmSystemTools::ReplaceString(output,
-                                           dartStuff.match(1).c_str(),"");
-              }
-            if (output != "" && m_Verbose)
-              {
-              std::cerr << output.c_str() << "\n";
+              if (dartStuff.find(output.c_str()))
+                {
+                cmSystemTools::ReplaceString(output,
+                                             dartStuff.match(1).c_str(),"");
+                }
+              if (output != "" && m_Verbose)
+                {
+                std::cerr << output.c_str() << "\n";
+                }
               }
+            failed.push_back(args[0].Value); 
             }
-          failed.push_back(args[0].Value); 
-          }
-        else
-          {
-          fprintf(stderr,"   Passed\n");
-          if (output != "")
+          else
             {
-            if (dartStuff.find(output.c_str()))
-              {
-              cmSystemTools::ReplaceString(output,
-                                           dartStuff.match(1).c_str(),"");
-              }
-            if (output != "" && m_Verbose)
+            fprintf(stderr,"   Passed\n");
+            if (output != "")
               {
-              std::cerr << output.c_str() << "\n";
+              if (dartStuff.find(output.c_str()))
+                {
+                cmSystemTools::ReplaceString(output,
+                                             dartStuff.match(1).c_str(),"");
+                }
+              if (output != "" && m_Verbose)
+                {
+                std::cerr << output.c_str() << "\n";
+                }
               }
+            passed.push_back(args[0].Value); 
             }
-          passed.push_back(args[0].Value); 
           }
         cres.m_Output = output;
         cres.m_ReturnValue = retVal;
@@ -1270,7 +1314,10 @@ int ctest::TestDirectory()
 
   if (total == 0)
     {
-    std::cerr << "No tests were found!!!\n";
+    if ( !m_ShowOnly )
+      {
+      std::cerr << "No tests were found!!!\n";
+      }
     }
   else
     {
@@ -1453,7 +1500,13 @@ int main (int argc, char *argv[])
       inst.m_Verbose = true;
       }
 
-    if( ( arg.find("-T",0) == 0 || arg.find("--dart-mode",0) == 0 ) && (i < args.size() -1) )
+    if( arg.find("-N",0) == 0 || arg.find("--show-only",0) == 0 )
+      {
+      inst.m_ShowOnly = true;
+      }
+
+    if( ( arg.find("-T",0) == 0 || arg.find("--dart-mode",0) == 0 ) && 
+        (i < args.size() -1) )
       {
       inst.m_DartMode = true;
       inst.SetTest(args[i+1].c_str());
@@ -1487,6 +1540,8 @@ int main (int argc, char *argv[])
                 << "\t -R test      Specify regular expression for tests to include" 
                 << std::endl
                 << "\t -V           Verbose testing" << std::endl
+                << "\t -N           Only show what would be done without this option" 
+                << std::endl
                 << "\t -H           Help page" << std::endl;
       return 1;
       }