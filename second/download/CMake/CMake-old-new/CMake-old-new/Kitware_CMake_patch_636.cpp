@@ -1685,6 +1685,7 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
           }
 
         cmCTestTestResult cres;
+        cres.m_Status = cmCTest::NOT_RUN;
 
         if (firstTest)
           {
@@ -1737,11 +1738,10 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
           {
           std::cout << std::endl << "Test command: " << testCommand << std::endl;
           }
-        bool res = true;
+        int res = 0;
         if ( !m_ShowOnly )
           {
-          res = cmSystemTools::RunSingleCommand(testCommand.c_str(), &output, 
-            &retVal, 0, false, m_TimeOut);
+          res = this->RunTest(testCommand.c_str(), &output, &retVal);
           }
         clock_finish = cmSystemTools::GetTime();
 
@@ -1750,41 +1750,63 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
 
         if ( !m_ShowOnly )
           {
-          if (!res || retVal != 0)
+          if (res == cmsysProcess_State_Exited && retVal )
             {
-            fprintf(stderr,"***Failed\n");
-            if (output != "")
+            fprintf(stderr,"   Passed\n");
+            passed.push_back(args[0].Value); 
+            }
+          else
+            {
+            if ( res == cmsysProcess_State_Expired )
               {
-              if (dartStuff.find(output.c_str()))
-                {
-                std::string dartString = dartStuff.match(1);
-                cmSystemTools::ReplaceString(output, dartString.c_str(),"");
-                cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
-                }
-              if (output != "" && m_Verbose)
+              fprintf(stderr,"***Timeout\n");
+              cres.m_Status = cmCTest::TIMEOUT;
+              }
+            else if ( res == cmsysProcess_State_Exception )
+              {
+              fprintf(stderr,"***Exception: ");
+              switch ( retVal )
                 {
-                std::cerr << output.c_str() << "\n";
+              case cmsysProcess_Exception_Fault:
+                fprintf(stderr,"SegFault");
+                cres.m_Status = cmCTest::SEGFAULT;
+                break;
+              case cmsysProcess_Exception_Illegal:
+                fprintf(stderr,"SegFault");
+                cres.m_Status = cmCTest::ILLEGAL;
+                break;
+              case cmsysProcess_Exception_Interrupt:
+                fprintf(stderr,"SegFault");
+                cres.m_Status = cmCTest::INTERRUPT;
+                break;
+              case cmsysProcess_Exception_Numerical:
+                fprintf(stderr,"SegFault");
+                cres.m_Status = cmCTest::NUMERICAL;
+                break;
+              default:
+                fprintf(stderr,"Other");
+                cres.m_Status = cmCTest::OTHER_FAULT;
                 }
               }
+            else if ( res == cmsysProcess_State_Error )
+              {
+              fprintf(stderr,"***Bad command\n");
+              cres.m_Status = cmCTest::BAD_COMMAND;
+              }
+            else
+              {
+              fprintf(stderr,"***Failed\n");
+              }
             failed.push_back(args[0].Value); 
             }
-          else
+          if (output != "")
             {
-            fprintf(stderr,"   Passed\n");
-            if (output != "")
+            if (dartStuff.find(output.c_str()))
               {
-              if (dartStuff.find(output.c_str()))
-                {
-                std::string dartString = dartStuff.match(1);
-                cmSystemTools::ReplaceString(output, dartString.c_str(),"");
-                cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
-                }
-              if (output != "" && m_Verbose)
-                {
-                std::cerr << output.c_str() << "\n";
-                }
+              std::string dartString = dartStuff.match(1);
+              cmSystemTools::ReplaceString(output, dartString.c_str(),"");
+              cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
               }
-            passed.push_back(args[0].Value); 
             }
           }
         cres.m_Output = output;
@@ -2018,7 +2040,7 @@ void cmCTest::GenerateDartTestOutput(std::ostream& os)
   for ( cc = 0; cc < m_TestResults.size(); cc ++ )
     {
     cmCTestTestResult *result = &m_TestResults[cc];
-    os << "\t<Test Status=\"" << (result->m_ReturnValue?"failed":"passed") 
+    os << "\t<Test Status=\"" << (result->m_Status==cmCTest::COMPLETED?"passed":"failed")
        << "\">\n"
        << "\t\t<Name>" << this->MakeXMLSafe(result->m_Name) << "</Name>\n"
        << "\t\t<Path>" << this->MakeXMLSafe(result->m_Path) << "</Path>\n"
@@ -2028,14 +2050,14 @@ void cmCTest::GenerateDartTestOutput(std::ostream& os)
        << this->MakeXMLSafe(result->m_FullCommandLine) 
        << "</FullCommandLine>\n"
        << "\t\t<Results>" << std::endl;
-    if ( result->m_ReturnValue )
+    if ( result->m_Status != cmCTest::COMPLETED || result->m_ReturnValue )
       {
       os << "\t\t\t<NamedMeasurement type=\"text/string\" name=\"Exit Code\"><Value>"
-         << "CHILDSTATUS" << "</Value></NamedMeasurement>\n"
+         << this->GetTestStatus(result->m_Status) << "</Value></NamedMeasurement>\n"
          << "\t\t\t<NamedMeasurement type=\"text/string\" name=\"Exit Value\"><Value>"
          << result->m_ReturnValue << "</Value></NamedMeasurement>" << std::endl;
-      os << result->m_RegressionImages;
       }
+    os << result->m_RegressionImages;
     os << "\t\t\t<NamedMeasurement type=\"numeric/double\" "
        << "name=\"Execution Time\"><Value>"
        << result->m_ExecutionTime << "</Value></NamedMeasurement>\n"
@@ -2354,3 +2376,89 @@ bool cmCTest::RunMakeCommand(const char* command, std::string* output,
   return result;
 }
 
+int cmCTest::RunTest( const char* command, std::string* output, int *retVal)
+{
+  std::vector<cmStdString> args = cmSystemTools::ParseArguments(command);
+
+  if(args.size() < 1)
+    {
+    return false;
+    }
+  
+  std::vector<const char*> argv;
+  for(std::vector<cmStdString>::const_iterator a = args.begin();
+      a != args.end(); ++a)
+    {
+    argv.push_back(a->c_str());
+    }
+  argv.push_back(0);
+
+  if ( output )
+    {
+    *output = "";
+    }
+
+  cmsysProcess* cp = cmsysProcess_New();
+  cmsysProcess_SetCommand(cp, &*argv.begin());
+  if(cmSystemTools::GetRunCommandHideConsole())
+    {
+    cmsysProcess_SetOption(cp, cmsysProcess_Option_HideWindow, 1);
+    }
+  cmsysProcess_SetTimeout(cp, m_TimeOut);
+  cmsysProcess_Execute(cp);
+  
+  char* data;
+  int length;
+  while(cmsysProcess_WaitForData(cp, (cmsysProcess_Pipe_STDOUT |
+                                      cmsysProcess_Pipe_STDERR),
+                                 &data, &length, 0))
+    {
+    if ( output )
+      {
+      output->append(data, length);
+      }
+    }
+  
+  cmsysProcess_WaitForExit(cp, 0);
+
+  int result = cmsysProcess_GetState(cp);
+
+  if(result == cmsysProcess_State_Exited)
+    {
+    *retVal = cmsysProcess_GetExitValue(cp);
+    }
+  else if(result == cmsysProcess_State_Exception)
+    {
+    *retVal = cmsysProcess_GetExitException(cp);
+    }
+  else if(result == cmsysProcess_State_Error)
+    {
+    *output += "\n*** ERROR executing: ";
+    *output += cmsysProcess_GetErrorString(cp);
+    }
+  
+  cmsysProcess_Delete(cp);
+  
+  return result;
+}
+
+const char* cmCTest::GetTestStatus(int status)
+{
+  static const char statuses[][100] = {
+    "Not Run",
+    "Timeout",
+    "SEGFAULT",
+    "ILLEGAL",
+    "INTERRUPT",
+    "NUMERICAL",
+    "OTHER_FAULT",
+    "BAD_COMMAND",
+    "Completed"
+  };
+
+  if ( status < cmCTest::NOT_RUN || status > cmCTest::COMPLETED )
+    {
+    return "No Status";
+    }
+  return statuses[status];
+}