@@ -50,35 +50,25 @@
 #define DEBUGERR std::cerr << __LINE__ << " "; std::cerr
 
 struct tm* cmCTest::GetNightlyTime(std::string str, 
-                                   bool verbose, 
                                    bool tomorrowtag)
 {
   struct tm* lctime;
   time_t tctime = time(0);
-  if ( verbose )
-    {
-    std::cout << "Determine Nightly Start Time" << std::endl;
-    std::cout << "   Specified time: " << str.c_str() << std::endl;
-    }
+  cmCTestLog(this, OUTPUT, "Determine Nightly Start Time" << std::endl
+    << "   Specified time: " << str.c_str() << std::endl);
   //Convert the nightly start time to seconds. Since we are
   //providing only a time and a timezone, the current date of
   //the local machine is assumed. Consequently, nightlySeconds
   //is the time at which the nightly dashboard was opened or
   //will be opened on the date of the current client machine.
   //As such, this time may be in the past or in the future.
   time_t ntime = curl_getdate(str.c_str(), &tctime);
-  if ( verbose )
-    {
-    std::cout << "   Get curl time: " << ntime << std::endl;
-    }
+  cmCTestLog(this, DEBUG, "   Get curl time: " << ntime << std::endl);
   tctime = time(0);
-  if ( verbose )
-    {
-    std::cout << "   Get the current time: " << tctime << std::endl;
-    }
+  cmCTestLog(this, DEBUG, "   Get the current time: " << tctime << std::endl);
 
   const int dayLength = 24 * 60 * 60;
-  //std::cout << "Seconds: " << tctime << std::endl;
+  cmCTestLog(this, DEBUG, "Seconds: " << tctime << std::endl);
   while ( ntime > tctime )
     {
     // If nightlySeconds is in the past, this is the current
@@ -87,29 +77,20 @@ struct tm* cmCTest::GetNightlyTime(std::string str,
     // dashboard to be opened, so subtract 24 hours to get the
     // time of the current open dashboard
     ntime -= dayLength;
-    //std::cout << "Pick yesterday" << std::endl;
-    if ( verbose )
-      {
-      std::cout << "   Future time, subtract day: " << ntime << std::endl;
-      }
+    cmCTestLog(this, DEBUG, "Pick yesterday" << std::endl);
+    cmCTestLog(this, DEBUG, "   Future time, subtract day: " << ntime << std::endl);
     }
   while ( tctime > (ntime + dayLength) )
     {
     ntime += dayLength;
-    if ( verbose )
-      {
-      std::cout << "   Past time, add day: " << ntime << std::endl;
-      }
-    }
-  //std::cout << "nightlySeconds: " << ntime << std::endl;
-  if ( verbose )
-    {
-    std::cout << "   Current time: " << tctime
-              << " Nightly time: " << ntime << std::endl;
+    cmCTestLog(this, DEBUG, "   Past time, add day: " << ntime << std::endl);
     }
+  cmCTestLog(this, DEBUG, "nightlySeconds: " << ntime << std::endl);
+  cmCTestLog(this, DEBUG, "   Current time: " << tctime
+    << " Nightly time: " << ntime << std::endl);
   if ( tomorrowtag )
     {
-    std::cout << "Use future tag, Add a day" << std::endl;
+    cmCTestLog(this, OUTPUT, "   Use future tag, Add a day" << std::endl);
     ntime += dayLength;
     }
   lctime = gmtime(&ntime);
@@ -145,7 +126,7 @@ std::string cmCTest::CurrentTime()
     {
     strftime(current_time, 1000, "%a %b %d %H:%M:%S %Z %Y", t);
     }
-  //std::cout << "Current_Time: " << current_time << std::endl;
+  cmCTestLog(this, DEBUG, "   Current_Time: " << current_time << std::endl);
   return cmCTest::MakeXMLSafe(cmCTest::CleanString(current_time));
 }
 
@@ -227,6 +208,8 @@ cmCTest::cmCTest()
   m_BuildNoClean           = false;
   m_BuildTwoConfig         = false;
   m_Verbose                = false;
+  m_Debug                  = false;
+  m_Quiet                  = false;
   m_ExtraVerbose           = false;
   m_ProduceXML             = false;
   m_ShowOnly               = false;
@@ -258,6 +241,8 @@ cmCTest::cmCTest()
     {
     it->second->SetCTestInstance(this);
     }
+  m_OutputLogFile = 0;
+  m_OutputLogFileLastTag = -1;
 }
 
 cmCTest::~cmCTest() 
