@@ -38,15 +38,15 @@
 //----------------------------------------------------------------------------
 cmLocalUnixMakefileGenerator3::cmLocalUnixMakefileGenerator3()
 {
-  m_SilentNoColon = false;
-  m_WindowsShell = false;
-  m_IncludeDirective = "include";
-  m_MakefileVariableSize = 0;
-  m_IgnoreLibPrefix = false;
-  m_PassMakeflags = false;
-  m_EchoNeedsQuote = true;
-  m_DefineWindowsNULL = false;
-  m_UnixCD = true;
+  this->SilentNoColon = false;
+  this->WindowsShell = false;
+  this->IncludeDirective = "include";
+  this->MakefileVariableSize = 0;
+  this->IgnoreLibPrefix = false;
+  this->PassMakeflags = false;
+  this->EchoNeedsQuote = true;
+  this->DefineWindowsNULL = false;
+  this->UnixCD = true;
 }
 
 //----------------------------------------------------------------------------
@@ -58,12 +58,12 @@ cmLocalUnixMakefileGenerator3::~cmLocalUnixMakefileGenerator3()
 void cmLocalUnixMakefileGenerator3::Configure()
 {
   // Include the rule file for each object.
-  m_HomeRelativeOutputPath = 
-    cmSystemTools::RelativePath(m_Makefile->GetHomeOutputDirectory(),
-                                m_Makefile->GetStartOutputDirectory());
-  if (m_HomeRelativeOutputPath.size())
+  this->HomeRelativeOutputPath = 
+    cmSystemTools::RelativePath(this->Makefile->GetHomeOutputDirectory(),
+                                this->Makefile->GetStartOutputDirectory());
+  if (this->HomeRelativeOutputPath.size())
     {
-    m_HomeRelativeOutputPath += "/";
+    this->HomeRelativeOutputPath += "/";
     }
   this->cmLocalGenerator::Configure();
 }
@@ -75,7 +75,7 @@ void cmLocalUnixMakefileGenerator3::Generate()
   this->ConfigureOutputPaths();
 
   // Generate the rule files for each target.
-  cmTargets& targets = m_Makefile->GetTargets();
+  cmTargets& targets = this->Makefile->GetTargets();
   std::string empty;
   for(cmTargets::iterator t = targets.begin(); t != targets.end(); ++t)
     {
@@ -84,7 +84,7 @@ void cmLocalUnixMakefileGenerator3::Generate()
     if (tg)
       {
       this->TargetGenerators.push_back(tg);
-      t->second.TraceVSDependencies(empty, m_Makefile);
+      t->second.TraceVSDependencies(empty, this->Makefile);
       tg->WriteRuleFiles();
       }
     }
@@ -110,27 +110,27 @@ void cmLocalUnixMakefileGenerator3::Generate()
 void cmLocalUnixMakefileGenerator3::ConfigureOutputPaths()
 {
   // Format the library and executable output paths.
-  if(const char* libOut = m_Makefile->GetDefinition("LIBRARY_OUTPUT_PATH"))
+  if(const char* libOut = this->Makefile->GetDefinition("LIBRARY_OUTPUT_PATH"))
     {
-    m_LibraryOutputPath = libOut;
-    this->FormatOutputPath(m_LibraryOutputPath, "LIBRARY");
+    this->LibraryOutputPath = libOut;
+    this->FormatOutputPath(this->LibraryOutputPath, "LIBRARY");
     }
-  if(const char* exeOut = m_Makefile->GetDefinition("EXECUTABLE_OUTPUT_PATH"))
+  if(const char* exeOut = this->Makefile->GetDefinition("EXECUTABLE_OUTPUT_PATH"))
     {
-    m_ExecutableOutputPath = exeOut;
-    this->FormatOutputPath(m_ExecutableOutputPath, "EXECUTABLE");
+    this->ExecutableOutputPath = exeOut;
+    this->FormatOutputPath(this->ExecutableOutputPath, "EXECUTABLE");
     }
 
   // Store the configuration name that will be generated.
-  if(const char* config = m_Makefile->GetDefinition("CMAKE_BUILD_TYPE"))
+  if(const char* config = this->Makefile->GetDefinition("CMAKE_BUILD_TYPE"))
     {
     // Use the build type given by the user.
-    m_ConfigurationName = config;
+    this->ConfigurationName = config;
     }
   else
     {
     // No configuration type given.
-    m_ConfigurationName = "";
+    this->ConfigurationName = "";
     }
 }
 
