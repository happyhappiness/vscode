@@ -1650,151 +1650,147 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
     }
 
   int firstTest = 1;
-  long line = 0;
 
-#define SPACE_REGEX "[ \t\r\n]"
-  
   cmsys::RegularExpression ireg(this->m_IncludeRegExp.c_str());
   cmsys::RegularExpression ereg(this->m_ExcludeRegExp.c_str());
   cmsys::RegularExpression dartStuff("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");
 
-  bool parseError;
-  while ( fin )
+  cmListFileCache cache;
+  cmListFile* listFile = cache.GetFileCache("DartTestfile.txt", false);
+  for(std::vector<cmListFileFunction>::const_iterator f =
+        listFile->m_Functions.begin(); f != listFile->m_Functions.end(); ++f)
     {
-    cmListFileFunction lff;
-    if(cmListFileCache::ParseFunction(fin, lff, "DartTestfile.txt",
-                                      parseError, line))
+    const cmListFileFunction& lff = *f;
+    const std::string& name = lff.m_Name;
+    const std::vector<cmListFileArgument>& args = lff.m_Arguments;
+    if (name == "SUBDIRS")
       {
-      const std::string& name = lff.m_Name;
-      const std::vector<cmListFileArgument>& args = lff.m_Arguments;
-      if (name == "SUBDIRS")
+      std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
+      for(std::vector<cmListFileArgument>::const_iterator j = args.begin();
+          j != args.end(); ++j)
         {
-        std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
-        for(std::vector<cmListFileArgument>::const_iterator j = args.begin();
-            j != args.end(); ++j)
-          {   
-          std::string nwd = cwd + "/";
-          nwd += j->Value;
-          if (cmSystemTools::FileIsDirectory(nwd.c_str()))
-            {
-            cmSystemTools::ChangeDirectory(nwd.c_str());
-            this->ProcessDirectory(passed, failed);
-            }
+        std::string nwd = cwd + "/";
+        nwd += j->Value;
+        if (cmSystemTools::FileIsDirectory(nwd.c_str()))
+          {
+          cmSystemTools::ChangeDirectory(nwd.c_str());
+          this->ProcessDirectory(passed, failed);
           }
-        // return to the original directory
-        cmSystemTools::ChangeDirectory(cwd.c_str());
         }
-      
-      if (name == "ADD_TEST")
+      // return to the original directory
+      cmSystemTools::ChangeDirectory(cwd.c_str());
+      }
+
+    if (name == "ADD_TEST")
+      {
+      if (this->m_UseExcludeRegExp &&
+          this->m_UseExcludeRegExpFirst &&
+          ereg.find(args[0].Value.c_str()))
         {
-        if (this->m_UseExcludeRegExp && 
-            this->m_UseExcludeRegExpFirst && 
-            ereg.find(args[0].Value.c_str()))
-          {
-          continue;
-          }
-        if (this->m_UseIncludeRegExp && !ireg.find(args[0].Value.c_str()))
-          {
-          continue;
-          }
-        if (this->m_UseExcludeRegExp && 
-            !this->m_UseExcludeRegExpFirst && 
-            ereg.find(args[0].Value.c_str()))
-          {
-          continue;
-          }
+        continue;
+        }
+      if (this->m_UseIncludeRegExp && !ireg.find(args[0].Value.c_str()))
+        {
+        continue;
+        }
+      if (this->m_UseExcludeRegExp &&
+          !this->m_UseExcludeRegExpFirst &&
+          ereg.find(args[0].Value.c_str()))
+        {
+        continue;
+        }
 
-        cmCTestTestResult cres;
-        cres.m_Status = cmCTest::NOT_RUN;
+      cmCTestTestResult cres;
+      cres.m_Status = cmCTest::NOT_RUN;
 
-        if (firstTest)
-          {
-          std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
-          std::cerr << "Changing directory into " << nwd.c_str() << "\n";
-          firstTest = 0;
-          }
-        cres.m_Name = args[0].Value;
-        if ( m_ShowOnly )
-          {
-          std::cout << args[0].Value << std::endl;
-          }
-        else
-          {
-          fprintf(stderr,"Testing %-30s ",args[0].Value.c_str());
-          fflush(stderr);
-          }
-        //std::cerr << "Testing " << args[0] << " ... ";
-        // find the test executable
-        std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());
-        std::string testCommand = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
+      if (firstTest)
+        {
+        std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
+        std::cerr << "Changing directory into " << nwd.c_str() << "\n";
+        firstTest = 0;
+        }
+      cres.m_Name = args[0].Value;
+      if ( m_ShowOnly )
+        {
+        std::cout << args[0].Value << std::endl;
+        }
+      else
+        {
+        fprintf(stderr,"Testing %-30s ",args[0].Value.c_str());
+        fflush(stderr);
+        }
+      //std::cerr << "Testing " << args[0] << " ... ";
+      // find the test executable
+      std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());
+      std::string testCommand = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
 
-        // continue if we did not find the executable
-        if (testCommand == "")
-          {
-          std::cerr << "Unable to find executable: " << 
-            args[1].Value.c_str() << "\n";
-          m_TestResults.push_back( cres );
-          continue;
-          }
-        
-        // add the arguments
-        std::vector<cmListFileArgument>::const_iterator j = args.begin();
-        ++j;
-        ++j;
-        std::vector<const char*> arguments;
-        arguments.push_back(actualCommand.c_str());
-        for(;j != args.end(); ++j)
-          {   
-          testCommand += " ";
-          testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());
-          arguments.push_back(j->Value.c_str());
-          }
-        arguments.push_back(0);
+      // continue if we did not find the executable
+      if (testCommand == "")
+        {
+        std::cerr << "Unable to find executable: " <<
+          args[1].Value.c_str() << "\n";
+        m_TestResults.push_back( cres );
+        continue;
+        }
 