@@ -268,6 +253,7 @@ cmCTest::~cmCTest()
     delete it->second;
     it->second = 0;
     }
+  this->SetOutputLogFileName(0);
 }
 
 int cmCTest::Initialize(const char* binary_dir, bool new_tag)
@@ -291,17 +277,17 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag)
       {
       if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
         {
-        std::cerr << "File " << testingDir << " is in the place of the testing directory"
-                  << std::endl;
+        cmCTestLog(this, ERROR, "File " << testingDir << " is in the place of the testing directory"
+                  << std::endl);
         return 0;
         }
       }
     else
       {
       if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
         {
-        std::cerr << "Cannot create directory " << testingDir
-                  << std::endl;
+        cmCTestLog(this, ERROR, "Cannot create directory " << testingDir
+                  << std::endl);
         return 0;
         }
       }
@@ -341,13 +327,11 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag)
       }
     if ( tag.size() == 0 || new_tag || m_Tests[cmCTest::START_TEST] || m_Tests[ALL_TEST])
       {
-      //std::cout << "TestModel: " << this->GetTestModelString() << std::endl;
-      //std::cout << "TestModel: " << m_TestModel << std::endl;
+      cmCTestLog(this, DEBUG, "TestModel: " << this->GetTestModelString() << std::endl);
+      cmCTestLog(this, DEBUG, "TestModel: " << m_TestModel << std::endl);
       if ( m_TestModel == cmCTest::NIGHTLY )
         {
-        lctime = cmCTest::GetNightlyTime(m_CTestConfiguration["NightlyStartTime"],
-          m_ExtraVerbose,
-          m_TomorrowTag);
+        lctime = this->GetNightlyTime(m_CTestConfiguration["NightlyStartTime"], m_TomorrowTag);
         }
       char datestring[100];
       sprintf(datestring, "%04d%02d%02d-%02d%02d",
@@ -364,8 +348,8 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag)
         ofs << this->GetTestModelString() << std::endl;
         }
       ofs.close();
-      std::cout << "Create new tag: " << tag << " - " 
-        << this->GetTestModelString() << std::endl;
+      cmCTestLog(this, OUTPUT, "Create new tag: " << tag << " - " 
+        << this->GetTestModelString() << std::endl);
       }
     m_CurrentTag = tag;
     }
@@ -389,7 +373,7 @@ bool cmCTest::UpdateCTestConfiguration()
     }
   if ( !cmSystemTools::FileExists(fileName.c_str()) )
     {
-    std::cerr << "Cannot find file: " << fileName.c_str() << std::endl;
+    cmCTestLog(this, ERROR, "Cannot find file: " << fileName.c_str() << std::endl);
     return false;
     }
   // parse the dart test file
@@ -501,7 +485,7 @@ bool cmCTest::SetTest(const char* ttype, bool report)
     {
     if ( report )
       {
-      std::cerr << "Don't know about test \"" << ttype << "\" yet..." << std::endl;
+      cmCTestLog(this, ERROR, "Don't know about test \"" << ttype << "\" yet..." << std::endl);
       }
     return false;
     }
