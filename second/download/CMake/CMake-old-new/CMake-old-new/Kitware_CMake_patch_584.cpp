@@ -45,13 +45,13 @@ void cmLocalVisualStudio6Generator::Generate()
 void cmLocalVisualStudio6Generator::OutputDSPFile()
 { 
   // If not an in source build, then create the output directory
-  if(strcmp(m_Makefile->GetStartOutputDirectory(),
-            m_Makefile->GetHomeDirectory()) != 0)
+  if(strcmp(this->Makefile->GetStartOutputDirectory(),
+            this->Makefile->GetHomeDirectory()) != 0)
     {
-    if(!cmSystemTools::MakeDirectory(m_Makefile->GetStartOutputDirectory()))
+    if(!cmSystemTools::MakeDirectory(this->Makefile->GetStartOutputDirectory()))
       {
       cmSystemTools::Error("Error creating directory ",
-                           m_Makefile->GetStartOutputDirectory());
+                           this->Makefile->GetStartOutputDirectory());
       }
     }
 
@@ -67,28 +67,29 @@ void cmLocalVisualStudio6Generator::OutputDSPFile()
     std::vector<std::string>::iterator i;
     for(i = includes.begin(); i != includes.end(); ++i)
       {
-      std::string tmp = this->ConvertToOptionallyRelativeOutputPath(i->c_str());
+      std::string tmp = 
+        this->ConvertToOptionallyRelativeOutputPath(i->c_str());
       if(useShortPath)
         {
         cmSystemTools::GetShortPath(tmp.c_str(), tmp);
         }
-      m_IncludeOptions +=  " /I ";
+      this->IncludeOptions +=  " /I ";
 
       // quote if not already quoted
       if (tmp[0] != '"')
         {
-        m_IncludeOptions += "\"";
-        m_IncludeOptions += tmp;
-        m_IncludeOptions += "\"";
+        this->IncludeOptions += "\"";
+        this->IncludeOptions += tmp;
+        this->IncludeOptions += "\"";
         }
       else
         {
-        m_IncludeOptions += tmp;
+        this->IncludeOptions += tmp;
         }
       }
-    if(j == 0 && m_IncludeOptions.size() > maxIncludeLength)
+    if(j == 0 && this->IncludeOptions.size() > maxIncludeLength)
       {
-      m_IncludeOptions = "";
+      this->IncludeOptions = "";
       useShortPath = true;
       }
     else
@@ -100,16 +101,16 @@ void cmLocalVisualStudio6Generator::OutputDSPFile()
   // Create the DSP or set of DSP's for libraries and executables
 
   // clear project names
-  m_CreatedProjectNames.clear();
+  this->CreatedProjectNames.clear();
   // Call TraceVSDependencies on all targets
-  cmTargets &tgts = m_Makefile->GetTargets(); 
+  cmTargets &tgts = this->Makefile->GetTargets(); 
   for(cmTargets::iterator l = tgts.begin(); 
       l != tgts.end(); l++)
     {
     // Add a rule to regenerate the build system when the target
     // specification source changes.
     const char* suppRegenRule =
-      m_Makefile->GetDefinition("CMAKE_SUPPRESS_REGENERATION");
+      this->Makefile->GetDefinition("CMAKE_SUPPRESS_REGENERATION");
     if (!cmSystemTools::IsOn(suppRegenRule))
       {
       this->AddDSPBuildRule(l->second);
@@ -122,13 +123,13 @@ void cmLocalVisualStudio6Generator::OutputDSPFile()
         && (strncmp(l->first.c_str(), "INCLUDE_EXTERNAL_MSPROJECT", 26) != 0))
       {
       cmTarget& target = l->second;
-      target.TraceVSDependencies(target.GetName(), m_Makefile);
+      target.TraceVSDependencies(target.GetName(), this->Makefile);
       }
     }
   // now for all custom commands that are not used directly in a 
   // target, add them to all targets in the current directory or
   // makefile
