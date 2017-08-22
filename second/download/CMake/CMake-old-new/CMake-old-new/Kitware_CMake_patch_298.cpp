@@ -306,7 +306,7 @@ void cmake::RemoveUnscriptableCommands()
       it != unscriptableCommands.end();
       ++it)
     {
-    this->RemoveCommand(it->c_str());
+    this->RemoveCommand(*it);
     }
 }
 
@@ -335,23 +335,23 @@ bool cmake::SetCacheArgs(const std::vector<std::string>& args)
         }
       std::string var, value;
       cmCacheManager::CacheEntryType type = cmCacheManager::UNINITIALIZED;
-      if(cmCacheManager::ParseEntry(entry.c_str(), var, value, type))
+      if(cmCacheManager::ParseEntry(entry, var, value, type))
         {
         // The value is transformed if it is a filepath for example, so
         // we can't compare whether the value is already in the cache until
         // after we call AddCacheEntry.
         const char *cachedValue =
-                              this->CacheManager->GetCacheValue(var.c_str());
+                              this->CacheManager->GetCacheValue(var);
 
-        this->CacheManager->AddCacheEntry(var.c_str(), value.c_str(),
+        this->CacheManager->AddCacheEntry(var, value.c_str(),
           "No help, variable specified on the command line.", type);
         if(this->WarnUnusedCli)
           {
           if (!cachedValue
-              || strcmp(this->CacheManager->GetCacheValue(var.c_str()),
+              || strcmp(this->CacheManager->GetCacheValue(var),
                         cachedValue) != 0)
             {
-            this->WatchUnusedCli(var.c_str());
+            this->WatchUnusedCli(var);
             }
           }
         }
@@ -390,7 +390,7 @@ bool cmake::SetCacheArgs(const std::vector<std::string>& args)
           }
         }
       cmsys::RegularExpression regex(
-        cmsys::Glob::PatternToRegex(entryPattern.c_str(), true, true).c_str());
+        cmsys::Glob::PatternToRegex(entryPattern, true, true).c_str());
       //go through all cache entries and collect the vars which will be removed
       std::vector<std::string> entriesToDelete;
       cmCacheManager::CacheIterator it =
@@ -414,7 +414,7 @@ bool cmake::SetCacheArgs(const std::vector<std::string>& args)
           currentEntry != entriesToDelete.end();
           ++currentEntry)
         {
-        this->CacheManager->RemoveCacheEntry(currentEntry->c_str());
+        this->CacheManager->RemoveCacheEntry(*currentEntry);
         }
       }
     else if(arg.find("-C",0) == 0)
