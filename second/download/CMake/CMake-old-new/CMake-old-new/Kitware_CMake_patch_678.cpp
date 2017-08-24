@@ -21,6 +21,7 @@
 #include "cmGlobalGenerator.h"
 #include <cmsys/Directory.hxx>
 #include "cmListFileCache.h"
+#include "cmGlob.h"
 
 #include "cmCTestSubmit.h"
 #include "curl/curl.h"
@@ -324,10 +325,14 @@ cmCTest::cmCTest()
     }
 }
 
-void cmCTest::Initialize()
+int cmCTest::Initialize()
 {
   m_ToplevelPath = cmSystemTools::GetCurrentWorkingDirectory();
   cmSystemTools::ConvertToUnixSlashes(m_ToplevelPath);
+  if ( !this->ReadCustomConfigurationFileTree(m_ToplevelPath.c_str()) )
+    {
+    return 0;
+    }
   this->UpdateCTestConfiguration();
   if ( m_DartMode )
     {
@@ -338,7 +343,7 @@ void cmCTest::Initialize()
         {
         std::cerr << "File " << testingDir << " is in the place of the testing directory"
                   << std::endl;
-        return;
+        return 0;
         }
       }
     else
@@ -347,7 +352,7 @@ void cmCTest::Initialize()
         {
         std::cerr << "Cannot create directory " << testingDir
                   << std::endl;
-        return;
+        return 0;
         }
       }
     std::string tagfile = testingDir + "/TAG";
@@ -408,6 +413,7 @@ void cmCTest::Initialize()
       }
     m_CurrentTag = tag;
     }
+  return 1;
 }
 
 void cmCTest::UpdateCTestConfiguration()
@@ -1042,7 +1048,7 @@ int cmCTest::BuildDirectory()
     ofs.close();
     }
 