@@ -527,26 +511,26 @@ bool cmCTest::OpenOutputFile(const std::string& path,
     {
     if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
       {
-      std::cerr << "File " << testingDir 
+      cmCTestLog(this, ERROR, "File " << testingDir 
                 << " is in the place of the testing directory"
-                << std::endl;
+                << std::endl);
       return false;
       }
     }
   else
     {
     if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
       {
-      std::cerr << "Cannot create directory " << testingDir
-                << std::endl;
+      cmCTestLog(this, ERROR, "Cannot create directory " << testingDir
+                << std::endl);
       return false;
       }
     }
   std::string filename = testingDir + "/" + name;
   stream.Open(filename.c_str());
   if( !stream )
     {
-    std::cerr << "Problem opening file: " << filename << std::endl;
+    cmCTestLog(this, ERROR, "Problem opening file: " << filename << std::endl);
     return false;
     }
   if ( compress )
@@ -751,7 +735,7 @@ int cmCTest::GetTestModelFromString(const char* str)
 }
 
 int cmCTest::RunMakeCommand(const char* command, std::string* output,
-  int* retVal, const char* dir, bool verbose, int timeout, std::ofstream& ofs)
+  int* retVal, const char* dir, int timeout, std::ofstream& ofs)
 {
   std::vector<cmStdString> args = cmSystemTools::ParseArguments(command);
 
@@ -786,11 +770,8 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
 
   char* data;
   int length;
-  if ( !verbose )
-    {
-    std::cout << "   Each . represents " << tick_len << " bytes of output" << std::endl;
-    std::cout << "    " << std::flush;
-    }
+  cmCTestLog(this, HANDLER_OUTPUT, "   Each . represents " << tick_len << " bytes of output" << std::endl
+    << "    " << std::flush);
   while(cmsysProcess_WaitForData(cp, &data, &length, 0))
     {
     if ( output )
@@ -804,34 +785,26 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
         }
 
       output->append(data, length);
-      if ( !verbose )
+      while ( output->size() > (tick * tick_len) )
         {
-        while ( output->size() > (tick * tick_len) )
+        tick ++;
+        cmCTestLog(this, HANDLER_OUTPUT, "." << std::flush);
+        if ( tick % tick_line_len == 0 && tick > 0 )
           {
-          tick ++;
-          std::cout << "." << std::flush;
-          if ( tick % tick_line_len == 0 && tick > 0 )
-            {
-            std::cout << "  Size: ";
-            std::cout << int((output->size() / 1024.0) + 1) << "K" << std::endl;
-            std::cout << "    " << std::flush;
-            }
+          cmCTestLog(this, HANDLER_OUTPUT, "  Size: "
+            << int((output->size() / 1024.0) + 1) << "K" << std::endl
+            << "    " << std::flush);
           }
         }
       }
-    if(verbose)
-      {
-      std::cout.write(data, length);
-      std::cout.flush();
-      }
+    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, cmCTestLogWrite(data, length));
     if ( ofs )
       {
-      ofs.write(data, length);
-      ofs.flush();
+      ofs << cmCTestLogWrite(data, length);
       }
     }
-  std::cout << " Size of output: ";
-  std::cout << int(output->size() / 1024.0) << "K" << std::endl;
+  cmCTestLog(this, OUTPUT, " Size of output: "
+    << int(output->size() / 1024.0) << "K" << std::endl);
 
   cmsysProcess_WaitForExit(cp, 0);
 
@@ -844,11 +817,11 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
   else if(result == cmsysProcess_State_Exception)
     {
     *retVal = cmsysProcess_GetExitException(cp);
-    std::cout << "There was an exception: " << *retVal << std::endl;
+    cmCTestLog(this, WARNING, "There was an exception: " << *retVal << std::endl);
     }
   else if(result == cmsysProcess_State_Expired)
     {
-    std::cout << "There was a timeout" << std::endl;
+    cmCTestLog(this, WARNING, "There was a timeout" << std::endl);
     } 
   else if(result == cmsysProcess_State_Error)
     {
@@ -892,11 +865,8 @@ int cmCTest::RunTest(std::vector<const char*> argv,
       }
     cmSystemTools::ChangeDirectory(oldpath.c_str());
     
-    if(m_ExtraVerbose)
-      {
-      std::cout << "Internal cmCTest object used to run test.\n";
-      std::cout <<  *output << "\n";
-      }
+    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, "Internal cmCTest object used to run test." << std::endl
+      <<  *output << std::endl);
     return cmsysProcess_State_Exited;
     }
   std::vector<char> tempOutput;