@@ -145,7 +145,7 @@ void cmLocalUnixMakefileGenerator3::FormatOutputPath(std::string& path,
     // relative to the current output directory for this makefile.
     path =
       cmSystemTools::CollapseFullPath(path.c_str(),
-                                      m_Makefile->GetStartOutputDirectory());
+                                      this->Makefile->GetStartOutputDirectory());
 
     // Add a trailing slash for easy appending later.
     if(path.empty() || path[path.size()-1] != '/')
@@ -161,7 +161,7 @@ void cmLocalUnixMakefileGenerator3::FormatOutputPath(std::string& path,
       }
 
     // Add this as a link directory automatically.
-    m_Makefile->AddLinkDirectory(path.c_str());
+    this->Makefile->AddLinkDirectory(path.c_str());
     }
 }
 
@@ -180,7 +180,7 @@ void cmLocalUnixMakefileGenerator3::WriteLocalMakefile()
     return;
     }
   // always write the top makefile
-  if (m_Parent)
+  if (this->Parent)
     {
     ruleFileStream.SetCopyIfDifferent(true);
     }
@@ -191,7 +191,7 @@ void cmLocalUnixMakefileGenerator3::WriteLocalMakefile()
   // only write local targets unless at the top Keep track of targets already
   // listed.
   std::set<cmStdString> emittedTargets;