-  int cc;
+  tm_VectorOfStrings::size_type cc;
   if ( m_DartConfiguration["SourceDirectory"].size() > 20 ||
     m_DartConfiguration["BuildDirectory"].size() > 20 )
     {
@@ -1090,7 +1096,24 @@ int cmCTest::BuildDirectory()
   // Errors
   for ( cc = 0; cmCTestErrorMatches[cc]; cc ++ )
     {
-    cmsys::RegularExpression re(cmCTestErrorMatches[cc]);
+    m_CustomErrorMatches.push_back(cmCTestErrorMatches[cc]);
+    }
+  for ( cc = 0; cmCTestErrorExceptions[cc]; cc ++ )
+    {
+    m_CustomErrorExceptions.push_back(cmCTestErrorExceptions[cc]);
+    }
+  for ( cc = 0; cmCTestWarningMatches[cc]; cc ++ )
+    {
+    m_CustomWarningMatches.push_back(cmCTestWarningMatches[cc]);
+    }
+  for ( cc = 0; cmCTestWarningExceptions[cc]; cc ++ )
+    {
+    m_CustomWarningExceptions.push_back(cmCTestWarningExceptions[cc]);
+    }
+
+  for ( cc = 0; cc < m_CustomErrorMatches.size(); cc ++ )
+    {
+    cmsys::RegularExpression re(m_CustomErrorMatches[cc].c_str());
     cmCTest::tm_VectorOfStrings::size_type kk;
     for ( kk = 0; kk < lines.size(); kk ++ )
       {
@@ -1101,9 +1124,9 @@ int cmCTest::BuildDirectory()
       }    
     }
   // Warnings
-  for ( cc = 0; cmCTestWarningMatches[cc]; cc ++ )
+  for ( cc = 0; cc < m_CustomWarningMatches.size(); cc ++ )
     {
-    cmsys::RegularExpression re(cmCTestWarningMatches[cc]);
+    cmsys::RegularExpression re(m_CustomWarningMatches[cc].c_str());
     cmCTest::tm_VectorOfStrings::size_type kk;
     for ( kk = 0; kk < lines.size(); kk ++ )
       {
@@ -1114,9 +1137,9 @@ int cmCTest::BuildDirectory()
       }    
     }
   // Errors exceptions
-  for ( cc = 0; cmCTestErrorExceptions[cc]; cc ++ )
+  for ( cc = 0; cc < m_CustomErrorExceptions.size(); cc ++ )
     {
-    cmsys::RegularExpression re(cmCTestErrorExceptions[cc]);
+    cmsys::RegularExpression re(m_CustomErrorExceptions[cc].c_str());
     std::vector<int>::size_type kk;
     for ( kk =0; kk < markedLines.size(); kk ++ )
       {
@@ -1130,9 +1153,9 @@ int cmCTest::BuildDirectory()
       }
     }
   // Warning exceptions
-  for ( cc = 0; cmCTestWarningExceptions[cc]; cc ++ )
+  for ( cc = 0; cc < m_CustomWarningExceptions.size(); cc ++ )
     {
-    cmsys::RegularExpression re(cmCTestWarningExceptions[cc]);
+    cmsys::RegularExpression re(m_CustomWarningExceptions[cc].c_str());
     std::vector<int>::size_type kk;
     for ( kk =0; kk < markedLines.size(); kk ++ )
       {
@@ -1818,13 +1841,59 @@ void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed,
         {
         continue;
         }
+      if ( memcheck )
+        {
+        tm_VectorOfStrings::iterator it;
+        bool found = false;
+        for ( it = m_CustomMemCheckIgnore.begin(); 
+          it != m_CustomMemCheckIgnore.end(); ++ it )
+          {
+          if ( *it == args[0].Value )
+            {
+            found = true;
+            break;
+            }
+          }
+        if ( found )
+          {
+          if ( m_Verbose )
+            {
+            std::cout << "Ignore memcheck: " << *it << std::endl;
+            }
+          continue;
+          }
+        }
+      else
+        {
+        tm_VectorOfStrings::iterator it;
+        bool found = false;
+        for ( it = m_CustomTestsIgnore.begin(); 
+          it != m_CustomTestsIgnore.end(); ++ it )
+          {
+          if ( *it == args[0].Value )
+            {
+            found = true;
+            break;
+            }
+          }
+        if ( found )
+          {
+          if ( m_Verbose )
+            {
+            std::cout << "Ignore test: " << *it << std::endl;
+            }
+          continue;
+          }
+        }
+
+
       if (this->m_UseIncludeRegExp && !ireg.find(args[0].Value.c_str()))
         {
         continue;
         }
       if (this->m_UseExcludeRegExp &&
-          !this->m_UseExcludeRegExpFirst &&
-          ereg.find(args[0].Value.c_str()))
+        !this->m_UseExcludeRegExpFirst &&
+        ereg.find(args[0].Value.c_str()))
         {
         continue;
         }
@@ -1941,25 +2010,25 @@ void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed,
             fprintf(stderr,"***Exception: ");
             switch ( retVal )
               {
-              case cmsysProcess_Exception_Fault:
-                fprintf(stderr,"SegFault");
-                cres.m_Status = cmCTest::SEGFAULT;
-                break;
-              case cmsysProcess_Exception_Illegal:
-                fprintf(stderr,"Illegal");
-                cres.m_Status = cmCTest::ILLEGAL;
-                break;
-              case cmsysProcess_Exception_Interrupt:
-                fprintf(stderr,"Interrupt");
-                cres.m_Status = cmCTest::INTERRUPT;
-                break;
-              case cmsysProcess_Exception_Numerical:
-                fprintf(stderr,"Numerical");
-                cres.m_Status = cmCTest::NUMERICAL;
-                break;
-              default:
-                fprintf(stderr,"Other");
-                cres.m_Status = cmCTest::OTHER_FAULT;
+            case cmsysProcess_Exception_Fault:
+              fprintf(stderr,"SegFault");
+              cres.m_Status = cmCTest::SEGFAULT;
+              break;
+            case cmsysProcess_Exception_Illegal:
+              fprintf(stderr,"Illegal");
+              cres.m_Status = cmCTest::ILLEGAL;
+              break;
+            case cmsysProcess_Exception_Interrupt:
+              fprintf(stderr,"Interrupt");
+              cres.m_Status = cmCTest::INTERRUPT;
+              break;
+            case cmsysProcess_Exception_Numerical:
+              fprintf(stderr,"Numerical");
+              cres.m_Status = cmCTest::NUMERICAL;
+              break;
+            default:
+              fprintf(stderr,"Other");
+              cres.m_Status = cmCTest::OTHER_FAULT;
               }
             fprintf(stderr,"\n");
             }
@@ -2101,6 +2170,23 @@ int cmCTest::TestDirectory(bool memcheck)
       }
     }
 
+  if ( memcheck )
+    {
+    if ( !this->ExecuteCommands(m_CustomPreMemCheck) )
+      {
+      std::cerr << "Problem executing pre-memcheck command(s)." << std::endl;
+      return 1;
+      }
+    }
+  else
+    {
+    if ( !this->ExecuteCommands(m_CustomPreTest) )
+      {
+      std::cerr << "Problem executing pre-test command(s)." << std::endl;
+      return 1;
+      }
+    }
+
   cmCTest::tm_VectorOfStrings passed;
   cmCTest::tm_VectorOfStrings failed;
   int total;
@@ -2125,7 +2211,7 @@ int cmCTest::TestDirectory(bool memcheck)
       {
       std::cerr << "\nThe following tests passed:\n";
       for(cmCTest::tm_VectorOfStrings::iterator j = passed.begin();
-          j != passed.end(); ++j)
+        j != passed.end(); ++j)
         {   
         std::cerr << "\t" << *j << "\n";
         }
@@ -2137,13 +2223,13 @@ int cmCTest::TestDirectory(bool memcheck)
       percent = 99;
       }
     fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
-            percent, int(failed.size()), total);
+      percent, int(failed.size()), total);
 
     if (failed.size()) 
       {
       std::cerr << "\nThe following tests FAILED:\n";
       for(cmCTest::tm_VectorOfStrings::iterator j = failed.begin();
-          j != failed.end(); ++j)
+        j != failed.end(); ++j)
         {   
         std::cerr << "\t" << *j << "\n";
         }