-        /**
-         * Run an executable command and put the stdout in output.
-         */
-        std::string output;
-        int retVal = 0;
+      // add the arguments
+      std::vector<cmListFileArgument>::const_iterator j = args.begin();
+      ++j;
+      ++j;
+      std::vector<const char*> arguments;
+      arguments.push_back(actualCommand.c_str());
+      for(;j != args.end(); ++j)
+        {
+        testCommand += " ";
+        testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());
+        arguments.push_back(j->Value.c_str());
+        }
+      arguments.push_back(0);
 
-        double clock_start, clock_finish;
-        clock_start = cmSystemTools::GetTime();
+      /**
+       * Run an executable command and put the stdout in output.
+       */
+      std::string output;
+      int retVal = 0;
 
-        if ( m_Verbose )
-          {
-          std::cout << std::endl << "Test command: " << testCommand << std::endl;
-          }
-        int res = 0;
-        if ( !m_ShowOnly )
-          {
-          res = this->RunTest(arguments, &output, &retVal);
-          }
-        clock_finish = cmSystemTools::GetTime();
+      double clock_start, clock_finish;
+      clock_start = cmSystemTools::GetTime();
 
-        cres.m_ExecutionTime = (double)(clock_finish - clock_start);
-        cres.m_FullCommandLine = testCommand;
+      if ( m_Verbose )
+        {
+        std::cout << std::endl << "Test command: " << testCommand << std::endl;
+        }
+      int res = 0;
+      if ( !m_ShowOnly )
+        {
+        res = this->RunTest(arguments, &output, &retVal);
+        }
+      clock_finish = cmSystemTools::GetTime();
+
+      cres.m_ExecutionTime = (double)(clock_finish - clock_start);
+      cres.m_FullCommandLine = testCommand;
 
