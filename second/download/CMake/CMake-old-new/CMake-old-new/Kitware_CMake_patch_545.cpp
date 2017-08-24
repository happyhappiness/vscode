@@ -9,8 +9,8 @@
   Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
   See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
-     This software is distributed WITHOUT ANY WARRANTY; without even 
-     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+     This software is distributed WITHOUT ANY WARRANTY; without even
+     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
      PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
@@ -42,7 +42,7 @@
 #include <cmsys/RegularExpression.hxx>
 #include <cmsys/Process.h>
 
-#include <stdlib.h> 
+#include <stdlib.h>
 #include <math.h>
 #include <float.h>
 
@@ -52,7 +52,7 @@
 #define DEBUGERR std::cerr << __LINE__ << " "; std::cerr
 
 //----------------------------------------------------------------------
-struct tm* cmCTest::GetNightlyTime(std::string str, 
+struct tm* cmCTest::GetNightlyTime(std::string str,
                                    bool tomorrowtag)
 {
   struct tm* lctime;
@@ -81,7 +81,8 @@ struct tm* cmCTest::GetNightlyTime(std::string str,
     // time of the current open dashboard
     ntime -= dayLength;
     cmCTestLog(this, DEBUG, "Pick yesterday" << std::endl);
-    cmCTestLog(this, DEBUG, "   Future time, subtract day: " << ntime << std::endl);
+    cmCTestLog(this, DEBUG, "   Future time, subtract day: " << ntime
+      << std::endl);
     }
   while ( tctime > (ntime + dayLength) )
     {
@@ -145,7 +146,8 @@ std::string cmCTest::MakeXMLSafe(const std::string& str)
   for ( ;*pos; ++pos)
     {
     char ch = *pos;
-    if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 && ch != '\r' )
+    if ( (ch > 126 || ch < 32) && ch != 9  &&
+      ch != 10 && ch != 13 && ch != '\r' )
       {
       char buffer[33];
       sprintf(buffer, "&lt;%d&gt;", (int)ch);
@@ -198,7 +200,7 @@ std::string cmCTest::MakeURLSafe(const std::string& str)
            ch == '&' ||
            ch == '%' ||
            ch == '+' ||
-           ch == '=' || 
+           ch == '=' ||
            ch == '@'
           ) && ch != 9 )
       {
@@ -214,8 +216,8 @@ std::string cmCTest::MakeURLSafe(const std::string& str)
 }
 
 //----------------------------------------------------------------------
-cmCTest::cmCTest() 
-{ 
+cmCTest::cmCTest()
+{
   m_SubmitIndex            = 0;
   m_ForceNewCTestProcess   = false;
   m_TomorrowTag            = false;
@@ -237,7 +239,7 @@ cmCTest::cmCTest()
   m_SuppressUpdatingCTestConfiguration = false;
   m_DartVersion            = 1;
 
-  int cc; 
+  int cc;
   for ( cc=0; cc < cmCTest::LAST_TEST; cc ++ )
     {
     m_Tests[cc] = 0;
@@ -265,8 +267,8 @@ cmCTest::cmCTest()
 }
 
 //----------------------------------------------------------------------
-cmCTest::~cmCTest() 
-{ 
+cmCTest::~cmCTest()
+{
   cmCTest::t_TestingHandlers::iterator it;
   for ( it = m_TestingHandlers.begin(); it != m_TestingHandlers.end(); ++ it )
     {
@@ -277,14 +279,15 @@ cmCTest::~cmCTest()
 }
 
 //----------------------------------------------------------------------
-int cmCTest::Initialize(const char* binary_dir, bool new_tag, bool verbose_tag)
+int cmCTest::Initialize(const char* binary_dir, bool new_tag,
+  bool verbose_tag)
 {
   cmCTestLog(this, DEBUG, "Here: " << __LINE__ << std::endl);
   if(!m_InteractiveDebugMode)
     {
     this->BlockTestErrorDiagnostics();
     }
-  
+
   m_BinaryDir = binary_dir;
   cmSystemTools::ConvertToUnixSlashes(m_BinaryDir);
 
@@ -296,8 +299,8 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag, bool verbose_tag)
   cmCTestLog(this, DEBUG, "Here: " << __LINE__ << std::endl);
     cmCTestLog(this, OUTPUT,
       "   Site: " << this->GetCTestConfiguration("Site") << std::endl
-      << "   Build name: " << this->GetCTestConfiguration("BuildName") << std::endl
-      );
+      << "   Build name: " << this->GetCTestConfiguration("BuildName")
+      << std::endl);
     cmCTestLog(this, DEBUG, "Produce XML is on" << std::endl);
     if ( this->GetCTestConfiguration("NightlyStartTime").empty() )
       {
@@ -309,7 +312,8 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag, bool verbose_tag)
 
   if ( !this->ReadCustomConfigurationFileTree(m_BinaryDir.c_str()) )
     {
-    cmCTestLog(this, DEBUG, "Cannot find custom configuration file tree" << std::endl);
+    cmCTestLog(this, DEBUG, "Cannot find custom configuration file tree"
+      << std::endl);
     return 0;
     }
 
@@ -320,17 +324,17 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag, bool verbose_tag)
       {
       if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
         {
-        cmCTestLog(this, ERROR_MESSAGE, "File " << testingDir << " is in the place of the testing directory"
-                  << std::endl);
+        cmCTestLog(this, ERROR_MESSAGE, "File " << testingDir
+          << " is in the place of the testing directory" << std::endl);
         return 0;
         }
       }
     else
       {
       if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
         {
-        cmCTestLog(this, ERROR_MESSAGE, "Cannot create directory " << testingDir
-                  << std::endl);
+        cmCTestLog(this, ERROR_MESSAGE, "Cannot create directory "
+          << testingDir << std::endl);
         return 0;
         }
       }
@@ -361,20 +365,24 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag, bool verbose_tag)
       std::string tagmode;
       if ( cmSystemTools::GetLineFromStream(tfin, tagmode) )
         {
-        if ( tagmode.size() > 4 && !( m_Tests[cmCTest::START_TEST] || m_Tests[ALL_TEST] ))
+        if ( tagmode.size() > 4 && !( m_Tests[cmCTest::START_TEST] ||
+            m_Tests[ALL_TEST] ))
           {
           m_TestModel = cmCTest::GetTestModelFromString(tagmode.c_str());
           }
         }
       tfin.close();
       }
-    if ( tag.size() == 0 || new_tag || m_Tests[cmCTest::START_TEST] || m_Tests[ALL_TEST])
+    if ( tag.size() == 0 || new_tag || m_Tests[cmCTest::START_TEST] ||
+      m_Tests[ALL_TEST])
       {
-      cmCTestLog(this, DEBUG, "TestModel: " << this->GetTestModelString() << std::endl);
+      cmCTestLog(this, DEBUG, "TestModel: " << this->GetTestModelString()
+        << std::endl);
       cmCTestLog(this, DEBUG, "TestModel: " << m_TestModel << std::endl);
       if ( m_TestModel == cmCTest::NIGHTLY )
         {
-        lctime = this->GetNightlyTime(this->GetCTestConfiguration("NightlyStartTime"), m_TomorrowTag);
+        lctime = this->GetNightlyTime(
+          this->GetCTestConfiguration("NightlyStartTime"), m_TomorrowTag);
         }
       char datestring[100];
       sprintf(datestring, "%04d%02d%02d-%02d%02d",
@@ -393,7 +401,7 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag, bool verbose_tag)
       ofs.close();
       if ( verbose_tag )
         {
-        cmCTestLog(this, OUTPUT, "Create new tag: " << tag << " - " 
+        cmCTestLog(this, OUTPUT, "Create new tag: " << tag << " - "
           << this->GetTestModelString() << std::endl);
         }
       }
@@ -410,7 +418,8 @@ bool cmCTest::InitializeFromCommand(cmCTestCommand* command, bool first)
     return true;
     }
 
-  std::string src_dir = this->GetCTestConfiguration("SourceDirectory").c_str();
+  std::string src_dir
+    = this->GetCTestConfiguration("SourceDirectory").c_str();
   std::string bld_dir = this->GetCTestConfiguration("BuildDirectory").c_str();
   m_DartVersion = 1;
   m_SubmitFiles.clear();
@@ -421,8 +430,9 @@ bool cmCTest::InitializeFromCommand(cmCTestCommand* command, bool first)
   cmSystemTools::ConvertToUnixSlashes(fname);
   if ( cmSystemTools::FileExists(fname.c_str()) )
     {
-    cmCTestLog(this, OUTPUT, "   Reading ctest configuration file: " << fname.c_str() << std::endl);
-    bool readit = mf->ReadListFile(mf->GetCurrentListFile(), 
+    cmCTestLog(this, OUTPUT, "   Reading ctest configuration file: "
+      << fname.c_str() << std::endl);
+    bool readit = mf->ReadListFile(mf->GetCurrentListFile(),
       fname.c_str() );
     if(!readit)
       {
@@ -434,24 +444,30 @@ bool cmCTest::InitializeFromCommand(cmCTestCommand* command, bool first)
     }
   else if ( !first )
     {
-    cmCTestLog(this, WARNING, "Cannot locate CTest configuration: " << fname.c_str() << std::endl);
+    cmCTestLog(this, WARNING, "Cannot locate CTest configuration: "
+      << fname.c_str() << std::endl);
     }
   else
     {
-    cmCTestLog(this, HANDLER_OUTPUT, "   Cannot locate CTest configuration: " << fname.c_str() << std::endl
+    cmCTestLog(this, HANDLER_OUTPUT, "   Cannot locate CTest configuration: "
+      << fname.c_str() << std::endl
       << "   Delay the initialization of CTest" << std::endl);
     }
 
-  this->SetCTestConfigurationFromCMakeVariable(mf, "NightlyStartTime", "CTEST_NIGHTLY_START_TIME");
+  this->SetCTestConfigurationFromCMakeVariable(mf, "NightlyStartTime",
+    "CTEST_NIGHTLY_START_TIME");
   this->SetCTestConfigurationFromCMakeVariable(mf, "Site", "CTEST_SITE");
-  this->SetCTestConfigurationFromCMakeVariable(mf, "BuildName", "CTEST_BUILD_NAME");
+  this->SetCTestConfigurationFromCMakeVariable(mf, "BuildName",
+    "CTEST_BUILD_NAME");
   const char* dartVersion = mf->GetDefinition("CTEST_DART_SERVER_VERSION");
   if ( dartVersion )
     {
     m_DartVersion = atoi(dartVersion);
     if ( m_DartVersion < 0 )
       {
-      cmCTestLog(this, ERROR_MESSAGE, "Invalid Dart server version: " << dartVersion << ". Please specify the version number." << std::endl);
+      cmCTestLog(this, ERROR_MESSAGE, "Invalid Dart server version: "
+        << dartVersion << ". Please specify the version number."
+        << std::endl);
       return false;
       }
     }
@@ -464,7 +480,8 @@ bool cmCTest::InitializeFromCommand(cmCTestCommand* command, bool first)
       }
     return false;
     }
-  cmCTestLog(this, OUTPUT, "   Use " << this->GetTestModelString() << " tag: " << this->GetCurrentTag() << std::endl);
+  cmCTestLog(this, OUTPUT, "   Use " << this->GetTestModelString()
+    << " tag: " << this->GetCurrentTag() << std::endl);
   return true;
 }
 
@@ -490,7 +507,8 @@ bool cmCTest::UpdateCTestConfiguration()
     // No need to exit if we are not producing XML
     if ( m_ProduceXML )
       {
-      cmCTestLog(this, ERROR_MESSAGE, "Cannot find file: " << fileName.c_str() << std::endl);
+      cmCTestLog(this, ERROR_MESSAGE, "Cannot find file: " << fileName.c_str()
+        << std::endl);
       return false;
       }
     }
@@ -532,15 +550,17 @@ bool cmCTest::UpdateCTestConfiguration()
         continue;
         }
       std::string key = line.substr(0, cpos);