@@ -2170,6 +2256,23 @@ int cmCTest::TestDirectory(bool memcheck)
       }
     }
 
+  if ( memcheck )
+    {
+    if ( !this->ExecuteCommands(m_CustomPostMemCheck) )
+      {
+      std::cerr << "Problem executing post-memcheck command(s)." << std::endl;
+      return 1;
+      }
+    }
+  else
+    {
+    if ( !this->ExecuteCommands(m_CustomPostTest) )
+      {
+      std::cerr << "Problem executing post-test command(s)." << std::endl;
+      return 1;
+      }
+    }
+
   return int(failed.size());
 }
 
@@ -2233,7 +2336,7 @@ int cmCTest::SubmitResults()
   cmCTestSubmit submit;
   submit.SetVerbose(m_Verbose);
   if ( m_DartConfiguration["DropMethod"] == "" ||
-       m_DartConfiguration["DropMethod"] ==  "ftp" )
+    m_DartConfiguration["DropMethod"] ==  "ftp" )
     {
     std::cout << "  Using FTP submit method" << std::endl;
     std::string url = "ftp://";
@@ -2286,7 +2389,7 @@ int cmCTest::SubmitResults()
     {
     std::cerr << "SCP submit not yet implemented" << std::endl;
     }
-                          
+
   return 0;
 }
 
@@ -2323,14 +2426,14 @@ void cmCTest::GenerateDartMemCheckOutput(std::ostream& os)
     os << "<MemCheck>" << std::endl;
     }
   os << "\t<StartDateTime>" << m_StartTest << "</StartDateTime>\n"
-     << "\t<TestList>\n";
+    << "\t<TestList>\n";
   tm_TestResultsVector::size_type cc;
   for ( cc = 0; cc < m_TestResults.size(); cc ++ )
     {
     cmCTestTestResult *result = &m_TestResults[cc];
     os << "\t\t<Test>" << this->MakeXMLSafe(result->m_Path) 
-       << "/" << this->MakeXMLSafe(result->m_Name)
-       << "</Test>" << std::endl;
+      << "/" << this->MakeXMLSafe(result->m_Name)
+      << "</Test>" << std::endl;
     }
   os << "\t</TestList>\n";
   for ( cc = 0; cc < m_TestResults.size(); cc ++ )
@@ -2375,7 +2478,7 @@ void cmCTest::GenerateDartMemCheckOutput(std::ostream& os)
       << "\t</Log>\n"
       << "\t</Test>" << std::endl;
     }
-  
+
   os << "\t<EndDateTime>" << m_EndTest << "</EndDateTime>" << std::endl;
   if ( m_CompatibilityMode )
     {
@@ -2405,15 +2508,15 @@ void cmCTest::GenerateDartTestOutput(std::ostream& os)
 
   this->StartXML(os);
   os << "<Testing>\n"
-     << "\t<StartDateTime>" << m_StartTest << "</StartDateTime>\n"
-     << "\t<TestList>\n";
+    << "\t<StartDateTime>" << m_StartTest << "</StartDateTime>\n"
+    << "\t<TestList>\n";
   tm_TestResultsVector::size_type cc;
   for ( cc = 0; cc < m_TestResults.size(); cc ++ )
     {
     cmCTestTestResult *result = &m_TestResults[cc];
     os << "\t\t<Test>" << this->MakeXMLSafe(result->m_Path) 
-       << "/" << this->MakeXMLSafe(result->m_Name)
-       << "</Test>" << std::endl;
+      << "/" << this->MakeXMLSafe(result->m_Name)
+      << "</Test>" << std::endl;
     }
   os << "\t</TestList>\n";
   for ( cc = 0; cc < m_TestResults.size(); cc ++ )
@@ -2467,9 +2570,9 @@ void cmCTest::GenerateDartTestOutput(std::ostream& os)
       << "\t\t</Results>\n"
       << "\t</Test>" << std::endl;
     }
-  
+
   os << "\t<EndDateTime>" << m_EndTest << "</EndDateTime>\n"
-     << "</Testing>" << std::endl;
+    << "</Testing>" << std::endl;
   this->EndXML(os);
 }
 
@@ -2556,10 +2659,10 @@ std::string cmCTest::GetTestModelString()
 {
   switch ( m_TestModel )
     {
-    case cmCTest::NIGHTLY:
-      return "Nightly";
-    case cmCTest::CONTINUOUS:
-      return "Continuous";
+  case cmCTest::NIGHTLY:
+    return "Nightly";
+  case cmCTest::CONTINUOUS:
+    return "Continuous";
     }
   return "Experimental";
 }
@@ -2661,7 +2764,7 @@ std::string cmCTest::GenerateRegressionImages(const std::string& xml)
 #ifdef _WIN32
           | std::ios::binary
 #endif
-          );
+        );
         unsigned char *file_buffer = new unsigned char [ len + 1 ];
         ifs.read(reinterpret_cast<char*>(file_buffer), len);
         unsigned char *encoded_buffer = new unsigned char [ static_cast<int>(len * 1.5 + 1) ];
