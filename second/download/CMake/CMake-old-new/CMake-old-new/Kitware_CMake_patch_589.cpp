@@ -217,35 +217,48 @@ void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
     this->AddDSPBuildRule();
     }
 
-  // for utility targets need custom command since post build doesn't
-  // do anything (Visual Studio 7 seems to do this correctly without 
-  // the hack)
-  if (target.GetType() == cmTarget::UTILITY && 
-      target.GetPostBuildCommands().size())
+  // For utility targets need custom command since pre- and post-
+  // build does not do anything in Visual Studio 6.  In order for the
+  // rules to run in the correct order as custom commands, we need
+  // special care for dependencies.  The first rule must depend on all
+  // the dependencies of all the rules.  The later rules must each
+  // depend only on the previous rule.
+  if (target.GetType() == cmTarget::UTILITY &&
+      (!target.GetPreBuildCommands().empty() ||
+       !target.GetPostBuildCommands().empty()))
     {
+    // Accumulate the dependencies of all the commands.
+    std::vector<std::string> depends;
+    for (std::vector<cmCustomCommand>::const_iterator cr =
+           target.GetPreBuildCommands().begin();
+         cr != target.GetPreBuildCommands().end(); ++cr)
+      {
+      depends.insert(depends.end(),
+                     cr->GetDepends().begin(), cr->GetDepends().end());
+      }
+    for (std::vector<cmCustomCommand>::const_iterator cr =
+           target.GetPostBuildCommands().begin();
+         cr != target.GetPostBuildCommands().end(); ++cr)
+      {
+      depends.insert(depends.end(),
+                     cr->GetDepends().begin(), cr->GetDepends().end());
+      }
+
+    // Add the pre- and post-build commands in order.
     int count = 1;
-    for (std::vector<cmCustomCommand>::const_iterator cr = 
-           target.GetPostBuildCommands().begin(); 
+    for (std::vector<cmCustomCommand>::const_iterator cr =
+           target.GetPreBuildCommands().begin();
+         cr != target.GetPreBuildCommands().end(); ++cr)
+      {
+      this->AddUtilityCommandHack(target, count++, depends,
+                                  cr->GetCommandLines());
+      }
+    for (std::vector<cmCustomCommand>::const_iterator cr =
+           target.GetPostBuildCommands().begin();
          cr != target.GetPostBuildCommands().end(); ++cr)
       {
-      char *output = new char [
-        strlen(m_Makefile->GetStartOutputDirectory()) + 
-        strlen(libName) + 30];
-      sprintf(output,"%s/%s_force_%i",
-              m_Makefile->GetStartOutputDirectory(),
-              libName, count);
-      const char* no_main_dependency = 0;
-      const char* no_comment = 0;
-      m_Makefile->AddCustomCommandToOutput(output,
-                                           cr->GetDepends(),
-                                           no_main_dependency,
-                                           cr->GetCommandLines(),
-                                           no_comment);
-      cmSourceFile* outsf = 
-        m_Makefile->GetSourceFileWithOutput(output);
-      target.GetSourceFiles().push_back(outsf);
-      count++;
-      delete [] output;
+      this->AddUtilityCommandHack(target, count++, depends,
+                                  cr->GetCommandLines());
       }
     }
   
@@ -409,6 +422,40 @@ void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
 }
 
 
+void
+cmLocalVisualStudio6Generator
+::AddUtilityCommandHack(cmTarget& target, int count,
+                        std::vector<std::string>& depends,
+                        const cmCustomCommandLines& commandLines)
+{
+  // Create a fake output that forces the rule to run.
+  char* output = new char[(strlen(m_Makefile->GetStartOutputDirectory()) +
+                           strlen(target.GetName()) + 30)];
+  sprintf(output,"%s/%s_force_%i", m_Makefile->GetStartOutputDirectory(),
+          target.GetName(), count);
+
+  // Add the rule with the given dependencies and commands.
+  const char* no_main_dependency = 0;
+  const char* no_comment = 0;
+  m_Makefile->AddCustomCommandToOutput(output,
+                                       depends,
+                                       no_main_dependency,
+                                       commandLines,
+                                       no_comment);
+
+  // Replace the dependencies with the output of this rule so that the
+  // next rule added will run after this one.
+  depends.clear();
+  depends.push_back(output);
+
+  // Add a source file representing this output to the project.
+  cmSourceFile* outsf = m_Makefile->GetSourceFileWithOutput(output);
+  target.GetSourceFiles().push_back(outsf);
+
+  // Free the fake output name.
+  delete [] output;
+}
+
 void cmLocalVisualStudio6Generator::WriteCustomRule(std::ostream& fout,
                                   const char* source,
                                   const char* command,