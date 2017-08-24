@@ -27,20 +27,20 @@ bool cmVTKWrapTclCommand::InitialPass(std::vector<std::string> const& argsIn)
   std::vector<std::string> args;
   
   // keep the library name
-  m_LibraryName = argsIn[0];
+  this->LibraryName = argsIn[0];
 
   if (argsIn[1] == std::string("SOURCES"))
     {
-    m_Makefile->ExpandSourceListArguments(argsIn, args, 3);
+    this->Makefile->ExpandSourceListArguments(argsIn, args, 3);
     }
   else
     {
-    m_Makefile->ExpandSourceListArguments(argsIn, args, 2);
+    this->Makefile->ExpandSourceListArguments(argsIn, args, 2);
     }
   
   // Now check and see if the value has been stored in the cache
   // already, if so use that value and don't look for the program
-  if(!m_Makefile->IsOn("VTK_WRAP_TCL"))
+  if(!this->Makefile->IsOn("VTK_WRAP_TCL"))
     {
     return true;
     }
@@ -68,7 +68,7 @@ bool cmVTKWrapTclCommand::InitialPass(std::vector<std::string> const& argsIn)
         }
       else
         {
-        m_Commands.push_back(*j);
+        this->Commands.push_back(*j);
         }
       }
     }
@@ -77,29 +77,29 @@ bool cmVTKWrapTclCommand::InitialPass(std::vector<std::string> const& argsIn)
   if (sources.size())
     {
     // what is the current source dir
-    std::string cdir = m_Makefile->GetCurrentDirectory();
+    std::string cdir = this->Makefile->GetCurrentDirectory();
 
     // get the resulting source list name
-    m_SourceList = sources[0];
+    this->SourceList = sources[0];
     std::string sourceListValue;
     
     // was the list already populated
-    const char *def = m_Makefile->GetDefinition(m_SourceList.c_str());  
+    const char *def = this->Makefile->GetDefinition(this->SourceList.c_str());  
     if (def)
       {
       sourceListValue = def;
       sourceListValue += ";";
       }
     
     // Create the init file 
-    std::string res = m_LibraryName;
+    std::string res = this->LibraryName;
     res += "Init.cxx";
     sourceListValue += res;
     
     for(std::vector<std::string>::iterator j = (sources.begin() + 1);
         j != sources.end(); ++j)
       {   
-      cmSourceFile *curr = m_Makefile->GetSource(j->c_str());
+      cmSourceFile *curr = this->Makefile->GetSource(j->c_str());
       
       // if we should wrap the class
       if (!curr || !curr->GetPropertyAsBool("WRAP_EXCLUDE"))
@@ -114,26 +114,26 @@ bool cmVTKWrapTclCommand::InitialPass(std::vector<std::string> const& argsIn)
         std::string srcName = cmSystemTools::GetFilenameWithoutExtension(*j);
         std::string newName = srcName + "Tcl";
         std::string hname = srcDir + "/" + srcName + ".h";
-        file.SetName(newName.c_str(), m_Makefile->GetCurrentOutputDirectory(),
+        file.SetName(newName.c_str(), this->Makefile->GetCurrentOutputDirectory(),
                      "cxx",false);
-        m_WrapHeaders.push_back(hname);
+        this->WrapHeaders.push_back(hname);
         // add starting depends
         file.GetDepends().push_back(hname);
-        m_WrapClasses.push_back(file);
+        this->WrapClasses.push_back(file);
         sourceListValue += ";";
         sourceListValue += newName + ".cxx";
         }
       }
     // add the init file
     cmSourceFile cfile;
     cfile.SetProperty("ABSTRACT","0");
-    std::string newName = m_LibraryName;
+    std::string newName = this->LibraryName;
     newName += "Init";
     this->CreateInitFile(res);
-    cfile.SetName(newName.c_str(), m_Makefile->GetCurrentOutputDirectory(),
+    cfile.SetName(newName.c_str(), this->Makefile->GetCurrentOutputDirectory(),
                   "cxx",false);
-    m_Makefile->AddSource(cfile);
-    m_Makefile->AddDefinition(m_SourceList.c_str(), sourceListValue.c_str());  
+    this->Makefile->AddSource(cfile);
+    this->Makefile->AddDefinition(this->SourceList.c_str(), sourceListValue.c_str());  
     }
   
   return true;
@@ -142,10 +142,10 @@ bool cmVTKWrapTclCommand::InitialPass(std::vector<std::string> const& argsIn)
 void cmVTKWrapTclCommand::FinalPass() 
 {
   // first we add the rules for all the .h to Tcl.cxx files
-  size_t lastClass = m_WrapClasses.size();
+  size_t lastClass = this->WrapClasses.size();
   std::vector<std::string> depends;
-  const char* wtcl = m_Makefile->GetRequiredDefinition("VTK_WRAP_TCL_EXE");
-  const char* hints = m_Makefile->GetDefinition("VTK_WRAP_HINTS");
+  const char* wtcl = this->Makefile->GetRequiredDefinition("VTK_WRAP_TCL_EXE");
+  const char* hints = this->Makefile->GetDefinition("VTK_WRAP_HINTS");
 
   // wrap all the .h files
   depends.push_back(wtcl);
@@ -155,30 +155,30 @@ void cmVTKWrapTclCommand::FinalPass()
     }
   for(size_t classNum = 0; classNum < lastClass; classNum++)
     {
-    m_Makefile->AddSource(m_WrapClasses[classNum]);
+    this->Makefile->AddSource(this->WrapClasses[classNum]);
     cmCustomCommandLine commandLine;
     commandLine.push_back(wtcl);
-    commandLine.push_back(m_WrapHeaders[classNum]);
+    commandLine.push_back(this->WrapHeaders[classNum]);
     if(hints)
       {
       commandLine.push_back(hints);
       }
-    commandLine.push_back(
-      (m_WrapClasses[classNum].GetPropertyAsBool("ABSTRACT") ? "0" : "1"));
-    std::string res = m_Makefile->GetCurrentOutputDirectory();
+    commandLine.push_back((this->WrapClasses[classNum].
+                           GetPropertyAsBool("ABSTRACT") ? "0" : "1"));
+    std::string res = this->Makefile->GetCurrentOutputDirectory();
     res += "/";
-    res += m_WrapClasses[classNum].GetSourceName() + ".cxx";
+    res += this->WrapClasses[classNum].GetSourceName() + ".cxx";
     commandLine.push_back(res);
 
     cmCustomCommandLines commandLines;
     commandLines.push_back(commandLine);
     std::vector<std::string> outputs;
     outputs.push_back(res);
     const char* no_comment = 0;
-    m_Makefile->AddCustomCommandOldStyle(m_LibraryName.c_str(),
+    this->Makefile->AddCustomCommandOldStyle(this->LibraryName.c_str(),
                                          outputs,
                                          depends,
-                                         m_WrapHeaders[classNum].c_str(),
+                                         this->WrapHeaders[classNum].c_str(),
                                          commandLines,
                                          no_comment);
     }
@@ -187,16 +187,16 @@ void cmVTKWrapTclCommand::FinalPass()
 bool cmVTKWrapTclCommand::CreateInitFile(std::string& res) 
 {
   /* we have to make sure that the name is the correct case */
-  std::string kitName = cmSystemTools::Capitalized(m_LibraryName);
+  std::string kitName = cmSystemTools::Capitalized(this->LibraryName);
   
   std::vector<std::string> classes;
-  size_t lastClass = m_WrapHeaders.size();
+  size_t lastClass = this->WrapHeaders.size();
   size_t classNum;
   for(classNum = 0; classNum < lastClass; classNum++)
     {
-    if (!m_WrapClasses[classNum].GetPropertyAsBool("ABSTRACT"))
+    if (!this->WrapClasses[classNum].GetPropertyAsBool("ABSTRACT"))
       {
-      std::string cls = m_WrapHeaders[classNum];
+      std::string cls = this->WrapHeaders[classNum];
       cls = cls.substr(0,cls.size()-2);
       std::string::size_type pos = cls.rfind('/');    
       if(pos != std::string::npos)
@@ -209,7 +209,7 @@ bool cmVTKWrapTclCommand::CreateInitFile(std::string& res)
   
   // open the init file
   std::string outFileName = 
-    m_Makefile->GetCurrentOutputDirectory();
+    this->Makefile->GetCurrentOutputDirectory();
   outFileName += "/" + res;
   
   return this->WriteInit(kitName.c_str(), outFileName, classes);
@@ -234,9 +234,9 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
 
   // capitalized commands just once
   std::vector<std::string> capcommands;
-  for (i = 0; i < m_Commands.size(); i++)
+  for (i = 0; i < this->Commands.size(); i++)
     {
-    capcommands.push_back(cmSystemTools::Capitalized(m_Commands[i]));
+    capcommands.push_back(cmSystemTools::Capitalized(this->Commands[i]));
     }
   
   fprintf(fout,"#include \"vtkTclUtil.h\"\n");
@@ -282,7 +282,7 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
   fprintf(fout,"extern void vtkTclDeleteObjectFromHash(void *);\n");  
   fprintf(fout,"extern void vtkTclListInstances(Tcl_Interp *interp, ClientData arg);\n");
 
-  for (i = 0; i < m_Commands.size(); i++)
+  for (i = 0; i < this->Commands.size(); i++)
     {
     fprintf(fout,"\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n",
             capcommands[i].c_str());
@@ -335,7 +335,7 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
                  "                    (ClientData *)NULL, NULL);\n\n");
     }
   
-  for (i = 0; i < m_Commands.size(); i++)
+  for (i = 0; i < this->Commands.size(); i++)
     {
     fprintf(fout,"  %s_Init(interp);\n", capcommands[i].c_str());
     }
@@ -348,7 +348,7 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     fprintf(fout,"                  %sCommand);\n",classes[i].c_str());
     }
   
-  fprintf(fout,"  char pkgName[]=\"%s\";\n", m_LibraryName.c_str());
+  fprintf(fout,"  char pkgName[]=\"%s\";\n", this->LibraryName.c_str());
   fprintf(fout,"  char pkgVers[]=VTK_TCL_TO_STRING(VTK_MAJOR_VERSION)"
                " \".\" "
                "VTK_TCL_TO_STRING(VTK_MINOR_VERSION);\n");