@@ -2715,18 +2818,18 @@ std::string cmCTest::GenerateRegressionImages(const std::string& xml)
 }
 
 int cmCTest::RunMakeCommand(const char* command, std::string* output,
-    int* retVal, const char* dir, bool verbose, int timeout, std::ofstream& ofs)
+  int* retVal, const char* dir, bool verbose, int timeout, std::ofstream& ofs)
 {
   std::vector<cmStdString> args = cmSystemTools::ParseArguments(command);
 
   if(args.size() < 1)
     {
     return false;
     }
-  
+
   std::vector<const char*> argv;
   for(std::vector<cmStdString>::const_iterator a = args.begin();
-      a != args.end(); ++a)
+    a != args.end(); ++a)
     {
     argv.push_back(a->c_str());
     }
@@ -2743,7 +2846,7 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
   cmsysProcess_SetOption(cp, cmsysProcess_Option_HideWindow, 1);
   cmsysProcess_SetTimeout(cp, timeout);
   cmsysProcess_Execute(cp);
-  
+
   std::string::size_type tick = 0;
   std::string::size_type tick_len = 1024;
   std::string::size_type tick_line_len = 50;
@@ -2766,7 +2869,7 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
           data[cc] = '\n';
           }
         }
-      
+
       output->append(data, length);
       if ( !verbose )
         {
@@ -2796,9 +2899,9 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
     }
   std::cout << " Size of output: ";
   std::cout << int(output->size() / 1024.0) << "K" << std::endl;
-  
+
   cmsysProcess_WaitForExit(cp, 0);
-  
+
   int result = cmsysProcess_GetState(cp);
 
   if(result == cmsysProcess_State_Exited)
@@ -2819,9 +2922,9 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
     *output += "\n*** ERROR executing: ";
     *output += cmsysProcess_GetErrorString(cp);
     }
-  
+
   cmsysProcess_Delete(cp);
-  
+
   return result;
 }
 
@@ -2854,14 +2957,14 @@ int cmCTest::RunTest(std::vector<const char*> argv, std::string* output, int *re
 
   cmsysProcess* cp = cmsysProcess_New();
   cmsysProcess_SetCommand(cp, &*argv.begin());
-//  std::cout << "Command is: " << argv[0] << std::endl;
+  //  std::cout << "Command is: " << argv[0] << std::endl;
   if(cmSystemTools::GetRunCommandHideConsole())
     {
     cmsysProcess_SetOption(cp, cmsysProcess_Option_HideWindow, 1);
     }
   cmsysProcess_SetTimeout(cp, m_TimeOut);
   cmsysProcess_Execute(cp);
-  
+
   char* data;
   int length;
   while(cmsysProcess_WaitForData(cp, &data, &length, 0))
@@ -2876,7 +2979,7 @@ int cmCTest::RunTest(std::vector<const char*> argv, std::string* output, int *re
       std::cout.flush();
       }
     }
-  
+
   cmsysProcess_WaitForExit(cp, 0);
   if(output)
     {
@@ -2905,7 +3008,7 @@ int cmCTest::RunTest(std::vector<const char*> argv, std::string* output, int *re
       }
     }
   cmsysProcess_Delete(cp);
-  
+
   return result;
 }
 
