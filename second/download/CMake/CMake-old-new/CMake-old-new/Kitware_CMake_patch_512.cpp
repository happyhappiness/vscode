@@ -422,7 +422,7 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
       // Set a variable telling the find script this component
       // is required.
       std::string req_var = this->Name + "_FIND_REQUIRED_" + args[i];
-      this->Makefile->AddDefinition(req_var.c_str(), "1");
+      this->AddFindDefinition(req_var.c_str(), "1");
 
       // Append to the list of required components.
       components += components_sep;
@@ -579,15 +579,15 @@ void cmFindPackageCommand::SetModuleVariables(const std::string& components)
 {
   // Store the list of components.
   std::string components_var = this->Name + "_FIND_COMPONENTS";
-  this->Makefile->AddDefinition(components_var.c_str(), components.c_str());
+  this->AddFindDefinition(components_var.c_str(), components.c_str());
    
   if(this->Quiet)
     {
     // Tell the module that is about to be read that it should find
     // quietly.
     std::string quietly = this->Name;
     quietly += "_FIND_QUIETLY";
-    this->Makefile->AddDefinition(quietly.c_str(), "1");
+    this->AddFindDefinition(quietly.c_str(), "1");
     }
 
   if(this->Required)
@@ -596,7 +596,7 @@ void cmFindPackageCommand::SetModuleVariables(const std::string& components)
     // a fatal error if the package is not found.
     std::string req = this->Name;
     req += "_FIND_REQUIRED";
-    this->Makefile->AddDefinition(req.c_str(), "1");
+    this->AddFindDefinition(req.c_str(), "1");
     }
 
   if(!this->Version.empty())
@@ -605,27 +605,58 @@ void cmFindPackageCommand::SetModuleVariables(const std::string& components)
     // package has been requested.
     std::string ver = this->Name;
     ver += "_FIND_VERSION";
-    this->Makefile->AddDefinition(ver.c_str(), this->Version.c_str());
+    this->AddFindDefinition(ver.c_str(), this->Version.c_str());
     char buf[64];
     sprintf(buf, "%u", this->VersionMajor);
-    this->Makefile->AddDefinition((ver+"_MAJOR").c_str(), buf);
+    this->AddFindDefinition((ver+"_MAJOR").c_str(), buf);
     sprintf(buf, "%u", this->VersionMinor);
-    this->Makefile->AddDefinition((ver+"_MINOR").c_str(), buf);
+    this->AddFindDefinition((ver+"_MINOR").c_str(), buf);
     sprintf(buf, "%u", this->VersionPatch);
-    this->Makefile->AddDefinition((ver+"_PATCH").c_str(), buf);
+    this->AddFindDefinition((ver+"_PATCH").c_str(), buf);
     sprintf(buf, "%u", this->VersionTweak);
-    this->Makefile->AddDefinition((ver+"_TWEAK").c_str(), buf);
+    this->AddFindDefinition((ver+"_TWEAK").c_str(), buf);
     sprintf(buf, "%u", this->VersionCount);
-    this->Makefile->AddDefinition((ver+"_COUNT").c_str(), buf);
+    this->AddFindDefinition((ver+"_COUNT").c_str(), buf);
 
     // Tell the module whether an exact version has been requested.
     std::string exact = this->Name;
     exact += "_FIND_VERSION_EXACT";
-    this->Makefile->AddDefinition(exact.c_str(),
-                                  this->VersionExact? "1":"0");
+    this->AddFindDefinition(exact.c_str(), this->VersionExact? "1":"0");
    }
 }
 
+//----------------------------------------------------------------------------
+void cmFindPackageCommand::AddFindDefinition(const char* var, const char* val)
+{
+  if(const char* old = this->Makefile->GetDefinition(var))
+    {
+    this->OriginalDefs[var].exists = true;
+    this->OriginalDefs[var].value = old;
+    }
+  else
+    {
+    this->OriginalDefs[var].exists = false;
+    }
+  this->Makefile->AddDefinition(var, val);
+}
+
+//----------------------------------------------------------------------------
+void cmFindPackageCommand::RestoreFindDefinitions()
+{
+  for(std::map<cmStdString, OriginalDef>::iterator
+        i = this->OriginalDefs.begin(); i != this->OriginalDefs.end(); ++i)
+    {
+    OriginalDef const& od = i->second;
+    if(od.exists)
+      {
+      this->Makefile->AddDefinition(i->first.c_str(), od.value.c_str());
+      }
+    else
+      {
+      this->Makefile->RemoveDefinition(i->first.c_str());
+      }
+    }
+}
 
 //----------------------------------------------------------------------------
 bool cmFindPackageCommand::FindModule(bool& found)
@@ -1008,6 +1039,9 @@ void cmFindPackageCommand::AppendSuccessInformation()
       this->AppendToProperty("DISABLED_FEATURES");
       }
     }
+
+  // Restore original state of "_FIND_" variables we set.
+  this->RestoreFindDefinitions();
 }
 
 //----------------------------------------------------------------------------