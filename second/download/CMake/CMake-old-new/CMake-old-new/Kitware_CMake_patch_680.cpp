@@ -304,6 +304,7 @@ bool TryExecutable(const char *dir, const char *file,
 
 cmCTest::cmCTest() 
 { 
+  m_BuildTwoConfig         = false;
   m_UseIncludeRegExp       = false;
   m_UseExcludeRegExp       = false;
   m_UseExcludeRegExpFirst  = false;
@@ -1961,7 +1962,7 @@ void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed,
             }
           else if ( res == cmsysProcess_State_Error )
             {
-            fprintf(stderr,"***Bad command\n");
+            fprintf(stderr,"***Bad command %d\n", res);
             cres.m_Status = cmCTest::BAD_COMMAND;
             }
           else
@@ -2818,6 +2819,27 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
 
 int cmCTest::RunTest(std::vector<const char*> argv, std::string* output, int *retVal)
 {
+  std::string cmd = argv[0];
+  if(cmSystemTools::SameFile(argv[0], m_CTestSelf.c_str()))
+    {
+    cmCTest inst;
+    std::vector<std::string> args;
+    for(int i =0; i < argv.size(); ++i)
+      {
+      if(argv[i])
+        {
+        args.push_back(argv[i]);
+        }
+      }
+    *retVal = inst.Run(args, output);
+    if(m_Verbose)
+      {
+      std::cout << "Internal cmCTest object used to run test.\n";
+      std::cout <<  *output << "\n";
+      }
+    return cmsysProcess_State_Exited;
+    }
+  
   std::vector<char> tempOutput;
   if ( output )
     {
@@ -2826,7 +2848,7 @@ int cmCTest::RunTest(std::vector<const char*> argv, std::string* output, int *re
 
   cmsysProcess* cp = cmsysProcess_New();
   cmsysProcess_SetCommand(cp, &*argv.begin());
-  //std::cout << "Command is: " << argv[0] << std::endl;
+//  std::cout << "Command is: " << argv[0] << std::endl;
   if(cmSystemTools::GetRunCommandHideConsole())
     {
     cmsysProcess_SetOption(cp, cmsysProcess_Option_HideWindow, 1);
@@ -2876,7 +2898,6 @@ int cmCTest::RunTest(std::vector<const char*> argv, std::string* output, int *re
       std::cout.flush();
       }
     }
-  
   cmsysProcess_Delete(cp);
   
   return result;
@@ -3396,6 +3417,756 @@ int cmCTest::GenerateNotesFile(const char* cfiles)
   return 0;
 }
 
+int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
+{
+  this->FindRunningCMake(args[0].c_str());
+  bool cmakeAndTest = false;
+  for(unsigned int i=1; i < args.size(); ++i)
+    {
+    std::string arg = args[i];
+    if(arg.find("-C",0) == 0 && i < args.size() - 1)
+      {
+      i++;
+      this->m_ConfigType = args[i];
+      }
+
+    if( arg.find("-V",0) == 0 || arg.find("--verbose",0) == 0 )
+      {
+      this->m_Verbose = true;
+      }
+
+    if( arg.find("-N",0) == 0 || arg.find("--show-only",0) == 0 )
+      {
+      this->m_ShowOnly = true;
+      }
+
+    if( arg.find("-S",0) == 0 && i < args.size() - 1 )
+      {
+      this->m_RunConfigurationScript = true;
+      i++;
+      this->m_ConfigurationScript = args[i];
+      }
+    
+    if( arg.find("-D",0) == 0 && i < args.size() - 1 )
+      {
+      this->m_DartMode = true;
+      i++;
+      std::string targ = args[i];
+      if ( targ == "Experimental" )
+        {
+        this->SetTestModel(cmCTest::EXPERIMENTAL);
+        this->SetTest("Start");
+        this->SetTest("Configure");
+        this->SetTest("Build");
+        this->SetTest("Test");
+        this->SetTest("Coverage");
+        this->SetTest("Submit");
+        }
+      else if ( targ == "ExperimentalStart" )
+        {
+        this->SetTestModel(cmCTest::EXPERIMENTAL);
+        this->SetTest("Start");
+        }
+      else if ( targ == "ExperimentalUpdate" )
+        {
+        this->SetTestModel(cmCTest::EXPERIMENTAL);
+        this->SetTest("Update");
+        }
+      else if ( targ == "ExperimentalConfigure" )
+        {
+        this->SetTestModel(cmCTest::EXPERIMENTAL);
+        this->SetTest("Configure");
+        }
+      else if ( targ == "ExperimentalBuild" )
+        {
+        this->SetTestModel(cmCTest::EXPERIMENTAL);
+        this->SetTest("Build");
+        }
+      else if ( targ == "ExperimentalTest" )
+        {
+        this->SetTestModel(cmCTest::EXPERIMENTAL);
+        this->SetTest("Test");
+        }
+      else if ( targ == "ExperimentalMemCheck" || targ == "ExperimentalPurify" )
+        {
+        this->SetTestModel(cmCTest::EXPERIMENTAL);
+        this->SetTest("MemCheck");
+        }
+      else if ( targ == "ExperimentalCoverage" )
+        {
+        this->SetTestModel(cmCTest::EXPERIMENTAL);
+        this->SetTest("Coverage");
+        }
+      else if ( targ == "ExperimentalSubmit" )
+        {
+        this->SetTestModel(cmCTest::EXPERIMENTAL);
+        this->SetTest("Submit");
+        }
+      else if ( targ == "Continuous" )
+        {
+        this->SetTestModel(cmCTest::CONTINUOUS);
+        this->SetTest("Start");
+        this->SetTest("Update");
+        this->SetTest("Configure");
+        this->SetTest("Build");
+        this->SetTest("Test");
+        this->SetTest("Coverage");
+        this->SetTest("Submit");
+        }
+      else if ( targ == "ContinuousStart" )
+        {
+        this->SetTestModel(cmCTest::CONTINUOUS);
+        this->SetTest("Start");
+        }
+      else if ( targ == "ContinuousUpdate" )
+        {
+        this->SetTestModel(cmCTest::CONTINUOUS);
+        this->SetTest("Update");
+        }  
+      else if ( targ == "ContinuousConfigure" )
+        {
+        this->SetTestModel(cmCTest::CONTINUOUS);
+        this->SetTest("Configure");
+        }
+      else if ( targ == "ContinuousBuild" )
+        {
+        this->SetTestModel(cmCTest::CONTINUOUS);
+        this->SetTest("Build");
+        }
+      else if ( targ == "ContinuousTest" )
+        {
+        this->SetTestModel(cmCTest::CONTINUOUS);
+        this->SetTest("Test");
+        }
+      else if ( targ == "ContinuousMemCheck" || targ == "ContinuousPurify" )
+        {
+        this->SetTestModel(cmCTest::CONTINUOUS);
+        this->SetTest("MemCheck");
+        }
+      else if ( targ == "ContinuousCoverage" )
+        {
+        this->SetTestModel(cmCTest::CONTINUOUS);
+        this->SetTest("Coverage");
+        }
+      else if ( targ == "ContinuousSubmit" )
+        {
+        this->SetTestModel(cmCTest::CONTINUOUS);
+        this->SetTest("Submit");
+        }
+      else if ( targ == "Nightly" )
+        {
+        this->SetTestModel(cmCTest::NIGHTLY);
+        this->SetTest("Start");
+        this->SetTest("Update");
+        this->SetTest("Configure");
+        this->SetTest("Build");
+        this->SetTest("Test");
+        this->SetTest("Coverage");
+        this->SetTest("Submit");
+        }
+      else if ( targ == "NightlyStart" )
+        {
+        this->SetTestModel(cmCTest::NIGHTLY);
+        this->SetTest("Start");
+        }
+      else if ( targ == "NightlyUpdate" )
+        {
+        this->SetTestModel(cmCTest::NIGHTLY);
+        this->SetTest("Update");
+        }
+      else if ( targ == "NightlyConfigure" )
+        {
+        this->SetTestModel(cmCTest::NIGHTLY);
+        this->SetTest("Configure");
+        }
+      else if ( targ == "NightlyBuild" )
+        {
+        this->SetTestModel(cmCTest::NIGHTLY);
+        this->SetTest("Build");
+        }
+      else if ( targ == "NightlyTest" )
+        {
+        this->SetTestModel(cmCTest::NIGHTLY);
+        this->SetTest("Test");
+        }
+      else if ( targ == "NightlyMemCheck" || targ == "NightlyPurify" )
+        {
+        this->SetTestModel(cmCTest::NIGHTLY);
+        this->SetTest("MemCheck");
+        }
+      else if ( targ == "NightlyCoverage" )
+        {
+        this->SetTestModel(cmCTest::NIGHTLY);
+        this->SetTest("Coverage");
+        }
+      else if ( targ == "NightlySubmit" )
+        {
+        this->SetTestModel(cmCTest::NIGHTLY);
+        this->SetTest("Submit");
+        }
+      else if ( targ == "MemoryCheck" )
+        {
+        this->SetTestModel(cmCTest::EXPERIMENTAL);
+        this->SetTest("Start");
+        this->SetTest("Configure");
+        this->SetTest("Build");
+        this->SetTest("MemCheck");
+        this->SetTest("Coverage");
+        this->SetTest("Submit");
+        }
+      else if ( targ == "NightlyMemoryCheck" )
+        {
+        this->SetTestModel(cmCTest::NIGHTLY);
+        this->SetTest("Start");
+        this->SetTest("Update");
+        this->SetTest("Configure");
+        this->SetTest("Build");
+        this->SetTest("MemCheck");
+        this->SetTest("Coverage");
+        this->SetTest("Submit");
+        }
+      }
+
+    if( ( arg.find("-T",0) == 0 ) && 
+        (i < args.size() -1) )
+      {
+      this->m_DartMode = true;
+      i++;
+      this->SetTest(args[i].c_str());
+      }
+    
+    if( ( arg.find("-M",0) == 0 || arg.find("--test-model",0) == 0 ) &&
+        (i < args.size() -1) )
+      {
+      i++;
+      std::string const& str = args[i];
+      if ( str == "NIGHTLY" || str == "nightly" || str == "Nightly" )
+        {
+        this->SetTestModel(cmCTest::NIGHTLY);
+        }
+      else if ( str == "CONTINUOUS" || str == "continuous" || 
+                str == "Continuous" )
+        {
+        this->SetTestModel(cmCTest::CONTINUOUS);
+        std::cout << "Continuous" << std::endl;
+        }
+      else
+        {
+        this->SetTestModel(cmCTest::EXPERIMENTAL);
+        }
+      }
+    
+    if(arg.find("-R",0) == 0 && i < args.size() - 1)
+      {
+      this->m_UseIncludeRegExp = true;
+      i++;
+      this->m_IncludeRegExp  = args[i];
+      }
+
+    if(arg.find("-E",0) == 0 && i < args.size() - 1)
+      {
+      this->m_UseExcludeRegExp = true;
+      i++;
+      this->m_ExcludeRegExp  = args[i];
+      this->m_UseExcludeRegExpFirst = this->m_UseIncludeRegExp ? false : true;
+      }
+
+    if(arg.find("-A",0) == 0 && i < args.size() - 1)
+      {
+      this->m_DartMode = true;
+      this->SetTest("Notes");
+      i++;
+      this->SetNotesFiles(args[i].c_str());
+      }
+    
+    // --build-and-test options
+    if(arg.find("--build-and-test",0) == 0 && i < args.size() - 1)
+      {
+      cmakeAndTest = true;
+      if(i+2 < args.size())
+        {
+        i++;
+        m_SourceDir = args[i];
+        i++;
+        m_BinaryDir = args[i];
+        // dir must exist before CollapseFullPath is called
+        cmSystemTools::MakeDirectory(m_BinaryDir.c_str());
+        m_BinaryDir = cmSystemTools::CollapseFullPath(m_BinaryDir.c_str());
+        m_SourceDir = cmSystemTools::CollapseFullPath(m_SourceDir.c_str());
+        }
+      else
+        {
+        std::cerr << "--build-and-test must have source and binary dir\n";
+        }
+      }
+    if(arg.find("--build-target",0) == 0 && i < args.size() - 1)
+      {
+      i++;
+      m_BuildTarget = args[i];
+      }
+    if(arg.find("--build-two-config",0) == 0 && i < args.size() - 1)
+      {
+      m_BuildTwoConfig = true;
+      }
+    if(arg.find("--build-exe-dir",0) == 0 && i < args.size() - 1)
+      {
+      i++;
+      m_ExecutableDirectory = args[i];
+      }
+    if(arg.find("--build-generator",0) == 0 && i < args.size() - 1)
+      {
+      i++;
+      m_BuildGenerator = args[i];
+      }
+    if(arg.find("--build-project",0) == 0 && i < args.size() - 1)
+      {
+      i++;
+      m_BuildProject = args[i];
+      }
+    if(arg.find("--build-makeprogram",0) == 0 && i < args.size() - 1)
+      {
+      i++;
+      m_BuildMakeProgram = args[i];
+      }
+    if(arg.find("--build-noclean",0) == 0 && i < args.size() - 1)
+      {
+      m_BuildNoClean = true;
+      }
+    if(arg.find("--build-options",0) == 0 && i < args.size() - 1)
+      {
+      ++i;
+      bool done = false;
+      while(i < args.size() && !done)
+        {
+        m_BuildOptions.push_back(args[i]);
+        if(i+1 < args.size() 
+           && (args[i+1] == "--build-target" || args[i+1] == "--test-command"))
+          {
+          done = true;
+          }
+        else
+          {
+          ++i;
+          }
+        }
+      if(i < args.size())
+        {
+        --i;
+        }
+      }
+    if(arg.find("--test-command",0) == 0 && i < args.size() - 1)
+      {
+      ++i;
+      m_TestCommand = args[i];
+      while(i+1 < args.size())
+        {
+        ++i;
+        m_TestCommandArgs.push_back(args[i]);
+        }
+      }
+    }
+  
+  if(cmakeAndTest)
+    {
+    return this->RunCMakeAndTest(output);
+    }
+  
+  int res;
+  // call process directory
+  if (this->m_RunConfigurationScript)
+    {
+    res = this->RunConfigurationScript();
+    }
+  else
+    {
+    this->Initialize();
+    res = this->ProcessTests();
+    this->Finalize();
+    }
+  return res;
+}
+
+void cmCTest::FindRunningCMake(const char* arg0)
+{
+  // Find our own executable.
+  std::vector<cmStdString> failures;
+  m_CTestSelf = arg0;
+  cmSystemTools::ConvertToUnixSlashes(m_CTestSelf);
+  failures.push_back(m_CTestSelf);
+  m_CTestSelf = cmSystemTools::FindProgram(m_CTestSelf.c_str());
+  if(!cmSystemTools::FileExists(m_CTestSelf.c_str()))
+    {
+    failures.push_back(m_CTestSelf);
+    m_CTestSelf =  "/usr/local/bin/ctest";
+    }
+  if(!cmSystemTools::FileExists(m_CTestSelf.c_str()))
+    {
+    failures.push_back(m_CTestSelf);
+    cmOStringStream msg;
+    msg << "CTEST can not find the command line program cmake.\n";
+    msg << "  argv[0] = \"" << arg0 << "\"\n";
+    msg << "  Attempted paths:\n";
+    std::vector<cmStdString>::iterator i;
+    for(i=failures.begin(); i != failures.end(); ++i)
+      {
+      msg << "    \"" << i->c_str() << "\"\n";
+      }
+    cmSystemTools::Error(msg.str().c_str());
+    }
+  std::string dir;
+  std::string file;
+  if(cmSystemTools::SplitProgramPath(m_CTestSelf.c_str(),
+                                     dir,
+                                     file,
+                                     true))
+    {
+    m_CMakeSelf = dir += "/cmake";
+    m_CMakeSelf += cmSystemTools::GetExecutableExtension();
+    if(!cmSystemTools::FileExists(m_CMakeSelf.c_str()))
+      {
+      cmOStringStream msg;
+      failures.push_back(m_CMakeSelf);
+      msg << "CTEST can not find the command line program cmake.\n";
+      msg << "  argv[0] = \"" << arg0 << "\"\n";
+      msg << "  Attempted path:\n";
+      msg << "    \"" << m_CMakeSelf.c_str() << "\"\n"; 
+      cmSystemTools::Error(msg.str().c_str());
+      }
+    }
+}
+
+void CMakeMessageCallback(const char* m, const char* title, bool& nomore, void* s)
+{
+  std::string* out = (std::string*)s;
+  *out += m;
+  *out += "\n";
+}
+
+void CMakeStdoutCallback(const char* m, int len, void* s)
+{
+  std::string* out = (std::string*)s;
+  out->append(m, len);
+}
+
+int cmCTest::RunCMakeAndTest(std::string* outstring)
+{  
+  cmSystemTools::ResetErrorOccuredFlag();
+  std::string cmakeOutString;
+  cmSystemTools::SetErrorCallback(CMakeMessageCallback, &cmakeOutString);
+  cmSystemTools::SetStdoutCallback(CMakeStdoutCallback, &cmakeOutString);
+  cmOStringStream out;
+  cmake cm;
+  // default to the build type of ctest itself
+  if(m_ConfigType.size() == 0)
+    {
+#ifdef  CMAKE_INTDIR
+    m_ConfigType = CMAKE_INTDIR;
+#endif
+    }
+  
+  std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
+  out << "Internal cmake changing into directory: " << m_BinaryDir << "\n";  
+  if (!cmSystemTools::FileIsDirectory(m_BinaryDir.c_str()))
+    {
+    cmSystemTools::MakeDirectory(m_BinaryDir.c_str());
+    }
+  cmSystemTools::ChangeDirectory(m_BinaryDir.c_str());
+  std::vector<std::string> args;
+  args.push_back(m_CMakeSelf);
+  args.push_back(m_SourceDir);
+  if(m_BuildGenerator.size())
+    {
+    std::string generator = "-G";
+    generator += m_BuildGenerator;
+    args.push_back(generator);
+    }
+  
+  int k;
+  for(k=0; k < m_BuildOptions.size(); ++k)
+    {
+    args.push_back(m_BuildOptions[k]);
+    }
+  if (cm.Run(args) != 0)
+    {
+    std::cerr << "Error: cmake execution failed\n";
+    // return to the original directory
+    cmSystemTools::ChangeDirectory(cwd.c_str());
+    return 1;
+    }
+  if(m_BuildTwoConfig)
+    {
+    if (cm.Run(args) != 0)
+      {
+      std::cerr << "Error: cmake execution failed\n";
+      // return to the original directory
+      cmSystemTools::ChangeDirectory(cwd.c_str());
+      return 1;
+      }
+    }
+  cmSystemTools::SetErrorCallback(0, 0);
+  if(outstring)
+    {
+    *outstring += cmakeOutString;
+    }
+  else
+    {
+    std::cout << cmakeOutString << "\n";
+    }
+  
+  cmListFileCache::GetInstance()->ClearCache();
+  if(m_BuildMakeProgram.size() == 0)
+    {
+    std::cerr << "Error: cmake does not have a valid MAKEPROGRAM\n";
+    std::cerr << "Did you specify a --build-makeprogram and a --build-generator?\n";
+    }
+  int retVal = 0;
+  int ret = 0;
+
+  std::string makeCommand = cmSystemTools::ConvertToOutputPath(m_BuildMakeProgram.c_str());
+  std::string lowerCaseCommand = cmSystemTools::LowerCase(makeCommand);
+  // if msdev is the make program then do the following
+  // MSDEV 6.0
+  if(lowerCaseCommand.find("msdev") != std::string::npos)
+    {
+    // if there are spaces in the makeCommand, assume a full path
+    // and convert it to a path with no spaces in it as the
+    // RunSingleCommand does not like spaces
+#if defined(_WIN32) && !defined(__CYGWIN__)      
+    if(makeCommand.find(' ') != std::string::npos)
+      {
+      cmSystemTools::GetShortPath(makeCommand.c_str(), makeCommand);
+      }
+#endif
+    makeCommand += " ";
+    makeCommand += m_BuildProject;
+    makeCommand += ".dsw /MAKE \"ALL_BUILD - ";
+    makeCommand += m_ConfigType;
+    if(m_BuildNoClean)
+      {
+      makeCommand += "\" /BUILD";
+      }
+    else
+      {
+      makeCommand += "\" /REBUILD";
+      }
+    }
+  // MSDEV 7.0 .NET
+  else if (lowerCaseCommand.find("devenv") != std::string::npos)
+    {
+#if defined(_WIN32) && !defined(__CYGWIN__)      
+    if(makeCommand.find(' ') != std::string::npos)
+      {
+      cmSystemTools::GetShortPath(makeCommand.c_str(), makeCommand);
+      }
+#endif
+    makeCommand += " ";
+    makeCommand += m_BuildProject;
+    makeCommand += ".sln ";
+    if(m_BuildNoClean)
+      {
+      makeCommand += "/build ";
+      }
+    else
+      {
+      makeCommand += "/rebuild ";
+      }
+    makeCommand += m_ConfigType + " /project ALL_BUILD";
+    }
+  else if (lowerCaseCommand.find("make") != std::string::npos)
+    {
+    // assume a make sytle program
+    // clean first
+    if(!m_BuildNoClean)
+      {
+      std::string cleanCommand = makeCommand;
+      cleanCommand += " clean";
+      out << "Running make clean command: " << cleanCommand.c_str() << " ...\n";
+      retVal = 0;
+      std::string output;
+      if (!cmSystemTools::RunSingleCommand(cleanCommand.c_str(), &output, &retVal) || 
+          retVal)
+        {
+        out << "Error: " << cleanCommand.c_str() << "  execution failed\n";
+        out << output.c_str() << "\n";
+        // return to the original directory
+        cmSystemTools::ChangeDirectory(cwd.c_str());
+        out << "Return value: " << retVal << std::endl;
+        if(outstring)
+          {
+          *outstring = out.str();
+          }
+        else
+          {
+          std::cerr << out << "\n";
+          }
+        return 1;
+        }
+      }
+        
+    if(m_BuildTarget.size())
+      {
+      makeCommand +=  " ";
+      makeCommand += m_BuildTarget;
+      }
+    }
+  
+  // command line make program
+
+  out << "Running make command: " << makeCommand.c_str() << " ...\n";
+  retVal = 0;
+  std::string output;
+  if (!cmSystemTools::RunSingleCommand(makeCommand.c_str(), &output, &retVal, 0, false))
+    {
+    out << "Error: " << makeCommand.c_str() <<  "  execution failed\n";
+    out << output.c_str() << "\n";
+    // return to the original directory
+    cmSystemTools::ChangeDirectory(cwd.c_str());
+    out << "Return value: " << retVal << std::endl;
+    if(outstring)
+      {
+      *outstring = out.str();
+      }
+    else
+      {
+      std::cerr << out << "\n";
+      }
+    return 1;
+    }
+  if ( retVal )
+    {
+    cmSystemTools::Error("Building of project failed\n");
+    if(outstring)
+      {
+      *outstring += output;
+      *outstring += "\n";
+      }
+    else
+      {
+      std::cout << output << "\n";
+      }
+    // return to the original directory
+    cmSystemTools::ChangeDirectory(cwd.c_str());
+    ret = 1;
+    }
+
+  if(outstring)
+    {
+    *outstring += output;
+    }
+  
+// now run the compiled test if we can find it
+  // See if the executable exists as written.
+  std::vector<std::string> failed;
+  std::string fullPath;
+  if(cmSystemTools::FileExists(m_TestCommand.c_str()))
+    {
+    fullPath = cmSystemTools::CollapseFullPath(m_TestCommand.c_str());
+    }
+  else
+    {
+    failed.push_back(m_TestCommand);
+    }
+  std::string tryPath = m_TestCommand;
+  tryPath += cmSystemTools::GetExecutableExtension();
+  if(cmSystemTools::FileExists(tryPath.c_str()))
+    {
+    fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
+    }
+  else
+    {
+    failed.push_back(tryPath);
+    }
+  // try the Debug extension
+  tryPath = m_ConfigType + "/";
+  tryPath += cmSystemTools::GetFilenameName(m_TestCommand);
+  if(cmSystemTools::FileExists(tryPath.c_str()))
+    {
+    fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
+    }
+  else
+    {
+    failed.push_back(tryPath);
+    }
+  tryPath += cmSystemTools::GetExecutableExtension();
+  if(cmSystemTools::FileExists(tryPath.c_str()))
+    {
+    fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
+    }
+  else
+    {
+    failed.push_back(tryPath);
+    }
+  tryPath = m_ExecutableDirectory;
+  tryPath += "/";
+  tryPath += m_TestCommand;
+  tryPath += cmSystemTools::GetExecutableExtension();
+  if(cmSystemTools::FileExists(tryPath.c_str()))
+    {
+    fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
+    }
+  else
+    {
+    failed.push_back(tryPath);
+    }
+  tryPath = m_ExecutableDirectory;
+  tryPath += "/";
+  tryPath += m_ConfigType + "/";
+  tryPath += m_TestCommand;
+  tryPath += cmSystemTools::GetExecutableExtension();
+  if(cmSystemTools::FileExists(tryPath.c_str()))
+    {
+    fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
+    }
+  else
+    {
+    failed.push_back(tryPath);
+    }
+  if(!cmSystemTools::FileExists(fullPath.c_str()))
+    {
+    out << "Could not find path to executable, perhaps it was not built: " <<
+      m_TestCommand << "\n";
+    out << "tried to find it in these places:\n";
+    for(unsigned int i=0; i < failed.size(); ++i)
+      {
+      out << failed[i] << "\n";
+      }
+    if(outstring)
+      {
+      *outstring +=  out.str();
+      }
+    else
+      {
+      std::cerr << out.str();
+      }
+    // return to the original directory
+    cmSystemTools::ChangeDirectory(cwd.c_str());
+    return 1;
+    }
+
+  std::vector<const char*> testCommand;
+  testCommand.push_back(fullPath.c_str());
+  for(int k=0; k < m_TestCommandArgs.size(); ++k)
+    {
+    out << m_TestCommandArgs[k].c_str() << "\n";
+    testCommand.push_back(m_TestCommandArgs[k].c_str());
+    }
+  testCommand.push_back(0);
+  std::string outs;
+  int retval = 0;
+  out << "Running test executable: " << fullPath << "\n";
+  this->RunTest(testCommand, &outs, &retval);
+  out << outs << "\n";
+  if(outstring)
+    {
+    *outstring += out.str();
+    }
+  else
+    {
+    std::cout << out.str() << "\n";
+    }
+  return retval;
+}
+
 void cmCTest::SetNotesFiles(const char* notes)
 {
   if ( !notes )
@@ -3404,4 +4175,3 @@ void cmCTest::SetNotesFiles(const char* notes)
     }
   m_NotesFiles = notes;
 }
-