-      std::string value = cmCTest::CleanString(line.substr(cpos+1, line.npos));
+      std::string value
+        = cmCTest::CleanString(line.substr(cpos+1, line.npos));
       m_CTestConfiguration[key] = value;
       }
     fin.close();
     }
   m_TimeOut = atoi(this->GetCTestConfiguration("TimeOut").c_str());
   if ( m_ProduceXML )
     {
-    m_CompressXMLFiles = cmSystemTools::IsOn(this->GetCTestConfiguration("CompressSubmission").c_str());
+    m_CompressXMLFiles = cmSystemTools::IsOn(
+      this->GetCTestConfiguration("CompressSubmission").c_str());
     }
   return true;
 }
@@ -551,7 +571,7 @@ void cmCTest::BlockTestErrorDiagnostics()
   cmSystemTools::PutEnv("DART_TEST_FROM_DART=1");
   cmSystemTools::PutEnv("DASHBOARD_TEST_FROM_CTEST=" CMake_VERSION);
 #if defined(_WIN32)
-  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX); 
+  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
 #endif
 }
 
@@ -609,7 +629,8 @@ bool cmCTest::SetTest(const char* ttype, bool report)
     {
     if ( report )
       {
-      cmCTestLog(this, ERROR_MESSAGE, "Don't know about test \"" << ttype << "\" yet..." << std::endl);
+      cmCTestLog(this, ERROR_MESSAGE, "Don't know about test \"" << ttype
+        << "\" yet..." << std::endl);
       }
     return false;
     }