@@ -2932,57 +3035,57 @@ const char* cmCTest::GetTestStatus(int status)
 }
 
 void cmCTest::RestoreBackupDirectories(bool backup, 
-                                       const char *srcDir, 
-                                       const char *binDir,
-                                       const char *backupSrcDir,
-                                       const char *backupBinDir)
+  const char *srcDir, 
+  const char *binDir,
+  const char *backupSrcDir,
+  const char *backupBinDir)
 {
   // if we backed up the dirs and the build failed, then restore
   // the backed up dirs
   if (backup)
     {
-      // if for some reason those directories exist then first delete them
-      if (cmSystemTools::FileExists(srcDir))
-        {
-        cmSystemTools::RemoveADirectory(srcDir);
-        }
-      if (cmSystemTools::FileExists(binDir))
-        {
-        cmSystemTools::RemoveADirectory(binDir);
-        }
-      // rename the src and binary directories 
-      rename(backupSrcDir, srcDir);
-      rename(backupBinDir, binDir);
+    // if for some reason those directories exist then first delete them
+    if (cmSystemTools::FileExists(srcDir))
+      {
+      cmSystemTools::RemoveADirectory(srcDir);
+      }
+    if (cmSystemTools::FileExists(binDir))
+      {
+      cmSystemTools::RemoveADirectory(binDir);
+      }
+    // rename the src and binary directories 
+    rename(backupSrcDir, srcDir);
+    rename(backupBinDir, binDir);
     }
 }
 
 int cmCTest::RunConfigurationScript()
 {
   m_ConfigurationScript = 
     cmSystemTools::CollapseFullPath(m_ConfigurationScript.c_str());
-    
+
   // make sure the file exists
   if (!cmSystemTools::FileExists(m_ConfigurationScript.c_str()))
     {
     return 1;
     }
-  
+
   // create a cmake instance to read the configuration script
   cmake cm;
   cmGlobalGenerator gg;
   gg.SetCMakeInstance(&cm);
-  
+
   // read in the list file to fill the cache
   cmLocalGenerator *lg = gg.CreateLocalGenerator();
   lg->SetGlobalGenerator(&gg);
 
   // set a variable with the path to the current script
   lg->GetMakefile()->AddDefinition("CTEST_SCRIPT_DIRECTORY",
-                                   cmSystemTools::GetFilenamePath(
-                                     m_ConfigurationScript).c_str());
+    cmSystemTools::GetFilenamePath(
+      m_ConfigurationScript).c_str());
   lg->GetMakefile()->AddDefinition("CTEST_SCRIPT_NAME",
-                                   cmSystemTools::GetFilenameName(
-                                     m_ConfigurationScript).c_str());
+    cmSystemTools::GetFilenameName(
+      m_ConfigurationScript).c_str());
   if (!lg->GetMakefile()->ReadListFile(0, m_ConfigurationScript.c_str()))
     {
     return 2;
@@ -2999,7 +3102,7 @@ int cmCTest::RunConfigurationScript()
   const char *ctestEnv = mf->GetDefinition("CTEST_ENVIRONMENT");
   const char *ctestRoot = mf->GetDefinition("CTEST_DASHBOARD_ROOT");
   bool backup = mf->IsOn("CTEST_BACKUP_AND_RESTORE");
-  
+
   // in order to back we also must have the cvs root
   const char *cvsCmd = mf->GetDefinition("CTEST_CVS_COMMAND");
   const char *cvsCheckOut = mf->GetDefinition("CTEST_CVS_CHECKOUT");
@@ -3008,14 +3111,14 @@ int cmCTest::RunConfigurationScript()
     cmSystemTools::Error("Backup was requested without a cvs checkout");    
     return 3;
     }
-  
+
   // make sure the required info is here
   if (!srcDir || !binDir || !ctestCmd)
     {
     cmSystemTools::Error("Some required settings in the configuration file were missing");    
     return 4;
     }
-  
+
   // set any environment variables
   if (ctestEnv)
     {
@@ -3052,7 +3155,7 @@ int cmCTest::RunConfigurationScript()
       {
       cmSystemTools::RemoveADirectory(backupBinDir.c_str());
       }
-    
+
     // first rename the src and binary directories 
     rename(srcDir, backupSrcDir.c_str());
     rename(binDir, backupBinDir.c_str());
@@ -3062,22 +3165,22 @@ int cmCTest::RunConfigurationScript()
       {
       cmSystemTools::Error("Unable to create the src directory");    
       this->RestoreBackupDirectories(backup, srcDir, binDir,
-                                     backupSrcDir.c_str(), 
-                                     backupBinDir.c_str());
+        backupSrcDir.c_str(), 
+        backupBinDir.c_str());
       return 5;
       }
-    
+
     // then do the checkout
     output = "";
     res = cmSystemTools::RunSingleCommand(cvsCheckOut, &output, 
-                                          &retVal, ctestRoot,
-                                          m_Verbose, 0 /*m_TimeOut*/);
+      &retVal, ctestRoot,
+      m_Verbose, 0 /*m_TimeOut*/);
     if (!res || retVal != 0)
       {
       cmSystemTools::Error("Unable to perform cvs checkout ");    
       this->RestoreBackupDirectories(backup, srcDir, binDir,
-                                     backupSrcDir.c_str(), 
-                                     backupBinDir.c_str());
+        backupSrcDir.c_str(), 
+        backupBinDir.c_str());
       return 6;
       }
     }
@@ -3093,21 +3196,21 @@ int cmCTest::RunConfigurationScript()
       cmSystemTools::RemoveADirectory(binDir);
       }
     }
-  
+
   // make sure the binary directory exists
   if (!cmSystemTools::FileExists(binDir))
     {
     if (!cmSystemTools::MakeDirectory(binDir))
       {
       cmSystemTools::Error("Unable to create the binary directory");    
       this->RestoreBackupDirectories(backup, srcDir, binDir,
-                                     backupSrcDir.c_str(), 
-                                     backupBinDir.c_str());
+        backupSrcDir.c_str(), 
+        backupBinDir.c_str());
       return 7;
       }
     }
-  
-  
+
+
   // do an initial cvs update as required
   if (cvsCmd)
     {
@@ -3130,21 +3233,21 @@ int cmCTest::RunConfigurationScript()
           output = "";
           retVal = 0;
           res = cmSystemTools::RunSingleCommand(fullCommand.c_str(), &output, 
-                                                &retVal, cvsArgs[0].c_str(),
-                                                m_Verbose, 0 /*m_TimeOut*/);
+            &retVal, cvsArgs[0].c_str(),
+            m_Verbose, 0 /*m_TimeOut*/);
           if (!res || retVal != 0)
             {
             cmSystemTools::Error("Unable to perform extra cvs updates");    
             this->RestoreBackupDirectories(backup, srcDir, binDir,
-                                           backupSrcDir.c_str(), 
-                                           backupBinDir.c_str());
+              backupSrcDir.c_str(), 
+              backupBinDir.c_str());
             return 8;
             }
           }
         }
       }
     }
