@@ -223,7 +223,7 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
         }
 
       std::string req_var = this->Name + "_FIND_REQUIRED_" + args[i];
-      this->AddFindDefinition(req_var.c_str(), isRequired);
+      this->AddFindDefinition(req_var, isRequired);
 
       // Append to the list of required components.
       components += components_sep;
@@ -255,7 +255,7 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
         e << "given CONFIGS option followed by invalid file name \""
           << args[i] << "\".  The names given must be file names without "
           << "a path and with a \".cmake\" extension.";
-        this->SetError(e.str().c_str());
+        this->SetError(e.str());
         return false;
         }
       this->Configs.push_back(args[i]);
@@ -269,7 +269,7 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
       {
       cmOStringStream e;
       e << "called with invalid argument \"" << args[i].c_str() << "\"";
-      this->SetError(e.str().c_str());
+      this->SetError(e.str());
       return false;
       }
     }
@@ -286,7 +286,7 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
       {
       e << "  " << doubledComponents[i] << "\n";
       }
-    this->SetError(e.str().c_str());
+    this->SetError(e.str());
     return false;
     }
 
@@ -309,7 +309,7 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
       e << "  " << args[*si] << "\n";
       }
     e << "The options are incompatible.";
-    this->SetError(e.str().c_str());
+    this->SetError(e.str());
     return false;
     }
 
@@ -327,25 +327,25 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
     // another find_package(<name>) call.
     std::string mod = this->Name;
     mod += "_FIND_MODULE";
-    if(this->Makefile->IsOn(mod.c_str()))
+    if(this->Makefile->IsOn(mod))
       {
       if(this->Version.empty())
         {
         // Get version information from the outer call if necessary.
         // Requested version string.
         std::string ver = this->Name;
         ver += "_FIND_VERSION";
-        this->Version = this->Makefile->GetSafeDefinition(ver.c_str());
+        this->Version = this->Makefile->GetSafeDefinition(ver);
 
         // Whether an exact version is required.
         std::string exact = this->Name;
         exact += "_FIND_VERSION_EXACT";
-        this->VersionExact = this->Makefile->IsOn(exact.c_str());
+        this->VersionExact = this->Makefile->IsOn(exact);
         }
       if(components.empty())
         {
         std::string components_var = this->Name + "_FIND_COMPONENTS";
-        components = this->Makefile->GetSafeDefinition(components_var.c_str());
+        components = this->Makefile->GetSafeDefinition(components_var);
         }
       }
     }
@@ -373,15 +373,15 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
 
   std::string disableFindPackageVar = "CMAKE_DISABLE_FIND_PACKAGE_";
   disableFindPackageVar += this->Name;
-  if(this->Makefile->IsOn(disableFindPackageVar.c_str()))
+  if(this->Makefile->IsOn(disableFindPackageVar))
     {
     if (this->Required)
       {
       cmOStringStream e;
       e << "for module " << this->Name << " called with REQUIRED, but "
         << disableFindPackageVar
         << " is enabled. A REQUIRED package cannot be disabled.";
-      this->SetError(e.str().c_str());
+      this->SetError(e.str());
       return false;
       }
 
@@ -488,15 +488,15 @@ void cmFindPackageCommand::SetModuleVariables(const std::string& components)
 
   // Store the list of components.
   std::string components_var = this->Name + "_FIND_COMPONENTS";
-  this->AddFindDefinition(components_var.c_str(), components.c_str());
+  this->AddFindDefinition(components_var, components.c_str());
 
   if(this->Quiet)
     {
     // Tell the module that is about to be read that it should find
     // quietly.
     std::string quietly = this->Name;
     quietly += "_FIND_QUIETLY";
-    this->AddFindDefinition(quietly.c_str(), "1");
+    this->AddFindDefinition(quietly, "1");
     }
 
   if(this->Required)
@@ -505,7 +505,7 @@ void cmFindPackageCommand::SetModuleVariables(const std::string& components)
     // a fatal error if the package is not found.
     std::string req = this->Name;
     req += "_FIND_REQUIRED";
-    this->AddFindDefinition(req.c_str(), "1");
+    this->AddFindDefinition(req, "1");
     }
 
   if(!this->Version.empty())