@@ -622,7 +643,7 @@ void cmCTest::Finalize()
 }
 
 //----------------------------------------------------------------------
-bool cmCTest::OpenOutputFile(const std::string& path, 
+bool cmCTest::OpenOutputFile(const std::string& path,
                      const std::string& name, cmGeneratedFileStream& stream,
                      bool compress)
 {
@@ -635,7 +656,7 @@ bool cmCTest::OpenOutputFile(const std::string& path,
     {
     if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
       {
-      cmCTestLog(this, ERROR_MESSAGE, "File " << testingDir 
+      cmCTestLog(this, ERROR_MESSAGE, "File " << testingDir
                 << " is in the place of the testing directory"
                 << std::endl);
       return false;
@@ -654,7 +675,8 @@ bool cmCTest::OpenOutputFile(const std::string& path,
   stream.Open(filename.c_str());
   if( !stream )
     {
-    cmCTestLog(this, ERROR_MESSAGE, "Problem opening file: " << filename << std::endl);
+    cmCTestLog(this, ERROR_MESSAGE, "Problem opening file: " << filename
+      << std::endl);
     return false;
     }
   if ( compress )
@@ -730,7 +752,7 @@ int cmCTest::ExecuteHandler(const char* shandler)
     return -1;
     }
   handler->Initialize();
-  return handler->ProcessHandler(); 
+  return handler->ProcessHandler();
 }
 
 //----------------------------------------------------------------------
@@ -754,8 +776,9 @@ int cmCTest::ProcessTests()
   if ( m_Tests[UPDATE_TEST] || m_Tests[ALL_TEST] )
     {
     cmCTestGenericHandler* uphandler = this->GetHandler("update");
-    uphandler->SetOption("SourceDirectory", this->GetCTestConfiguration("SourceDirectory").c_str());
-    update_count = uphandler->ProcessHandler(); 
+    uphandler->SetOption("SourceDirectory",
+      this->GetCTestConfiguration("SourceDirectory").c_str());
+    update_count = uphandler->ProcessHandler();
     if ( update_count < 0 )
       {
       res |= cmCTest::UPDATE_ERRORS;
@@ -847,7 +870,8 @@ int cmCTest::ProcessTests()
     }
   if ( res != 0 )
     {
-    cmCTestLog(this, ERROR_MESSAGE, "Errors while running CTest" << std::endl);
+    cmCTestLog(this, ERROR_MESSAGE, "Errors while running CTest"
+      << std::endl);
     }
   return res;
 }
@@ -921,7 +945,7 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
     cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, " \"" << *ait << "\"");
     }
   cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, std::endl);
-  
+
   // Now create process object
   cmsysProcess* cp = cmsysProcess_New();
   cmsysProcess_SetCommand(cp, &*argv.begin());
@@ -981,22 +1005,25 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
   if(result == cmsysProcess_State_Exited)
     {
     *retVal = cmsysProcess_GetExitValue(cp);
-    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, "Command exited with the value: " << *retVal << std::endl);
+    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, "Command exited with the value: "
+      << *retVal << std::endl);
     }
   else if(result == cmsysProcess_State_Exception)
     {
     *retVal = cmsysProcess_GetExitException(cp);
-    cmCTestLog(this, WARNING, "There was an exception: " << *retVal << std::endl);
+    cmCTestLog(this, WARNING, "There was an exception: " << *retVal
+      << std::endl);
     }
   else if(result == cmsysProcess_State_Expired)
     {
     cmCTestLog(this, WARNING, "There was a timeout" << std::endl);
-    } 
+    }
   else if(result == cmsysProcess_State_Error)
     {
     *output += "\n*** ERROR executing: ";
     *output += cmsysProcess_GetErrorString(cp);
-    cmCTestLog(this, ERROR_MESSAGE, "There was an error: " << cmsysProcess_GetErrorString(cp) << std::endl);
+    cmCTestLog(this, ERROR_MESSAGE, "There was an error: "
+      << cmsysProcess_GetErrorString(cp) << std::endl);
     }
 
   cmsysProcess_Delete(cp);
