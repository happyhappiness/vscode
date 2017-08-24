@@ -98,7 +98,7 @@ void cmLocalVisualStudio6Generator::AddCMakeListsRules()
       this->Makefile->GetDefinition("CMAKE_SUPPRESS_REGENERATION");
     if (!cmSystemTools::IsOn(suppRegenRule))
       {
-      this->AddDSPBuildRule(*(*l)->Target);
+      this->AddDSPBuildRule(*l);
       }
     }
 }
@@ -133,21 +133,21 @@ void cmLocalVisualStudio6Generator::OutputDSPFile()
       case cmState::STATIC_LIBRARY:
       case cmState::OBJECT_LIBRARY:
         this->SetBuildType(STATIC_LIBRARY,
-                           (*l)->GetName().c_str(), *(*l)->Target);
+                           (*l)->GetName().c_str(), *l);
         break;
       case cmState::SHARED_LIBRARY:
       case cmState::MODULE_LIBRARY:
         this->SetBuildType(DLL,
-                           (*l)->GetName().c_str(), *(*l)->Target);
+                           (*l)->GetName().c_str(), *l);
         break;
       case cmState::EXECUTABLE:
         this->SetBuildType(EXECUTABLE,
-                           (*l)->GetName().c_str(), *(*l)->Target);
+                           (*l)->GetName().c_str(), *l);
         break;
       case cmState::UTILITY:
       case cmState::GLOBAL_TARGET:
         this->SetBuildType(UTILITY,
-                           (*l)->GetName().c_str(), *(*l)->Target);
+                           (*l)->GetName().c_str(), *l);
         break;
       case cmState::INTERFACE_LIBRARY:
         continue;
@@ -173,7 +173,7 @@ void cmLocalVisualStudio6Generator::OutputDSPFile()
           cmSystemTools::Error("Error creating directory: ", dir.c_str());
           }
         }
-      this->CreateSingleDSP((*l)->GetName().c_str(), *(*l)->Target);
+      this->CreateSingleDSP((*l)->GetName().c_str(), *l);
       }
     }
 }
@@ -184,7 +184,7 @@ void cmLocalVisualStudio6Generator::OutputDSPFile()
 extern std::string GetVS6TargetName(const std::string& targetName);
 
 void cmLocalVisualStudio6Generator::CreateSingleDSP(const std::string& lname,
-                                                    cmTarget &target)
+                                                    cmGeneratorTarget* target)
 {
   // add to the list of projects
   std::string pname = GetVS6TargetName(lname);
@@ -211,9 +211,9 @@ void cmLocalVisualStudio6Generator::CreateSingleDSP(const std::string& lname,
 }
 
 
-void cmLocalVisualStudio6Generator::AddDSPBuildRule(cmTarget& tgt)
+void cmLocalVisualStudio6Generator::AddDSPBuildRule(cmGeneratorTarget *tgt)
 {
-  std::string dspname = GetVS6TargetName(tgt.GetName());
+  std::string dspname = GetVS6TargetName(tgt->GetName());
   dspname += ".dsp.cmake";
   cmCustomCommandLine commandLine;
   commandLine.push_back(cmSystemTools::GetCMakeCommand());
@@ -245,8 +245,7 @@ void cmLocalVisualStudio6Generator::AddDSPBuildRule(cmTarget& tgt)
                                            no_working_directory, true);
   if(this->Makefile->GetSource(makefileIn.c_str()))
     {
-    cmGeneratorTarget* gt = this->GlobalGenerator->GetGeneratorTarget(&tgt);
-    gt->AddSource(makefileIn);
+    tgt->AddSource(makefileIn);
     }
   else
     {
@@ -257,31 +256,31 @@ void cmLocalVisualStudio6Generator::AddDSPBuildRule(cmTarget& tgt)
 
 void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
                                                  const std::string& libName,
-                                                 cmTarget &target)
+                                                 cmGeneratorTarget *target)
 {
   // For utility targets need custom command since pre- and post-
   // build does not do anything in Visual Studio 6.  In order for the
   // rules to run in the correct order as custom commands, we need
   // special care for dependencies.  The first rule must depend on all
   // the dependencies of all the rules.  The later rules must each
   // depend only on the previous rule.
-  if ((target.GetType() == cmState::UTILITY ||
-      target.GetType() == cmState::GLOBAL_TARGET) &&
-      (!target.GetPreBuildCommands().empty() ||
-       !target.GetPostBuildCommands().empty()))
+  if ((target->GetType() == cmState::UTILITY ||
+      target->GetType() == cmState::GLOBAL_TARGET) &&
+      (!target->Target->GetPreBuildCommands().empty() ||
+       !target->Target->GetPostBuildCommands().empty()))
     {
     // Accumulate the dependencies of all the commands.
     std::vector<std::string> depends;
     for (std::vector<cmCustomCommand>::const_iterator cr =
-           target.GetPreBuildCommands().begin();
-         cr != target.GetPreBuildCommands().end(); ++cr)
+           target->Target->GetPreBuildCommands().begin();
+         cr != target->Target->GetPreBuildCommands().end(); ++cr)
       {
       depends.insert(depends.end(),
                      cr->GetDepends().begin(), cr->GetDepends().end());
       }
     for (std::vector<cmCustomCommand>::const_iterator cr =
-           target.GetPostBuildCommands().begin();
-         cr != target.GetPostBuildCommands().end(); ++cr)
+           target->Target->GetPostBuildCommands().begin();
+         cr != target->Target->GetPostBuildCommands().end(); ++cr)
       {
       depends.insert(depends.end(),
                      cr->GetDepends().begin(), cr->GetDepends().end());
@@ -290,14 +289,14 @@ void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
     // Add the pre- and post-build commands in order.
     int count = 1;
     for (std::vector<cmCustomCommand>::const_iterator cr =
-           target.GetPreBuildCommands().begin();
-         cr != target.GetPreBuildCommands().end(); ++cr)
+           target->Target->GetPreBuildCommands().begin();
+         cr != target->Target->GetPreBuildCommands().end(); ++cr)
       {
       this->AddUtilityCommandHack(target, count++, depends, *cr);
       }
     for (std::vector<cmCustomCommand>::const_iterator cr =
-           target.GetPostBuildCommands().begin();
-         cr != target.GetPostBuildCommands().end(); ++cr)
+           target->Target->GetPostBuildCommands().begin();
+         cr != target->Target->GetPostBuildCommands().end(); ++cr)
       {
       this->AddUtilityCommandHack(target, count++, depends, *cr);
       }
