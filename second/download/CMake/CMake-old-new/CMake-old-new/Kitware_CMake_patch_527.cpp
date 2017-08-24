@@ -69,7 +69,7 @@ bool cmListCommand::GetListString(std::string& listString, const char* var)
     }
   // get the old value
   const char* cacheValue
-    = m_Makefile->GetDefinition(var);
+    = this->Makefile->GetDefinition(var);
   if(!cacheValue)
     {
     cmOStringStream str;
@@ -115,7 +115,7 @@ bool cmListCommand::HandleLengthCommand(std::vector<std::string> const& args)
   char buffer[1024];
   sprintf(buffer, "%d", static_cast<int>(length));
 
-  m_Makefile->AddDefinition(variableName.c_str(), buffer);
+  this->Makefile->AddDefinition(variableName.c_str(), buffer);
   return true;
 }
 
@@ -161,7 +161,7 @@ bool cmListCommand::HandleGetCommand(std::vector<std::string> const& args)
     value += varArgsExpanded[item];
     }
 
-  m_Makefile->AddDefinition(variableName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(variableName.c_str(), value.c_str());
   return true;
 }
 
@@ -191,7 +191,7 @@ bool cmListCommand::HandleSetCommand(std::vector<std::string> const& args)
     listString += args[cc];
     }
 
-  m_Makefile->AddDefinition(listName.c_str(), listString.c_str());
+  this->Makefile->AddDefinition(listName.c_str(), listString.c_str());
   return true;
 }
 
@@ -244,7 +244,7 @@ bool cmListCommand::HandleInsertCommand(std::vector<std::string> const& args)
     value += varArgsExpanded[cc];
     }
 
-  m_Makefile->AddDefinition(listName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(listName.c_str(), value.c_str());
   return true;
 }
 
@@ -289,7 +289,7 @@ bool cmListCommand::HandleRemoveCommand(std::vector<std::string> const& args)
     value += varArgsExpanded[cc];
     }
 
-  m_Makefile->AddDefinition(listName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(listName.c_str(), value.c_str());
   return true;
 }
 
@@ -353,7 +353,7 @@ bool cmListCommand::HandleRemoveItemCommand(std::vector<std::string> const& args
       }
     }
 
-  m_Makefile->AddDefinition(listName.c_str(), value.c_str());
+  this->Makefile->AddDefinition(listName.c_str(), value.c_str());
   return true;
 }
 