@@ -907,7 +877,7 @@ int cmCTest::RunTest(std::vector<const char*> argv,
 
   cmsysProcess* cp = cmsysProcess_New();
   cmsysProcess_SetCommand(cp, &*argv.begin());
-  //  std::cout << "Command is: " << argv[0] << std::endl;
+  cmCTestLog(this, DEBUG, "Command is: " << argv[0] << std::endl);
   if(cmSystemTools::GetRunCommandHideConsole())
     {
     cmsysProcess_SetOption(cp, cmsysProcess_Option_HideWindow, 1);
@@ -923,15 +893,10 @@ int cmCTest::RunTest(std::vector<const char*> argv,
       {
       tempOutput.insert(tempOutput.end(), data, data+length);
       }
-    if ( m_ExtraVerbose )
-      {
-      std::cout.write(data, length);
-      std::cout.flush();
-      }
+    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, cmCTestLogWrite(data, length));
     if ( log )
       {
       log->write(data, length);
-      log->flush();
       }
     }
 
@@ -940,10 +905,7 @@ int cmCTest::RunTest(std::vector<const char*> argv,
     {
     output->append(&*tempOutput.begin(), tempOutput.size());
     }
-  if ( m_ExtraVerbose )
-    {
-    std::cout << "-- Process completed" << std::endl;
-    }
+  cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, "-- Process completed" << std::endl);
 
   int result = cmsysProcess_GetState(cp);
 
@@ -957,22 +919,14 @@ int cmCTest::RunTest(std::vector<const char*> argv,
     std::string outerr = "\n*** Exception executing: ";
     outerr += cmsysProcess_GetExceptionString(cp);
     *output += outerr;
-    if ( m_ExtraVerbose )
-      {
-      std::cout << outerr.c_str() << "\n";
-      std::cout.flush();
-      }
+    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, outerr.c_str() << std::endl << std::flush);
     }
   else if(result == cmsysProcess_State_Error)
     {
     std::string outerr = "\n*** ERROR executing: ";
     outerr += cmsysProcess_GetErrorString(cp);
     *output += outerr;
-    if ( m_ExtraVerbose )
-      {
-      std::cout << outerr.c_str() << "\n";
-      std::cout.flush();
-      }
+    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, outerr.c_str() << std::endl << std::flush);
     }
   cmsysProcess_Delete(cp);
 