@@ -514,23 +514,23 @@ void cmFindPackageCommand::SetModuleVariables(const std::string& components)
     // package has been requested.
     std::string ver = this->Name;
     ver += "_FIND_VERSION";
-    this->AddFindDefinition(ver.c_str(), this->Version.c_str());
+    this->AddFindDefinition(ver, this->Version.c_str());
     char buf[64];
     sprintf(buf, "%u", this->VersionMajor);
-    this->AddFindDefinition((ver+"_MAJOR").c_str(), buf);
+    this->AddFindDefinition(ver+"_MAJOR", buf);
     sprintf(buf, "%u", this->VersionMinor);
-    this->AddFindDefinition((ver+"_MINOR").c_str(), buf);
+    this->AddFindDefinition(ver+"_MINOR", buf);
     sprintf(buf, "%u", this->VersionPatch);
-    this->AddFindDefinition((ver+"_PATCH").c_str(), buf);
+    this->AddFindDefinition(ver+"_PATCH", buf);
     sprintf(buf, "%u", this->VersionTweak);
-    this->AddFindDefinition((ver+"_TWEAK").c_str(), buf);
+    this->AddFindDefinition(ver+"_TWEAK", buf);
     sprintf(buf, "%u", this->VersionCount);
-    this->AddFindDefinition((ver+"_COUNT").c_str(), buf);
+    this->AddFindDefinition(ver+"_COUNT", buf);
 
     // Tell the module whether an exact version has been requested.
     std::string exact = this->Name;
     exact += "_FIND_VERSION_EXACT";
-    this->AddFindDefinition(exact.c_str(), this->VersionExact? "1":"0");
+    this->AddFindDefinition(exact, this->VersionExact? "1":"0");
    }
 }
 
@@ -559,11 +559,11 @@ void cmFindPackageCommand::RestoreFindDefinitions()
     OriginalDef const& od = i->second;
     if(od.exists)
       {
-      this->Makefile->AddDefinition(i->first.c_str(), od.value.c_str());
+      this->Makefile->AddDefinition(i->first, od.value.c_str());
       }
     else
       {
-      this->Makefile->RemoveDefinition(i->first.c_str());
+      this->Makefile->RemoveDefinition(i->first);
       }
     }
 }
@@ -582,9 +582,9 @@ bool cmFindPackageCommand::FindModule(bool& found)
     found = true;
     std::string var = this->Name;
     var += "_FIND_MODULE";
-    this->Makefile->AddDefinition(var.c_str(), "1");
+    this->Makefile->AddDefinition(var, "1");
     bool result = this->ReadListFile(mfile.c_str(), DoPolicyScope);
-    this->Makefile->RemoveDefinition(var.c_str());
+    this->Makefile->RemoveDefinition(var);
     return result;
     }
   return true;
@@ -602,7 +602,7 @@ bool cmFindPackageCommand::HandlePackageMode()
   upperFound += "_FOUND";
 
   // Try to find the config file.
-  const char* def = this->Makefile->GetDefinition(this->Variable.c_str());
+  const char* def = this->Makefile->GetDefinition(this->Variable);
 
   // Try to load the config file if the directory is known
   bool fileFound = false;
@@ -627,14 +627,14 @@ bool cmFindPackageCommand::HandlePackageMode()
         this->FileFound = file;
         fileFound = true;
         }
-      def = this->Makefile->GetDefinition(this->Variable.c_str());
+      def = this->Makefile->GetDefinition(this->Variable);
       }
 
     // Search for the config file if it is not already found.
     if(cmSystemTools::IsOff(def) || !fileFound)
       {
       fileFound = this->FindConfig();
-      def = this->Makefile->GetDefinition(this->Variable.c_str());
+      def = this->Makefile->GetDefinition(this->Variable);
       }
 
     // Sanity check.