@@ -1010,11 +1037,11 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
 //######################################################################
 
 //----------------------------------------------------------------------
-int cmCTest::RunTest(std::vector<const char*> argv, 
+int cmCTest::RunTest(std::vector<const char*> argv,
                      std::string* output, int *retVal,
                      std::ostream* log)
 {
-  if(cmSystemTools::SameFile(argv[0], m_CTestSelf.c_str()) && 
+  if(cmSystemTools::SameFile(argv[0], m_CTestSelf.c_str()) &&
      !m_ForceNewCTestProcess)
     {
     cmCTest inst;
@@ -1033,15 +1060,16 @@ int cmCTest::RunTest(std::vector<const char*> argv,
       *log << "* Run internal CTest" << std::endl;
       }
     std::string oldpath = cmSystemTools::GetCurrentWorkingDirectory();
-    
+
     *retVal = inst.Run(args, output);
     if ( *log )
       {
       *log << output->c_str();
       }
     cmSystemTools::ChangeDirectory(oldpath.c_str());
-    
-    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, "Internal cmCTest object used to run test." << std::endl
+
+    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT,
+      "Internal cmCTest object used to run test." << std::endl
       <<  *output << std::endl);
     return cmsysProcess_State_Exited;
     }
@@ -1081,7 +1109,8 @@ int cmCTest::RunTest(std::vector<const char*> argv,
     {
     output->append(&*tempOutput.begin(), tempOutput.size());
     }
-  cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, "-- Process completed" << std::endl);
+  cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, "-- Process completed"
+    << std::endl);
 
   int result = cmsysProcess_GetState(cp);
 
@@ -1095,14 +1124,16 @@ int cmCTest::RunTest(std::vector<const char*> argv,
     std::string outerr = "\n*** Exception executing: ";
     outerr += cmsysProcess_GetExceptionString(cp);
     *output += outerr;
-    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, outerr.c_str() << std::endl << std::flush);
+    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, outerr.c_str() << std::endl
+      << std::flush);
     }
   else if(result == cmsysProcess_State_Error)
     {
     std::string outerr = "\n*** ERROR executing: ";
     outerr += cmsysProcess_GetErrorString(cp);
     *output += outerr;
-    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, outerr.c_str() << std::endl << std::flush);
+    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, outerr.c_str() << std::endl
+      << std::flush);
     }
   cmsysProcess_Delete(cp);
 
