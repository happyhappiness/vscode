@@ -122,10 +122,6 @@ bool cmMacroHelperCommand::InvokeInitialPass
     sprintf(argvName,"${ARGV%i}",j);
     argVs.push_back(argvName);
     }
-  if(!this->Functions.empty())
-    {
-    this->FilePath = this->Functions[0].FilePath;
-    }
   // Invoke all the functions that were collected in the block.
   cmListFileFunction newLFF;
   // for each function
@@ -225,6 +221,7 @@ IsFunctionBlocked(const cmListFileFunction& lff, cmMakefile &mf,
       cmMacroHelperCommand *f = new cmMacroHelperCommand();
       f->Args = this->Args;
       f->Functions = this->Functions;
+      f->FilePath = this->GetStartingContext().FilePath;
       mf.RecordPolicies(f->Policies);
       std::string newName = "_" + this->Args[0];
       mf.GetState()->RenameCommand(this->Args[0], newName);