-        if ( !m_ShowOnly )
+      if ( !m_ShowOnly )
+        {
+        if (res == cmsysProcess_State_Exited && retVal == 0)
           {
-          if (res == cmsysProcess_State_Exited && retVal == 0)
+          fprintf(stderr,"   Passed\n");
+          passed.push_back(args[0].Value);
+          cres.m_Status = cmCTest::COMPLETED;
+          }
+        else
+          {
+          cres.m_Status = cmCTest::FAILED;
+          if ( res == cmsysProcess_State_Expired )
             {
-            fprintf(stderr,"   Passed\n");
-            passed.push_back(args[0].Value); 
-            cres.m_Status = cmCTest::COMPLETED;
+            fprintf(stderr,"***Timeout\n");
+            cres.m_Status = cmCTest::TIMEOUT;
             }
-          else
+          else if ( res == cmsysProcess_State_Exception )
             {
-            cres.m_Status = cmCTest::FAILED;
-            if ( res == cmsysProcess_State_Expired )
+            fprintf(stderr,"***Exception: ");
+            switch ( retVal )
               {
-              fprintf(stderr,"***Timeout\n");
-              cres.m_Status = cmCTest::TIMEOUT;
-              }
-            else if ( res == cmsysProcess_State_Exception )
-              {
-              fprintf(stderr,"***Exception: ");
-              switch ( retVal )
-                {
               case cmsysProcess_Exception_Fault:
                 fprintf(stderr,"SegFault");
                 cres.m_Status = cmCTest::SEGFAULT;
@@ -1814,42 +1810,41 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
               default:
                 fprintf(stderr,"Other");
                 cres.m_Status = cmCTest::OTHER_FAULT;
-                }
-              fprintf(stderr,"\n");
-              }
-            else if ( res == cmsysProcess_State_Error )
-              {
-              fprintf(stderr,"***Bad command\n");
-              cres.m_Status = cmCTest::BAD_COMMAND;
-              }
-            else
-              {
-              fprintf(stderr,"***Failed\n");
               }
-            failed.push_back(args[0].Value); 
+            fprintf(stderr,"\n");
             }
-          if (output != "")
+          else if ( res == cmsysProcess_State_Error )
             {
-            if (dartStuff.find(output.c_str()))
-              {
-              std::string dartString = dartStuff.match(1);
-              cmSystemTools::ReplaceString(output, dartString.c_str(),"");
-              cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
-              }
+            fprintf(stderr,"***Bad command\n");
+            cres.m_Status = cmCTest::BAD_COMMAND;
+            }
+          else
+            {
+            fprintf(stderr,"***Failed\n");
             }
+          failed.push_back(args[0].Value);
           }
-        cres.m_Output = output;
-        cres.m_ReturnValue = retVal;
-        std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
-        if ( nwd.size() > m_ToplevelPath.size() )
+        if (output != "")
           {
-          nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);
+          if (dartStuff.find(output.c_str()))
+            {
+            std::string dartString = dartStuff.match(1);
+            cmSystemTools::ReplaceString(output, dartString.c_str(),"");
+            cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
+            }
           }
-        cmSystemTools::ReplaceString(nwd, "\\", "/");
-        cres.m_Path = nwd;
-        cres.m_CompletionStatus = "Completed";
-        m_TestResults.push_back( cres );
         }
+      cres.m_Output = output;
+      cres.m_ReturnValue = retVal;
+      std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
+      if ( nwd.size() > m_ToplevelPath.size() )
+        {
+        nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);
+        }
+      cmSystemTools::ReplaceString(nwd, "\\", "/");
+      cres.m_Path = nwd;
+      cres.m_CompletionStatus = "Completed";
+      m_TestResults.push_back( cres );
       }
     }
 }
@@ -2193,6 +2188,8 @@ std::string cmCTest::GetTestModelString()
   return "Experimental";
 }
 
+#define SPACE_REGEX "[ \t\r\n]"
+
 std::string cmCTest::GenerateRegressionImages(const std::string& xml)
 {
   cmsys::RegularExpression twoattributes(