@@ -1009,7 +963,7 @@ int cmCTest::GenerateCTestNotesOutput(std::ostream& os, const cmCTest::tm_Vector
 
   for ( it = files.begin(); it != files.end(); it ++ )
     {
-    std::cout << "\tAdd file: " << it->c_str() << std::endl;
+    cmCTestLog(this, OUTPUT, "\tAdd file: " << it->c_str() << std::endl);
     std::string note_time = this->CurrentTime();
     os << "<Note Name=\"" << this->MakeXMLSafe(it->c_str()) << "\">\n"
       << "<DateTime>" << note_time << "</DateTime>\n"
@@ -1027,7 +981,7 @@ int cmCTest::GenerateCTestNotesOutput(std::ostream& os, const cmCTest::tm_Vector
     else
       {
       os << "Problem reading file: " << it->c_str() << std::endl;
-      std::cerr << "Problem reading file: " << it->c_str() << " while creating notes" << std::endl;
+      cmCTestLog(this, ERROR, "Problem reading file: " << it->c_str() << " while creating notes" << std::endl);
       }
     os << "</Text>\n"
       << "</Note>" << std::endl;
@@ -1042,7 +996,7 @@ int cmCTest::GenerateNotesFile(const std::vector<cmStdString> &files)
   cmGeneratedFileStream ofs;
   if ( !this->OpenOutputFile(m_CurrentTag, "Notes.xml", ofs) )
     {
-    std::cerr << "Cannot open notes file" << std::endl;
+    cmCTestLog(this, ERROR, "Cannot open notes file" << std::endl);
     return 1;
     }
 
@@ -1059,7 +1013,7 @@ int cmCTest::GenerateNotesFile(const char* cfiles)
 
   std::vector<cmStdString> files;
 
-  std::cout << "Create notes file" << std::endl;
+  cmCTestLog(this, OUTPUT, "Create notes file" << std::endl);
 
   files = cmSystemTools::SplitString(cfiles, ';');
   if ( files.size() == 0 )
@@ -1092,6 +1046,10 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       cmSystemTools::ReplaceString(this->m_ConfigType, ".\\", "");
       }
 
+    if( arg.find("-Q",0) == 0 || arg.find("--quiet",0) == 0 )
+      {
+      this->m_Quiet = true;
+      }
     if( arg.find("-V",0) == 0 || arg.find("--verbose",0) == 0 )
       {
       this->m_Verbose = true;
@@ -1115,6 +1073,12 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       ch->AddConfigurationScript(args[i].c_str());
       }
 
+    if( ( arg.find("-O",0) == 0 || arg.find("--output-log") == 0 ) && i < args.size() - 1 )
+      {
+      i++;
+      this->SetOutputLogFileName(args[i].c_str());
+      }
+
     if( arg.find("--tomorrow-tag",0) == 0 )
       {
       m_TomorrowTag = true;
@@ -1312,8 +1276,8 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       else
         {
         performSomeTest = false;
-        std::cerr << "CTest -D called with incorrect option: " << targ << std::endl;
-        std::cerr << "Available options are:" << std::endl
+        cmCTestLog(this, ERROR, "CTest -D called with incorrect option: " << targ << std::endl);
+        cmCTestLog(this, ERROR, "Available options are:" << std::endl
           << "  " << ctestExec << " -D Continuous" << std::endl
           << "  " << ctestExec << " -D Continuous(Start|Update|Configure|Build)" << std::endl
           << "  " << ctestExec << " -D Continuous(Test|Coverage|MemCheck|Submit)" << std::endl
@@ -1323,8 +1287,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
           << "  " << ctestExec << " -D Nightly" << std::endl
           << "  " << ctestExec << " -D Nightly(Start|Update|Configure|Build)" << std::endl
           << "  " << ctestExec << " -D Nightly(Test|Coverage|MemCheck|Submit)" << std::endl
-          << "  " << ctestExec << " -D NightlyMemoryCheck" << std::endl;
-          ;
+          << "  " << ctestExec << " -D NightlyMemoryCheck" << std::endl);
         }
       }
 
@@ -1336,8 +1299,8 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       if ( !this->SetTest(args[i].c_str(), false) )
         {
         performSomeTest = false;
-        std::cerr << "CTest -T called with incorrect option: " << args[i].c_str() << std::endl;
-        std::cerr << "Available options are:" << std::endl
+        cmCTestLog(this, ERROR, "CTest -T called with incorrect option: " << args[i].c_str() << std::endl);
+        cmCTestLog(this, ERROR, "Available options are:" << std::endl
           << "  " << ctestExec << " -T all" << std::endl
           << "  " << ctestExec << " -T start" << std::endl
           << "  " << ctestExec << " -T update" << std::endl
@@ -1347,7 +1310,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
           << "  " << ctestExec << " -T coverage" << std::endl
           << "  " << ctestExec << " -T memcheck" << std::endl
           << "  " << ctestExec << " -T notes" << std::endl
-          << "  " << ctestExec << " -T submit" << std::endl;
+          << "  " << ctestExec << " -T submit" << std::endl);
         }
       }
 
@@ -1371,11 +1334,11 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       else
         {
         performSomeTest = false;
-        std::cerr << "CTest -M called with incorrect option: " << str.c_str() << std::endl;
-        std::cerr << "Available options are:" << std::endl
+        cmCTestLog(this, ERROR, "CTest -M called with incorrect option: " << str.c_str() << std::endl);
+        cmCTestLog(this, ERROR, "Available options are:" << std::endl
           << "  " << ctestExec << " -M Continuous" << std::endl
           << "  " << ctestExec << " -M Experimental" << std::endl
-          << "  " << ctestExec << " -M Nightly" << std::endl;
+          << "  " << ctestExec << " -M Nightly" << std::endl);
         }
       }
 
@@ -1425,7 +1388,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         }
       else
         {
-        std::cerr << "--build-and-test must have source and binary dir\n";
+        cmCTestLog(this, ERROR, "--build-and-test must have source and binary dir" << std::endl);
         }
       }
     if(arg.find("--build-target",0) == 0 && i < args.size() - 1)
@@ -1530,6 +1493,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
     else
       {
       m_ExtraVerbose = m_Verbose;
+      m_Verbose = true;
       cmCTest::t_TestingHandlers::iterator it;
       for ( it = m_TestingHandlers.begin(); it != m_TestingHandlers.end(); ++ it )
         {
@@ -1666,7 +1630,7 @@ int cmCTest::RunCMake(std::string* outstring, cmOStringStream &out,
       }
     else
       {
-      std::cerr << out.str() << "\n";
+      cmCTestLog(this, ERROR, out.str() << std::endl);
       }
     return 1;
     }
@@ -1685,7 +1649,7 @@ int cmCTest::RunCMake(std::string* outstring, cmOStringStream &out,
         }
       else
         {
-        std::cerr << out.str() << "\n";
+        cmCTestLog(this, ERROR, out.str() << std::endl);
         }
       return 1;
       }
