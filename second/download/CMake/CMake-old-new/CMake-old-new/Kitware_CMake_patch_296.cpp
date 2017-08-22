@@ -69,7 +69,7 @@ ::InitialPass(std::vector<std::string> const& args, cmExecutionStatus &)
     }
 
   std::string e = "does not recognize sub-command "+subCommand;
-  this->SetError(e.c_str());
+  this->SetError(e);
   return false;
 }
 
@@ -176,12 +176,12 @@ bool cmListCommand::HandleLengthCommand(std::vector<std::string> const& args)
   // do not check the return value here
   // if the list var is not found varArgsExpanded will have size 0
   // and we will return 0
-  this->GetList(varArgsExpanded, listName.c_str());
+  this->GetList(varArgsExpanded, listName);
   size_t length = varArgsExpanded.size();
   char buffer[1024];
   sprintf(buffer, "%d", static_cast<int>(length));
 
-  this->Makefile->AddDefinition(variableName.c_str(), buffer);
+  this->Makefile->AddDefinition(variableName, buffer);
   return true;
 }
 
@@ -198,9 +198,9 @@ bool cmListCommand::HandleGetCommand(std::vector<std::string> const& args)
   const std::string& variableName = args[args.size() - 1];
   // expand the variable
   std::vector<std::string> varArgsExpanded;
-  if ( !this->GetList(varArgsExpanded, listName.c_str()) )
+  if ( !this->GetList(varArgsExpanded, listName) )
     {
-    this->Makefile->AddDefinition(variableName.c_str(), "NOTFOUND");
+    this->Makefile->AddDefinition(variableName, "NOTFOUND");
     return true;
     }
   // FIXME: Add policy to make non-existing lists an error like empty lists.
@@ -229,13 +229,13 @@ bool cmListCommand::HandleGetCommand(std::vector<std::string> const& args)
       str << "index: " << item << " out of range (-"
           << varArgsExpanded.size() << ", "
           << varArgsExpanded.size()-1 << ")";
-      this->SetError(str.str().c_str());
+      this->SetError(str.str());
       return false;
       }
     value += varArgsExpanded[item];
     }
 
-  this->Makefile->AddDefinition(variableName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(variableName, value.c_str());
   return true;
 }
 
@@ -253,7 +253,7 @@ bool cmListCommand::HandleAppendCommand(std::vector<std::string> const& args)
   const std::string& listName = args[1];
   // expand the variable
   std::string listString;
-  this->GetListString(listString, listName.c_str());
+  this->GetListString(listString, listName);
   size_t cc;
   for ( cc = 2; cc < args.size(); ++ cc )
     {
@@ -264,7 +264,7 @@ bool cmListCommand::HandleAppendCommand(std::vector<std::string> const& args)
     listString += args[cc];
     }
 
-  this->Makefile->AddDefinition(listName.c_str(), listString.c_str());
+  this->Makefile->AddDefinition(listName, listString.c_str());
   return true;
 }
 
@@ -281,9 +281,9 @@ bool cmListCommand::HandleFindCommand(std::vector<std::string> const& args)
   const std::string& variableName = args[args.size() - 1];
   // expand the variable
   std::vector<std::string> varArgsExpanded;
-  if ( !this->GetList(varArgsExpanded, listName.c_str()) )
+  if ( !this->GetList(varArgsExpanded, listName) )
     {
-    this->Makefile->AddDefinition(variableName.c_str(), "-1");
+    this->Makefile->AddDefinition(variableName, "-1");
     return true;
     }
 
@@ -295,13 +295,13 @@ bool cmListCommand::HandleFindCommand(std::vector<std::string> const& args)
       {
       char indexString[32];
       sprintf(indexString, "%d", index);
-      this->Makefile->AddDefinition(variableName.c_str(), indexString);
+      this->Makefile->AddDefinition(variableName, indexString);
       return true;
       }
     index++;
     }
 
-  this->Makefile->AddDefinition(variableName.c_str(), "-1");
+  this->Makefile->AddDefinition(variableName, "-1");
   return true;
 }
 
@@ -319,12 +319,12 @@ bool cmListCommand::HandleInsertCommand(std::vector<std::string> const& args)
   // expand the variable
   int item = atoi(args[2].c_str());
   std::vector<std::string> varArgsExpanded;