@@ -1128,13 +1159,17 @@ void cmCTest::EndXML(std::ostream& ostr)
 }
 
 //----------------------------------------------------------------------
-int cmCTest::GenerateCTestNotesOutput(std::ostream& os, const cmCTest::tm_VectorOfStrings& files)
+int cmCTest::GenerateCTestNotesOutput(std::ostream& os,
+  const cmCTest::tm_VectorOfStrings& files)
 {
   cmCTest::tm_VectorOfStrings::const_iterator it;
   os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
-    << "<?xml-stylesheet type=\"text/xsl\" href=\"Dart/Source/Server/XSL/Build.xsl <file:///Dart/Source/Server/XSL/Build.xsl> \"?>\n"
-    << "<Site BuildName=\"" << this->GetCTestConfiguration("BuildName") << "\" BuildStamp=\"" 
-    << m_CurrentTag << "-" << this->GetTestModelString() << "\" Name=\"" 
+    << "<?xml-stylesheet type=\"text/xsl\" "
+    "href=\"Dart/Source/Server/XSL/Build.xsl "
+    "<file:///Dart/Source/Server/XSL/Build.xsl> \"?>\n"
+    << "<Site BuildName=\"" << this->GetCTestConfiguration("BuildName")
+    << "\" BuildStamp=\""
+    << m_CurrentTag << "-" << this->GetTestModelString() << "\" Name=\""
     << this->GetCTestConfiguration("Site") << "\" Generator=\"ctest"
     << cmVersion::GetCMakeVersion()
     << "\">\n"
@@ -1160,7 +1195,8 @@ int cmCTest::GenerateCTestNotesOutput(std::ostream& os, const cmCTest::tm_Vector
     else
       {
       os << "Problem reading file: " << it->c_str() << std::endl;
-      cmCTestLog(this, ERROR_MESSAGE, "Problem reading file: " << it->c_str() << " while creating notes" << std::endl);
+      cmCTestLog(this, ERROR_MESSAGE, "Problem reading file: " << it->c_str()
+        << " while creating notes" << std::endl);
       }
     os << "</Text>\n"
       << "</Note>" << std::endl;
@@ -1215,7 +1251,8 @@ bool cmCTest::SubmitExtraFiles(const std::vector<cmStdString> &files)
     {
     if ( !cmSystemTools::FileExists(it->c_str()) )
       {
-      cmCTestLog(this, ERROR_MESSAGE, "Cannot find extra file: " << it->c_str() << " to submit."
+      cmCTestLog(this, ERROR_MESSAGE, "Cannot find extra file: "
+        << it->c_str() << " to submit."
         << std::endl;);
       return false;
       }
@@ -1246,7 +1283,8 @@ bool cmCTest::SubmitExtraFiles(const char* cfiles)
 }
 
 //----------------------------------------------------------------------
-bool cmCTest::CheckArgument(const std::string& arg, const char* varg1, const char* varg2)
+bool cmCTest::CheckArgument(const std::string& arg, const char* varg1,
+  const char* varg2)
 {
   if ( varg1 && arg == varg1 || varg2 && arg == varg2 )
     {
@@ -1271,7 +1309,8 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       this->m_CTestConfigFile= args[i];
       }
 
-    if(this->CheckArgument(arg, "-C", "--build-config") && i < args.size() - 1)
+    if(this->CheckArgument(arg, "-C", "--build-config") &&
+      i < args.size() - 1)
       {
       i++;
       this->m_ConfigType = args[i];
@@ -1309,7 +1348,8 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       {
       this->m_RunConfigurationScript = true;
       i++;
-      cmCTestScriptHandler* ch = static_cast<cmCTestScriptHandler*>(this->GetHandler("script"));
+      cmCTestScriptHandler* ch
+        = static_cast<cmCTestScriptHandler*>(this->GetHandler("script"));
       ch->AddConfigurationScript(args[i].c_str());
       }
 
@@ -1327,7 +1367,8 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       {
       m_ForceNewCTestProcess = true;
       }
-    if(this->CheckArgument(arg, "--interactive-debug-mode") && i < args.size() - 1 )
+    if(this->CheckArgument(arg, "--interactive-debug-mode") &&
+      i < args.size() - 1 )
       {
       i++;
       m_InteractiveDebugMode = cmSystemTools::IsOn(args[i].c_str());
@@ -1417,7 +1458,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         {
         this->SetTestModel(cmCTest::CONTINUOUS);
         this->SetTest("Update");
-        }  
+        }
       else if ( targ == "ContinuousConfigure" )
         {
         this->SetTestModel(cmCTest::CONTINUOUS);
@@ -1525,29 +1566,38 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       else
         {
         performSomeTest = false;
-        cmCTestLog(this, ERROR_MESSAGE, "CTest -D called with incorrect option: " << targ << std::endl);
+        cmCTestLog(this, ERROR_MESSAGE,
+          "CTest -D called with incorrect option: " << targ << std::endl);
         cmCTestLog(this, ERROR_MESSAGE, "Available options are:" << std::endl
           << "  " << ctestExec << " -D Continuous" << std::endl
-          << "  " << ctestExec << " -D Continuous(Start|Update|Configure|Build)" << std::endl
-          << "  " << ctestExec << " -D Continuous(Test|Coverage|MemCheck|Submit)" << std::endl
+          << "  " << ctestExec
+          << " -D Continuous(Start|Update|Configure|Build)" << std::endl
+          << "  " << ctestExec
+          << " -D Continuous(Test|Coverage|MemCheck|Submit)" << std::endl
           << "  " << ctestExec << " -D Experimental" << std::endl
-          << "  " << ctestExec << " -D Experimental(Start|Update|Configure|Build)" << std::endl
-          << "  " << ctestExec << " -D Experimental(Test|Coverage|MemCheck|Submit)" << std::endl
+          << "  " << ctestExec
+          << " -D Experimental(Start|Update|Configure|Build)" << std::endl
+          << "  " << ctestExec
+          << " -D Experimental(Test|Coverage|MemCheck|Submit)" << std::endl
           << "  " << ctestExec << " -D Nightly" << std::endl
-          << "  " << ctestExec << " -D Nightly(Start|Update|Configure|Build)" << std::endl
-          << "  " << ctestExec << " -D Nightly(Test|Coverage|MemCheck|Submit)" << std::endl
+          << "  " << ctestExec
+          << " -D Nightly(Start|Update|Configure|Build)" << std::endl
+          << "  " << ctestExec
+          << " -D Nightly(Test|Coverage|MemCheck|Submit)" << std::endl
           << "  " << ctestExec << " -D NightlyMemoryCheck" << std::endl);
         }
       }
 
-    if(this->CheckArgument(arg, "-T", "--test-action") && (i < args.size() -1) )
+    if(this->CheckArgument(arg, "-T", "--test-action") &&
+      (i < args.size() -1) )
       {
       this->m_ProduceXML = true;
       i++;
       if ( !this->SetTest(args[i].c_str(), false) )
         {
         performSomeTest = false;
-        cmCTestLog(this, ERROR_MESSAGE, "CTest -T called with incorrect option: "
+        cmCTestLog(this, ERROR_MESSAGE,
+          "CTest -T called with incorrect option: "
           << args[i].c_str() << std::endl);
         cmCTestLog(this, ERROR_MESSAGE, "Available options are:" << std::endl
           << "  " << ctestExec << " -T all" << std::endl
@@ -1563,7 +1613,8 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         }
       }
 
-    if(this->CheckArgument(arg, "-M", "--test-model") && (i < args.size() -1) )
+    if(this->CheckArgument(arg, "-M", "--test-model") &&
+      (i < args.size() -1) )
       {
       i++;
       std::string const& str = args[i];
@@ -1582,33 +1633,40 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       else
         {
         performSomeTest = false;
-        cmCTestLog(this, ERROR_MESSAGE, "CTest -M called with incorrect option: " << str.c_str() << std::endl);
+        cmCTestLog(this, ERROR_MESSAGE,
+          "CTest -M called with incorrect option: " << str.c_str()
+          << std::endl);
         cmCTestLog(this, ERROR_MESSAGE, "Available options are:" << std::endl
           << "  " << ctestExec << " -M Continuous" << std::endl
           << "  " << ctestExec << " -M Experimental" << std::endl
           << "  " << ctestExec << " -M Nightly" << std::endl);
         }
       }
 
-    if(this->CheckArgument(arg, "-I", "--tests-information") && i < args.size() - 1)
+    if(this->CheckArgument(arg, "-I", "--tests-information") &&
+      i < args.size() - 1)
       {
       i++;
-      this->GetHandler("test")->SetOption("TestsToRunInformation", args[i].c_str());
-      }                                                       
+      this->GetHandler("test")->SetOption("TestsToRunInformation",
+        args[i].c_str());
+      }
     if(this->CheckArgument(arg, "-U", "--union"))
-      {                                                       
+      {
       this->GetHandler("test")->SetOption("UseUnion", "true");
-      }                                                       
-    if(this->CheckArgument(arg, "-R", "--tests-regex") && i < args.size() - 1)          
-      {                                                       
-      i++;                                                    
-      this->GetHandler("test")->SetOption("IncludeRegularExpression", args[i].c_str());
-      }                                                       
-
-    if(this->CheckArgument(arg, "-E", "--exclude-regex") && i < args.size() - 1)          
-      {                                                       
+      }
+    if(this->CheckArgument(arg, "-R", "--tests-regex") && i < args.size() - 1)
+      {
+      i++;
+      this->GetHandler("test")->SetOption("IncludeRegularExpression",
+        args[i].c_str());
+      }
+
+    if(this->CheckArgument(arg, "-E", "--exclude-regex") &&
+      i < args.size() - 1)
+      {
       i++;
-      this->GetHandler("test")->SetOption("ExcludeRegularExpression", args[i].c_str());
+      this->GetHandler("test")->SetOption("ExcludeRegularExpression",
+        args[i].c_str());
       }
 
     if(this->CheckArgument(arg, "--overwrite") && i < args.size() - 1)
@@ -1639,11 +1697,14 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       cmakeAndTest = true;
       }
     cmCTest::t_TestingHandlers::iterator it;
-    for ( it = m_TestingHandlers.begin(); it != m_TestingHandlers.end(); ++ it )
+    for ( it = m_TestingHandlers.begin();
+      it != m_TestingHandlers.end();
+      ++ it )
       {
       if ( !it->second->ProcessCommandLineArguments(arg, i, args) )
         {
-        cmCTestLog(this, ERROR_MESSAGE, "Problem parsing command line arguments within a handler");
+        cmCTestLog(this, ERROR_MESSAGE,
+          "Problem parsing command line arguments within a handler");
         return 0;
         }
       }
@@ -1660,7 +1721,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
   if(cmakeAndTest)
     {
     m_Verbose = true;
-    cmCTestBuildAndTestHandler* handler = 
+    cmCTestBuildAndTestHandler* handler =
       static_cast<cmCTestBuildAndTestHandler*>(this->GetHandler("buildtest"));
     int retv = handler->ProcessHandler();
     *output = handler->GetOutput();
@@ -1681,7 +1742,9 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         cmCTestLog(this, OUTPUT, "* Extra verbosity turned on" << std::endl);
         }
       cmCTest::t_TestingHandlers::iterator it;
-      for ( it = m_TestingHandlers.begin(); it != m_TestingHandlers.end(); ++ it )
+      for ( it = m_TestingHandlers.begin();
+        it != m_TestingHandlers.end();
+        ++ it )
         {
         it->second->SetVerbose(this->m_ExtraVerbose);
         it->second->SetSubmitIndex(m_SubmitIndex);
@@ -1694,17 +1757,21 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       m_ExtraVerbose = m_Verbose;
       m_Verbose = true;
       cmCTest::t_TestingHandlers::iterator it;
-      for ( it = m_TestingHandlers.begin(); it != m_TestingHandlers.end(); ++ it )
+      for ( it = m_TestingHandlers.begin();
+        it != m_TestingHandlers.end();
+        ++ it )
         {
         it->second->SetVerbose(this->m_Verbose);
         it->second->SetSubmitIndex(m_SubmitIndex);
         }
       cmCTestLog(this, DEBUG, "Here: " << __LINE__ << std::endl);
-      if ( !this->Initialize(cmSystemTools::GetCurrentWorkingDirectory().c_str()) )
+      if ( !this->Initialize(
+          cmSystemTools::GetCurrentWorkingDirectory().c_str()) )
         {
         cmCTestLog(this, DEBUG, "Here: " << __LINE__ << std::endl);
         res = 12;
-        cmCTestLog(this, ERROR_MESSAGE, "Problem initializing the dashboard." << std::endl);
+        cmCTestLog(this, ERROR_MESSAGE, "Problem initializing the dashboard."
+          << std::endl);
         }
       else
         {
@@ -1817,11 +1884,13 @@ int cmCTest::ReadCustomConfigurationFileTree(const char* dir)
   for ( fileIt = files.begin(); fileIt != files.end();
     ++ fileIt )
     {
-    cmCTestLog(this, DEBUG, "* Read custom CTest configuration file: " << fileIt->c_str() << std::endl);
+    cmCTestLog(this, DEBUG, "* Read custom CTest configuration file: "
+      << fileIt->c_str() << std::endl);
     if ( !lg->GetMakefile()->ReadListFile(0, fileIt->c_str()) ||
       cmSystemTools::GetErrorOccuredFlag() )
       {
-      cmCTestLog(this, ERROR_MESSAGE, "Problem reading custom configuration: " << fileIt->c_str() << std::endl);
+      cmCTestLog(this, ERROR_MESSAGE, "Problem reading custom configuration: "
+        << fileIt->c_str() << std::endl);
       }
     }
 
@@ -1830,12 +1899,13 @@ int cmCTest::ReadCustomConfigurationFileTree(const char* dir)
     {
     it->second->PopulateCustomVectors(mf);
     }
-  
+
   return 1;
 }
 
 //----------------------------------------------------------------------
-void cmCTest::PopulateCustomVector(cmMakefile* mf, const char* def, tm_VectorOfStrings& vec)
+void cmCTest::PopulateCustomVector(cmMakefile* mf, const char* def,
+  tm_VectorOfStrings& vec)
 {
   if ( !def)
     {
@@ -1874,7 +1944,8 @@ void cmCTest::PopulateCustomInteger(cmMakefile* mf, const char* def, int& val)
 //----------------------------------------------------------------------
 std::string cmCTest::GetShortPathToFile(const char* cfname)
 {
-  const std::string& sourceDir = this->GetCTestConfiguration("SourceDirectory");
+  const std::string& sourceDir
+    = this->GetCTestConfiguration("SourceDirectory");
   const std::string& buildDir = this->GetCTestConfiguration("BuildDirectory");
   std::string fname = cmSystemTools::CollapseFullPath(cfname);
 
@@ -1928,7 +1999,8 @@ std::string cmCTest::GetShortPathToFile(const char* cfname)
 //----------------------------------------------------------------------
 std::string cmCTest::GetCTestConfiguration(const char *name)
 {
-  if ( m_CTestConfigurationOverwrites.find(name) != m_CTestConfigurationOverwrites.end() )
+  if ( m_CTestConfigurationOverwrites.find(name) !=
+    m_CTestConfigurationOverwrites.end() )
     {
     return m_CTestConfigurationOverwrites[name];
     }
@@ -1956,7 +2028,7 @@ void cmCTest::SetCTestConfiguration(const char *name, const char* value)
   m_CTestConfiguration[name] = value;
 }
 
-  
+
 //----------------------------------------------------------------------
 std::string cmCTest::GetCurrentTag()
 {
@@ -2007,7 +2079,8 @@ void cmCTest::AddCTestConfigurationOverwrite(const char* encstr)
   if ( epos == overStr.npos )
     {
     cmCTestLog(this, ERROR_MESSAGE,
-      "CTest configuration overwrite specified in the wrong format." << std::endl
+      "CTest configuration overwrite specified in the wrong format."
+      << std::endl
       << "Valid format is: --overwrite key=value" << std::endl
       << "The specified was: --overwrite " << overStr.c_str() << std::endl);
     return;
@@ -2018,7 +2091,8 @@ void cmCTest::AddCTestConfigurationOverwrite(const char* encstr)
 }
 
 //----------------------------------------------------------------------
-bool cmCTest::SetCTestConfigurationFromCMakeVariable(cmMakefile* mf, const char* dconfig, const char* cmake_var)
+bool cmCTest::SetCTestConfigurationFromCMakeVariable(cmMakefile* mf,
+  const char* dconfig, const char* cmake_var)
 {
   const char* ctvar;
   ctvar = mf->GetDefinition(cmake_var);
@@ -2031,10 +2105,10 @@ bool cmCTest::SetCTestConfigurationFromCMakeVariable(cmMakefile* mf, const char*
 }
 
 bool cmCTest::RunCommand(
-  const char* command, 
+  const char* command,
   std::string* stdOut,
   std::string* stdErr,
-  int *retVal, 
+  int *retVal,
   const char* dir,
   double timeout)
 {
@@ -2044,7 +2118,7 @@ bool cmCTest::RunCommand(
     {
     return false;
     }
-  
+
   std::vector<const char*> argv;
   for(std::vector<cmStdString>::const_iterator a = args.begin();
       a != args.end(); ++a)
@@ -2065,7 +2139,7 @@ bool cmCTest::RunCommand(
     }
   cmsysProcess_SetTimeout(cp, timeout);
   cmsysProcess_Execute(cp);
-  
+
   std::vector<char> tempOutput;
   std::vector<char> tempError;
   char* data;
@@ -2086,16 +2160,17 @@ bool cmCTest::RunCommand(
     default:
       done = true;
       }
-    if ( (res == cmsysProcess_Pipe_STDOUT || res == cmsysProcess_Pipe_STDERR) && m_ExtraVerbose )
+    if ( (res == cmsysProcess_Pipe_STDOUT ||
+        res == cmsysProcess_Pipe_STDERR) && m_ExtraVerbose )
       {
       cmSystemTools::Stdout(data, length);
       }
     }
-  
+
   cmsysProcess_WaitForExit(cp, 0);
   stdOut->append(&*tempOutput.begin(), tempOutput.size());
   stdErr->append(&*tempError.begin(), tempError.size());
-  
+
   bool result = true;
   if(cmsysProcess_GetState(cp) == cmsysProcess_State_Exited)
     {
@@ -2132,7 +2207,7 @@ bool cmCTest::RunCommand(
     stdErr->append(error_str, strlen(error_str));
     result = false;
     }
-  
+
   cmsysProcess_Delete(cp);
   return result;
 }
@@ -2152,7 +2227,7 @@ void cmCTest::SetOutputLogFileName(const char* name)
 }
 
 //----------------------------------------------------------------------
-static const char* cmCTestStringLogType[] = 
+static const char* cmCTestStringLogType[] =
 {
   "DEBUG",
   "OUTPUT",
@@ -2187,7 +2262,8 @@ void cmCTest::Log(int logType, const char* file, int line, const char* msg)
     {
     bool display = true;
     if ( logType == cmCTest::DEBUG && !m_Debug ) { display = false; }
-    if ( logType == cmCTest::HANDLER_VERBOSE_OUTPUT && !m_Debug && !m_ExtraVerbose ) { display = false; }
+    if ( logType == cmCTest::HANDLER_VERBOSE_OUTPUT && !m_Debug &&
+      !m_ExtraVerbose ) { display = false; }
     if ( display )
       {
       cmCTestLogOutputFileLine(*m_OutputLogFile);