@@ -486,13 +486,13 @@ void cmake::ReadListFile(const std::vector<std::string>& args,
     {
     cmsys::auto_ptr<cmLocalGenerator> lg(gg->CreateLocalGenerator());
     lg->GetMakefile()->SetHomeOutputDirectory
-      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+      (cmSystemTools::GetCurrentWorkingDirectory());
     lg->GetMakefile()->SetStartOutputDirectory
-      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+      (cmSystemTools::GetCurrentWorkingDirectory());
     lg->GetMakefile()->SetHomeDirectory
-      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+      (cmSystemTools::GetCurrentWorkingDirectory());
     lg->GetMakefile()->SetStartDirectory
-      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+      (cmSystemTools::GetCurrentWorkingDirectory());
     if (this->GetWorkingMode() != NORMAL_MODE)
       {
       std::string file(cmSystemTools::CollapseFullPath(path));
@@ -526,13 +526,13 @@ bool cmake::FindPackage(const std::vector<std::string>& args)
   cmsys::auto_ptr<cmLocalGenerator> lg(gg->CreateLocalGenerator());
   cmMakefile* mf = lg->GetMakefile();
   mf->SetHomeOutputDirectory
-    (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+    (cmSystemTools::GetCurrentWorkingDirectory());
   mf->SetStartOutputDirectory
-    (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+    (cmSystemTools::GetCurrentWorkingDirectory());
   mf->SetHomeDirectory
-    (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+    (cmSystemTools::GetCurrentWorkingDirectory());
   mf->SetStartDirectory
-    (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+    (cmSystemTools::GetCurrentWorkingDirectory());
 
   mf->SetArgcArgv(args);
 
@@ -566,7 +566,7 @@ bool cmake::FindPackage(const std::vector<std::string>& args)
     cmSystemTools::ExpandListArgument(includes, includeDirs);
 
     std::string includeFlags = lg->GetIncludeFlags(includeDirs, 0,
-                                                   language.c_str(), false);
+                                                   language, false);
 
     std::string definitions = mf->GetSafeDefinition("PACKAGE_DEFINITIONS");
     printf("%s %s\n", includeFlags.c_str(), definitions.c_str());
@@ -585,7 +585,7 @@ bool cmake::FindPackage(const std::vector<std::string>& args)
             libIt != libList.end();
             ++libIt)
       {
-      mf->AddLinkLibraryForTarget(targetName, libIt->c_str(),
+      mf->AddLinkLibraryForTarget(targetName, *libIt,
                                   cmTarget::GENERAL);
       }
 
@@ -636,7 +636,7 @@ void cmake::SetArgs(const std::vector<std::string>& args,
       std::string path = arg.substr(2);
       path = cmSystemTools::CollapseFullPath(path.c_str());
       cmSystemTools::ConvertToUnixSlashes(path);
-      this->SetHomeDirectory(path.c_str());
+      this->SetHomeDirectory(path);
       }
     else if(arg.find("-S",0) == 0)
       {
@@ -652,7 +652,7 @@ void cmake::SetArgs(const std::vector<std::string>& args,
       std::string path = arg.substr(2);
       path = cmSystemTools::CollapseFullPath(path.c_str());
       cmSystemTools::ConvertToUnixSlashes(path);
-      this->SetHomeOutputDirectory(path.c_str());
+      this->SetHomeOutputDirectory(path);
       }
     else if((i < args.size()-2) && (arg.find("--check-build-system",0) == 0))
       {
@@ -790,7 +790,7 @@ void cmake::SetArgs(const std::vector<std::string>& args,
         value = args[i];
         }
       cmGlobalGenerator* gen =
-        this->CreateGlobalGenerator(value.c_str());
+        this->CreateGlobalGenerator(value);
       if(!gen)
         {
         cmSystemTools::Error("Could not create named generator ",
@@ -811,13 +811,13 @@ void cmake::SetArgs(const std::vector<std::string>& args,
   if(!directoriesSet)
     {
     this->SetHomeOutputDirectory
-      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+      (cmSystemTools::GetCurrentWorkingDirectory());
     this->SetStartOutputDirectory
-      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+      (cmSystemTools::GetCurrentWorkingDirectory());
     this->SetHomeDirectory
-      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+      (cmSystemTools::GetCurrentWorkingDirectory());
     this->SetStartDirectory
-      (cmSystemTools::GetCurrentWorkingDirectory().c_str());
+      (cmSystemTools::GetCurrentWorkingDirectory());
     }
 
   this->SetStartDirectory(this->GetHomeDirectory());
@@ -853,28 +853,28 @@ void cmake::SetDirectoriesFromFile(const char* arg)
     {
     argIsFile = true;
     std::string fullPath = cmSystemTools::CollapseFullPath(arg);
-    std::string name = cmSystemTools::GetFilenameName(fullPath.c_str());
+    std::string name = cmSystemTools::GetFilenameName(fullPath);
     name = cmSystemTools::LowerCase(name);
     if(name == "cmakecache.txt")
       {
-      cachePath = cmSystemTools::GetFilenamePath(fullPath.c_str());
+      cachePath = cmSystemTools::GetFilenamePath(fullPath);
       }
     else if(name == "cmakelists.txt")
       {
-      listPath = cmSystemTools::GetFilenamePath(fullPath.c_str());
+      listPath = cmSystemTools::GetFilenamePath(fullPath);
       }
     }
   else
     {
     // Specified file or directory does not exist.  Try to set things
     // up to produce a meaningful error message.
     std::string fullPath = cmSystemTools::CollapseFullPath(arg);
-    std::string name = cmSystemTools::GetFilenameName(fullPath.c_str());
+    std::string name = cmSystemTools::GetFilenameName(fullPath);
     name = cmSystemTools::LowerCase(name);
     if(name == "cmakecache.txt" || name == "cmakelists.txt")
       {
       argIsFile = true;
-      listPath = cmSystemTools::GetFilenamePath(fullPath.c_str());
+      listPath = cmSystemTools::GetFilenamePath(fullPath);
       }
     else
       {
@@ -887,11 +887,11 @@ void cmake::SetDirectoriesFromFile(const char* arg)
     {
     cmCacheManager* cachem = this->GetCacheManager();
     cmCacheManager::CacheIterator it = cachem->NewIterator();
-    if(cachem->LoadCache(cachePath.c_str()) &&
+    if(cachem->LoadCache(cachePath) &&
       it.Find("CMAKE_HOME_DIRECTORY"))
       {
-      this->SetHomeOutputDirectory(cachePath.c_str());
-      this->SetStartOutputDirectory(cachePath.c_str());
+      this->SetHomeOutputDirectory(cachePath);
+      this->SetStartOutputDirectory(cachePath);
       this->SetHomeDirectory(it.GetValue());
       this->SetStartDirectory(it.GetValue());
       return;
@@ -901,23 +901,23 @@ void cmake::SetDirectoriesFromFile(const char* arg)
   // If there is a CMakeLists.txt file, use it as the source tree.
   if(listPath.length() > 0)
     {
-    this->SetHomeDirectory(listPath.c_str());
-    this->SetStartDirectory(listPath.c_str());
+    this->SetHomeDirectory(listPath);
+    this->SetStartDirectory(listPath);
 
     if(argIsFile)
       {
       // Source CMakeLists.txt file given.  It was probably dropped
       // onto the executable in a GUI.  Default to an in-source build.
-      this->SetHomeOutputDirectory(listPath.c_str());
-      this->SetStartOutputDirectory(listPath.c_str());
+      this->SetHomeOutputDirectory(listPath);
+      this->SetStartOutputDirectory(listPath);
       }
     else
       {
       // Source directory given on command line.  Use current working
       // directory as build tree.
       std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
-      this->SetHomeOutputDirectory(cwd.c_str());
-      this->SetStartOutputDirectory(cwd.c_str());
+      this->SetHomeOutputDirectory(cwd);
+      this->SetStartOutputDirectory(cwd);
       }
     return;
     }
@@ -927,10 +927,10 @@ void cmake::SetDirectoriesFromFile(const char* arg)
   // current working directory as the build tree.
   std::string full = cmSystemTools::CollapseFullPath(arg);
   std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
-  this->SetHomeDirectory(full.c_str());
-  this->SetStartDirectory(full.c_str());
-  this->SetHomeOutputDirectory(cwd.c_str());
-  this->SetStartOutputDirectory(cwd.c_str());
+  this->SetHomeDirectory(full);
+  this->SetStartDirectory(full);
+  this->SetHomeOutputDirectory(cwd);
+  this->SetStartOutputDirectory(cwd);
 }
 
 // at the end of this CMAKE_ROOT and CMAKE_COMMAND should be added to the
@@ -979,8 +979,8 @@ void cmake::AddExtraGenerator(const std::string& name,
       ++it )
     {
     std::string fullName = cmExternalMakefileProjectGenerator::
-                                    CreateFullGeneratorName(it->c_str(), name);
-    this->ExtraGenerators[fullName.c_str()] = newFunction;
+                                    CreateFullGeneratorName(*it, name);
+    this->ExtraGenerators[fullName] = newFunction;
     }
   delete extraGenerator;
 }
@@ -1230,7 +1230,7 @@ int cmake::HandleDeleteCacheVariables(const std::string& var)
     i++;
     save.value = *i;
     warning << *i << "\n";
-    if(ci.Find(save.key.c_str()))
+    if(ci.Find(save.key))
       {
       save.type = ci.GetType();
       save.help = ci.GetProperty("HELPSTRING");
@@ -1246,7 +1246,7 @@ int cmake::HandleDeleteCacheVariables(const std::string& var)
   for(std::vector<SaveCacheEntry>::iterator i = saved.begin();
       i != saved.end(); ++i)
     {
-    this->AddCacheEntry(i->key.c_str(), i->value.c_str(),
+    this->AddCacheEntry(i->key, i->value.c_str(),
                         i->help.c_str(), i->type);
     }
   cmSystemTools::Message(warning.str().c_str());
@@ -1328,7 +1328,7 @@ int cmake::ActualConfigure()
       std::string fullName = cmExternalMakefileProjectGenerator::
                                 CreateFullGeneratorName(genName,
                                     extraGenName ? extraGenName : "");
-      this->GlobalGenerator = this->CreateGlobalGenerator(fullName.c_str());
+      this->GlobalGenerator = this->CreateGlobalGenerator(fullName);
       }
     if(this->GlobalGenerator)
       {
@@ -1692,8 +1692,8 @@ int cmake::Run(const std::vector<std::string>& args, bool noconfigure)
     {
     return ret;
     }
-  this->SetStartDirectory(oldstartdir.c_str());
-  this->SetStartOutputDirectory(oldstartoutputdir.c_str());
+  this->SetStartDirectory(oldstartdir);
+  this->SetStartOutputDirectory(oldstartoutputdir);
 
   return ret;
 }
@@ -1854,7 +1854,7 @@ void cmake::GetGeneratorDocumentation(std::vector<cmDocumentationEntry>& v)
     {
     cmDocumentationEntry e;
     cmExternalMakefileProjectGenerator* generator = (i->second)();
-    generator->GetDocumentation(e, i->first.c_str());
+    generator->GetDocumentation(e, i->first);
     e.Name = i->first;
     delete generator;
     v.push_back(e);
@@ -2313,7 +2313,7 @@ int cmake::GetSystemInformation(std::vector<std::string>& args)
         value = args[i];
         }
       cmGlobalGenerator* gen =
-        this->CreateGlobalGenerator(value.c_str());
+        this->CreateGlobalGenerator(value);
       if(!gen)
         {
         cmSystemTools::Error("Could not create named generator ",
@@ -2650,7 +2650,7 @@ int cmake::Build(const std::string& dir,
   cmSystemTools::ConvertToUnixSlashes(cachePath);
   cmCacheManager* cachem = this->GetCacheManager();
   cmCacheManager::CacheIterator it = cachem->NewIterator();
-  if(!cachem->LoadCache(cachePath.c_str()))
+  if(!cachem->LoadCache(cachePath))
     {
     std::cerr << "Error: could not load cache\n";
     return 1;
@@ -2670,11 +2670,11 @@ int cmake::Build(const std::string& dir,
     return 1;
     }
   projName = it.GetValue();
-  return gen->Build("", dir.c_str(),
-                    projName.c_str(), target.c_str(),
+  return gen->Build("", dir,
+                    projName, target,
                     &output,
                     "",
-                    config.c_str(), clean, false, 0,
+                    config, clean, false, 0,
                     cmSystemTools::OUTPUT_PASSTHROUGH,
                     nativeOptions);
 }