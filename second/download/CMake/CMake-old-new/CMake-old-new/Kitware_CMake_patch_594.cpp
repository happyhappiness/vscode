@@ -81,9 +81,6 @@ void cmLocalVisualStudio6Generator::OutputDSPFile()
   // clear project names
   m_CreatedProjectNames.clear();
 
-  // expand vars for custom commands
-  m_Makefile->ExpandVariablesInCustomCommands();
-
   // build any targets
   cmTargets &tgts = m_Makefile->GetTargets();
   for(cmTargets::iterator l = tgts.begin(); 
@@ -170,23 +167,22 @@ void cmLocalVisualStudio6Generator::AddDSPBuildRule()
   makefileIn += "/";
   makefileIn += "CMakeLists.txt";
   makefileIn = this->ConvertToRelativeOutputPath(makefileIn.c_str());
-  std::string dsprule = "${CMAKE_COMMAND}";
-  m_Makefile->ExpandVariablesInString(dsprule);
-  dsprule = this->ConvertToRelativeOutputPath(dsprule.c_str());
-  std::vector<std::string> argv;
-  argv.push_back(makefileIn);
+  const char* dsprule = m_Makefile->GetRequiredDefinition("CMAKE_COMMAND");
+  cmCustomCommandLine commandLine;
+  commandLine.push_back(dsprule);
+  commandLine.push_back(makefileIn);
   makefileIn = m_Makefile->GetStartDirectory();
   makefileIn += "/";
   makefileIn += "CMakeLists.txt";
   std::string args;
   args = "-H";
   args +=
     this->ConvertToRelativeOutputPath(m_Makefile->GetHomeDirectory());
-  argv.push_back(args);
+  commandLine.push_back(args);
   args = "-B";
   args += 
     this->ConvertToRelativeOutputPath(m_Makefile->GetHomeOutputDirectory());
-  argv.push_back(args);
+  commandLine.push_back(args);
 
   std::string configFile = 
     m_Makefile->GetRequiredDefinition("CMAKE_ROOT");
@@ -205,9 +201,12 @@ void cmLocalVisualStudio6Generator::AddDSPBuildRule()
     {
     listFiles.push_back(configFile);
     }
-  m_Makefile->AddCustomCommandToOutput(dspname.c_str(), dsprule.c_str(), 
-                                       argv, makefileIn.c_str(), listFiles,
-                                       NULL, true);
+
+  cmCustomCommandLines commandLines;
+  commandLines.push_back(commandLine);
+  const char* no_comment = 0;
+  m_Makefile->AddCustomCommandToOutput(dspname.c_str(), listFiles, makefileIn.c_str(),
+                                       commandLines, no_comment, true);
 }
 
 
@@ -234,26 +233,19 @@ void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
            target.GetPostBuildCommands().begin(); 
          cr != target.GetPostBuildCommands().end(); ++cr)
       {
-      cmCustomCommand cc(*cr);
-      cc.ExpandVariables(*m_Makefile);
       char *output = new char [
         strlen(m_Makefile->GetStartOutputDirectory()) + 
         strlen(libName) + 30];
       sprintf(output,"%s/%s_force_%i",
               m_Makefile->GetStartOutputDirectory(),
               libName, count);
-      std::vector<std::string> args;
-      // This is a hack to fix a problem with cmCustomCommand
-      // The cmCustomCommand should store the arguments as a vector
-      // and not a string, and the cmAddCustomTargetCommand should
-      // not EscapeSpaces.
-      args.push_back("This is really a single argument do not escape spaces");
-      args.push_back(cc.GetArguments());
-      m_Makefile->AddCustomCommandToOutput(output, 
-                                           cc.GetCommand().c_str(), 
-                                           args, 
-                                           0, 
-                                           cc.GetDepends());
+      const char* no_main_dependency = 0;
+      const char* no_comment = 0;
+      m_Makefile->AddCustomCommandToOutput(output,
+                                           cr->GetDepends(),
+                                           no_main_dependency,
+                                           cr->GetCommandLines(),
+                                           no_comment);
       cmSourceFile* outsf = 
         m_Makefile->GetSourceFileWithOutput(output);
       target.GetSourceFiles().push_back(outsf);
@@ -380,18 +372,13 @@ void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
           }
         if (command)
           {
-          std::string totalCommandStr;
-          totalCommandStr = 
-            this->ConvertToRelativeOutputPath(command->GetCommand().c_str()); 
-          totalCommandStr += " ";
-          totalCommandStr += command->GetArguments();
-          totalCommandStr += "\n";
-          const char* comment = command->GetComment().c_str();
+          std::string script = this->ConstructScript(command->GetCommandLines());
+          const char* comment = command->GetComment();
           const char* flags = compileFlags.size() ? compileFlags.c_str(): 0;
-          this->WriteCustomRule(fout, source.c_str(), totalCommandStr.c_str(), 
+          this->WriteCustomRule(fout, source.c_str(), script.c_str(), 
                                 (*comment?comment:"Custom Rule"),
                                 command->GetDepends(), 
-                                command->GetOutput().c_str(), flags);
+                                command->GetOutput(), flags);
           }
         else if(compileFlags.size())
           {
@@ -635,8 +622,6 @@ cmLocalVisualStudio6Generator::CreateTargetRules(const cmTarget &target,
          target.GetPreBuildCommands().begin(); 
        cr != target.GetPreBuildCommands().end(); ++cr)
     {
-    cmCustomCommand cc(*cr);
-    cc.ExpandVariables(*m_Makefile);
     if (!init)
       {
       // header stuff
@@ -647,15 +632,13 @@ cmLocalVisualStudio6Generator::CreateTargetRules(const cmTarget &target,
       {
       customRuleCode += "\\\n\t";
       }
-    customRuleCode += this->ConvertToRelativeOutputPath(cc.GetCommand().c_str()) + " " + cc.GetArguments();
+    customRuleCode += this->ConstructScript(cr->GetCommandLines(), "\\\n\t");
     }
 
   for (std::vector<cmCustomCommand>::const_iterator cr = 
          target.GetPreLinkCommands().begin(); 
        cr != target.GetPreLinkCommands().end(); ++cr)
     {
-    cmCustomCommand cc(*cr);
-    cc.ExpandVariables(*m_Makefile);
     if (!init)
       {
       // header stuff
@@ -666,7 +649,7 @@ cmLocalVisualStudio6Generator::CreateTargetRules(const cmTarget &target,
       {
       customRuleCode += "\\\n\t";
       }
-    customRuleCode += this->ConvertToRelativeOutputPath(cc.GetCommand().c_str()) + " " + cc.GetArguments();
+    customRuleCode += this->ConstructScript(cr->GetCommandLines(), "\\\n\t");
     }
 
   // do the post build rules
@@ -675,8 +658,6 @@ cmLocalVisualStudio6Generator::CreateTargetRules(const cmTarget &target,
          target.GetPostBuildCommands().begin(); 
        cr != target.GetPostBuildCommands().end(); ++cr)
     {
-    cmCustomCommand cc(*cr);
-    cc.ExpandVariables(*m_Makefile);
     if (!init)
       {
       // header stuff
@@ -687,9 +668,7 @@ cmLocalVisualStudio6Generator::CreateTargetRules(const cmTarget &target,
       {
       customRuleCode += "\\\n\t";
       }
-    customRuleCode += 
-      this->ConvertToRelativeOutputPath(cc.GetCommand().c_str()) + 
-      " " + cc.GetArguments();
+    customRuleCode += this->ConstructScript(cr->GetCommandLines(), "\\\n\t");
     }
 
   customRuleCode += "\n# End Special Build Tool\n";