@@ -659,16 +659,16 @@ bool cmFindPackageCommand::HandlePackageMode()
 
   if(fileFound)
     {
-    if ((this->Makefile->IsDefinitionSet(foundVar.c_str()))
-      && (this->Makefile->IsOn(foundVar.c_str()) == false))
+    if ((this->Makefile->IsDefinitionSet(foundVar))
+      && (this->Makefile->IsOn(foundVar) == false))
       {
       // by removing Foo_FOUND here if it is FALSE, we don't really change
       // the situation for the Config file which is about to be included,
       // but we make it possible to detect later on whether the Config file
       // has set Foo_FOUND to FALSE itself:
-      this->Makefile->RemoveDefinition(foundVar.c_str());
+      this->Makefile->RemoveDefinition(foundVar);
       }
-    this->Makefile->RemoveDefinition(notFoundMessageVar.c_str());
+    this->Makefile->RemoveDefinition(notFoundMessageVar);
 
     // Set the version variables before loading the config file.
     // It may override them.
@@ -681,14 +681,14 @@ bool cmFindPackageCommand::HandlePackageMode()
       found = true;
 
       // Check whether the Config file has set Foo_FOUND to FALSE:
-      if ((this->Makefile->IsDefinitionSet(foundVar.c_str()))
-           && (this->Makefile->IsOn(foundVar.c_str()) == false))
+      if ((this->Makefile->IsDefinitionSet(foundVar))
+           && (this->Makefile->IsOn(foundVar) == false))
         {
         // we get here if the Config file has set Foo_FOUND actively to FALSE
         found = false;
         configFileSetFOUNDFalse = true;
         notFoundMessage = this->Makefile->GetSafeDefinition(
-                                                   notFoundMessageVar.c_str());
+                                                   notFoundMessageVar);
         }
       }
     else
@@ -810,18 +810,18 @@ bool cmFindPackageCommand::HandlePackageMode()
     }
 
   // Set a variable marking whether the package was found.
-  this->Makefile->AddDefinition(foundVar.c_str(), found? "1":"0");
+  this->Makefile->AddDefinition(foundVar, found? "1":"0");
 
   // Set a variable naming the configuration file that was found.
   std::string fileVar = this->Name;
   fileVar += "_CONFIG";
   if(found)
     {
-    this->Makefile->AddDefinition(fileVar.c_str(), this->FileFound.c_str());
+    this->Makefile->AddDefinition(fileVar, this->FileFound.c_str());
     }
   else
     {
-    this->Makefile->RemoveDefinition(fileVar.c_str());
+    this->Makefile->RemoveDefinition(fileVar);
     }
 
   std::string consideredConfigsVar = this->Name;
@@ -843,10 +843,10 @@ bool cmFindPackageCommand::HandlePackageMode()
     sep = ";";
     }
 