-  
+
   // put the initial cache into the bin dir
   if (mf->GetDefinition("CTEST_INITIAL_CACHE"))
     {
@@ -3155,20 +3258,20 @@ int cmCTest::RunConfigurationScript()
     if(!fout)
       {
       this->RestoreBackupDirectories(backup, srcDir, binDir,
-                                     backupSrcDir.c_str(), 
-                                     backupBinDir.c_str());
+        backupSrcDir.c_str(), 
+        backupBinDir.c_str());
       return 9;
       }
-    
+
     fout.write(initCache, strlen(initCache));
-  
+
     // Make sure the operating system has finished writing the file
     // before closing it.  This will ensure the file is finished before
     // the check below.
     fout.flush();
     fout.close();
     }
-  
+
   // do an initial cmake to setup the DartConfig file
   const char *cmakeCmd = mf->GetDefinition("CTEST_CMAKE_COMMAND");
   int cmakeFailed = 0;
@@ -3181,30 +3284,30 @@ int cmCTest::RunConfigurationScript()
     command += "\"";
     retVal = 0;
     res = cmSystemTools::RunSingleCommand(command.c_str(), &output, 
-                                          &retVal, binDir,
-                                          m_Verbose, 0 /*m_TimeOut*/);
+      &retVal, binDir,
+      m_Verbose, 0 /*m_TimeOut*/);
     if (!res || retVal != 0)
       {
       // even if this fails continue to the next step
       cmakeFailed = 1;
       }
     }
-  
+
   // run ctest
   command = ctestCmd;
   output = "";
   retVal = 0;
   res = cmSystemTools::RunSingleCommand(command.c_str(), &output, 
-                                        &retVal, binDir,
-                                        m_Verbose, 0 /*m_TimeOut*/);
+    &retVal, binDir,
+    m_Verbose, 0 /*m_TimeOut*/);
 
   // did something critical fail in ctest
   if (!res || cmakeFailed ||
-      retVal & CTEST_BUILD_ERRORS)
+    retVal & CTEST_BUILD_ERRORS)
     {
     this->RestoreBackupDirectories(backup, srcDir, binDir,
-                                   backupSrcDir.c_str(), 
-                                   backupBinDir.c_str());
+      backupSrcDir.c_str(), 
+      backupBinDir.c_str());
     if (cmakeFailed)
       {
       cmSystemTools::Error("Unable to run cmake");    
@@ -3224,7 +3327,7 @@ int cmCTest::RunConfigurationScript()
     cmSystemTools::RemoveADirectory(backupSrcDir.c_str());
     cmSystemTools::RemoveADirectory(backupBinDir.c_str());
     }
-  
+
   return 0;  
 }
 
@@ -3293,7 +3396,7 @@ bool cmCTest::ProcessMemCheckPurifyOutput(const std::string&, std::string& log,
       }
     ostr << cmCTest::MakeXMLSafe(line) << std::endl;
     }
-  
+
   log = ostr.str();
   return true;
 }
@@ -3340,7 +3443,7 @@ bool cmCTest::ProcessMemCheckValgrindOutput(const std::string& str, std::string&
     if ( valgrindLine.find(lines[cc]) )
       {
       int failure = cmCTest::NO_MEMORY_FAULT;
-           if ( vgFIM.find(lines[cc]) ) { failure = cmCTest::FIM; }
+      if ( vgFIM.find(lines[cc]) ) { failure = cmCTest::FIM; }
       else if ( vgFMM.find(lines[cc]) ) { failure = cmCTest::FMM; }
       else if ( vgMLK.find(lines[cc]) ) { failure = cmCTest::MLK; }
       else if ( vgPAR.find(lines[cc]) ) { failure = cmCTest::PAR; }
@@ -3503,7 +3606,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       i++;
       this->m_ConfigurationScript = args[i];
       }
-    
+
     if( arg.find("-D",0) == 0 && i < args.size() - 1 )
       {
       this->m_DartMode = true;
@@ -3685,15 +3788,15 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       }
 
     if( ( arg.find("-T",0) == 0 ) && 
-        (i < args.size() -1) )
+      (i < args.size() -1) )
       {
       this->m_DartMode = true;
       i++;
       this->SetTest(args[i].c_str());
       }
-    
+
     if( ( arg.find("-M",0) == 0 || arg.find("--test-model",0) == 0 ) &&
-        (i < args.size() -1) )
+      (i < args.size() -1) )
       {
       i++;
       std::string const& str = args[i];
@@ -3702,7 +3805,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         this->SetTestModel(cmCTest::NIGHTLY);
         }
       else if ( str == "CONTINUOUS" || str == "continuous" || 
-                str == "Continuous" )
+        str == "Continuous" )
         {
         this->SetTestModel(cmCTest::CONTINUOUS);
         std::cout << "Continuous" << std::endl;
@@ -3712,7 +3815,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         this->SetTestModel(cmCTest::EXPERIMENTAL);
         }
       }
