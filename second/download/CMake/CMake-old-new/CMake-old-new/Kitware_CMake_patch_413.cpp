@@ -93,6 +93,10 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
     {
     return this->HandleTimestampCommand(args);
     }
+  else if(subCommand == "MAKE_C_IDENTIFIER")
+    {
+    return this->HandleMakeCIdentifierCommand(args);
+    }
 
   std::string e = "does not recognize sub-command "+subCommand;
   this->SetError(e.c_str());
@@ -530,8 +534,12 @@ void cmStringCommand::ClearMatches(cmMakefile* mf)
     {
     char name[128];
     sprintf(name, "CMAKE_MATCH_%d", i);
-    mf->AddDefinition(name, "");
-    mf->MarkVariableAsUsed(name);
+    const char* s = mf->GetDefinition(name);
+    if(s && *s != 0)
+      {
+      mf->AddDefinition(name, "");
+      mf->MarkVariableAsUsed(name);
+      }
     }
 }
 
@@ -540,10 +548,14 @@ void cmStringCommand::StoreMatches(cmMakefile* mf,cmsys::RegularExpression& re)
 {
   for (unsigned int i=0; i<10; i++)
     {
-    char name[128];
-    sprintf(name, "CMAKE_MATCH_%d", i);
-    mf->AddDefinition(name, re.match(i).c_str());
-    mf->MarkVariableAsUsed(name);
+    std::string m = re.match(i);
+    if(m.size() > 0)
+      {
+      char name[128];
+      sprintf(name, "CMAKE_MATCH_%d", i);
+      mf->AddDefinition(name, re.match(i).c_str());
+      mf->MarkVariableAsUsed(name);
+      }
     }
 }
 
@@ -755,6 +767,24 @@ ::HandleLengthCommand(std::vector<std::string> const& args)
 }
 
 //----------------------------------------------------------------------------
+bool cmStringCommand
+::HandleMakeCIdentifierCommand(std::vector<std::string> const& args)
+{
+  if(args.size() != 3)
+    {
+    this->SetError("sub-command MAKE_C_IDENTIFIER requires two arguments.");
+    return false;
+    }
+
+  const std::string& input = args[1];
+  const std::string& variableName = args[2];
+
+  this->Makefile->AddDefinition(variableName.c_str(),
+                      cmSystemTools::MakeCidentifier(input.c_str()).c_str());
+  return true;
+}
+
+//----------------------------------------------------------------------------
 bool cmStringCommand::HandleStripCommand(
   std::vector<std::string> const& args)
 {