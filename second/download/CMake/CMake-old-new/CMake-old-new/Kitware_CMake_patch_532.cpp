@@ -9,8 +9,8 @@
   Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
   See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
-     This software is distributed WITHOUT ANY WARRANTY; without even 
-     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+     This software is distributed WITHOUT ANY WARRANTY; without even
+     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
      PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
@@ -48,18 +48,18 @@ cmMakefile::cmMakefile()
   // Source and header file extensions that we can handle
 
   // Set up a list of source and header extensions
-  // these are used to find files when the extension 
+  // these are used to find files when the extension
   // is not given
   // The "c" extension MUST precede the "C" extension.
   this->SourceFileExtensions.push_back( "c" );
   this->SourceFileExtensions.push_back( "C" );
-  
+
   this->SourceFileExtensions.push_back( "c++" );
   this->SourceFileExtensions.push_back( "cc" );
   this->SourceFileExtensions.push_back( "cpp" );
   this->SourceFileExtensions.push_back( "cxx" );
   this->SourceFileExtensions.push_back( "m" );
-  this->SourceFileExtensions.push_back( "M" ); 
+  this->SourceFileExtensions.push_back( "M" );
   this->SourceFileExtensions.push_back( "mm" );
 
   this->HeaderFileExtensions.push_back( "h" );
@@ -70,7 +70,7 @@ cmMakefile::cmMakefile()
   this->HeaderFileExtensions.push_back( "hxx" );
   this->HeaderFileExtensions.push_back( "in" );
   this->HeaderFileExtensions.push_back( "txx" );
-  
+
   this->DefineFlags = " ";
   this->LocalGenerator = 0;
 
@@ -79,7 +79,7 @@ cmMakefile::cmMakefile()
   this->AddSourceGroup
     ("Source Files",
      "\\.(C|M|c|c\\+\\+|cc|cpp|cxx|m|mm|rc|def|r|odl|idl|hpj|bat)$");
-  this->AddSourceGroup("Header Files", 
+  this->AddSourceGroup("Header Files",
                        "\\.(h|hh|h\\+\\+|hm|hpp|hxx|in|txx|inl)$");
   this->AddSourceGroup("CMake Rules", "\\.rule$");
   this->AddSourceGroup("Resources", "\\.plist$");
@@ -95,9 +95,9 @@ cmMakefile::cmMakefile(const cmMakefile& mf)
 {
   this->Prefix = mf.Prefix;
   this->AuxSourceDirectories = mf.AuxSourceDirectories;
-  this->cmStartDirectory = mf.cmStartDirectory; 
-  this->StartOutputDirectory = mf.StartOutputDirectory; 
-  this->cmHomeDirectory = mf.cmHomeDirectory; 
+  this->cmStartDirectory = mf.cmStartDirectory;
+  this->StartOutputDirectory = mf.StartOutputDirectory;
+  this->cmHomeDirectory = mf.cmHomeDirectory;
   this->HomeOutputDirectory = mf.HomeOutputDirectory;
   this->cmCurrentListFile = mf.cmCurrentListFile;
   this->ProjectName = mf.ProjectName;
@@ -194,7 +194,7 @@ cmMakefile::~cmMakefile()
       }
     }
   std::list<cmFunctionBlocker *>::iterator pos;