-    
+
     if(arg.find("-R",0) == 0 && i < args.size() - 1)
       {
       this->m_UseIncludeRegExp = true;
@@ -3735,7 +3838,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       i++;
       this->SetNotesFiles(args[i].c_str());
       }
-    
+
     // --build-and-test options
     if(arg.find("--build-and-test",0) == 0 && i < args.size() - 1)
       {
@@ -3806,7 +3909,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         {
         m_BuildOptions.push_back(args[i]);
         if(i+1 < args.size() 
-           && (args[i+1] == "--build-target" || args[i+1] == "--test-command"))
+          && (args[i+1] == "--build-target" || args[i+1] == "--test-command"))
           {
           done = true;
           }
@@ -3827,7 +3930,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         }
       }
     }
-  
+
   if(cmakeAndTest)
     {
     cmSystemTools::ResetErrorOccuredFlag();
@@ -3837,7 +3940,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
     cmListFileCache::GetInstance()->ClearCache();
     return retv;
     }
-  
+
   int res;
   // call process directory
   if (this->m_RunConfigurationScript)
@@ -3846,8 +3949,14 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
     }
   else
     {
-    this->Initialize();
-    res = this->ProcessTests();
+    if ( !this->Initialize() )
+      {
+      res = 12;
+      }
+    else
+      {
+      res = this->ProcessTests();
+      }
     this->Finalize();
     }
   return res;
@@ -3883,9 +3992,9 @@ void cmCTest::FindRunningCMake(const char* arg0)
   std::string dir;
   std::string file;
   if(cmSystemTools::SplitProgramPath(m_CTestSelf.c_str(),
-                                     dir,
-                                     file,
-                                     true))
+      dir,
+      file,
+      true))
     {
     m_CMakeSelf = dir += "/cmake";
     m_CMakeSelf += cmSystemTools::GetExecutableExtension();
@@ -3931,7 +4040,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
     m_ConfigType = CMAKE_INTDIR;
 #endif
     }
-  
+
   std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
   out << "Internal cmake changing into directory: " << m_BinaryDir << "\n";  
   if (!cmSystemTools::FileIsDirectory(m_BinaryDir.c_str()))
@@ -3950,7 +4059,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
       generator += m_BuildGenerator;
       args.push_back(generator);
       }
-    
+
     for(k=0; k < m_BuildOptions.size(); ++k)
       {
       args.push_back(m_BuildOptions[k]);
@@ -3991,7 +4100,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
         }
       } 
     }
-  
+
   cmSystemTools::SetErrorCallback(0, 0);
   out << cmakeOutString << "\n";
   if(m_BuildMakeProgram.size() == 0)
@@ -4071,7 +4180,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
       retVal = 0;
       std::string output;
       if (!cmSystemTools::RunSingleCommand(cleanCommand.c_str(), &output, &retVal) || 
-          retVal)
+        retVal)
         {
         out << "Error: " << cleanCommand.c_str() << "  execution failed\n";
         out << output.c_str() << "\n";
@@ -4090,16 +4199,16 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
         }
       out << output;
       }
-        
+
     if(m_BuildTarget.size())
       {
       makeCommand +=  " ";
       makeCommand += m_BuildTarget;
       }
     }
-  
+
   // command line make program
-  
+
   out << "Running make command: " << makeCommand.c_str() << "\n";
   retVal = 0;
   std::string output;
@@ -4139,7 +4248,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
     return 1;
     }
   out << output;
-  
+
   if(m_TestCommand.size() == 0)
     {
     if(outstring)
@@ -4152,8 +4261,8 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
       }
     return retVal;
     }
-  
-// now run the compiled test if we can find it
+
+  // now run the compiled test if we can find it
   // See if the executable exists as written.
   std::vector<std::string> failed;
   std::string fullPath;
@@ -4168,7 +4277,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
     std::string tryPath = m_TestCommand;
     tryPath += cmSystemTools::GetExecutableExtension();
     if(cmSystemTools::FileExists(tryPath.c_str())
-       && !cmSystemTools::FileIsDirectory(tryPath.c_str()))
+      && !cmSystemTools::FileIsDirectory(tryPath.c_str()))
       {
       fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
       }
@@ -4179,7 +4288,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
       tryPath = m_ConfigType + "/";
       tryPath += cmSystemTools::GetFilenameName(m_TestCommand);
       if(cmSystemTools::FileExists(tryPath.c_str())
-         && !cmSystemTools::FileIsDirectory(tryPath.c_str()))
+        && !cmSystemTools::FileIsDirectory(tryPath.c_str()))
         {
         fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
         }
@@ -4188,7 +4297,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
         failed.push_back(tryPath);
         tryPath += cmSystemTools::GetExecutableExtension();
         if(cmSystemTools::FileExists(tryPath.c_str())
-           && !cmSystemTools::FileIsDirectory(tryPath.c_str()))
+          && !cmSystemTools::FileIsDirectory(tryPath.c_str()))
           {
           fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
           }
