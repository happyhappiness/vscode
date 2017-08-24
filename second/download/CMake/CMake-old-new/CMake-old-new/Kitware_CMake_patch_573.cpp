@@ -362,7 +362,7 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag, bool verbose_tag)
       cmCTestLog(this, DEBUG, "TestModel: " << m_TestModel << std::endl);
       if ( m_TestModel == cmCTest::NIGHTLY )
         {
-        lctime = this->GetNightlyTime(m_CTestConfiguration["NightlyStartTime"], m_TomorrowTag);
+        lctime = this->GetNightlyTime(this->GetCTestConfiguration("NightlyStartTime"), m_TomorrowTag);
         }
       char datestring[100];
       sprintf(datestring, "%04d%02d%02d-%02d%02d",
@@ -525,10 +525,10 @@ bool cmCTest::UpdateCTestConfiguration()
       }
     fin.close();
     }
+  m_TimeOut = atoi(this->GetCTestConfiguration("TimeOut").c_str());
   if ( m_ProduceXML )
     {
-    m_TimeOut = atoi(m_CTestConfiguration["TimeOut"].c_str());
-    m_CompressXMLFiles = cmSystemTools::IsOn(m_CTestConfiguration["CompressSubmission"].c_str());
+    m_CompressXMLFiles = cmSystemTools::IsOn(this->GetCTestConfiguration("CompressSubmission").c_str());
     }
   return true;
 }