-  std::vector<cmSourceFile*> & classesmf = m_Makefile->GetSourceFiles();
+  std::vector<cmSourceFile*> & classesmf = this->Makefile->GetSourceFiles();
   for(std::vector<cmSourceFile*>::const_iterator i = classesmf.begin(); 
       i != classesmf.end(); i++)
     {
@@ -204,7 +205,7 @@ void cmLocalVisualStudio6Generator::OutputDSPFile()
       std::string::size_type pos = l->first.rfind('/');
       if(pos != std::string::npos)
         {
-        std::string dir = m_Makefile->GetStartOutputDirectory();
+        std::string dir = this->Makefile->GetStartOutputDirectory();
         dir += "/";
         dir += l->first.substr(0, pos);
         if(!cmSystemTools::MakeDirectory(dir.c_str()))
@@ -221,10 +222,10 @@ void cmLocalVisualStudio6Generator::CreateSingleDSP(const char *lname, cmTarget
 {
   // add to the list of projects
   std::string pname = lname;
-  m_CreatedProjectNames.push_back(pname);
+  this->CreatedProjectNames.push_back(pname);
   // create the dsp.cmake file
   std::string fname;
-  fname = m_Makefile->GetStartOutputDirectory();
+  fname = this->Makefile->GetStartOutputDirectory();
   fname += "/";
   fname += lname;
   fname += ".dsp";
@@ -248,27 +249,27 @@ void cmLocalVisualStudio6Generator::AddDSPBuildRule(cmTarget& tgt)
 {
   std::string dspname = tgt.GetName();
   dspname += ".dsp.cmake";
-  const char* dsprule = m_Makefile->GetRequiredDefinition("CMAKE_COMMAND");
+  const char* dsprule = this->Makefile->GetRequiredDefinition("CMAKE_COMMAND");
   cmCustomCommandLine commandLine;
   commandLine.push_back(dsprule);
-  std::string makefileIn = m_Makefile->GetStartDirectory();
+  std::string makefileIn = this->Makefile->GetStartDirectory();
   makefileIn += "/";
   makefileIn += "CMakeLists.txt";
   std::string args;
   args = "-H";
   args +=
-    this->Convert(m_Makefile->GetHomeDirectory(),START_OUTPUT, SHELL, true);
+    this->Convert(this->Makefile->GetHomeDirectory(),START_OUTPUT, SHELL, true);
   commandLine.push_back(args);
   args = "-B";
   args += 
-    this->Convert(m_Makefile->GetHomeOutputDirectory(), 
+    this->Convert(this->Makefile->GetHomeOutputDirectory(), 
                   START_OUTPUT, SHELL, true);
   commandLine.push_back(args);
 
   std::string configFile = 
-    m_Makefile->GetRequiredDefinition("CMAKE_ROOT");
+    this->Makefile->GetRequiredDefinition("CMAKE_ROOT");
   configFile += "/Templates/CMakeWindowsSystemConfig.cmake";
-  std::vector<std::string> listFiles = m_Makefile->GetListFiles();
+  std::vector<std::string> listFiles = this->Makefile->GetListFiles();
   bool found = false;
   for(std::vector<std::string>::iterator i = listFiles.begin();
       i != listFiles.end(); ++i)
@@ -287,9 +288,9 @@ void cmLocalVisualStudio6Generator::AddDSPBuildRule(cmTarget& tgt)
   commandLines.push_back(commandLine);
   const char* no_comment = 0;
   const char* no_working_directory = 0;
-  m_Makefile->AddCustomCommandToOutput(dspname.c_str(), listFiles, makefileIn.c_str(),
+  this->Makefile->AddCustomCommandToOutput(dspname.c_str(), listFiles, makefileIn.c_str(),
                                        commandLines, no_comment, no_working_directory, true);
-  if(cmSourceFile* file = m_Makefile->GetSource(makefileIn.c_str()))
+  if(cmSourceFile* file = this->Makefile->GetSource(makefileIn.c_str()))
     {
     tgt.GetSourceFiles().push_back(file);
     }
@@ -353,7 +354,7 @@ void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
   name += ".dsp.cmake";
 
   // We may be modifying the source groups temporarily, so make a copy.
-  std::vector<cmSourceGroup> sourceGroups = m_Makefile->GetSourceGroups();
+  std::vector<cmSourceGroup> sourceGroups = this->Makefile->GetSourceGroups();
   
   // get the classes from the source lists then add them to the groups
   std::vector<cmSourceFile*> & classes = target.GetSourceFiles();
@@ -365,7 +366,7 @@ void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
     {
     // Add the file to the list of sources.
     std::string source = (*i)->GetFullPath();
-    cmSourceGroup& sourceGroup = m_Makefile->FindSourceGroup(source.c_str(),
+    cmSourceGroup& sourceGroup = this->Makefile->FindSourceGroup(source.c_str(),
                                                              sourceGroups);
     sourceGroup.AssignSource(*i);
     // while we are at it, if it is a .rule file then for visual studio 6 we
@@ -442,7 +443,7 @@ void cmLocalVisualStudio6Generator::WriteGroup(const cmSourceGroup *sg, cmTarget
       }
 
     const char* lang = 
-      m_GlobalGenerator->GetLanguageFromExtension((*sf)->GetSourceExtension().c_str());
+      this->GlobalGenerator->GetLanguageFromExtension((*sf)->GetSourceExtension().c_str());
     if(lang && strcmp(lang, "CXX") == 0)
       {
       // force a C++ file type
@@ -492,9 +493,9 @@ void cmLocalVisualStudio6Generator::WriteGroup(const cmSourceGroup *sg, cmTarget
       else if(compileFlags.size())
         {
         for(std::vector<std::string>::iterator i
-              = m_Configurations.begin(); i != m_Configurations.end(); ++i)
+              = this->Configurations.begin(); i != this->Configurations.end(); ++i)
           { 
-          if (i == m_Configurations.begin())
+          if (i == this->Configurations.begin())
             {
             fout << "!IF  \"$(CFG)\" == " << i->c_str() << std::endl;
             }
@@ -536,14 +537,14 @@ ::AddUtilityCommandHack(cmTarget& target, int count,
                         const cmCustomCommand& origCommand)
 {
   // Create a fake output that forces the rule to run.
-  char* output = new char[(strlen(m_Makefile->GetStartOutputDirectory()) +
+  char* output = new char[(strlen(this->Makefile->GetStartOutputDirectory()) +
                            strlen(target.GetName()) + 30)];
-  sprintf(output,"%s/%s_force_%i", m_Makefile->GetStartOutputDirectory(),
+  sprintf(output,"%s/%s_force_%i", this->Makefile->GetStartOutputDirectory(),
           target.GetName(), count);
 
   // Add the rule with the given dependencies and commands.
   const char* no_main_dependency = 0;
-  m_Makefile->AddCustomCommandToOutput(output,
+  this->Makefile->AddCustomCommandToOutput(output,
                                        depends,
                                        no_main_dependency,
                                        origCommand.GetCommandLines(),
@@ -556,7 +557,7 @@ ::AddUtilityCommandHack(cmTarget& target, int count,
   depends.push_back(output);
 
   // Add a source file representing this output to the project.
-  cmSourceFile* outsf = m_Makefile->GetSourceFileWithOutput(output);
+  cmSourceFile* outsf = this->Makefile->GetSourceFileWithOutput(output);
   target.GetSourceFiles().push_back(outsf);
 
   // Free the fake output name.
@@ -573,9 +574,9 @@ void cmLocalVisualStudio6Generator::WriteCustomRule(std::ostream& fout,
   )
 {
   std::vector<std::string>::iterator i;
-  for(i = m_Configurations.begin(); i != m_Configurations.end(); ++i)
+  for(i = this->Configurations.begin(); i != this->Configurations.end(); ++i)
     {
-    if (i == m_Configurations.begin())
+    if (i == this->Configurations.begin())
       {
       fout << "!IF  \"$(CFG)\" == " << i->c_str() << std::endl;
       }
@@ -640,8 +641,8 @@ void cmLocalVisualStudio6Generator::SetBuildType(BuildType b,
                                                  const char* libName,
                                                  cmTarget& target)
 {
-  std::string root= m_Makefile->GetRequiredDefinition("CMAKE_ROOT");
-  const char *def= m_Makefile->GetDefinition( "MSPROJECT_TEMPLATE_DIRECTORY");
+  std::string root= this->Makefile->GetRequiredDefinition("CMAKE_ROOT");
+  const char *def= this->Makefile->GetDefinition( "MSPROJECT_TEMPLATE_DIRECTORY");
 
   if( def)
     {
@@ -655,61 +656,61 @@ void cmLocalVisualStudio6Generator::SetBuildType(BuildType b,
   switch(b)
     {
     case STATIC_LIBRARY:
-      m_DSPHeaderTemplate = root;
-      m_DSPHeaderTemplate += "/staticLibHeader.dsptemplate";
-      m_DSPFooterTemplate = root;
-      m_DSPFooterTemplate += "/staticLibFooter.dsptemplate";
+      this->DSPHeaderTemplate = root;
+      this->DSPHeaderTemplate += "/staticLibHeader.dsptemplate";
+      this->DSPFooterTemplate = root;
+      this->DSPFooterTemplate += "/staticLibFooter.dsptemplate";
       break;
     case DLL:
-      m_DSPHeaderTemplate =  root;
-      m_DSPHeaderTemplate += "/DLLHeader.dsptemplate";
-      m_DSPFooterTemplate =  root;
-      m_DSPFooterTemplate += "/DLLFooter.dsptemplate";
+      this->DSPHeaderTemplate =  root;
+      this->DSPHeaderTemplate += "/DLLHeader.dsptemplate";
+      this->DSPFooterTemplate =  root;
+      this->DSPFooterTemplate += "/DLLFooter.dsptemplate";
       break;
     case EXECUTABLE:
       if ( target.GetPropertyAsBool("WIN32_EXECUTABLE") )
         {
-        m_DSPHeaderTemplate = root;
-        m_DSPHeaderTemplate += "/EXEWinHeader.dsptemplate";
-        m_DSPFooterTemplate = root;
-        m_DSPFooterTemplate += "/EXEFooter.dsptemplate";
+        this->DSPHeaderTemplate = root;
+        this->DSPHeaderTemplate += "/EXEWinHeader.dsptemplate";
+        this->DSPFooterTemplate = root;
+        this->DSPFooterTemplate += "/EXEFooter.dsptemplate";
         }
       else
         {
-        m_DSPHeaderTemplate = root;
-        m_DSPHeaderTemplate += "/EXEHeader.dsptemplate";
-        m_DSPFooterTemplate = root;
-        m_DSPFooterTemplate += "/EXEFooter.dsptemplate";
+        this->DSPHeaderTemplate = root;
+        this->DSPHeaderTemplate += "/EXEHeader.dsptemplate";
+        this->DSPFooterTemplate = root;
+        this->DSPFooterTemplate += "/EXEFooter.dsptemplate";
         }
       break;
     case UTILITY:
-      m_DSPHeaderTemplate = root;
-      m_DSPHeaderTemplate += "/UtilityHeader.dsptemplate";
-      m_DSPFooterTemplate = root;
-      m_DSPFooterTemplate += "/UtilityFooter.dsptemplate";
+      this->DSPHeaderTemplate = root;
+      this->DSPHeaderTemplate += "/UtilityHeader.dsptemplate";
+      this->DSPFooterTemplate = root;
+      this->DSPFooterTemplate += "/UtilityFooter.dsptemplate";
       break;
     }
 
   // once the build type is set, determine what configurations are
   // possible
-  std::ifstream fin(m_DSPHeaderTemplate.c_str());
+  std::ifstream fin(this->DSPHeaderTemplate.c_str());
 
   cmsys::RegularExpression reg("# Name ");
   if(!fin)
     {
-    cmSystemTools::Error("Error Reading ", m_DSPHeaderTemplate.c_str());
+    cmSystemTools::Error("Error Reading ", this->DSPHeaderTemplate.c_str());
     }
 
-  // reset m_Configurations
-  m_Configurations.erase(m_Configurations.begin(), m_Configurations.end());
+  // reset this->Configurations
+  this->Configurations.erase(this->Configurations.begin(), this->Configurations.end());
   // now add all the configurations possible
   std::string line;
   while(cmSystemTools::GetLineFromStream(fin, line))
     {
     cmSystemTools::ReplaceString(line, "OUTPUT_LIBNAME",libName);
     if (reg.find(line))
       {
-      m_Configurations.push_back(line.substr(reg.end()));
+      this->Configurations.push_back(line.substr(reg.end()));
       }
     }
 }
@@ -837,14 +838,14 @@ ::WriteDSPHeader(std::ostream& fout,
 
   // suppoirt override in output directory
   std::string libPath = "";
-  if (m_Makefile->GetDefinition("LIBRARY_OUTPUT_PATH"))
+  if (this->Makefile->GetDefinition("LIBRARY_OUTPUT_PATH"))
     {
-    libPath = m_Makefile->GetDefinition("LIBRARY_OUTPUT_PATH");
+    libPath = this->Makefile->GetDefinition("LIBRARY_OUTPUT_PATH");
     }
   std::string exePath = "";
-  if (m_Makefile->GetDefinition("EXECUTABLE_OUTPUT_PATH"))
+  if (this->Makefile->GetDefinition("EXECUTABLE_OUTPUT_PATH"))
     {
-    exePath = m_Makefile->GetDefinition("EXECUTABLE_OUTPUT_PATH");
+    exePath = this->Makefile->GetDefinition("EXECUTABLE_OUTPUT_PATH");
     
     }
   if(libPath.size())
@@ -963,8 +964,8 @@ ::WriteDSPHeader(std::ostream& fout,
       }
     }
   // find link libraries
-  const cmTarget::LinkLibraries& libs = target.GetLinkLibraries();
-  cmTarget::LinkLibraries::const_iterator j;
+  const cmTarget::LinkLibraryVectorType& libs = target.GetLinkLibraries();
+  cmTarget::LinkLibraryVectorType::const_iterator j;
   for(j = libs.begin(); j != libs.end(); ++j)
     {
     // add libraries to executables and dlls (but never include
@@ -979,7 +980,7 @@ ::WriteDSPHeader(std::ostream& fout,
       // Compute the proper name to use to link this library.
       std::string lib;
       std::string libDebug;
-      cmTarget* tgt = m_GlobalGenerator->FindTarget(0, j->first.c_str());
+      cmTarget* tgt = this->GlobalGenerator->FindTarget(0, j->first.c_str());
       if(tgt)
         {
         lib = cmSystemTools::GetFilenameWithoutExtension(tgt->GetFullName().c_str());
@@ -1042,7 +1043,7 @@ ::WriteDSPHeader(std::ostream& fout,
   if(target.GetType() == cmTarget::EXECUTABLE)
     {
     extraLinkOptions = 
-      m_Makefile->GetRequiredDefinition("CMAKE_EXE_LINKER_FLAGS");
+      this->Makefile->GetRequiredDefinition("CMAKE_EXE_LINKER_FLAGS");
 
     // Use the OUTPUT_NAME property if it was set.  This is supported
     // only for executables.
@@ -1058,11 +1059,11 @@ ::WriteDSPHeader(std::ostream& fout,
     }
   if(target.GetType() == cmTarget::SHARED_LIBRARY)
     {
-    extraLinkOptions = m_Makefile->GetRequiredDefinition("CMAKE_SHARED_LINKER_FLAGS");
+    extraLinkOptions = this->Makefile->GetRequiredDefinition("CMAKE_SHARED_LINKER_FLAGS");
     }
   if(target.GetType() == cmTarget::MODULE_LIBRARY)
     {
-    extraLinkOptions = m_Makefile->GetRequiredDefinition("CMAKE_MODULE_LINKER_FLAGS");
+    extraLinkOptions = this->Makefile->GetRequiredDefinition("CMAKE_MODULE_LINKER_FLAGS");
     }
 
   if(extraLinkOptions.size())
@@ -1077,7 +1078,7 @@ ::WriteDSPHeader(std::ostream& fout,
     libMultiLineOptionsForDebug +=  extraLinkOptions;
     libMultiLineOptionsForDebug += " \n";
     }
-  if(const char* stdLibs =  m_Makefile->GetDefinition("CMAKE_STANDARD_LIBRARIES"))
+  if(const char* stdLibs =  this->Makefile->GetDefinition("CMAKE_STANDARD_LIBRARIES"))
     {
     libOptions += " ";
     libOptions += stdLibs;
@@ -1107,10 +1108,10 @@ ::WriteDSPHeader(std::ostream& fout,
   // only if the target is a lib or exe
   std::string customRuleCode = this->CreateTargetRules(target, libName);
 
-  std::ifstream fin(m_DSPHeaderTemplate.c_str());
+  std::ifstream fin(this->DSPHeaderTemplate.c_str());
   if(!fin)
     {
-    cmSystemTools::Error("Error Reading ", m_DSPHeaderTemplate.c_str());
+    cmSystemTools::Error("Error Reading ", this->DSPHeaderTemplate.c_str());
     }
   std::string staticLibOptions;
   if(target.GetType() == cmTarget::STATIC_LIBRARY )
@@ -1136,7 +1137,7 @@ ::WriteDSPHeader(std::ostream& fout,
   std::string line;
   while(cmSystemTools::GetLineFromStream(fin, line))
     {
-    const char* mfcFlag = m_Makefile->GetDefinition("CMAKE_MFC_FLAG");
+    const char* mfcFlag = this->Makefile->GetDefinition("CMAKE_MFC_FLAG");
     if(!mfcFlag)
       {
       mfcFlag = "0";
@@ -1152,7 +1153,7 @@ ::WriteDSPHeader(std::ostream& fout,
       cmSystemTools::ReplaceString(line, "CM_STATIC_LIB_ARGS",
                                    staticLibOptions.c_str());
       } 
-    if(m_Makefile->IsOn("CMAKE_VERBOSE_MAKEFILE"))
+    if(this->Makefile->IsOn("CMAKE_VERBOSE_MAKEFILE"))
       {
       cmSystemTools::ReplaceString(line, "/nologo", "");
       }
@@ -1178,7 +1179,7 @@ ::WriteDSPHeader(std::ostream& fout,
     cmSystemTools::ReplaceString(line, "OUTPUT_NAME", outputName.c_str());
 
     cmSystemTools::ReplaceString(line, "BUILD_INCLUDES",
-                                 m_IncludeOptions.c_str());
+                                 this->IncludeOptions.c_str());
     cmSystemTools::ReplaceString(line, "OUTPUT_LIBNAME",libName);
     // because LIBRARY_OUTPUT_PATH and EXECUTABLE_OUTPUT_PATH 
     // are already quoted in the template file,
@@ -1194,9 +1195,9 @@ ::WriteDSPHeader(std::ostream& fout,
 
     cmSystemTools::ReplaceString(line, 
                                  "EXTRA_DEFINES", 
-                                 m_Makefile->GetDefineFlags());
+                                 this->Makefile->GetDefineFlags());
     const char* debugPostfix
-      = m_Makefile->GetDefinition("CMAKE_DEBUG_POSTFIX");
+      = this->Makefile->GetDefinition("CMAKE_DEBUG_POSTFIX");
     cmSystemTools::ReplaceString(line, "DEBUG_POSTFIX", 
                                  debugPostfix?debugPostfix:"");
     // store flags for each configuration
@@ -1219,27 +1220,27 @@ ::WriteDSPHeader(std::ostream& fout,
       std::string baseFlagVar = "CMAKE_";
       baseFlagVar += linkLanguage;
       baseFlagVar += "_FLAGS";
-      flags = m_Makefile->GetRequiredDefinition(baseFlagVar.c_str());
+      flags = this->Makefile->GetRequiredDefinition(baseFlagVar.c_str());
       
       std::string flagVar = baseFlagVar + "_RELEASE";
-      flagsRelease = m_Makefile->GetRequiredDefinition(flagVar.c_str());
+      flagsRelease = this->Makefile->GetRequiredDefinition(flagVar.c_str());
       flagsRelease += " -DCMAKE_INTDIR=\\\"Release\\\" ";
       
       flagVar = baseFlagVar + "_MINSIZEREL";
-      flagsMinSize = m_Makefile->GetRequiredDefinition(flagVar.c_str());
+      flagsMinSize = this->Makefile->GetRequiredDefinition(flagVar.c_str());
       flagsMinSize += " -DCMAKE_INTDIR=\\\"MinSizeRel\\\" ";
       
       flagVar = baseFlagVar + "_DEBUG";
-      flagsDebug = m_Makefile->GetRequiredDefinition(flagVar.c_str());
+      flagsDebug = this->Makefile->GetRequiredDefinition(flagVar.c_str());
       flagsDebug += " -DCMAKE_INTDIR=\\\"Debug\\\" ";
       
       flagVar = baseFlagVar + "_RELWITHDEBINFO";
-      flagsDebugRel = m_Makefile->GetRequiredDefinition(flagVar.c_str());
+      flagsDebugRel = this->Makefile->GetRequiredDefinition(flagVar.c_str());
       flagsDebugRel += " -DCMAKE_INTDIR=\\\"RelWithDebInfo\\\" ";
       }
     
     // if unicode is not found, then add -D_MBCS
-    std::string defs = m_Makefile->GetDefineFlags();
+    std::string defs = this->Makefile->GetDefineFlags();
     if(flags.find("D_UNICODE") == flags.npos &&
        defs.find("D_UNICODE") == flags.npos) 
       {
@@ -1268,11 +1269,11 @@ ::WriteDSPHeader(std::ostream& fout,
 
 void cmLocalVisualStudio6Generator::WriteDSPFooter(std::ostream& fout)
 {  
-  std::ifstream fin(m_DSPFooterTemplate.c_str());
+  std::ifstream fin(this->DSPFooterTemplate.c_str());
   if(!fin)
     {
     cmSystemTools::Error("Error Reading ",
-                         m_DSPFooterTemplate.c_str());
+                         this->DSPFooterTemplate.c_str());
     }
   std::string line;
   while(cmSystemTools::GetLineFromStream(fin, line))