@@ -1874,7 +1838,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
       }
     else
       {
-      std::cerr << out.str();
+      cmCTestLog(this, ERROR, out.str());
       }
     // return to the original directory
     cmSystemTools::ChangeDirectory(cwd.c_str());
@@ -1917,7 +1881,7 @@ int cmCTest::RunCMakeAndTest(std::string* outstring)
     }
   else
     {
-    std::cout << out.str() << "\n";
+    cmCTestLog(this, OUTPUT, out.str() << std::endl);
     }
   return retval;
 }
@@ -1952,7 +1916,7 @@ int cmCTest::ReadCustomConfigurationFileTree(const char* dir)
       (!lg->GetMakefile()->ReadListFile(0, fname.c_str()) ||
        cmSystemTools::GetErrorOccuredFlag() ) )
       {
-      std::cerr << "Problem reading custom configuration" << std::endl;
+      cmCTestLog(this, ERROR, "Problem reading custom configuration" << std::endl);
       }
     dirs.erase(dirs.end()-1, dirs.end());
     cmSystemTools::SimpleGlob(rexpr, ndirs, -1);
@@ -2117,3 +2081,109 @@ bool cmCTest::SetCTestConfigurationFromCMakeVariable(cmMakefile* mf, const char*
   this->SetCTestConfiguration(dconfig, ctvar);
   return true;
 }
+
+void cmCTest::SetOutputLogFileName(const char* name)
+{
+  if ( m_OutputLogFile)
+    {
+    delete m_OutputLogFile;
+    m_OutputLogFile= 0;
+    }
+  if ( name )
+    {
+    m_OutputLogFile = new cmGeneratedFileStream(name);
+    }
+}
+
+static const char* cmCTestStringLogType[] = 
+{
+  "DEBUG",
+  "OUTPUT",
+  "HANDLER_OUTPUT",
+  "HANDLER_VERBOSE_OUTPUT",
+  "WARNING",
+  "ERROR",
+  0
+};
+
+#ifdef cerr
+#  undef cerr
+#endif
+#ifdef cout
+#  undef cout
+#endif
+
+void cmCTest::Log(int logType, const char* msg)
+{
+  if ( !msg || !*msg )
+    {
+    return;
+    }
+  if ( m_OutputLogFile )
+    {
+    bool display = true;
+    if ( logType == cmCTest::DEBUG && !m_Debug ) { display = false; }
+    if ( logType == cmCTest::HANDLER_VERBOSE_OUTPUT && !m_Debug && !m_ExtraVerbose ) { display = false; }
+    if ( display )
+      {
+      if ( logType != m_OutputLogFileLastTag )
+        {
+        *m_OutputLogFile << "[";
+        if ( logType >= OTHER || logType < 0 )
+          {
+          *m_OutputLogFile << "OTHER";
+          }
+        else
+          {
+          *m_OutputLogFile << cmCTestStringLogType[logType];
+          }
+        *m_OutputLogFile << "] " << std::endl << std::flush;
+        }
+      *m_OutputLogFile << msg << std::flush;
+      if ( logType != m_OutputLogFileLastTag )
+        {
+        *m_OutputLogFile << std::endl << std::flush;
+        m_OutputLogFileLastTag = logType;
+        }
+      }
+    }
+  if ( !m_Quiet )
+    {
+    switch ( logType )
+      {
+    case DEBUG:
+      if ( m_Debug )
+        {
+        std::cout << msg;
+        std::cout.flush();
+        }
+      break;
+    case OUTPUT: case HANDLER_OUTPUT:
+      if ( m_Debug || m_Verbose )
+        {
+        std::cout << msg;
+        std::cout.flush();
+        }
+      break;
+    case HANDLER_VERBOSE_OUTPUT:
+      if ( m_Debug || m_ExtraVerbose )
+        {
+        std::cout << msg;
+        std::cout.flush();
+        }
+      break;
+    case WARNING:
+      std::cerr << msg;
+      std::cerr.flush();
+      break;
+    case ERROR:
+      std::cerr << msg;
+      std::cerr.flush();
+      break;
+    default:
+      std::cout << msg;
+      std::cout.flush();
+      }
+    }
+}
+