-  this->Makefile->AddDefinition(consideredConfigsVar.c_str(),
+  this->Makefile->AddDefinition(consideredConfigsVar,
                                 consideredConfigFiles.c_str());
 
-  this->Makefile->AddDefinition(consideredVersionsVar.c_str(),
+  this->Makefile->AddDefinition(consideredVersionsVar,
                                 consideredVersions.c_str());
 
   return result;
@@ -906,7 +906,7 @@ bool cmFindPackageCommand::FindConfig()
   help += this->Name;
   help += ".";
   // We force the value since we do not get here if it was already set.
-  this->Makefile->AddCacheDefinition(this->Variable.c_str(),
+  this->Makefile->AddCacheDefinition(this->Variable,
                                      init.c_str(), help.c_str(),
                                      cmCacheManager::PATH, true);
   return found;
@@ -968,7 +968,7 @@ bool cmFindPackageCommand::ReadListFile(const char* f, PolicyScopeRule psr)
   std::string e = "Error reading CMake code from \"";
   e += f;
   e += "\".";
-  this->SetError(e.c_str());
+  this->SetError(e);
   return false;
 }
 
@@ -1048,14 +1048,14 @@ void cmFindPackageCommand::AppendSuccessInformation()
   std::string transitivePropName = "_CMAKE_";
   transitivePropName += this->Name + "_TRANSITIVE_DEPENDENCY";
   this->Makefile->GetCMakeInstance()
-                ->SetProperty(transitivePropName.c_str(), "False");
+                ->SetProperty(transitivePropName, "False");
   }
   std::string found = this->Name;
   found += "_FOUND";
   std::string upperFound = cmSystemTools::UpperCase(found);
 
-  const char* upperResult = this->Makefile->GetDefinition(upperFound.c_str());
-  const char* result = this->Makefile->GetDefinition(found.c_str());
+  const char* upperResult = this->Makefile->GetDefinition(upperFound);
+  const char* result = this->Makefile->GetDefinition(found);
   bool packageFound = ((cmSystemTools::IsOn(result))
                                         || (cmSystemTools::IsOn(upperResult)));
 
@@ -1066,7 +1066,7 @@ void cmFindPackageCommand::AppendSuccessInformation()
   std::string quietInfoPropName = "_CMAKE_";
   quietInfoPropName += this->Name;
   quietInfoPropName += "_QUIET";
-  this->Makefile->GetCMakeInstance()->SetProperty(quietInfoPropName.c_str(),
+  this->Makefile->GetCMakeInstance()->SetProperty(quietInfoPropName,
                                                this->Quiet ? "TRUE" : "FALSE");
 
   // set a global property to record the required version of this package
@@ -1080,15 +1080,15 @@ void cmFindPackageCommand::AppendSuccessInformation()
     versionInfo += " ";
     versionInfo += this->Version;
     }
-  this->Makefile->GetCMakeInstance()->SetProperty(versionInfoPropName.c_str(),
+  this->Makefile->GetCMakeInstance()->SetProperty(versionInfoPropName,
                                                   versionInfo.c_str());
   if (this->Required)
     {
     std::string requiredInfoPropName = "_CMAKE_";
     requiredInfoPropName += this->Name;
     requiredInfoPropName += "_TYPE";
     this->Makefile->GetCMakeInstance()->SetProperty(
-                                     requiredInfoPropName.c_str(), "REQUIRED");
+                                     requiredInfoPropName, "REQUIRED");
     }
 
 
@@ -1648,25 +1648,25 @@ void cmFindPackageCommand::StoreVersionFound()
   ver += "_VERSION";
   if(this->VersionFound.empty())
     {
-    this->Makefile->RemoveDefinition(ver.c_str());
+    this->Makefile->RemoveDefinition(ver);
     }
   else
     {
-    this->Makefile->AddDefinition(ver.c_str(), this->VersionFound.c_str());
+    this->Makefile->AddDefinition(ver, this->VersionFound.c_str());
     }
 
   // Store the version components.
   char buf[64];
   sprintf(buf, "%u", this->VersionFoundMajor);
-  this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
+  this->Makefile->AddDefinition(ver+"_MAJOR", buf);
   sprintf(buf, "%u", this->VersionFoundMinor);
-  this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
+  this->Makefile->AddDefinition(ver+"_MINOR", buf);
   sprintf(buf, "%u", this->VersionFoundPatch);
-  this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
+  this->Makefile->AddDefinition(ver+"_PATCH", buf);
   sprintf(buf, "%u", this->VersionFoundTweak);
-  this->Makefile->AddDefinition((ver+"_TWEAK").c_str(), buf);
+  this->Makefile->AddDefinition(ver+"_TWEAK", buf);
   sprintf(buf, "%u", this->VersionFoundCount);
-  this->Makefile->AddDefinition((ver+"_COUNT").c_str(), buf);
+  this->Makefile->AddDefinition(ver+"_COUNT", buf);
 }
 
 //----------------------------------------------------------------------------