@@ -4200,7 +4309,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
           tryPath += m_TestCommand;
           tryPath += cmSystemTools::GetExecutableExtension();
           if(cmSystemTools::FileExists(tryPath.c_str())
-             && !cmSystemTools::FileIsDirectory(tryPath.c_str()))
+            && !cmSystemTools::FileIsDirectory(tryPath.c_str()))
             {
             fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
             }
@@ -4213,7 +4322,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
             tryPath += m_TestCommand;
             tryPath += cmSystemTools::GetExecutableExtension();
             if(cmSystemTools::FileExists(tryPath.c_str())
-               && !cmSystemTools::FileIsDirectory(tryPath.c_str()))
+              && !cmSystemTools::FileIsDirectory(tryPath.c_str()))
               {
               fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
               }
@@ -4275,7 +4384,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
     out << "Test failed to run.\n";
     retval = 1;
     }
-   
+
   out << outs << "\n";
   if(outstring)
     {
@@ -4296,3 +4405,85 @@ void cmCTest::SetNotesFiles(const char* notes)
     }
   m_NotesFiles = notes;
 }
+
+int cmCTest::ReadCustomConfigurationFileTree(const char* dir)
+{
+  tm_VectorOfStrings dirs;
+  tm_VectorOfStrings ndirs;
+  dirs.push_back(dir);
+  cmake cm;
+  cmGlobalGenerator gg;
+  gg.SetCMakeInstance(&cm);
+  cmLocalGenerator *lg = gg.CreateLocalGenerator();
+  lg->SetGlobalGenerator(&gg);
+  cmMakefile *mf = lg->GetMakefile();
+
+  while ( dirs.size() > 0 )
+    {
+    tm_VectorOfStrings::iterator cdir = dirs.end()-1;
+    std::string rexpr = *cdir + "/*";
+    std::string fname = *cdir + "/CTestCustom.ctest";
+    if ( cmSystemTools::FileExists(fname.c_str()) && 
+      (!lg->GetMakefile()->ReadListFile(0, fname.c_str()) ||
+       cmSystemTools::GetErrorOccuredFlag() ) )
+      {
+      std::cerr << "Problem reading custom configuration" << std::endl;
+      return 0;
+      }
+    dirs.erase(dirs.end()-1, dirs.end());
+    cmSystemTools::SimpleGlob(rexpr, ndirs, -1);
+    dirs.insert(dirs.end(), ndirs.begin(), ndirs.end());
+    }
+
+  this->PopulateCustomVector(mf, "CTEST_CUSTOM_ERROR_MATCH", m_CustomErrorMatches);
+  this->PopulateCustomVector(mf, "CTEST_CUSTOM_ERROR_EXCEPTION", m_CustomErrorExceptions);
+  this->PopulateCustomVector(mf, "CTEST_CUSTOM_WARNING_MATCH", m_CustomWarningMatches);
+  this->PopulateCustomVector(mf, "CTEST_CUSTOM_WARNING_EXCEPTION", m_CustomWarningExceptions);
+
+  this->PopulateCustomVector(mf, "CTEST_CUSTOM_TESTS_IGNORE", m_CustomTestsIgnore);
+  this->PopulateCustomVector(mf, "CTEST_CUSTOM_MEMCHECK_IGNORE", m_CustomMemCheckIgnore);
+
+  this->PopulateCustomVector(mf, "CTEST_CUSTOM_PRE_TEST", m_CustomPreTest);
+  this->PopulateCustomVector(mf, "CTEST_CUSTOM_POST_TEST", m_CustomPostTest);
+  this->PopulateCustomVector(mf, "CTEST_CUSTOM_PRE_MEMCHECK", m_CustomPreMemCheck);
+  this->PopulateCustomVector(mf, "CTEST_CUSTOM_POST_MEMCHECK", m_CustomPostMemCheck);
+
+  return 1;
+}
+
+void cmCTest::PopulateCustomVector(cmMakefile* mf, const char* def, tm_VectorOfStrings& vec)
+{
+  if ( !def)
+    {
+    return;
+    }
+  const char* dval = mf->GetDefinition(def);
+  if ( !dval )
+    {
+    return;
+    }
+  std::vector<std::string> slist;
+  cmSystemTools::ExpandListArgument(dval, slist);
+  vec.insert(vec.end(), slist.begin(), slist.end());
+}
+
+int cmCTest::ExecuteCommands(tm_VectorOfStrings& vec)
+{
+  tm_VectorOfStrings::iterator it;
+  for ( it = vec.begin(); it != vec.end(); ++it )
+    {
+    int retVal = 0;
+    if ( m_Verbose )
+      {
+      std::cout << "Run command: " << *it << std::endl;
+      }
+    if ( !cmSystemTools::RunSingleCommand(it->c_str(), 0, &retVal, 0, true /*m_Verbose*/) || 
+      retVal != 0 )
+      {
+      std::cerr << "Problem running command: " << *it << std::endl;
+      return 0;
+      }
+    }
+  return 1;
+}
+