@@ -306,12 +305,9 @@ void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
   // We may be modifying the source groups temporarily, so make a copy.
   std::vector<cmSourceGroup> sourceGroups = this->Makefile->GetSourceGroups();
 
-  cmGeneratorTarget* gt =
-    this->GlobalGenerator->GetGeneratorTarget(&target);
-
   // get the classes from the source lists then add them to the groups
   std::vector<cmSourceFile*> classes;
-  if (!gt->GetConfigCommonSourceFiles(classes))
+  if (!target->GetConfigCommonSourceFiles(classes))
     {
     return;
     }
@@ -375,11 +371,9 @@ void cmLocalVisualStudio6Generator::WriteDSPFile(std::ostream& fout,
 }
 
 void cmLocalVisualStudio6Generator
-::WriteGroup(const cmSourceGroup *sg, cmTarget& target,
+::WriteGroup(const cmSourceGroup *sg, cmGeneratorTarget* target,
              std::ostream &fout, const std::string& libName)
 {
-  cmGeneratorTarget* gt =
-    this->GlobalGenerator->GetGeneratorTarget(&target);
   const std::vector<const cmSourceFile *> &sourceFiles =
     sg->GetSourceFiles();
   // If the group is empty, don't write it at all.
@@ -411,9 +405,10 @@ ::WriteGroup(const cmSourceGroup *sg, cmTarget& target,
     std::string compileFlags;
     std::vector<std::string> depends;
     std::string objectNameDir;
-    if(gt->HasExplicitObjectName(*sf))
+    if(target->HasExplicitObjectName(*sf))
       {
-      objectNameDir = cmSystemTools::GetFilenamePath(gt->GetObjectName(*sf));
+      objectNameDir =
+          cmSystemTools::GetFilenamePath(target->GetObjectName(*sf));
       }
 
     // Add per-source file flags.
@@ -484,8 +479,8 @@ ::WriteGroup(const cmSourceGroup *sg, cmTarget& target,
       cmSystemTools::ExpandListArgument(dependsValue, depends);
       }
     if (GetVS6TargetName(source) != libName ||
-      target.GetType() == cmState::UTILITY ||
-      target.GetType() == cmState::GLOBAL_TARGET)
+      target->GetType() == cmState::UTILITY ||
+      target->GetType() == cmState::GLOBAL_TARGET)
       {
       fout << "# Begin Source File\n\n";
 
@@ -575,15 +570,15 @@ ::WriteGroup(const cmSourceGroup *sg, cmTarget& target,
 
 void
 cmLocalVisualStudio6Generator
-::AddUtilityCommandHack(cmTarget& target, int count,
+::AddUtilityCommandHack(cmGeneratorTarget *target, int count,
                         std::vector<std::string>& depends,
                         const cmCustomCommand& origCommand)
 {
   // Create a fake output that forces the rule to run.
   char* output = new char[(strlen(this->GetCurrentBinaryDirectory())
-                           + target.GetName().size() + 30)];
+                           + target->GetName().size() + 30)];
   sprintf(output,"%s/%s_force_%i", this->GetCurrentBinaryDirectory(),
-          target.GetName().c_str(), count);
+          target->GetName().c_str(), count);
   const char* comment = origCommand.GetComment();
   if(!comment && origCommand.GetOutputs().empty())
     {
@@ -598,8 +593,7 @@ ::AddUtilityCommandHack(cmTarget& target, int count,
        origCommand.GetCommandLines(), comment,
        origCommand.GetWorkingDirectory().c_str()))
     {
-    cmGeneratorTarget* gt = this->GlobalGenerator->GetGeneratorTarget(&target);
-    gt->AddSource(outsf->GetFullPath());
+    target->AddSource(outsf->GetFullPath());
     }
 
   // Replace the dependencies with the output of this rule so that the
@@ -715,7 +709,7 @@ void cmLocalVisualStudio6Generator::WriteDSPEndGroup(std::ostream& fout)
 
 void cmLocalVisualStudio6Generator::SetBuildType(BuildType b,
                                                  const std::string& libName,
-                                                 cmTarget& target)
+                                                 cmGeneratorTarget *target)
 {
   std::string root= this->Makefile->GetRequiredDefinition("CMAKE_ROOT");
   const char *def=
@@ -747,7 +741,7 @@ void cmLocalVisualStudio6Generator::SetBuildType(BuildType b,
       this->DSPFooterTemplate += "/DLLFooter.dsptemplate";
       break;
     case EXECUTABLE:
-      if ( target.GetPropertyAsBool("WIN32_EXECUTABLE") )
+      if ( target->GetPropertyAsBool("WIN32_EXECUTABLE") )
         {
         this->DSPHeaderTemplate = root;
         this->DSPHeaderTemplate += "/EXEWinHeader.dsptemplate";
@@ -799,19 +793,16 @@ void cmLocalVisualStudio6Generator::SetBuildType(BuildType b,
 
 //----------------------------------------------------------------------------
 cmsys::auto_ptr<cmCustomCommand>
-cmLocalVisualStudio6Generator::MaybeCreateOutputDir(cmTarget& target,
+cmLocalVisualStudio6Generator::MaybeCreateOutputDir(cmGeneratorTarget* target,
                                                     const std::string& config)
 {
   cmsys::auto_ptr<cmCustomCommand> pcc;
 
   // VS6 forgets to create the output directory for archives if it
   // differs from the intermediate directory.
-  if(target.GetType() != cmState::STATIC_LIBRARY) { return pcc; }
-
-  cmGeneratorTarget* gt =
-    this->GlobalGenerator->GetGeneratorTarget(&target);
+  if(target->GetType() != cmState::STATIC_LIBRARY) { return pcc; }
 
-  std::string outDir = gt->GetDirectory(config, false);
+  std::string outDir = target->GetDirectory(config, false);
 
   // Add a pre-link event to create the directory.
   cmCustomCommandLine command;
@@ -833,11 +824,11 @@ cmLocalVisualStudio6Generator::MaybeCreateOutputDir(cmTarget& target,
 
 // look for custom rules on a target and collect them together
 std::string
-cmLocalVisualStudio6Generator::CreateTargetRules(cmTarget &target,
+cmLocalVisualStudio6Generator::CreateTargetRules(cmGeneratorTarget *target,
                                               const std::string& configName,
                                               const std::string& /* libName */)
 {
-  if (target.GetType() >= cmState::UTILITY )
+  if (target->GetType() >= cmState::UTILITY )
     {
     return "";
     }
@@ -847,10 +838,10 @@ cmLocalVisualStudio6Generator::CreateTargetRules(cmTarget &target,
 
   // Write the pre-build and pre-link together (VS6 does not support both).
   event.Start("PreLink");
-  event.Write(target.GetPreBuildCommands());
-  event.Write(target.GetPreLinkCommands());
+  event.Write(target->Target->GetPreBuildCommands());
+  event.Write(target->Target->GetPreLinkCommands());
   cmsys::auto_ptr<cmCustomCommand> pcc(
-    this->MaybeCreateImplibDir(target, configName, false));
+    this->MaybeCreateImplibDir(*target->Target, configName, false));
   if(pcc.get())
     {
     event.Write(*pcc);
@@ -864,7 +855,7 @@ cmLocalVisualStudio6Generator::CreateTargetRules(cmTarget &target,
 
   // Write the post-build rules.
   event.Start("PostBuild");
-  event.Write(target.GetPostBuildCommands());
+  event.Write(target->Target->GetPostBuildCommands());
   event.Finish();
 
   customRuleCode += "# End Special Build Tool\n";
@@ -883,7 +874,8 @@ inline std::string removeQuotes(const std::string& s)
 
 
 std::string
-cmLocalVisualStudio6Generator::GetTargetIncludeOptions(cmTarget &target,
+cmLocalVisualStudio6Generator::GetTargetIncludeOptions(
+        cmGeneratorTarget *target,
                                                   const std::string& config)
 {
   std::string includeOptions;
@@ -894,12 +886,10 @@ cmLocalVisualStudio6Generator::GetTargetIncludeOptions(cmTarget &target,
   unsigned int maxIncludeLength = 3000;
   bool useShortPath = false;
 
-  cmGeneratorTarget* gt =
-    this->GlobalGenerator->GetGeneratorTarget(&target);
   for(int j=0; j < 2; ++j)
     {
     std::vector<std::string> includes;
-    this->GetIncludeDirectories(includes, gt, "C", config);
+    this->GetIncludeDirectories(includes, target, "C", config);
 
     std::vector<std::string>::iterator i;
     for(i = includes.begin(); i != includes.end(); ++i)
@@ -947,11 +937,11 @@ cmLocalVisualStudio6Generator::GetTargetIncludeOptions(cmTarget &target,
 
 void cmLocalVisualStudio6Generator
 ::WriteDSPHeader(std::ostream& fout,
-                 const std::string& libName, cmTarget &target,
+                 const std::string& libName, cmGeneratorTarget* target,
                  std::vector<cmSourceGroup> &)
 {
-  bool targetBuilds = (target.GetType() >= cmState::EXECUTABLE &&
-                       target.GetType() <= cmState::MODULE_LIBRARY);
+  bool targetBuilds = (target->GetType() >= cmState::EXECUTABLE &&
+                       target->GetType() <= cmState::MODULE_LIBRARY);
 #ifdef CM_USE_OLD_VS6
   // Lookup the library and executable output directories.
   std::string libPath;
@@ -1061,7 +1051,8 @@ ::WriteDSPHeader(std::ostream& fout,
       }
     }
   std::vector<std::string>::const_iterator i;
-  const std::vector<std::string>& libdirs = target.GetLinkDirectories();
+  const std::vector<std::string>& libdirs =
+      target->Target->GetLinkDirectories();
   for(i = libdirs.begin(); i != libdirs.end(); ++i)
     {
     std::string path = *i;
@@ -1103,19 +1094,19 @@ ::WriteDSPHeader(std::ostream& fout,
     }
   // find link libraries
   const cmTarget::LinkLibraryVectorType& libs =
-    target.GetLinkLibrariesForVS6();
+    target->Target->GetLinkLibrariesForVS6();
   cmTarget::LinkLibraryVectorType::const_iterator j;
   for(j = libs.begin(); j != libs.end(); ++j)
     {
     // add libraries to executables and dlls (but never include
     // a library in a library, bad recursion)
     // NEVER LINK STATIC LIBRARIES TO OTHER STATIC LIBRARIES
-    if ((target.GetType() != cmState::SHARED_LIBRARY
-         && target.GetType() != cmState::STATIC_LIBRARY
-         && target.GetType() != cmState::MODULE_LIBRARY) ||
-        (target.GetType()==cmState::SHARED_LIBRARY
+    if ((target->GetType() != cmState::SHARED_LIBRARY
+         && target->GetType() != cmState::STATIC_LIBRARY
+         && target->GetType() != cmState::MODULE_LIBRARY) ||
+        (target->GetType()==cmState::SHARED_LIBRARY
          && libName != GetVS6TargetName(j->first)) ||
-        (target.GetType()==cmState::MODULE_LIBRARY
+        (target->GetType()==cmState::MODULE_LIBRARY
          && libName != GetVS6TargetName(j->first)))
       {
       // Compute the proper name to use to link this library.
@@ -1197,7 +1188,7 @@ ::WriteDSPHeader(std::ostream& fout,
   std::string extraLinkOptionsRelease;
   std::string extraLinkOptionsMinSizeRel;
   std::string extraLinkOptionsRelWithDebInfo;
-  if(target.GetType() == cmState::EXECUTABLE)
+  if(target->GetType() == cmState::EXECUTABLE)
     {
     extraLinkOptions = this->Makefile->
       GetRequiredDefinition("CMAKE_EXE_LINKER_FLAGS");
@@ -1210,7 +1201,7 @@ ::WriteDSPHeader(std::ostream& fout,
     extraLinkOptionsRelWithDebInfo = this->Makefile->
       GetRequiredDefinition("CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO");
     }
-  if(target.GetType() == cmState::SHARED_LIBRARY)
+  if(target->GetType() == cmState::SHARED_LIBRARY)
     {
     extraLinkOptions = this->Makefile->
       GetRequiredDefinition("CMAKE_SHARED_LINKER_FLAGS");
@@ -1223,7 +1214,7 @@ ::WriteDSPHeader(std::ostream& fout,
     extraLinkOptionsRelWithDebInfo = this->Makefile->
       GetRequiredDefinition("CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO");
     }
-  if(target.GetType() == cmState::MODULE_LIBRARY)
+  if(target->GetType() == cmState::MODULE_LIBRARY)
     {
     extraLinkOptions = this->Makefile->
       GetRequiredDefinition("CMAKE_MODULE_LINKER_FLAGS");
@@ -1238,63 +1229,61 @@ ::WriteDSPHeader(std::ostream& fout,
     }
 
   // Get extra linker options for this target.
-  if(const char* targetLinkFlags = target.GetProperty("LINK_FLAGS"))
+  if(const char* targetLinkFlags = target->GetProperty("LINK_FLAGS"))
     {
     extraLinkOptions += " ";
     extraLinkOptions += targetLinkFlags;
     }
 
-  if(const char* targetLinkFlags = target.GetProperty("LINK_FLAGS_DEBUG"))
+  if(const char* targetLinkFlags = target->GetProperty("LINK_FLAGS_DEBUG"))
     {
     extraLinkOptionsDebug += " ";
     extraLinkOptionsDebug += targetLinkFlags;
     }
 
-  if(const char* targetLinkFlags = target.GetProperty("LINK_FLAGS_RELEASE"))
+  if(const char* targetLinkFlags = target->GetProperty("LINK_FLAGS_RELEASE"))
     {
     extraLinkOptionsRelease += " ";
     extraLinkOptionsRelease += targetLinkFlags;
     }
 
-  if(const char* targetLinkFlags = target.GetProperty("LINK_FLAGS_MINSIZEREL"))
+  if(const char* targetLinkFlags =
+     target->GetProperty("LINK_FLAGS_MINSIZEREL"))
     {
     extraLinkOptionsMinSizeRel += " ";
     extraLinkOptionsMinSizeRel += targetLinkFlags;
     }
 
   if(const char* targetLinkFlags =
-     target.GetProperty("LINK_FLAGS_RELWITHDEBINFO"))
+     target->GetProperty("LINK_FLAGS_RELWITHDEBINFO"))
     {
     extraLinkOptionsRelWithDebInfo += " ";
     extraLinkOptionsRelWithDebInfo += targetLinkFlags;
     }
 
-  cmGeneratorTarget* gt =
-    this->GlobalGenerator->GetGeneratorTarget(&target);
-
   // Get standard libraries for this language.
   if(targetBuilds)
     {
     // Get the language to use for linking.
     std::vector<std::string> configs;
-    target.GetMakefile()->GetConfigurations(configs);
+    target->Target->GetMakefile()->GetConfigurations(configs);
     std::vector<std::string>::const_iterator it = configs.begin();
-    const std::string& linkLanguage = gt->GetLinkerLanguage(*it);
+    const std::string& linkLanguage = target->GetLinkerLanguage(*it);
     for ( ; it != configs.end(); ++it)
       {
-      const std::string& configLinkLanguage = gt->GetLinkerLanguage(*it);
+      const std::string& configLinkLanguage = target->GetLinkerLanguage(*it);
       if (configLinkLanguage != linkLanguage)
         {
         cmSystemTools::Error
           ("Linker language must not vary by configuration for target: ",
-          target.GetName().c_str());
+          target->GetName().c_str());
         }
       }
     if(linkLanguage.empty())
       {
       cmSystemTools::Error
         ("CMake can not determine linker language for target: ",
-         target.GetName().c_str());
+         target->GetName().c_str());
       return;
       }
 
@@ -1315,13 +1304,13 @@ ::WriteDSPHeader(std::ostream& fout,
 
   // Compute version number information.
   std::string targetVersionFlag;
-  if(target.GetType() == cmState::EXECUTABLE ||
-     target.GetType() == cmState::SHARED_LIBRARY ||
-     target.GetType() == cmState::MODULE_LIBRARY)
+  if(target->GetType() == cmState::EXECUTABLE ||
+     target->GetType() == cmState::SHARED_LIBRARY ||
+     target->GetType() == cmState::MODULE_LIBRARY)
     {
     int major;
     int minor;
-    gt->GetTargetVersion(major, minor);
+    target->GetTargetVersion(major, minor);
     std::ostringstream targetVersionStream;
     targetVersionStream << "/version:" << major << "." << minor;
     targetVersionFlag = targetVersionStream.str();
@@ -1334,20 +1323,20 @@ ::WriteDSPHeader(std::ostream& fout,
   std::string outputNameRelease = outputName;
   std::string outputNameMinSizeRel = outputName;
   std::string outputNameRelWithDebInfo = outputName;
-  if(target.GetType() == cmState::EXECUTABLE ||
-     target.GetType() == cmState::STATIC_LIBRARY ||
-     target.GetType() == cmState::SHARED_LIBRARY ||
-     target.GetType() == cmState::MODULE_LIBRARY)
+  if(target->GetType() == cmState::EXECUTABLE ||
+     target->GetType() == cmState::STATIC_LIBRARY ||
+     target->GetType() == cmState::SHARED_LIBRARY ||
+     target->GetType() == cmState::MODULE_LIBRARY)
     {
-    outputName = gt->GetFullName();
-    outputNameDebug = gt->GetFullName("Debug");
-    outputNameRelease = gt->GetFullName("Release");
-    outputNameMinSizeRel = gt->GetFullName("MinSizeRel");
-    outputNameRelWithDebInfo = gt->GetFullName("RelWithDebInfo");
+    outputName = target->GetFullName();
+    outputNameDebug = target->GetFullName("Debug");
+    outputNameRelease = target->GetFullName("Release");
+    outputNameMinSizeRel = target->GetFullName("MinSizeRel");
+    outputNameRelWithDebInfo = target->GetFullName("RelWithDebInfo");
     }
-  else if(target.GetType() == cmState::OBJECT_LIBRARY)
+  else if(target->GetType() == cmState::OBJECT_LIBRARY)
     {
-    outputName = target.GetName();
+    outputName = target->GetName();
     outputName += ".lib";
     outputNameDebug = outputName;
     outputNameRelease = outputName;
@@ -1361,30 +1350,30 @@ ::WriteDSPHeader(std::ostream& fout,
   std::string outputDirRelease;
   std::string outputDirMinSizeRel;
   std::string outputDirRelWithDebInfo;
-  if(target.GetType() == cmState::EXECUTABLE ||
-     target.GetType() == cmState::STATIC_LIBRARY ||
-     target.GetType() == cmState::SHARED_LIBRARY ||
-     target.GetType() == cmState::MODULE_LIBRARY)
+  if(target->GetType() == cmState::EXECUTABLE ||
+     target->GetType() == cmState::STATIC_LIBRARY ||
+     target->GetType() == cmState::SHARED_LIBRARY ||
+     target->GetType() == cmState::MODULE_LIBRARY)
     {
 #ifdef CM_USE_OLD_VS6
     outputDirOld =
       removeQuotes(this->ConvertToOutputFormat
-                   (gt->GetDirectory().c_str(), SHELL));
+                   (target->GetDirectory().c_str(), SHELL));
 #endif
     outputDirDebug =
         removeQuotes(this->ConvertToOutputFormat(
-                       gt->GetDirectory("Debug").c_str(), SHELL));
+                       target->GetDirectory("Debug").c_str(), SHELL));
     outputDirRelease =
         removeQuotes(this->ConvertToOutputFormat(
-                 gt->GetDirectory("Release").c_str(), SHELL));
+                 target->GetDirectory("Release").c_str(), SHELL));
     outputDirMinSizeRel =
         removeQuotes(this->ConvertToOutputFormat(
-                 gt->GetDirectory("MinSizeRel").c_str(), SHELL));
+                 target->GetDirectory("MinSizeRel").c_str(), SHELL));
     outputDirRelWithDebInfo =
         removeQuotes(this->ConvertToOutputFormat(
-                 gt->GetDirectory("RelWithDebInfo").c_str(), SHELL));
+                 target->GetDirectory("RelWithDebInfo").c_str(), SHELL));
     }
-  else if(target.GetType() == cmState::OBJECT_LIBRARY)
+  else if(target->GetType() == cmState::OBJECT_LIBRARY)
     {
     std::string outputDir = cmake::GetCMakeFilesDirectoryPostSlash();
     outputDirDebug = outputDir + "Debug";
@@ -1398,9 +1387,9 @@ ::WriteDSPHeader(std::ostream& fout,
   std::string optionsRelease;
   std::string optionsMinSizeRel;
   std::string optionsRelWithDebInfo;
-  if(target.GetType() == cmState::EXECUTABLE ||
-     target.GetType() == cmState::SHARED_LIBRARY ||
-     target.GetType() == cmState::MODULE_LIBRARY)
+  if(target->GetType() == cmState::EXECUTABLE ||
+     target->GetType() == cmState::SHARED_LIBRARY ||
+     target->GetType() == cmState::MODULE_LIBRARY)
     {
     extraLinkOptionsDebug =
       extraLinkOptions + " " + extraLinkOptionsDebug;
@@ -1426,24 +1415,24 @@ ::WriteDSPHeader(std::ostream& fout,
   std::string targetImplibFlagRelease;
   std::string targetImplibFlagMinSizeRel;
   std::string targetImplibFlagRelWithDebInfo;
-  if(target.GetType() == cmState::SHARED_LIBRARY ||
-     target.GetType() == cmState::MODULE_LIBRARY ||
-     target.GetType() == cmState::EXECUTABLE)
+  if(target->GetType() == cmState::SHARED_LIBRARY ||
+     target->GetType() == cmState::MODULE_LIBRARY ||
+     target->GetType() == cmState::EXECUTABLE)
     {
-    std::string fullPathImpDebug = gt->GetDirectory("Debug", true);
-    std::string fullPathImpRelease = gt->GetDirectory("Release", true);
+    std::string fullPathImpDebug = target->GetDirectory("Debug", true);
+    std::string fullPathImpRelease = target->GetDirectory("Release", true);
     std::string fullPathImpMinSizeRel =
-      gt->GetDirectory("MinSizeRel", true);
+      target->GetDirectory("MinSizeRel", true);
     std::string fullPathImpRelWithDebInfo =
-      gt->GetDirectory("RelWithDebInfo", true);
+      target->GetDirectory("RelWithDebInfo", true);
     fullPathImpDebug += "/";
     fullPathImpRelease += "/";
     fullPathImpMinSizeRel += "/";
     fullPathImpRelWithDebInfo += "/";
-    fullPathImpDebug += gt->GetFullName("Debug", true);
-    fullPathImpRelease += gt->GetFullName("Release", true);
-    fullPathImpMinSizeRel += gt->GetFullName("MinSizeRel", true);
-    fullPathImpRelWithDebInfo += gt->GetFullName("RelWithDebInfo", true);
+    fullPathImpDebug += target->GetFullName("Debug", true);
+    fullPathImpRelease += target->GetFullName("Release", true);
+    fullPathImpMinSizeRel += target->GetFullName("MinSizeRel", true);
+    fullPathImpRelWithDebInfo += target->GetFullName("RelWithDebInfo", true);
 
     targetImplibFlagDebug = "/implib:";
     targetImplibFlagRelease = "/implib:";
@@ -1496,7 +1485,7 @@ ::WriteDSPHeader(std::ostream& fout,
   std::string staticLibOptionsRelease;
   std::string staticLibOptionsMinSizeRel;
   std::string staticLibOptionsRelWithDebInfo;
-  if(target.GetType() == cmState::STATIC_LIBRARY )
+  if(target->GetType() == cmState::STATIC_LIBRARY )
     {
     const char *libflagsGlobal =
       this->Makefile->GetSafeDefinition("CMAKE_STATIC_LINKER_FLAGS");
@@ -1515,21 +1504,21 @@ ::WriteDSPHeader(std::ostream& fout,
     this->AppendFlags(staticLibOptionsRelWithDebInfo, this->Makefile->
       GetSafeDefinition("CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO"));
 
-    const char *libflags = target.GetProperty("STATIC_LIBRARY_FLAGS");
+    const char *libflags = target->GetProperty("STATIC_LIBRARY_FLAGS");
     this->AppendFlags(staticLibOptions, libflags);
     this->AppendFlags(staticLibOptionsDebug, libflags);
     this->AppendFlags(staticLibOptionsRelease, libflags);
     this->AppendFlags(staticLibOptionsMinSizeRel, libflags);
     this->AppendFlags(staticLibOptionsRelWithDebInfo, libflags);
 
     this->AppendFlags(staticLibOptionsDebug,
-      target.GetProperty("STATIC_LIBRARY_FLAGS_DEBUG"));
+      target->GetProperty("STATIC_LIBRARY_FLAGS_DEBUG"));
     this->AppendFlags(staticLibOptionsRelease,
-      target.GetProperty("STATIC_LIBRARY_FLAGS_RELEASE"));
+      target->GetProperty("STATIC_LIBRARY_FLAGS_RELEASE"));
     this->AppendFlags(staticLibOptionsMinSizeRel,
-      target.GetProperty("STATIC_LIBRARY_FLAGS_MINSIZEREL"));
+      target->GetProperty("STATIC_LIBRARY_FLAGS_MINSIZEREL"));
     this->AppendFlags(staticLibOptionsRelWithDebInfo,
-      target.GetProperty("STATIC_LIBRARY_FLAGS_RELWITHDEBINFO"));
+      target->GetProperty("STATIC_LIBRARY_FLAGS_RELWITHDEBINFO"));
 
     std::string objects;
     this->OutputObjects(target, "LIB", objects);
@@ -1545,7 +1534,7 @@ ::WriteDSPHeader(std::ostream& fout,
 
   // Add the export symbol definition for shared library objects.
   std::string exportSymbol;
-  if(const char* exportMacro = gt->GetExportMacro())
+  if(const char* exportMacro = target->GetExportMacro())
     {
     exportSymbol = exportMacro;
     }
@@ -1569,8 +1558,8 @@ ::WriteDSPHeader(std::ostream& fout,
                                  libnameExports.c_str());
     cmSystemTools::ReplaceString(line, "CMAKE_MFC_FLAG",
                                  mfcFlag);
-    if(target.GetType() == cmState::STATIC_LIBRARY ||
-       target.GetType() == cmState::OBJECT_LIBRARY)
+    if(target->GetType() == cmState::STATIC_LIBRARY ||
+       target->GetType() == cmState::OBJECT_LIBRARY)
       {
       cmSystemTools::ReplaceString(line, "CM_STATIC_LIB_ARGS_DEBUG",
                                    staticLibOptionsDebug.c_str());
@@ -1676,7 +1665,7 @@ ::WriteDSPHeader(std::ostream& fout,
                     (exePath.c_str(), SHELL)).c_str());
 #endif
 
-    if(targetBuilds || target.GetType() == cmState::OBJECT_LIBRARY)
+    if(targetBuilds || target->GetType() == cmState::OBJECT_LIBRARY)
       {
       cmSystemTools::ReplaceString(line, "OUTPUT_DIRECTORY_DEBUG",
                                    outputDirDebug.c_str());
@@ -1700,8 +1689,8 @@ ::WriteDSPHeader(std::ostream& fout,
       = this->Makefile->GetDefinition("CMAKE_DEBUG_POSTFIX");
     cmSystemTools::ReplaceString(line, "DEBUG_POSTFIX",
                                  debugPostfix?debugPostfix:"");
-    if(target.GetType() >= cmState::EXECUTABLE &&
-       target.GetType() <= cmState::OBJECT_LIBRARY)
+    if(target->GetType() >= cmState::EXECUTABLE &&
+       target->GetType() <= cmState::OBJECT_LIBRARY)
       {
       // store flags for each configuration
       std::string flags = " ";
@@ -1710,24 +1699,24 @@ ::WriteDSPHeader(std::ostream& fout,
       std::string flagsDebug = " ";
       std::string flagsRelWithDebInfo = " ";
       std::vector<std::string> configs;
-      target.GetMakefile()->GetConfigurations(configs);
+      target->Target->GetMakefile()->GetConfigurations(configs);
       std::vector<std::string>::const_iterator it = configs.begin();
-      const std::string& linkLanguage = gt->GetLinkerLanguage(*it);
+      const std::string& linkLanguage = target->GetLinkerLanguage(*it);
       for ( ; it != configs.end(); ++it)
         {
-        const std::string& configLinkLanguage = gt->GetLinkerLanguage(*it);
+        const std::string& configLinkLanguage = target->GetLinkerLanguage(*it);
         if (configLinkLanguage != linkLanguage)
           {
           cmSystemTools::Error
             ("Linker language must not vary by configuration for target: ",
-            target.GetName().c_str());
+            target->GetName().c_str());
           }
         }
       if(linkLanguage.empty())
         {
         cmSystemTools::Error
           ("CMake can not determine linker language for target: ",
-           target.GetName().c_str());
+           target->GetName().c_str());
         return;
         }
       // if CXX is on and the target contains cxx code then add the cxx flags
@@ -1752,12 +1741,12 @@ ::WriteDSPHeader(std::ostream& fout,
       flagsRelWithDebInfo = this->Makefile->GetSafeDefinition(flagVar.c_str());
       flagsRelWithDebInfo += " -DCMAKE_INTDIR=\\\"RelWithDebInfo\\\" ";
 
-      this->AddCompileOptions(flags, gt, linkLanguage, "");
-      this->AddCompileOptions(flagsDebug, gt, linkLanguage, "Debug");
-      this->AddCompileOptions(flagsRelease, gt, linkLanguage, "Release");
-      this->AddCompileOptions(flagsMinSizeRel, gt, linkLanguage,
+      this->AddCompileOptions(flags, target, linkLanguage, "");
+      this->AddCompileOptions(flagsDebug, target, linkLanguage, "Debug");
+      this->AddCompileOptions(flagsRelease, target, linkLanguage, "Release");
+      this->AddCompileOptions(flagsMinSizeRel, target, linkLanguage,
                               "MinSizeRel");
-      this->AddCompileOptions(flagsRelWithDebInfo, gt, linkLanguage,
+      this->AddCompileOptions(flagsRelWithDebInfo, target, linkLanguage,
                               "RelWithDebInfo");
 
       // if _UNICODE and _SBCS are not found, then add -D_MBCS
@@ -1777,14 +1766,14 @@ ::WriteDSPHeader(std::ostream& fout,
       std::set<std::string> minsizeDefinesSet;
       std::set<std::string> debugrelDefinesSet;
 
-      this->AddCompileDefinitions(definesSet, gt, "", linkLanguage);
-      this->AddCompileDefinitions(debugDefinesSet, gt,
+      this->AddCompileDefinitions(definesSet, target, "", linkLanguage);
+      this->AddCompileDefinitions(debugDefinesSet, target,
                                   "DEBUG", linkLanguage);
-      this->AddCompileDefinitions(releaseDefinesSet, gt,
+      this->AddCompileDefinitions(releaseDefinesSet, target,
                                   "RELEASE", linkLanguage);
-      this->AddCompileDefinitions(minsizeDefinesSet, gt,
+      this->AddCompileDefinitions(minsizeDefinesSet, target,
                                   "MINSIZEREL", linkLanguage);
-      this->AddCompileDefinitions(debugrelDefinesSet, gt,
+      this->AddCompileDefinitions(debugrelDefinesSet, target,
                                   "RELWITHDEBINFO", linkLanguage);
 
       std::string defines = " ";
@@ -1852,15 +1841,13 @@ void cmLocalVisualStudio6Generator::WriteDSPFooter(std::ostream& fout)
 
 //----------------------------------------------------------------------------
 void cmLocalVisualStudio6Generator
-::ComputeLinkOptions(cmTarget& target,
+::ComputeLinkOptions(cmGeneratorTarget *target,
                      const std::string& configName,
                      const std::string extraOptions,
                      std::string& options)
 {
-  cmGeneratorTarget* gt =
-    this->GlobalGenerator->GetGeneratorTarget(&target);
   // Compute the link information for this configuration.
-  cmComputeLinkInformation* pcli = gt->GetLinkInformation(configName);
+  cmComputeLinkInformation* pcli = target->GetLinkInformation(configName);
   if(!pcli)
     {
     return;
@@ -1919,15 +1906,13 @@ ::ComputeLinkOptions(cmTarget& target,
 
 //----------------------------------------------------------------------------
 void cmLocalVisualStudio6Generator
-::OutputObjects(cmTarget& target, const char* tool,
+::OutputObjects(cmGeneratorTarget* target, const char* tool,
                 std::string& options)
 {
   // VS 6 does not support per-config source locations so we
   // list object library content on the link line instead.
-  cmGeneratorTarget* gt =
-    this->GlobalGenerator->GetGeneratorTarget(&target);
   std::vector<std::string> objs;
-  gt->UseObjectLibraries(objs, "");
+  target->UseObjectLibraries(objs, "");
   for(std::vector<std::string>::const_iterator
         oi = objs.begin(); oi != objs.end(); ++oi)
     {