-  if((!this->GetList(varArgsExpanded, listName.c_str())
+  if((!this->GetList(varArgsExpanded, listName)
       || varArgsExpanded.empty()) && item != 0)
     {
     cmOStringStream str;
     str << "index: " << item << " out of range (0, 0)";
-    this->SetError(str.str().c_str());
+    this->SetError(str.str());
     return false;
     }
 
@@ -341,7 +341,7 @@ bool cmListCommand::HandleInsertCommand(std::vector<std::string> const& args)
       str << "index: " << item << " out of range (-"
         << varArgsExpanded.size() << ", "
         << (varArgsExpanded.size() == 0?0:(varArgsExpanded.size()-1)) << ")";
-      this->SetError(str.str().c_str());
+      this->SetError(str.str());
       return false;
       }
     }
@@ -362,7 +362,7 @@ bool cmListCommand::HandleInsertCommand(std::vector<std::string> const& args)
     sep = ";";
     }
 
-  this->Makefile->AddDefinition(listName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(listName, value.c_str());
   return true;
 }
 
@@ -379,7 +379,7 @@ ::HandleRemoveItemCommand(std::vector<std::string> const& args)
   const std::string& listName = args[1];
   // expand the variable
   std::vector<std::string> varArgsExpanded;
-  if ( !this->GetList(varArgsExpanded, listName.c_str()) )
+  if ( !this->GetList(varArgsExpanded, listName) )
     {
     this->SetError("sub-command REMOVE_ITEM requires list to be present.");
     return false;
@@ -411,7 +411,7 @@ ::HandleRemoveItemCommand(std::vector<std::string> const& args)
     sep = ";";
     }
 
-  this->Makefile->AddDefinition(listName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(listName, value.c_str());
   return true;
 }
 
@@ -430,7 +430,7 @@ ::HandleReverseCommand(std::vector<std::string> const& args)
   const std::string& listName = args[1];
   // expand the variable
   std::vector<std::string> varArgsExpanded;
-  if ( !this->GetList(varArgsExpanded, listName.c_str()) )
+  if ( !this->GetList(varArgsExpanded, listName) )
     {
     this->SetError("sub-command REVERSE requires list to be present.");
     return false;
@@ -446,7 +446,7 @@ ::HandleReverseCommand(std::vector<std::string> const& args)
     sep = ";";
     }
 
-  this->Makefile->AddDefinition(listName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(listName, value.c_str());
   return true;
 }
 
@@ -465,7 +465,7 @@ ::HandleRemoveDuplicatesCommand(std::vector<std::string> const& args)
   const std::string& listName = args[1];
   // expand the variable
   std::vector<std::string> varArgsExpanded;
-  if ( !this->GetList(varArgsExpanded, listName.c_str()) )
+  if ( !this->GetList(varArgsExpanded, listName) )
     {
     this->SetError(
       "sub-command REMOVE_DUPLICATES requires list to be present.");
@@ -491,7 +491,7 @@ ::HandleRemoveDuplicatesCommand(std::vector<std::string> const& args)
     }
 
 
-  this->Makefile->AddDefinition(listName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(listName, value.c_str());
   return true;
 }
 
@@ -510,7 +510,7 @@ ::HandleSortCommand(std::vector<std::string> const& args)
   const std::string& listName = args[1];
   // expand the variable
   std::vector<std::string> varArgsExpanded;
-  if ( !this->GetList(varArgsExpanded, listName.c_str()) )
+  if ( !this->GetList(varArgsExpanded, listName) )
     {
     this->SetError("sub-command SORT requires list to be present.");
     return false;
@@ -528,7 +528,7 @@ ::HandleSortCommand(std::vector<std::string> const& args)
     sep = ";";
     }
 
-  this->Makefile->AddDefinition(listName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(listName, value.c_str());
   return true;
 }
 
@@ -546,7 +546,7 @@ bool cmListCommand::HandleRemoveAtCommand(
   const std::string& listName = args[1];
   // expand the variable
   std::vector<std::string> varArgsExpanded;
-  if ( !this->GetList(varArgsExpanded, listName.c_str()) )
+  if ( !this->GetList(varArgsExpanded, listName) )
     {
     this->SetError("sub-command REMOVE_AT requires list to be present.");
     return false;
@@ -574,7 +574,7 @@ bool cmListCommand::HandleRemoveAtCommand(
       str << "index: " << item << " out of range (-"
           << varArgsExpanded.size() << ", "
           << varArgsExpanded.size()-1 << ")";
-      this->SetError(str.str().c_str());
+      this->SetError(str.str());
       return false;
       }
     removed.push_back(static_cast<size_t>(item));
@@ -602,7 +602,7 @@ bool cmListCommand::HandleRemoveAtCommand(
       }
     }
 
-  this->Makefile->AddDefinition(listName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(listName, value.c_str());
   return true;
 }
 