-  for (pos = this->FunctionBlockers.begin(); 
+  for (pos = this->FunctionBlockers.begin();
        pos != this->FunctionBlockers.end(); ++pos)
     {
     cmFunctionBlocker* b = *pos;
@@ -203,7 +203,7 @@ cmMakefile::~cmMakefile()
   this->FunctionBlockers.clear();
 }
 
-void cmMakefile::PrintStringVector(const char* s, 
+void cmMakefile::PrintStringVector(const char* s,
                                    const std::vector<std::string>& v) const
 {
   std::cout << s << ": ( \n";
@@ -216,11 +216,11 @@ void cmMakefile::PrintStringVector(const char* s,
 }
 
 void cmMakefile
-::PrintStringVector(const char* s, 
+::PrintStringVector(const char* s,
                     const std::vector<std::pair<cmStdString, bool> >& v) const
 {
   std::cout << s << ": ( \n";
-  for(std::vector<std::pair<cmStdString, bool> >::const_iterator i 
+  for(std::vector<std::pair<cmStdString, bool> >::const_iterator i
         = v.begin(); i != v.end(); ++i)
     {
     std::cout << i->first.c_str() << " " << i->second;
@@ -242,21 +242,21 @@ void cmMakefile::Print()
     std::cout << l->first << std::endl;
     }
 
-  std::cout << " this->StartOutputDirectory; " << 
+  std::cout << " this->StartOutputDirectory; " <<
     this->StartOutputDirectory.c_str() << std::endl;
-  std::cout << " this->HomeOutputDirectory; " << 
+  std::cout << " this->HomeOutputDirectory; " <<
     this->HomeOutputDirectory.c_str() << std::endl;
-  std::cout << " this->cmStartDirectory; " << 
+  std::cout << " this->cmStartDirectory; " <<
     this->cmStartDirectory.c_str() << std::endl;
-  std::cout << " this->cmHomeDirectory; " << 
+  std::cout << " this->cmHomeDirectory; " <<
     this->cmHomeDirectory.c_str() << std::endl;
-  std::cout << " this->ProjectName; " 
+  std::cout << " this->ProjectName; "
             <<  this->ProjectName.c_str() << std::endl;
-  this->PrintStringVector("this->IncludeDirectories;", 
+  this->PrintStringVector("this->IncludeDirectories;",
                           this->IncludeDirectories);
   this->PrintStringVector("this->LinkDirectories", this->LinkDirectories);
 #if defined(CMAKE_BUILD_WITH_CMAKE)
-  for( std::vector<cmSourceGroup>::const_iterator i = 
+  for( std::vector<cmSourceGroup>::const_iterator i =
          this->SourceGroups.begin(); i != this->SourceGroups.end(); ++i)
     {
     std::cout << "Source Group: " << i->GetName() << std::endl;
@@ -281,7 +281,7 @@ bool cmMakefile::ExecuteCommand(const cmListFileFunction& lff)
 
   std::string name = lff.Name;
   // execute the command
-  cmCommand *rm = 
+  cmCommand *rm =
     this->GetCMakeInstance()->GetCommand(name.c_str());
   if(rm)
     {
@@ -307,7 +307,7 @@ bool cmMakefile::ExecuteCommand(const cmListFileFunction& lff)
     usedCommand->SetMakefile(this);
     bool keepCommand = false;
     if(usedCommand->GetEnabled() && !cmSystemTools::GetFatalErrorOccured()  &&
-       (!this->GetCMakeInstance()->GetScriptMode() || 
+       (!this->GetCMakeInstance()->GetScriptMode() ||
         usedCommand->IsScriptable()))
       {
       if(!usedCommand->InvokeInitialPass(lff.Arguments))
@@ -331,19 +331,19 @@ bool cmMakefile::ExecuteCommand(const cmListFileFunction& lff)
         this->UsedCommands.push_back(usedCommand);
         }
       }
-    else if ( this->GetCMakeInstance()->GetScriptMode() 
+    else if ( this->GetCMakeInstance()->GetScriptMode()
               && !usedCommand->IsScriptable() )
       {
       cmOStringStream error;
       error << "Error in cmake code at\n"
             << lff.FilePath << ":" << lff.Line << ":\n"
-            << "Command " << usedCommand->GetName() 
+            << "Command " << usedCommand->GetName()
             << " not scriptable" << std::endl;
       cmSystemTools::Error(error.str().c_str());
       result = false;
       cmSystemTools::SetFatalErrorOccured();
       }
-    // if the Cloned command was not used 
+    // if the Cloned command was not used
     // then delete it
     if(!keepCommand)
       {
@@ -363,13 +363,13 @@ bool cmMakefile::ExecuteCommand(const cmListFileFunction& lff)
       cmSystemTools::SetFatalErrorOccured();
       }
     }
-  
+
   return result;
 }
 
 // Parse the given CMakeLists.txt file executing all commands
 //
-bool cmMakefile::ReadListFile(const char* filename_in, 
+bool cmMakefile::ReadListFile(const char* filename_in,
                               const char *external_in,
                               std::string* fullPath)
 {
@@ -403,7 +403,7 @@ bool cmMakefile::ReadListFile(const char* filename_in,
       filename = filename_abs.c_str();
       }
     }
-  
+
   // keep track of the current file being read
   if (filename)
     {
@@ -413,13 +413,13 @@ bool cmMakefile::ReadListFile(const char* filename_in,
       }
     // loop over current function blockers and record them
     std::list<cmFunctionBlocker *>::iterator pos;
-    for (pos = this->FunctionBlockers.begin(); 
+    for (pos = this->FunctionBlockers.begin();
          pos != this->FunctionBlockers.end(); ++pos)
       {
       originalBlockers.insert(*pos);
       }
     }
-  
+
   // Now read the input file
   const char *filenametoread= filename;
 
@@ -433,7 +433,7 @@ bool cmMakefile::ReadListFile(const char* filename_in,
   // try to see if the list file is the top most
   // list file for a project, and if it is, then it
   // must have a project command.   If there is not
-  // one, then cmake will provide one via the 
+  // one, then cmake will provide one via the
   // cmListFileCache class.
   bool requireProjectCommand = false;
   if(!external && this->cmStartDirectory == this->cmHomeDirectory)
@@ -444,7 +444,7 @@ bool cmMakefile::ReadListFile(const char* filename_in,
       requireProjectCommand = true;
       }
     }
-      
+
   // push the listfile onto the stack
   this->ListFileStack.push_back(filenametoread);
   if(fullPath!=0)
@@ -486,18 +486,18 @@ bool cmMakefile::ReadListFile(const char* filename_in,
     {
     // loop over all function blockers to see if any block this command
     std::list<cmFunctionBlocker *>::iterator pos;
-    for (pos = this->FunctionBlockers.begin(); 
+    for (pos = this->FunctionBlockers.begin();
          pos != this->FunctionBlockers.end(); ++pos)
       {
-      // if this blocker was not in the original then send a 
+      // if this blocker was not in the original then send a
       // scope ended message
       if (originalBlockers.find(*pos) == originalBlockers.end())
         {
         (*pos)->ScopeEnded(*this);
         }
       }
     }
-  
+
   this->AddDefinition("CMAKE_PARENT_LIST_FILE", currentParentFile.c_str());
   this->AddDefinition("CMAKE_CURRENT_LIST_FILE", currentFile.c_str());
 
@@ -513,7 +513,7 @@ void cmMakefile::AddCommand(cmCommand* wg)
   this->GetCMakeInstance()->AddCommand(wg);
 }
 
-// Set the make file 
+// Set the make file
 void cmMakefile::SetLocalGenerator(cmLocalGenerator* lg)
 {
   this->LocalGenerator = lg;
@@ -779,7 +779,7 @@ cmMakefile::AddCustomCommandOldStyle(const char* target,
 }
 
 //----------------------------------------------------------------------------
-void cmMakefile::AddUtilityCommand(const char* utilityName, 
+void cmMakefile::AddUtilityCommand(const char* utilityName,
                                    bool excludeFromAll,
                                    const std::vector<std::string>& depends,
                                    const char* workingDirectory,
@@ -812,12 +812,12 @@ void cmMakefile::AddUtilityCommand(const char* utilityName,
   commandLines.push_back(commandLine);
 
   // Call the real signature of this method.
-  this->AddUtilityCommand(utilityName, excludeFromAll, workingDirectory, 
+  this->AddUtilityCommand(utilityName, excludeFromAll, workingDirectory,
                           depends, commandLines);
 }
 
 //----------------------------------------------------------------------------
-void cmMakefile::AddUtilityCommand(const char* utilityName, 
+void cmMakefile::AddUtilityCommand(const char* utilityName,
                                    bool excludeFromAll,
                                    const char* workingDirectory,
                                    const std::vector<std::string>& depends,
@@ -916,7 +916,7 @@ void cmMakefile::RemoveDefineFlag(const char* flag)
     }
 }
 
-void cmMakefile::AddLinkLibrary(const char* lib, 
+void cmMakefile::AddLinkLibrary(const char* lib,
                                 cmTarget::LinkLibraryType llt)
 {
   cmTarget::LibraryID tmp;
@@ -926,13 +926,13 @@ void cmMakefile::AddLinkLibrary(const char* lib,
 }
 
 void cmMakefile::AddLinkLibraryForTarget(const char *target,
-                                         const char* lib, 
+                                         const char* lib,
                                          cmTarget::LinkLibraryType llt)
-{ 
+{
   cmTargets::iterator i = this->Targets.find(target);
   if ( i != this->Targets.end())
     {
-    cmTarget* tgt = 
+    cmTarget* tgt =
       this->GetCMakeInstance()->GetGlobalGenerator()->FindTarget(0, lib, false);
     if(tgt)
       {
@@ -958,12 +958,12 @@ void cmMakefile::AddLinkLibraryForTarget(const char *target,
         // in older versions of cmake linking to modules was allowed
         if( tgt->GetType() == cmTarget::MODULE_LIBRARY )
           {
-          e << 
+          e <<
             "\nTo allow linking of modules set "
             "CMAKE_BACKWARDS_COMPATIBILITY to 2.2 or lower\n";
           }
         // if no modules are allowed then this is always an error
-        if(!allowModules || 
+        if(!allowModules ||
            // if we allow modules but the type is not a module then it is
            // still an error
            (allowModules && tgt->GetType() != cmTarget::MODULE_LIBRARY))
@@ -995,7 +995,7 @@ void cmMakefile::AddLinkDirectoryForTarget(const char *target,
   else
     {
     cmSystemTools::Error
-      ("Attempt to add link directories to non-existant target: ", 
+      ("Attempt to add link directories to non-existant target: ",
        target, " for directory ", d);
     }
 }
@@ -1011,14 +1011,14 @@ void cmMakefile::AddLinkDirectory(const char* dir)
   // linear search results in n^2 behavior, but n won't be getting
   // much bigger than 20.  We cannot use a set because of order
   // dependency of the link search path.
-  
+
   // remove trailing slashes
   if(dir && dir[strlen(dir)-1] == '/')
     {
     std::string newdir = dir;
     newdir = newdir.substr(0, newdir.size()-1);
     if(std::find(this->LinkDirectories.begin(),
-                 this->LinkDirectories.end(), 
+                 this->LinkDirectories.end(),
                  newdir.c_str()) == this->LinkDirectories.end())
       {
       this->LinkDirectories.push_back(newdir);
@@ -1027,7 +1027,7 @@ void cmMakefile::AddLinkDirectory(const char* dir)
   else
     {
     if(std::find(this->LinkDirectories.begin(),
-                 this->LinkDirectories.end(), dir) 
+                 this->LinkDirectories.end(), dir)
        == this->LinkDirectories.end())
       {
       this->LinkDirectories.push_back(dir);
@@ -1038,23 +1038,23 @@ void cmMakefile::AddLinkDirectory(const char* dir)
 void cmMakefile::InitializeFromParent()
 {
   cmMakefile *parent = this->LocalGenerator->GetParent()->GetMakefile();
-  
+
   // copy the definitions
   this->Definitions = parent->Definitions;
 
   // copy include paths
   this->IncludeDirectories = parent->IncludeDirectories;
   this->SystemIncludeDirectories = parent->SystemIncludeDirectories;
-  
+
   // define flags
   this->DefineFlags = parent->DefineFlags;
-  
+
   // link libraries
   this->LinkLibraries = parent->LinkLibraries;
-  
+
   // link directories
   this->LinkDirectories = parent->LinkDirectories;
-  
+
   // the initial project name
   this->ProjectName = parent->ProjectName;
 
@@ -1068,12 +1068,12 @@ void cmMakefile::ConfigureSubDirectory(cmLocalGenerator *lg2)
   // copy our variables from the child makefile
   lg2->GetMakefile()->InitializeFromParent();
   lg2->GetMakefile()->MakeStartDirectoriesCurrent();
-  
+
   // finally configure the subdir
   lg2->Configure();
 }
 
-void cmMakefile::AddSubDirectory(const char* sub, 
+void cmMakefile::AddSubDirectory(const char* sub,
                                  bool excludeFromAll, bool preorder)
 {
   // the source path must be made full if it isn't already
@@ -1093,18 +1093,18 @@ void cmMakefile::AddSubDirectory(const char* sub,
     binPath += "/";
     binPath += sub;
     }
-  
-  
-  this->AddSubDirectory(srcPath.c_str(), binPath.c_str(), 
+
+
+  this->AddSubDirectory(srcPath.c_str(), binPath.c_str(),
                         excludeFromAll, preorder, false);
 }
 
-                        
+
 void cmMakefile::AddSubDirectory(const char* srcPath, const char *binPath,
-                                 bool excludeFromAll, bool preorder, 
+                                 bool excludeFromAll, bool preorder,
                                  bool immediate)
 {
-  std::vector<cmLocalGenerator *>& children = 
+  std::vector<cmLocalGenerator *>& children =
     this->LocalGenerator->GetChildren();
   // has this directory already been added? If so error
   unsigned int i;
@@ -1113,18 +1113,18 @@ void cmMakefile::AddSubDirectory(const char* srcPath, const char *binPath,
     if (srcPath == children[i]->GetMakefile()->GetStartDirectory())
       {
       cmSystemTools::Error
-        ("Attempt to add subdirectory multiple times for directory.\n", 
+        ("Attempt to add subdirectory multiple times for directory.\n",
          srcPath);
       return;
       }
     }
-  
+
   // create a new local generator and set its parent
-  cmLocalGenerator *lg2 = 
+  cmLocalGenerator *lg2 =
     this->LocalGenerator->GetGlobalGenerator()->CreateLocalGenerator();
   lg2->SetParent(this->LocalGenerator);
   this->LocalGenerator->GetGlobalGenerator()->AddLocalGenerator(lg2);
-  
+
   // set the subdirs start dirs
   lg2->GetMakefile()->SetStartDirectory(srcPath);
   lg2->GetMakefile()->SetStartOutputDirectory(binPath);
@@ -1133,7 +1133,7 @@ void cmMakefile::AddSubDirectory(const char* srcPath, const char *binPath,
     lg2->GetMakefile()->SetProperty("EXCLUDE_FROM_ALL", "TRUE");
     }
   lg2->GetMakefile()->SetPreOrder(preorder);
-  
+
   if (immediate)
     {
     this->ConfigureSubDirectory(lg2);
@@ -1152,7 +1152,7 @@ void cmMakefile::AddIncludeDirectory(const char* inc, bool before)
   // this linear search results in n^2 behavior, but n won't be
   // getting much bigger than 20.  We cannot use a set because of
   // order dependency of the include path.
-  std::vector<std::string>::iterator i = 
+  std::vector<std::string>::iterator i =
     std::find(this->IncludeDirectories.begin(),
               this->IncludeDirectories.end(), inc);
   if(i == this->IncludeDirectories.end())
@@ -1205,7 +1205,7 @@ void cmMakefile::AddDefinition(const char* name, const char* value)
   cmVariableWatch* vv = this->GetVariableWatch();
   if ( vv )
     {
-    vv->VariableAccessed(this->TemporaryDefinitionKey, 
+    vv->VariableAccessed(this->TemporaryDefinitionKey,
                          cmVariableWatch::VARIABLE_MODIFIED_ACCESS,
                          value,
                          this);
@@ -1214,12 +1214,12 @@ void cmMakefile::AddDefinition(const char* name, const char* value)
 }
 
 
-void cmMakefile::AddCacheDefinition(const char* name, const char* value, 
+void cmMakefile::AddCacheDefinition(const char* name, const char* value,
                                     const char* doc,
                                     cmCacheManager::CacheEntryType type)
 {
   const char* val = value;
-  cmCacheManager::CacheIterator it = 
+  cmCacheManager::CacheIterator it =
     this->GetCacheManager()->GetCacheIterator(name);
   if(!it.IsAtEnd() && (it.GetType() == cmCacheManager::UNINITIALIZED) &&
      it.Initialized())
@@ -1275,12 +1275,12 @@ void cmMakefile::AddDefinition(const char* name, bool value)
 }
 
 
-void cmMakefile::AddCacheDefinition(const char* name, 
-                                    bool value, 
+void cmMakefile::AddCacheDefinition(const char* name,
+                                    bool value,
                                     const char* doc)
 {
   bool val = value;
-  cmCacheManager::CacheIterator it = 
+  cmCacheManager::CacheIterator it =
     this->GetCacheManager()->GetCacheIterator(name);
   if(!it.IsAtEnd() && (it.GetType() == cmCacheManager::UNINITIALIZED) &&
      it.Initialized())
@@ -1315,8 +1315,8 @@ void cmMakefile::AddGlobalLinkInformation(const char* name, cmTarget& target)
   // for these targets do not add anything
   switch(target.GetType())
     {
-    case cmTarget::UTILITY: 
-    case cmTarget::GLOBAL_TARGET: 
+    case cmTarget::UTILITY:
+    case cmTarget::GLOBAL_TARGET:
       return;
     default:;
     }
@@ -1362,7 +1362,7 @@ void cmMakefile::AddLibrary(const char* lname, int shared,
   this->AddGlobalLinkInformation(lname, *target);
 }
 
-cmTarget* cmMakefile::AddExecutable(const char *exeName, 
+cmTarget* cmMakefile::AddExecutable(const char *exeName,
                                     const std::vector<std::string> &srcs,
                                     bool excludeFromAll)
 {
@@ -1404,7 +1404,7 @@ cmSourceFile *cmMakefile::GetSourceFileWithOutput(const char *cname)
   // look through all the source files that have custom commands
   // and see if the custom command has the passed source file as an output
   // keep in mind the possible .rule extension that may be tacked on
-  for(std::vector<cmSourceFile*>::const_iterator i = 
+  for(std::vector<cmSourceFile*>::const_iterator i =
         this->SourceFiles.begin(); i != this->SourceFiles.end(); ++i)
     {
     // does this source file have a custom command?
@@ -1428,7 +1428,7 @@ cmSourceFile *cmMakefile::GetSourceFileWithOutput(const char *cname)
         }
       }
     }
-  
+
   // otherwise return NULL
   return 0;
 }
@@ -1444,7 +1444,7 @@ cmSourceGroup* cmMakefile::GetSourceGroup(const char* name)
     if(sgName == name)
       {
       return &(*sg);
-      } 
+      }
     else
       {
       cmSourceGroup *target = sg->lookupChild(name);
@@ -1458,15 +1458,15 @@ cmSourceGroup* cmMakefile::GetSourceGroup(const char* name)
   return 0;
 }
 
-void cmMakefile::AddSourceGroup(const char* name, 
-                                const char* regex, 
+void cmMakefile::AddSourceGroup(const char* name,
+                                const char* regex,
                                 const char *parent)
 {
   // First see if the group exists.  If so, replace its regular expression.
   for(unsigned int i=0;i<this->SourceGroups.size();++i)
     {
     cmSourceGroup *sg = &this->SourceGroups[i];
-                                
+
     std::string sgName = sg->GetName();
     if(!parent)
       {
@@ -1495,21 +1495,21 @@ void cmMakefile::AddSourceGroup(const char* name,
             // them.
             localtarget->SetGroupRegex(regex);
             }
-          } 
+          }
         else
           {
           sg->AddChild(cmSourceGroup(name, regex));
           }
         return;
-        } 
-      else 
+        }
+      else
         {
         cmSourceGroup *localtarget = sg->lookupChild(parent);
 
         if(localtarget)
           {
           cmSourceGroup *addtarget = localtarget->lookupChild(name);
-                                                        
+
           if(addtarget)
             {
             if ( regex )
@@ -1519,17 +1519,17 @@ void cmMakefile::AddSourceGroup(const char* name,
               // remove them.
               addtarget->SetGroupRegex(regex);
               }
-            } 
+            }
           else
             {
             localtarget->AddChild(cmSourceGroup(name, regex));
             }
           return;
-          } 
+          }
         }
       }
     }
-                
+
   // The group doesn't exist.  Add it.
   this->SourceGroups.push_back(cmSourceGroup(name, regex));
 }
@@ -1557,7 +1557,7 @@ void cmMakefile::ExpandVariables()
     {
     this->ExpandVariablesInString(*d, true, true);
     }
-  for(cmTarget::LinkLibraryVectorType::iterator l = 
+  for(cmTarget::LinkLibraryVectorType::iterator l =
         this->LinkLibraries.begin();
       l != this->LinkLibraries.end(); ++l)
     {
@@ -1599,7 +1599,7 @@ bool cmMakefile::CanIWriteThisFile(const char* fileName)
     return true;
     }
   // If we are doing an in-source build, than the test will always fail
-  if ( cmSystemTools::SameFile(this->GetHomeDirectory(), 
+  if ( cmSystemTools::SameFile(this->GetHomeDirectory(),
                                this->GetHomeOutputDirectory()) )
     {
     if ( this->IsOn("CMAKE_DISABLE_IN_SOURCE_BUILD") )
@@ -1682,13 +1682,13 @@ const char* cmMakefile::GetDefinition(const char* name) const
       vv->VariableAccessed(name, cmVariableWatch::VARIABLE_READ_ACCESS,
         def, this);
       }
-    else 
+    else
       {
       // are unknown access allowed
-      DefinitionMap::const_iterator pos2 = 
+      DefinitionMap::const_iterator pos2 =
         this->Definitions.find("CMAKE_ALLOW_UNKNOWN_VARIABLE_READ_ACCESS");
-      if (pos2 != this->Definitions.end() && 
-          cmSystemTools::IsOn((*pos2).second.c_str())) 
+      if (pos2 != this->Definitions.end() &&
+          cmSystemTools::IsOn((*pos2).second.c_str()))
         {
         vv->VariableAccessed(name,
           cmVariableWatch::ALLOWED_UNKNOWN_VARIABLE_READ_ACCESS, def, this);
@@ -1721,19 +1721,19 @@ ::GetDefinitions(int cacheonly /* = 0 */) const
   if ( !cacheonly )
     {
     DefinitionMap::const_iterator it;
-    for ( it = this->Definitions.begin(); 
+    for ( it = this->Definitions.begin();
           it != this->Definitions.end(); it ++ )
       {
       definitions[it->first] = 1;
       }
     }
-  cmCacheManager::CacheIterator cit = 
+  cmCacheManager::CacheIterator cit =
     this->GetCacheManager()->GetCacheIterator();
   for ( cit.Begin(); !cit.IsAtEnd(); cit.Next() )
     {
     definitions[cit.GetName()] = 1;
     }
-  
+
   std::vector<std::string> res;
 
   std::map<cmStdString, int>::iterator fit;
@@ -1820,7 +1820,7 @@ const char *cmMakefile::ExpandVariablesInString(std::string& source,
   // with GetDefinition(), if not found in the map, nothing is expanded.
   // It also supports the $ENV{VAR} syntax where VAR is looked up in
   // the current environment variables.
-  
+
   cmCommandArgumentParserHelper parser;
   parser.SetMakefile(this);
   parser.SetLineFile(line, filename);
@@ -1837,9 +1837,9 @@ const char *cmMakefile::ExpandVariablesInString(std::string& source,
     {
     cmOStringStream error;
     error << "Syntax error in cmake code at\n"
-          << (filename?filename:"(no filename given)") 
+          << (filename?filename:"(no filename given)")
           << ":" << line << ":\n"
-          << parser.GetError() << ", when parsing string \"" 
+          << parser.GetError() << ", when parsing string \""
           << source.c_str() << "\"";
     const char* versionValue
       = this->GetDefinition("CMAKE_BACKWARDS_COMPATIBILITY");
@@ -1874,7 +1874,7 @@ void cmMakefile::RemoveVariablesInString(std::string& source,
       source.erase(var.start(),var.end() - var.start());
       }
     }
-  
+
   if(!atOnly)
     {
     cmsys::RegularExpression varb("(\\$ENV{[A-Za-z_0-9]*})");
@@ -1925,7 +1925,7 @@ void cmMakefile::AddDefaultDefinitions()
   sprintf(temp, "%d", cmVersion::GetPatchVersion());
   this->AddDefinition("CMAKE_PATCH_VERSION", temp);
 
-  this->AddDefinition("CMAKE_FILES_DIRECTORY", 
+  this->AddDefinition("CMAKE_FILES_DIRECTORY",
                       cmake::GetCMakeFilesDirectory());
 }
 
@@ -1937,7 +1937,7 @@ void cmMakefile::AddDefaultDefinitions()
  * non-inherited SOURCE_GROUP commands will have precedence over
  * inherited ones.
  */
-cmSourceGroup& 
+cmSourceGroup&
 cmMakefile::FindSourceGroup(const char* source,
                             std::vector<cmSourceGroup> &groups)
 {
@@ -1951,7 +1951,7 @@ cmMakefile::FindSourceGroup(const char* source,
       return *result;
       }
     }
-  
+
   // Now search for a group whose regex matches the file.
   for(std::vector<cmSourceGroup>::reverse_iterator sg = groups.rbegin();
       sg != groups.rend(); ++sg)
@@ -1963,7 +1963,7 @@ cmMakefile::FindSourceGroup(const char* source,
       }
     }
 
-                
+
   // Shouldn't get here, but just in case, return the default group.
   return groups.front();
 }
@@ -1980,15 +1980,15 @@ bool cmMakefile::IsFunctionBlocked(const cmListFileFunction& lff)
   // loop over all function blockers to see if any block this command
   // evaluate in reverse, this is critical for balanced IF statements etc
   std::list<cmFunctionBlocker *>::reverse_iterator pos;
-  for (pos = this->FunctionBlockers.rbegin(); 
+  for (pos = this->FunctionBlockers.rbegin();
        pos != this->FunctionBlockers.rend(); ++pos)
     {
     if((*pos)->IsFunctionBlocked(lff, *this))
       {
       return true;
       }
     }
-  
+
   return false;
 }
 
@@ -2003,7 +2003,7 @@ void cmMakefile::ExpandArguments(
     {
     // Expand the variables in the argument.
     value = i->Value;
-    this->ExpandVariablesInString(value, false, false, false, 
+    this->ExpandVariablesInString(value, false, false, false,
                                   i->FilePath, i->Line,
                                   false, true);
 
@@ -2024,7 +2024,7 @@ void cmMakefile::RemoveFunctionBlocker(const cmListFileFunction& lff)
 {
   // loop over all function blockers to see if any block this command
   std::list<cmFunctionBlocker *>::reverse_iterator pos;
-  for (pos = this->FunctionBlockers.rbegin(); 
+  for (pos = this->FunctionBlockers.rbegin();
        pos != this->FunctionBlockers.rend(); ++pos)
     {
     if ((*pos)->ShouldRemove(lff, *this))
@@ -2035,11 +2035,11 @@ void cmMakefile::RemoveFunctionBlocker(const cmListFileFunction& lff)
       break;
       }
     }
-  
+
   return;
 }
 
-void cmMakefile::SetHomeDirectory(const char* dir) 
+void cmMakefile::SetHomeDirectory(const char* dir)
 {
   this->cmHomeDirectory = dir;
   cmSystemTools::ConvertToUnixSlashes(this->cmHomeDirectory);
@@ -2057,7 +2057,7 @@ void cmMakefile::SetHomeOutputDirectory(const char* lib)
   this->AddDefinition("CMAKE_BINARY_DIR", this->GetHomeOutputDirectory());
   if ( !this->GetDefinition("CMAKE_CURRENT_BINARY_DIR") )
     {
-    this->AddDefinition("CMAKE_CURRENT_BINARY_DIR", 
+    this->AddDefinition("CMAKE_CURRENT_BINARY_DIR",
                         this->GetHomeOutputDirectory());
     }
 }
@@ -2132,7 +2132,7 @@ cmSourceFile* cmMakefile::GetSource(const char* sourceName) const
     }
   path = cmSystemTools::CollapseFullPath(path.c_str());
 
-  std::string sname = 
+  std::string sname =
     cmSystemTools::GetFilenameWithoutLastExtension(sourceName);
 
   // compute the extension
@@ -2143,7 +2143,7 @@ cmSourceFile* cmMakefile::GetSource(const char* sourceName) const
     ext = ext.substr(1);
     }
 
-  for(std::vector<cmSourceFile*>::const_iterator i = 
+  for(std::vector<cmSourceFile*>::const_iterator i =
         this->SourceFiles.begin();
       i != this->SourceFiles.end(); ++i)
     {
@@ -2160,9 +2160,9 @@ cmSourceFile* cmMakefile::GetSource(const char* sourceName) const
     {
     return 0;
     }
-    
+
   path = this->GetCurrentOutputDirectory();
-  for(std::vector<cmSourceFile*>::const_iterator i = 
+  for(std::vector<cmSourceFile*>::const_iterator i =
         this->SourceFiles.begin();
       i != this->SourceFiles.end(); ++i)
     {
@@ -2172,12 +2172,12 @@ cmSourceFile* cmMakefile::GetSource(const char* sourceName) const
       {
       return *i;
       }
-    }  
-  
+    }
+
   return 0;
 }
 
-cmSourceFile* cmMakefile::GetOrCreateSource(const char* sourceName, 
+cmSourceFile* cmMakefile::GetOrCreateSource(const char* sourceName,
                                             bool generated)
 {
   // make it a full path first
@@ -2191,7 +2191,7 @@ cmSourceFile* cmMakefile::GetOrCreateSource(const char* sourceName,
     {
     src = srcTreeFile;
     }
-  
+
   // check to see if it exists
   cmSourceFile* ret = this->GetSource(src.c_str());
   if (ret)
@@ -2217,7 +2217,7 @@ cmSourceFile* cmMakefile::GetOrCreateSource(const char* sourceName,
     // src tree
     if(!generated)
       {
-      // see if the file is in the source tree, otherwise assume it 
+      // see if the file is in the source tree, otherwise assume it
       // is in the binary tree
       if (cmSystemTools::FileExists(srcTreeFile.c_str()) &&
           !cmSystemTools::FileIsDirectory(srcTreeFile.c_str()))
@@ -2248,7 +2248,7 @@ cmSourceFile* cmMakefile::GetOrCreateSource(const char* sourceName,
   // go back to looking in the source directory for it
 
   // we must create one
-  cmSourceFile file; 
+  cmSourceFile file;
   file.SetMakefile(this);
   std::string path = cmSystemTools::GetFilenamePath(src);
   if(generated)
@@ -2259,9 +2259,9 @@ cmSourceFile* cmMakefile::GetOrCreateSource(const char* sourceName,
     if ( ext.length() && ext[0] == '.' )
       {
       ext = ext.substr(1);
-      } 
-    bool headerFile = 
-      !(std::find( this->HeaderFileExtensions.begin(), 
+      }
+    bool headerFile =
+      !(std::find( this->HeaderFileExtensions.begin(),
                    this->HeaderFileExtensions.end(), ext ) ==
         this->HeaderFileExtensions.end());
     file.SetName(name_no_ext.c_str(), path.c_str(), ext.c_str(), headerFile);
@@ -2277,7 +2277,7 @@ cmSourceFile* cmMakefile::GetOrCreateSource(const char* sourceName,
       if (pos == std::string::npos)
         {
         cmSystemTools::Error(
-          "CMake failed to properly look up relative cmSourceFile: ", 
+          "CMake failed to properly look up relative cmSourceFile: ",
           sourceName);
         }
       fullPathLessRel.erase(pos-1);
@@ -2287,7 +2287,7 @@ cmSourceFile* cmMakefile::GetOrCreateSource(const char* sourceName,
       }
     else
       {
-      file.SetName(cmSystemTools::GetFilenameName(src.c_str()).c_str(), 
+      file.SetName(cmSystemTools::GetFilenameName(src.c_str()).c_str(),
                    path.c_str(),
                    this->GetSourceExtensions(),
                    this->GetHeaderExtensions());
@@ -2322,7 +2322,7 @@ cmSourceFile* cmMakefile::AddSource(cmSourceFile const&sf)
   return ret;
 }
 
-  
+
 void cmMakefile::EnableLanguage(std::vector<std::string> const &  lang)
 {
   this->AddDefinition("CMAKE_CFG_INTDIR",
@@ -2331,7 +2331,7 @@ void cmMakefile::EnableLanguage(std::vector<std::string> const &  lang)
 }
 
 void cmMakefile::ExpandSourceListArguments(
-  std::vector<std::string> const& arguments, 
+  std::vector<std::string> const& arguments,
   std::vector<std::string>& newargs, unsigned int /* start */)
 {
   // now expand the args
@@ -2343,7 +2343,7 @@ void cmMakefile::ExpandSourceListArguments(
     }
 }
 
-int cmMakefile::TryCompile(const char *srcdir, const char *bindir, 
+int cmMakefile::TryCompile(const char *srcdir, const char *bindir,
                            const char *projectName, const char *targetName,
                            const std::vector<std::string> *cmakeArgs,
                            std::string *output)
@@ -2353,12 +2353,12 @@ int cmMakefile::TryCompile(const char *srcdir, const char *bindir,
     {
     cmSystemTools::MakeDirectory(bindir);
     }
-  
+
   // change to the tests directory and run cmake
   // use the cmake object instead of calling cmake
   std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
   cmSystemTools::ChangeDirectory(bindir);
-  
+
   // make sure the same generator is used
   // use this program as the cmake to be run, it should not
   // be run that way but the cmake object requires a vailid path
@@ -2376,7 +2376,7 @@ int cmMakefile::TryCompile(const char *srcdir, const char *bindir,
     return 1;
     }
   cm.SetGlobalGenerator(gg);
-  
+
   // do a configure
   cm.SetHomeDirectory(srcdir);
   cm.SetHomeOutputDirectory(bindir);
@@ -2392,7 +2392,7 @@ int cmMakefile::TryCompile(const char *srcdir, const char *bindir,
   // to save time we pass the EnableLanguage info directly
   gg->EnableLanguagesFromGenerator
     (this->LocalGenerator->GetGlobalGenerator());
-  
+
   if (cm.Configure() != 0)
     {
     cmSystemTools::Error(
@@ -2412,13 +2412,13 @@ int cmMakefile::TryCompile(const char *srcdir, const char *bindir,
     }
 
   // finally call the generator to actually build the resulting project
-  int ret = 
+  int ret =
     this->LocalGenerator->GetGlobalGenerator()->TryCompile(srcdir,bindir,
-                                                           projectName, 
+                                                           projectName,
                                                            targetName,
                                                            output,
                                                            this);
-  
+
   cmSystemTools::ChangeDirectory(cwd.c_str());
   return ret;
 }
@@ -2518,7 +2518,7 @@ void cmMakefile::ConfigureString(const std::string& input,
                                  bool escapeQuotes)
 {
   // Split input to handle one line at a time.
-  std::string::const_iterator lineStart = input.begin();  
+  std::string::const_iterator lineStart = input.begin();
   while(lineStart != input.end())
     {
     // Find the end of this line.
@@ -2541,7 +2541,7 @@ void cmMakefile::ConfigureString(const std::string& input,
     // Replace #cmakedefine instances.
     if(this->cmDefineRegex.find(line))
       {
-      const char* def = 
+      const char* def =
         this->GetDefinition(this->cmDefineRegex.match(1).c_str());
       if(!cmSystemTools::IsOff(def))
         {
@@ -2558,7 +2558,7 @@ void cmMakefile::ConfigureString(const std::string& input,
       }
     else if(this->cmDefine01Regex.find(line))
       {
-      const char* def = 
+      const char* def =
         this->GetDefinition(this->cmDefine01Regex.match(1).c_str());
       cmSystemTools::ReplaceString(line, "#cmakedefine01", "#define");
       output += line;
@@ -2586,17 +2586,17 @@ void cmMakefile::ConfigureString(const std::string& input,
     }
 
   // Perform variable replacements.
-  this->ExpandVariablesInString(output, escapeQuotes, true, 
+  this->ExpandVariablesInString(output, escapeQuotes, true,
                                 atOnly, 0, -1, true);
 }
 
-int cmMakefile::ConfigureFile(const char* infile, const char* outfile, 
+int cmMakefile::ConfigureFile(const char* infile, const char* outfile,
                               bool copyonly, bool atOnly, bool escapeQuotes)
 {
   int res = 1;
   if ( !this->CanIWriteThisFile(outfile) )
     {
-    cmSystemTools::Error("Attempt to write file: ", 
+    cmSystemTools::Error("Attempt to write file: ",
                          outfile, " into a source directory.");
     return 0;
     }
@@ -2617,7 +2617,7 @@ int cmMakefile::ConfigureFile(const char* infile, const char* outfile,
     std::string path = soutfile.substr(0, pos);
     cmSystemTools::MakeDirectory(path.c_str());
     }
-  
+
   if(copyonly)
     {
     if ( !cmSystemTools::CopyFileIfDifferent(sinfile.c_str(),
@@ -2634,7 +2634,7 @@ int cmMakefile::ConfigureFile(const char* infile, const char* outfile,
     if(!fout)
       {
       cmSystemTools::Error(
-        "Could not open file for write in copy operation ", 
+        "Could not open file for write in copy operation ",
         tempOutputFile.c_str());
       cmSystemTools::ReportLastSystemError("");
       return 0;
@@ -2690,7 +2690,7 @@ bool cmMakefile::CheckInfiniteLoops()
     if ( this->HasWrittenFile(it->c_str()) )
       {
       cmOStringStream str;
-      str << "File " << it->c_str() << 
+      str << "File " << it->c_str() <<
         " is written by WRITE_FILE (or FILE WRITE) command and should "
         "not be used as input to CMake. Please use CONFIGURE_FILE to "
         "be safe. Refer to the note next to FILE WRITE command.";
@@ -2749,9 +2749,9 @@ const char *cmMakefile::GetProperty(const char* prop,
       }
     this->SetProperty("LISTFILE_STACK",tmp.c_str());
     }
-  
+
   bool chain = false;
-  const char *retVal = 
+  const char *retVal =
     this->Properties.GetPropertyValue(prop, scope, chain);
   if (chain)
     {
@@ -2861,19 +2861,19 @@ std::string cmMakefile::GetListFileStack()
 void cmMakefile::DefineProperties(cmake *cm)
 {
   cm->DefineProperty
-    ("ADDITIONAL_MAKE_CLEAN_FILES", cmProperty::DIRECTORY, 
+    ("ADDITIONAL_MAKE_CLEAN_FILES", cmProperty::DIRECTORY,
      "Addditional files to clean during the make clean stage.",
      "A list of files that will be cleaned as a part of the "
      "\"make clean\" stage. ");
 
   cm->DefineProperty
-    ("CLEAN_NO_CUSTOM", cmProperty::DIRECTORY, 
+    ("CLEAN_NO_CUSTOM", cmProperty::DIRECTORY,
      "Should the output of custom commands be left.",
      "If this is true then the outputs of custom commands for this "
      "directory will not be removed during the \"make clean\" stage. ");
 
   cm->DefineProperty
-    ("CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS", cmProperty::DIRECTORY, 
+    ("CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS", cmProperty::DIRECTORY,
      "Allow loops to have non-matching closing statements.",
      "If this is set then the closing statement of control "
      "structures in CMake will not require an exact match to the "
@@ -2882,7 +2882,7 @@ void cmMakefile::DefineProperties(cmake *cm)
      true);
 
   cm->DefineProperty
-    ("LISTFILE_STACK", cmProperty::DIRECTORY, 
+    ("LISTFILE_STACK", cmProperty::DIRECTORY,
      "The current stack of listfiles being processed.",
      "This property is mainly useful when trying to debug errors "
      "in your CMake scripts. It returns a list of what list files "
@@ -2891,13 +2891,13 @@ void cmMakefile::DefineProperties(cmake *cm)
      "the included listfile onto the stack.");
 
   cm->DefineProperty
-    ("TEST_INCLUDE_FILE", cmProperty::DIRECTORY, 
+    ("TEST_INCLUDE_FILE", cmProperty::DIRECTORY,
      "A cmake file that will be included when ctest is run.",
      "If you specify TEST_INCLUDE_FILE, that file will be "
      "included and processed when ctest is run on the directory.");
 
   cm->DefineProperty
-    ("EXCLUDE_FROM_ALL", cmProperty::DIRECTORY, 
+    ("EXCLUDE_FROM_ALL", cmProperty::DIRECTORY,
      "Exclude the target from the all target.",
      "A property on a target that indicates if the target is excluded "
      "from the default build target. If it is not, then with a Makefile "