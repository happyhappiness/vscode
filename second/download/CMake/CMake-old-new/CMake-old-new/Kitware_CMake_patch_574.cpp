@@ -215,6 +215,8 @@ void cmLocalVisualStudio6Generator::AddDSPBuildRule(cmTarget& tgt)
   std::string makefileIn = this->Makefile->GetStartDirectory();
   makefileIn += "/";
   makefileIn += "CMakeLists.txt";
+  std::string comment = "Building Custom Rule ";
+  comment += makefileIn;
   std::string args;
   args = "-H";
   args +=
@@ -246,10 +248,11 @@ void cmLocalVisualStudio6Generator::AddDSPBuildRule(cmTarget& tgt)
 
   cmCustomCommandLines commandLines;
   commandLines.push_back(commandLine);
-  const char* no_comment = 0;
   const char* no_working_directory = 0;
-  this->Makefile->AddCustomCommandToOutput(dspname.c_str(), listFiles, makefileIn.c_str(),
-                                       commandLines, no_comment, no_working_directory, true);
+  this->Makefile->AddCustomCommandToOutput(dspname.c_str(), listFiles,
+                                           makefileIn.c_str(), commandLines,
+                                           comment.c_str(),
+                                           no_working_directory, true);
   if(cmSourceFile* file = this->Makefile->GetSource(makefileIn.c_str()))
     {
     tgt.GetSourceFiles().push_back(file);
@@ -443,12 +446,17 @@ void cmLocalVisualStudio6Generator::WriteGroup(const cmSourceGroup *sg, cmTarget
           this->ConstructScript(command->GetCommandLines(), 
                                 command->GetWorkingDirectory(),
                                 "\\\n\t");
-        const char* comment = command->GetComment();
+        std::string comment =
+          this->ConstructComment(*command,
+                                 "Building Custom Rule $(InputPath)");
+        if(comment == "<hack>")
+          {
+          comment = "";
+          }
         const char* flags = compileFlags.size() ? compileFlags.c_str(): 0;
-        this->WriteCustomRule(fout, source.c_str(), script.c_str(), 
-                              (*comment?comment:"Custom Rule"),
-                              command->GetDepends(), 
-                              command->GetOutput(), flags);
+        this->WriteCustomRule(fout, source.c_str(), script.c_str(),
+                              comment.c_str(), command->GetDepends(),
+                              command->GetOutputs(), flags);
         }
       else if(compileFlags.size())
         {
@@ -501,14 +509,15 @@ ::AddUtilityCommandHack(cmTarget& target, int count,
                            strlen(target.GetName()) + 30)];
   sprintf(output,"%s/%s_force_%i", this->Makefile->GetStartOutputDirectory(),
           target.GetName(), count);
+  std::string comment = this->ConstructComment(origCommand, "<hack>");
 
   // Add the rule with the given dependencies and commands.
   const char* no_main_dependency = 0;
   this->Makefile->AddCustomCommandToOutput(output,
                                        depends,
                                        no_main_dependency,
                                        origCommand.GetCommandLines(),
-                                       origCommand.GetComment(),
+                                       comment.c_str(),
                                        origCommand.GetWorkingDirectory());
 
   // Replace the dependencies with the output of this rule so that the
@@ -524,15 +533,17 @@ ::AddUtilityCommandHack(cmTarget& target, int count,
   delete [] output;
 }
 
-void cmLocalVisualStudio6Generator::WriteCustomRule(std::ostream& fout,
-                                                    const char* source,
-                                                    const char* command,
-                                                    const char* comment,
-                                                    const std::vector<std::string>& depends,
-                                                    const char *output,
-                                                    const char* flags
-  )
+void
+cmLocalVisualStudio6Generator
+::WriteCustomRule(std::ostream& fout,
+                  const char* source,
+                  const char* command,
+                  const char* comment,
+                  const std::vector<std::string>& depends,
+                  const std::vector<std::string>& outputs,
+                  const char* flags)
 {
+  // Write the rule for each configuration.
   std::vector<std::string>::iterator i;
   for(i = this->Configurations.begin(); i != this->Configurations.end(); ++i)
     {
@@ -561,18 +572,28 @@ void cmLocalVisualStudio6Generator::WriteCustomRule(std::ostream& fout,
     fout << "\n";
 
     fout << "# PROP Ignore_Default_Tool 1\n";
-    fout << "# Begin Custom Build - Building " << comment 
-         << " $(InputPath)\n\n";
-    if(output == 0)
+    fout << "# Begin Custom Build -";
+    if(comment && *comment)
+      {
+      fout << " " << comment;
+      }
+    fout << "\n\n";
+    if(outputs.empty())
       {
       fout << source << "_force :  \"$(SOURCE)\" \"$(INTDIR)\" \"$(OUTDIR)\"\n\t";
       fout << command << "\n\n";
       }
-    
-    // Write a rule for every output generated by this command.
-    fout << this->ConvertToOptionallyRelativeOutputPath(output)
-         << " :  \"$(SOURCE)\" \"$(INTDIR)\" \"$(OUTDIR)\"\n\t";
-    fout << command << "\n\n";
+    else
+      {
+      for(std::vector<std::string>::const_iterator o = outputs.begin();
+          o != outputs.end(); ++o)
+        {
+        // Write a rule for every output generated by this command.
+        fout << this->ConvertToOptionallyRelativeOutputPath(o->c_str())
+             << " :  \"$(SOURCE)\" \"$(INTDIR)\" \"$(OUTDIR)\"\n\t";
+        fout << command << "\n\n";
+        }
+      }
     fout << "# End Custom Build\n\n";
     }
   