-  if (m_Parent)
+  if (this->Parent)
     {
     // write our targets, and while doing it collect up the object
     // file rules
@@ -200,7 +200,7 @@ void cmLocalUnixMakefileGenerator3::WriteLocalMakefile()
   else
     {
     cmGlobalUnixMakefileGenerator3 *gg = 
-      static_cast<cmGlobalUnixMakefileGenerator3*>(m_GlobalGenerator);
+      static_cast<cmGlobalUnixMakefileGenerator3*>(this->GlobalGenerator);
     gg->WriteConvenienceRules(ruleFileStream,emittedTargets);
     }
   
@@ -210,8 +210,8 @@ void cmLocalUnixMakefileGenerator3::WriteLocalMakefile()
   // now write out the object rules
   // for each object file name
   for (std::map<cmStdString,std::vector<cmTarget *> >::iterator lo = 
-         m_LocalObjectFiles.begin();
-       lo != m_LocalObjectFiles.end(); ++lo)
+         this->LocalObjectFiles.begin();
+       lo != this->LocalObjectFiles.end(); ++lo)
     {
     commands.clear();
     // for each target using the object file
@@ -226,8 +226,8 @@ void cmLocalUnixMakefileGenerator3::WriteLocalMakefile()
       commands.push_back(this->GetRecursiveMakeCall
                          (tgtMakefileName.c_str(),targetName.c_str()));  
       this->CreateCDCommand(commands,
-                                    m_Makefile->GetHomeOutputDirectory(),
-                                    m_Makefile->GetStartOutputDirectory());
+                                    this->Makefile->GetHomeOutputDirectory(),
+                                    this->Makefile->GetStartOutputDirectory());
       }
     this->WriteMakeRule(ruleFileStream, 
                         "target for object file", 
@@ -238,7 +238,7 @@ void cmLocalUnixMakefileGenerator3::WriteLocalMakefile()
   if(emittedTargets.insert("help").second)
     {
     cmGlobalUnixMakefileGenerator3 *gg = 
-      static_cast<cmGlobalUnixMakefileGenerator3*>(m_GlobalGenerator);
+      static_cast<cmGlobalUnixMakefileGenerator3*>(this->GlobalGenerator);
     gg->WriteHelpRule(ruleFileStream,this);
     }
 
@@ -254,7 +254,7 @@ ::WriteLocalMakefileTargets(std::ostream& ruleFileStream,
 
   // for each target we just provide a rule to cd up to the top and do a make
   // on the target
-  cmTargets& targets = m_Makefile->GetTargets();
+  cmTargets& targets = this->Makefile->GetTargets();
   std::string localName;
   for(cmTargets::iterator t = targets.begin(); t != targets.end(); ++t)
     {
@@ -276,8 +276,8 @@ ::WriteLocalMakefileTargets(std::ostream& ruleFileStream,
       commands.push_back(this->GetRecursiveMakeCall
                          ("CMakeFiles/Makefile2",localName.c_str()));
       this->CreateCDCommand(commands,
-                            m_Makefile->GetHomeOutputDirectory(),
-                            m_Makefile->GetStartOutputDirectory());
+                            this->Makefile->GetHomeOutputDirectory(),
+                            this->Makefile->GetStartOutputDirectory());
       this->WriteMakeRule(ruleFileStream, "Convenience name for target.",
                           localName.c_str(), depends, commands, true);
       
@@ -296,7 +296,7 @@ ::WriteLocalMakefileTargets(std::ostream& ruleFileStream,
 //----------------------------------------------------------------------------
 void cmLocalUnixMakefileGenerator3::WriteDirectoryInformationFile()
 {
-  std::string infoFileName = m_Makefile->GetStartOutputDirectory();
+  std::string infoFileName = this->Makefile->GetStartOutputDirectory();
   infoFileName += "/CMakeFiles/CMakeDirectoryInformation.cmake";
 
   // Open the output file.
@@ -345,13 +345,13 @@ void cmLocalUnixMakefileGenerator3::WriteDirectoryInformationFile()
   infoFileStream
     << "SET(CMAKE_C_INCLUDE_REGEX_SCAN ";
   this->WriteCMakeArgument(infoFileStream,
-                           m_Makefile->GetIncludeRegularExpression());
+                           this->Makefile->GetIncludeRegularExpression());
   infoFileStream
     << ")\n";
   infoFileStream
     << "SET(CMAKE_C_INCLUDE_REGEX_COMPLAIN ";
   this->WriteCMakeArgument(infoFileStream,
-                           m_Makefile->GetComplainRegularExpression());
+                           this->Makefile->GetComplainRegularExpression());
   infoFileStream
     << ")\n";
   infoFileStream
@@ -366,8 +366,8 @@ void cmLocalUnixMakefileGenerator3::WriteDirectoryInformationFile()
   infoFileStream
     << "SET(CMAKE_GENERATED_FILES\n";
   for(std::vector<cmSourceFile*>::const_iterator
-        i = m_Makefile->GetSourceFiles().begin();
-      i != m_Makefile->GetSourceFiles().end(); ++i)
+        i = this->Makefile->GetSourceFiles().begin();
+      i != this->Makefile->GetSourceFiles().end(); ++i)
     {
     cmSourceFile* src = *i;
     if(src->GetPropertyAsBool("GENERATED"))
@@ -389,7 +389,7 @@ std::string
 cmLocalUnixMakefileGenerator3
 ::ConvertToFullPath(const std::string& localPath)
 {
-  std::string dir = m_Makefile->GetStartOutputDirectory();
+  std::string dir = this->Makefile->GetStartOutputDirectory();
   dir += "/";
   dir += localPath;
   return dir;
@@ -398,7 +398,7 @@ ::ConvertToFullPath(const std::string& localPath)
 
 const std::string &cmLocalUnixMakefileGenerator3::GetHomeRelativeOutputPath()
 {
-  return m_HomeRelativeOutputPath;
+  return this->HomeRelativeOutputPath;
 }
 
 
@@ -452,7 +452,7 @@ ::WriteMakeRule(std::ostream& os,
   if(symbolic)
     {
     if(const char* sym =
-       m_Makefile->GetDefinition("CMAKE_MAKE_SYMBOLIC_RULE"))
+       this->Makefile->GetDefinition("CMAKE_MAKE_SYMBOLIC_RULE"))
       {
       os << tgt.c_str() << space << ": " << sym << "\n";
       }
@@ -497,7 +497,7 @@ ::WriteMakeVariables(std::ostream& makefileStream)
   makefileStream
     << "# Set environment variables for the build.\n"
     << "\n";
-  if(m_DefineWindowsNULL)
+  if(this->DefineWindowsNULL)
     {
     makefileStream
       << "!IF \"$(OS)\" == \"Windows_NT\"\n"
@@ -506,7 +506,7 @@ ::WriteMakeVariables(std::ostream& makefileStream)
       << "NULL=nul\n"
       << "!ENDIF\n";
     }
-  if(m_WindowsShell)
+  if(this->WindowsShell)
     {
      makefileStream
        << "SHELL = C:\\WINDOWS\\system32\\cmd.exe\n";
@@ -520,7 +520,7 @@ ::WriteMakeVariables(std::ostream& makefileStream)
     }
 
   std::string cmakecommand =
-      m_Makefile->GetRequiredDefinition("CMAKE_COMMAND");
+      this->Makefile->GetRequiredDefinition("CMAKE_COMMAND");
   makefileStream
     << "# The CMake executable.\n"
     << "CMAKE_COMMAND = "
@@ -534,26 +534,26 @@ ::WriteMakeVariables(std::ostream& makefileStream)
     << " -E remove -f\n"
     << "\n";
   
-  if(m_Makefile->GetDefinition("CMAKE_EDIT_COMMAND"))
+  if(this->Makefile->GetDefinition("CMAKE_EDIT_COMMAND"))
     {
     makefileStream
       << "# The program to use to edit the cache.\n"
       << "CMAKE_EDIT_COMMAND = "
       << (this->ConvertToOutputForExisting(
-            m_Makefile->GetDefinition("CMAKE_EDIT_COMMAND"))) << "\n"
+            this->Makefile->GetDefinition("CMAKE_EDIT_COMMAND"))) << "\n"
       << "\n";
     }
 
   makefileStream
     << "# The top-level source directory on which CMake was run.\n"
     << "CMAKE_SOURCE_DIR = "
-    << this->Convert(m_Makefile->GetHomeDirectory(), FULL, SHELL)
+    << this->Convert(this->Makefile->GetHomeDirectory(), FULL, SHELL)
     << "\n"
     << "\n";
   makefileStream
     << "# The top-level build directory on which CMake was run.\n"
     << "CMAKE_BINARY_DIR = "
-    << this->Convert(m_Makefile->GetHomeOutputDirectory(), FULL, SHELL)
+    << this->Convert(this->Makefile->GetHomeOutputDirectory(), FULL, SHELL)
     << "\n"
     << "\n";
 }
@@ -577,14 +577,14 @@ ::WriteSpecialTargetsTop(std::ostream& makefileStream)
   std::vector<std::string> commands;
   std::vector<std::string> no_depends;
   commands.clear();
-  if(m_Makefile->IsOn("CMAKE_VERBOSE_MAKEFILE"))
+  if(this->Makefile->IsOn("CMAKE_VERBOSE_MAKEFILE"))
     {
     makefileStream
       << "# Produce verbose output by default.\n"
       << "VERBOSE = 1\n"
       << "\n";
     }
-  if(m_SilentNoColon)
+  if(this->SilentNoColon)
     {
     makefileStream << "$(VERBOSE).SILENT\n";
     }
@@ -635,11 +635,11 @@ ::WriteSpecialTargetsBottom(std::ostream& makefileStream)
   std::vector<std::string> no_depends;
   std::vector<std::string> commands;
   commands.push_back(runRule);
-  if(m_Parent)
+  if(this->Parent)
     {
     this->CreateCDCommand(commands,
-                          m_Makefile->GetHomeOutputDirectory(),
-                          m_Makefile->GetStartOutputDirectory());
+                          this->Makefile->GetHomeOutputDirectory(),
+                          this->Makefile->GetStartOutputDirectory());
     }
   this->WriteMakeRule(makefileStream,
                       "Special rule to run CMake to check the build system "
@@ -686,10 +686,10 @@ ::WriteConvenienceRule(std::ostream& ruleFileStream,
 std::string
 cmLocalUnixMakefileGenerator3::GetRelativeTargetDirectory(cmTarget& target)
 {
-  std::string dir = m_Makefile->GetStartOutputDirectory();
+  std::string dir = this->Makefile->GetStartOutputDirectory();
   dir += "/";
   dir += this->GetTargetDirectory(target);
-  dir = cmSystemTools::RelativePath(m_Makefile->GetHomeOutputDirectory(), dir.c_str());
+  dir = cmSystemTools::RelativePath(this->Makefile->GetHomeOutputDirectory(), dir.c_str());
   return this->Convert(dir.c_str(),NONE,MAKEFILE);
 }
 
@@ -703,7 +703,7 @@ ::AppendRuleDepend(std::vector<std::string>& depends,
 {
   // Add a dependency on the rule file itself unless an option to skip
   // it is specifically enabled by the user or project.
-  const char* nodep = m_Makefile->GetDefinition("CMAKE_SKIP_RULE_DEPENDENCY");
+  const char* nodep = this->Makefile->GetDefinition("CMAKE_SKIP_RULE_DEPENDENCY");
   if(!nodep || cmSystemTools::IsOff(nodep))
     {
     depends.push_back(ruleFileName);
@@ -734,7 +734,7 @@ ::AppendCustomDepend(std::vector<std::string>& depends,
     {
     // Lookup the real name of the dependency in case it is a CMake target.
     std::string dep = this->GetRealDependency(d->c_str(),
-                                              m_ConfigurationName.c_str());
+                                              this->ConfigurationName.c_str());
     depends.push_back(dep);
     }
 }
@@ -782,12 +782,12 @@ ::AppendCustomCommand(std::vector<std::string>& commands,
         {
         cmd += " ";
         bool forceOn =  cmSystemTools::GetForceUnixPaths();
-        if(forceOn && m_WindowsShell)
+        if(forceOn && this->WindowsShell)
           {
           cmSystemTools::SetForceUnixPaths(false);
           }
         cmd += cmSystemTools::EscapeSpaces(commandLine[j].c_str());
-        if(forceOn && m_WindowsShell)
+        if(forceOn && this->WindowsShell)
           {
           cmSystemTools::SetForceUnixPaths(true);
           }
@@ -797,14 +797,14 @@ ::AppendCustomCommand(std::vector<std::string>& commands,
     }
 
   // push back the custom commands
-  const char* dir  = m_Makefile->GetStartOutputDirectory();
+  const char* dir  = this->Makefile->GetStartOutputDirectory();
   // if the command specified a working directory use it.
   if(cc.GetWorkingDirectory())
     {
     dir = cc.GetWorkingDirectory();
     }
   this->CreateCDCommand(commands1, dir,
-                        m_Makefile->GetHomeOutputDirectory());
+                        this->Makefile->GetHomeOutputDirectory());
 
   commands.insert(commands.end(), commands1.begin(), commands1.end());
 }
@@ -818,7 +818,7 @@ ::AppendCleanCommand(std::vector<std::string>& commands,
 {
   if(!files.empty())
     {
-    std::string cleanfile = m_Makefile->GetCurrentOutputDirectory();
+    std::string cleanfile = this->Makefile->GetCurrentOutputDirectory();
     cleanfile += "/";
     cleanfile += this->GetTargetDirectory(target);
     cleanfile += "/cmake_clean";
@@ -864,12 +864,12 @@ cmLocalUnixMakefileGenerator3::AppendEcho(std::vector<std::string>& commands,
         {
         // Add a command to echo this line.
         std::string cmd = "@echo ";
-        if(m_EchoNeedsQuote)
+        if(this->EchoNeedsQuote)
           {
           cmd += "\"";
           }
         cmd += line;
-        if(m_EchoNeedsQuote)
+        if(this->EchoNeedsQuote)
           {
           cmd += "\"";
           }
@@ -921,10 +921,10 @@ cmLocalUnixMakefileGenerator3::CreateSafeUniqueObjectFileName(const char* sin)
 {
   // Look for an existing mapped name for this object file.
   std::map<cmStdString,cmStdString>::iterator it =
-    m_UniqueObjectNamesMap.find(sin);
+    this->UniqueObjectNamesMap.find(sin);
 
   // If no entry exists create one.
-  if(it == m_UniqueObjectNamesMap.end())
+  if(it == this->UniqueObjectNamesMap.end())
     {
     // Start with the original name.
     std::string ssin = sin;
@@ -944,7 +944,7 @@ cmLocalUnixMakefileGenerator3::CreateSafeUniqueObjectFileName(const char* sin)
     cmSystemTools::ReplaceString(ssin, " ", "_");
 
     // Mangle the name if necessary.
-    if(m_Makefile->IsOn("CMAKE_MANGLE_OBJECT_FILE_NAMES"))
+    if(this->Makefile->IsOn("CMAKE_MANGLE_OBJECT_FILE_NAMES"))
       {
       bool done;
       int cc = 0;
@@ -955,8 +955,8 @@ cmLocalUnixMakefileGenerator3::CreateSafeUniqueObjectFileName(const char* sin)
       do
         {
         done = true;
-        for ( it = m_UniqueObjectNamesMap.begin();
-              it != m_UniqueObjectNamesMap.end();
+        for ( it = this->UniqueObjectNamesMap.begin();
+              it != this->UniqueObjectNamesMap.end();
               ++ it )
           {
           if ( it->second == ssin )
@@ -977,7 +977,7 @@ cmLocalUnixMakefileGenerator3::CreateSafeUniqueObjectFileName(const char* sin)
 
     // Insert the newly mapped object file name.
     std::map<cmStdString, cmStdString>::value_type e(sin, ssin);
-    it = m_UniqueObjectNamesMap.insert(e).first;
+    it = this->UniqueObjectNamesMap.insert(e).first;
     }
 
   // Return the map entry.
@@ -996,47 +996,47 @@ ::CreateMakeVariable(const char* sin, const char* s2in)
   // if there is no restriction on the length of make variables
   // and there are no "." charactors in the string, then return the
   // unmodified combination.
-  if((!m_MakefileVariableSize && unmodified.find('.') == s.npos)
-     && (!m_MakefileVariableSize && unmodified.find('-') == s.npos))
+  if((!this->MakefileVariableSize && unmodified.find('.') == s.npos)
+     && (!this->MakefileVariableSize && unmodified.find('-') == s.npos))
     {
     return unmodified;
     }
 
   // see if the variable has been defined before and return
   // the modified version of the variable
-  std::map<cmStdString, cmStdString>::iterator i = m_MakeVariableMap.find(unmodified);
-  if(i != m_MakeVariableMap.end())
+  std::map<cmStdString, cmStdString>::iterator i = this->MakeVariableMap.find(unmodified);
+  if(i != this->MakeVariableMap.end())
     {
     return i->second;
     }
   // start with the unmodified variable
   std::string ret = unmodified;
-  // if this there is no value for m_MakefileVariableSize then
+  // if this there is no value for this->MakefileVariableSize then
   // the string must have bad characters in it
-  if(!m_MakefileVariableSize)
+  if(!this->MakefileVariableSize)
     {
     cmSystemTools::ReplaceString(ret, ".", "_");
     cmSystemTools::ReplaceString(ret, "-", "__");
     int ni = 0;
     char buffer[5];
     // make sure the _ version is not already used, if
     // it is used then add number to the end of the variable
-    while(m_ShortMakeVariableMap.count(ret) && ni < 1000)
+    while(this->ShortMakeVariableMap.count(ret) && ni < 1000)
       {
       ++ni;
       sprintf(buffer, "%04d", ni);
       ret = unmodified + buffer;
       }
-    m_ShortMakeVariableMap[ret] = "1";
-    m_MakeVariableMap[unmodified] = ret;
+    this->ShortMakeVariableMap[ret] = "1";
+    this->MakeVariableMap[unmodified] = ret;
     return ret;
     }
 
   // if the string is greater the 32 chars it is an invalid vairable name
   // for borland make
-  if(static_cast<int>(ret.size()) > m_MakefileVariableSize)
+  if(static_cast<int>(ret.size()) > this->MakefileVariableSize)
     {
-    int keep = m_MakefileVariableSize - 8;
+    int keep = this->MakefileVariableSize - 8;
     int size = keep + 3;
     std::string str1 = s;
     std::string str2 = s2;
@@ -1054,7 +1054,7 @@ ::CreateMakeVariable(const char* sin, const char* s2in)
     int ni = 0;
     sprintf(buffer, "%04d", ni);
     ret = str1 + str2 + buffer;
-    while(m_ShortMakeVariableMap.count(ret) && ni < 1000)
+    while(this->ShortMakeVariableMap.count(ret) && ni < 1000)
       {
       ++ni;
       sprintf(buffer, "%04d", ni);
@@ -1066,10 +1066,10 @@ ::CreateMakeVariable(const char* sin, const char* s2in)
       return unmodified;
       }
     // once an unused variable is found
-    m_ShortMakeVariableMap[ret] = "1";
+    this->ShortMakeVariableMap[ret] = "1";
     }
   // always make an entry into the unmodified to variable map
-  m_MakeVariableMap[unmodified] = ret;
+  this->MakeVariableMap[unmodified] = ret;
   return ret;
 }
 
@@ -1242,7 +1242,7 @@ ::ScanDependencies(std::vector<std::string> const& args)
     
     if (scanner)
       {
-      scanner->SetFileComparison(m_GlobalGenerator->GetCMakeInstance()->GetFileComparison());
+      scanner->SetFileComparison(this->GlobalGenerator->GetCMakeInstance()->GetFileComparison());
       // for each file we need to scan
       std::string srcLang = "CMAKE_DEPENDS_CHECK_";
       srcLang += lang;
@@ -1298,7 +1298,7 @@ ::WriteLocalAllRules(std::ostream& ruleFileStream)
   }
 
   // Write all global targets
-  cmTargets* targets = &(m_Makefile->GetTargets());
+  cmTargets* targets = &(this->Makefile->GetTargets());
   cmTargets::iterator glIt;
   for ( glIt = targets->begin(); glIt != targets->end(); ++ glIt )
     {
@@ -1323,11 +1323,16 @@ ::WriteLocalAllRules(std::ostream& ruleFileStream)
       this->AppendEcho(commands, text);
 
       // Utility targets store their rules in pre- and post-build commands.
-      this->AppendCustomDepends(depends,   glIt->second.GetPreBuildCommands());
-      this->AppendCustomDepends(depends,   glIt->second.GetPostBuildCommands());
-      this->AppendCustomCommands(commands, glIt->second.GetPreBuildCommands());
-      this->AppendCustomCommands(commands, glIt->second.GetPostBuildCommands());
-      this->WriteMakeRule(ruleFileStream, targetString.c_str(), glIt->first.c_str(), depends, commands, true);
+      this->AppendCustomDepends(depends,   
+                                glIt->second.GetPreBuildCommands());
+      this->AppendCustomDepends(depends,   
+                                glIt->second.GetPostBuildCommands());
+      this->AppendCustomCommands(commands, 
+                                 glIt->second.GetPreBuildCommands());
+      this->AppendCustomCommands(commands, 
+                                 glIt->second.GetPostBuildCommands());
+      this->WriteMakeRule(ruleFileStream, targetString.c_str(), 
+                          glIt->first.c_str(), depends, commands, true);
       }
     }
 
@@ -1337,40 +1342,43 @@ ::WriteLocalAllRules(std::ostream& ruleFileStream)
   std::vector<std::string> commands;
 
   // Write the all rule.
-  std::string dir = m_Makefile->GetStartOutputDirectory();
+  std::string dir = this->Makefile->GetStartOutputDirectory();
   dir += "/all";
+
   dir = this->Convert(dir.c_str(),HOME_OUTPUT,MAKEFILE);
+
   depends.push_back("cmake_check_build_system");
+
   commands.push_back
     (this->GetRecursiveMakeCall("CMakeFiles/Makefile2",dir.c_str()));  
   this->CreateCDCommand(commands,
-                                m_Makefile->GetHomeOutputDirectory(),
-                                m_Makefile->GetStartOutputDirectory());
+                                this->Makefile->GetHomeOutputDirectory(),
+                                this->Makefile->GetStartOutputDirectory());
   this->WriteMakeRule(ruleFileStream, "The main all target", "all",
                       depends, commands, true);
 
   // Write the clean rule.
-  dir = m_Makefile->GetStartOutputDirectory();
+  dir = this->Makefile->GetStartOutputDirectory();
   dir += "/clean";
   dir = this->Convert(dir.c_str(),HOME_OUTPUT,MAKEFILE);
   commands.clear();
   depends.clear();
   commands.push_back
     (this->GetRecursiveMakeCall("CMakeFiles/Makefile2",dir.c_str()));  
   this->CreateCDCommand(commands,
-                                m_Makefile->GetHomeOutputDirectory(),
-                                m_Makefile->GetStartOutputDirectory());
+                                this->Makefile->GetHomeOutputDirectory(),
+                                this->Makefile->GetStartOutputDirectory());
   this->WriteMakeRule(ruleFileStream, "The main clean target", "clean",
                       depends, commands, true);
 
   // Write the preinstall rule.
-  dir = m_Makefile->GetStartOutputDirectory();
+  dir = this->Makefile->GetStartOutputDirectory();
   dir += "/preinstall";
   dir = this->Convert(dir.c_str(), HOME_OUTPUT,MAKEFILE);
   commands.clear();
   depends.clear();
   const char* noall =
-    m_Makefile->GetDefinition("CMAKE_SKIP_INSTALL_ALL_DEPENDENCY");
+    this->Makefile->GetDefinition("CMAKE_SKIP_INSTALL_ALL_DEPENDENCY");
   if(!noall || cmSystemTools::IsOff(noall))
     {
     // Drive the build before installing.
@@ -1384,8 +1392,8 @@ ::WriteLocalAllRules(std::ostream& ruleFileStream)
   commands.push_back
     (this->GetRecursiveMakeCall("CMakeFiles/Makefile2", dir.c_str()));
   this->CreateCDCommand(commands,
-                        m_Makefile->GetHomeOutputDirectory(),
-                        m_Makefile->GetStartOutputDirectory());
+                        this->Makefile->GetHomeOutputDirectory(),
+                        this->Makefile->GetStartOutputDirectory());
   this->WriteMakeRule(ruleFileStream, "Prepare targets for installation.",
                       "preinstall", depends, commands, true);
 
@@ -1425,7 +1433,7 @@ void cmLocalUnixMakefileGenerator3::CheckDependencies(cmMakefile* mf,
   // For each info file run the check
   cmDependsC checker;
   checker.SetVerbose(verbose);
-  checker.SetFileComparison(m_GlobalGenerator->GetCMakeInstance()->GetFileComparison());
+  checker.SetFileComparison(this->GlobalGenerator->GetCMakeInstance()->GetFileComparison());
   for(std::vector<std::string>::iterator l = files.begin();
       l != files.end(); ++l)
     {
@@ -1489,7 +1497,7 @@ ::WriteDependLanguageInfo(std::ostream& cmakefileStream, cmTarget &target)
       {
       cmakefileStream << "  \"" << (*csIter)->GetFullPath() << "\"\n";
       // Get the full path name of the object file.
-      std::string obj = m_Makefile->GetStartOutputDirectory();
+      std::string obj = this->Makefile->GetStartOutputDirectory();
       obj += "/";
       obj += this->GetObjectFileName(target, **csIter);
       cmakefileStream << "  \"" << 
@@ -1535,7 +1543,7 @@ ::GetObjectFileName(cmTarget& target,
     objectName = objectName.substr(0, dot_pos);
     }
   objectName +=
-    m_GlobalGenerator->GetLanguageOutputExtensionFromExtension(
+    this->GlobalGenerator->GetLanguageOutputExtensionFromExtension(
       source.GetSourceExtension().c_str());
 
   // Convert to a safe name.
@@ -1557,7 +1565,7 @@ void cmLocalUnixMakefileGenerator3::WriteDisclaimer(std::ostream& os)
 {
   os
     << "# CMAKE generated file: DO NOT EDIT!\n"
-    << "# Generated by \"" << m_GlobalGenerator->GetName() << "\""
+    << "# Generated by \"" << this->GlobalGenerator->GetName() << "\""
     << " Generator, CMake Version "
     << cmMakefile::GetMajorVersion() << "."
     << cmMakefile::GetMinorVersion() << "\n\n";
@@ -1713,7 +1721,7 @@ ::CreateCDCommand(std::vector<std::string>& commands, const char *tgtDir,
     return;
     }
   
-  if(!m_UnixCD)
+  if(!this->UnixCD)
     {
     // On Windows we must perform each step separately and then change
     // back because the shell keeps the working directory between
@@ -1756,7 +1764,7 @@ cmLocalUnixMakefileGenerator3
 ::GetSourceFileLanguage(const cmSourceFile& source)
 {
   // Identify the language of the source file.
-  return (m_GlobalGenerator
+  return (this->GlobalGenerator
           ->GetLanguageFromExtension(source.GetSourceExtension().c_str()));
 }
 