@@ -1095,10 +1095,10 @@ int cmCTest::RunTest(std::vector<const char*> argv,
 void cmCTest::StartXML(std::ostream& ostr)
 {
   ostr << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
-    << "<Site BuildName=\"" << m_CTestConfiguration["BuildName"]
+    << "<Site BuildName=\"" << this->GetCTestConfiguration("BuildName")
     << "\" BuildStamp=\"" << m_CurrentTag << "-"
     << this->GetTestModelString() << "\" Name=\""
-    << m_CTestConfiguration["Site"] << "\" Generator=\"ctest"
+    << this->GetCTestConfiguration("Site") << "\" Generator=\"ctest"
     << cmVersion::GetCMakeVersion()
     << "\">" << std::endl;
 }
@@ -1115,9 +1115,9 @@ int cmCTest::GenerateCTestNotesOutput(std::ostream& os, const cmCTest::tm_Vector
   cmCTest::tm_VectorOfStrings::const_iterator it;
   os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
     << "<?xml-stylesheet type=\"text/xsl\" href=\"Dart/Source/Server/XSL/Build.xsl <file:///Dart/Source/Server/XSL/Build.xsl> \"?>\n"
-    << "<Site BuildName=\"" << m_CTestConfiguration["BuildName"] << "\" BuildStamp=\"" 
+    << "<Site BuildName=\"" << this->GetCTestConfiguration("BuildName") << "\" BuildStamp=\"" 
     << m_CurrentTag << "-" << this->GetTestModelString() << "\" Name=\"" 
-    << m_CTestConfiguration["Site"] << "\" Generator=\"ctest"
+    << this->GetCTestConfiguration("Site") << "\" Generator=\"ctest"
     << cmVersion::GetCMakeVersion()
     << "\">\n"
     << "<Notes>" << std::endl;
@@ -1188,6 +1188,43 @@ int cmCTest::GenerateNotesFile(const char* cfiles)
 }
 
 //----------------------------------------------------------------------
+bool cmCTest::CheckArgument(const std::string& arg, const char* varg1, const char* varg2 = 0)
+{
+  cmOStringStream ostr;
+  ostr << varg1;
+  if ( varg2 )
+    {
+    ostr << ", " << varg2;
+    }
+
+  size_t minlen = arg.size();
+  size_t lenvarg = strlen(varg1);
+  if ( lenvarg < minlen )
+    {
+    minlen = lenvarg;
+    }
+  if ( strncmp(arg.c_str(), varg1, minlen) == 0 )
+    {
+    return true;
+    }
+  if ( ! varg2 )
+    {
+    return false;
+    }
+  minlen = arg.size();
+  lenvarg = strlen(varg2);
+  if ( lenvarg < minlen )
+    {
+    minlen = lenvarg;
+    }
+  if ( strncmp(arg.c_str(), varg2, minlen) == 0 )
+    {
+    return true;
+    }
+  return false;
+}
+
+//----------------------------------------------------------------------
 int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
 {
   this->FindRunningCMake(args[0].c_str());
@@ -1197,74 +1234,83 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
   for(size_t i=1; i < args.size(); ++i)
     {
     std::string arg = args[i];
-    if(arg.find("--ctest-config",0) == 0 && i < args.size() - 1)
+    if(this->CheckArgument(arg, "--ctest-config") && i < args.size() - 1)
       {
       i++;
       this->m_CTestConfigFile= args[i];
       }
 
-    if(arg.find("-C",0) == 0 && i < args.size() - 1)
+    if(this->CheckArgument(arg, "-C", "--build-config") && i < args.size() - 1)
       {
       i++;
       this->m_ConfigType = args[i];
       cmSystemTools::ReplaceString(this->m_ConfigType, ".\\", "");
       }
 
-    if( arg.find("--debug",0) == 0 )
+    if(this->CheckArgument(arg, "--debug"))
       {
       this->m_Debug = true;
       }
-    if( arg.find("--show-line-numbers",0) == 0 )
+    if(this->CheckArgument(arg, "--show-line-numbers"))
       {
       this->m_ShowLineNumbers = true;
       }
-    if( arg.find("-Q",0) == 0 || arg.find("--quiet",0) == 0 )
+    if(this->CheckArgument(arg, "-Q", "--quiet"))
       {
       this->m_Quiet = true;
       }
-    if( arg.find("-V",0) == 0 || arg.find("--verbose",0) == 0 )
+    if(this->CheckArgument(arg, "-V", "--verbose"))
       {
       this->m_Verbose = true;
       }
-    if( arg.find("-VV",0) == 0 || arg.find("--extra-verbose",0) == 0 )
+    if(this->CheckArgument(arg, "-VV", "--extra-verbose"))
       {
       this->m_ExtraVerbose = true;
       this->m_Verbose = true;
       }
 
-    if( arg.find("-N",0) == 0 || arg.find("--show-only",0) == 0 )
+    if(this->CheckArgument(arg, "-N", "--show-only"))
       {
       this->m_ShowOnly = true;
       }
 
-    if( arg.find("-S",0) == 0 && i < args.size() - 1 )
+    if(this->CheckArgument(arg, "-S", "--script") && i < args.size() - 1 )
       {
       this->m_RunConfigurationScript = true;
       i++;
       cmCTestScriptHandler* ch = static_cast<cmCTestScriptHandler*>(this->GetHandler("script"));
       ch->AddConfigurationScript(args[i].c_str());
       }
 
-    if( ( arg.find("-O",0) == 0 || arg.find("--output-log") == 0 ) && i < args.size() - 1 )
+    if(this->CheckArgument(arg, "-O", "--output-log") && i < args.size() - 1 )
       {
       i++;
       this->SetOutputLogFileName(args[i].c_str());
       }
 
-    if( arg.find("--tomorrow-tag",0) == 0 )
+    if(this->CheckArgument(arg, "--tomorrow-tag"))
       {
       m_TomorrowTag = true;
       }
-    if( arg.find("--force-new-ctest-process",0) == 0 )
+    if(this->CheckArgument(arg, "--force-new-ctest-process"))
       {
       m_ForceNewCTestProcess = true;
       }
-    if( arg.find("--interactive-debug-mode",0) == 0 && i < args.size() - 1 )
+    if(this->CheckArgument(arg, "--interactive-debug-mode") && i < args.size() - 1 )
       {
       i++;
       m_InteractiveDebugMode = cmSystemTools::IsOn(args[i].c_str());
       }
-    if( arg.find("-D",0) == 0 && i < args.size() - 1 )
+    if(this->CheckArgument(arg, "--submit-index") && i < args.size() - 1 )
+      {
+      i++;
+      m_SubmitIndex = atoi(args[i].c_str());
+      if ( m_SubmitIndex < 0 )
+        {
+        m_SubmitIndex = 0;
+        }
+      }
+    if(this->CheckArgument(arg, "-D", "--dashboard") && i < args.size() - 1 )
       {
       this->m_ProduceXML = true;
       i++;
@@ -1463,15 +1509,15 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         }
       }
 
-    if( ( arg.find("-T",0) == 0 ) && 
-      (i < args.size() -1) )
+    if(this->CheckArgument(arg, "-T", "--test-action") && (i < args.size() -1) )
       {
       this->m_ProduceXML = true;
       i++;
       if ( !this->SetTest(args[i].c_str(), false) )
         {
         performSomeTest = false;
-        cmCTestLog(this, ERROR_MESSAGE, "CTest -T called with incorrect option: " << args[i].c_str() << std::endl);
+        cmCTestLog(this, ERROR_MESSAGE, "CTest -T called with incorrect option: "
+          << args[i].c_str() << std::endl);
         cmCTestLog(this, ERROR_MESSAGE, "Available options are:" << std::endl
           << "  " << ctestExec << " -T all" << std::endl
           << "  " << ctestExec << " -T start" << std::endl
@@ -1486,8 +1532,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         }
       }
 
-    if( ( arg.find("-M",0) == 0 || arg.find("--test-model",0) == 0 ) &&
-      (i < args.size() -1) )
+    if(this->CheckArgument(arg, "-M", "--test-model") && (i < args.size() -1) )
       {
       i++;
       std::string const& str = args[i];
@@ -1514,36 +1559,41 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
         }
       }
 
-    if(arg.find("-I",0) == 0 && i < args.size() - 1)
+    if(this->CheckArgument(arg, "-I", "--tests-information") && i < args.size() - 1)
       {
       i++;
       this->GetHandler("test")->SetOption("TestsToRunInformation", args[i].c_str());
       }                                                       
-    if(arg.find("-U",0) == 0)                                 
+    if(this->CheckArgument(arg, "-U", "--union"))
       {                                                       
       this->GetHandler("test")->SetOption("UseUnion", "true");
       }                                                       
-    if(arg.find("-R",0) == 0 && i < args.size() - 1)          
+    if(this->CheckArgument(arg, "-R", "--tests-regex") && i < args.size() - 1)          
       {                                                       
       i++;                                                    
       this->GetHandler("test")->SetOption("IncludeRegularExpression", args[i].c_str());
       }                                                       
 
-    if(arg.find("-E",0) == 0 && i < args.size() - 1)          
+    if(this->CheckArgument(arg, "-E", "--exclude-regex") && i < args.size() - 1)          
       {                                                       
       i++;
       this->GetHandler("test")->SetOption("ExcludeRegularExpression", args[i].c_str());
       }
 
-    if(arg.find("-A",0) == 0 && i < args.size() - 1)
+    if(this->CheckArgument(arg, "--overwrite") && i < args.size() - 1)
+      {
+      i++;
+      this->AddCTestConfigurationOverwrite(args[i].c_str());
+      }
+    if(this->CheckArgument(arg, "-A", "--add-notes") && i < args.size() - 1)
       {
       this->m_ProduceXML = true;
       this->SetTest("Notes");
       i++;
       this->SetNotesFiles(args[i].c_str());
       }
     // --build-and-test options
-    if(arg.find("--build-and-test",0) == 0 && i < args.size() - 1)
+    if(this->CheckArgument(arg, "--build-and-test") && i < args.size() - 1)
       {
       cmakeAndTest = true;
       }
@@ -1566,7 +1616,6 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
 #endif
     }
 
-
   if(cmakeAndTest)
     {
     m_Verbose = true;
@@ -1597,6 +1646,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       for ( it = m_TestingHandlers.begin(); it != m_TestingHandlers.end(); ++ it )
         {
         it->second->SetVerbose(this->m_ExtraVerbose);
+        it->second->SetSubmitIndex(m_SubmitIndex);
         }
       this->GetHandler("script")->SetVerbose(m_Verbose);
       res = this->GetHandler("script")->ProcessHandler();
@@ -1609,6 +1659,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       for ( it = m_TestingHandlers.begin(); it != m_TestingHandlers.end(); ++ it )
         {
         it->second->SetVerbose(this->m_Verbose);
+        it->second->SetSubmitIndex(m_SubmitIndex);
         }
       if ( !this->Initialize(cmSystemTools::GetCurrentWorkingDirectory().c_str()) )
         {
@@ -1836,6 +1887,10 @@ std::string cmCTest::GetShortPathToFile(const char* cfname)
 //----------------------------------------------------------------------
 std::string cmCTest::GetCTestConfiguration(const char *name)
 {
+  if ( m_CTestConfigurationOverwrites.find(name) != m_CTestConfigurationOverwrites.end() )
+    {
+    return m_CTestConfigurationOverwrites[name];
+    }
   return m_CTestConfiguration[name];
 }
 
@@ -1904,6 +1959,24 @@ void cmCTest::AddSubmitFile(const char* name)
 }
 
 //----------------------------------------------------------------------
+void cmCTest::AddCTestConfigurationOverwrite(const char* encstr)
+{
+  std::string overStr = encstr;
+  size_t epos = overStr.find("=");
+  if ( epos == overStr.npos )
+    {
+    cmCTestLog(this, ERROR_MESSAGE,
+      "CTest configuration overwrite specified in the wrong format." << std::endl
+      << "Valid format is: --overwrite key=value" << std::endl
+      << "The specified was: --overwrite " << overStr.c_str() << std::endl);
+    return;
+    }
+  std::string key = overStr.substr(0, epos);
+  std::string value = overStr.substr(epos+1, overStr.npos);
+  m_CTestConfigurationOverwrites[key] = value;
+}
+
+//----------------------------------------------------------------------
 bool cmCTest::SetCTestConfigurationFromCMakeVariable(cmMakefile* mf, const char* dconfig, const char* cmake_var)
 {
   const char* ctvar;