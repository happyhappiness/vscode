@@ -56,39 +56,72 @@ bool cmVTKWrapTclCommand::Invoke(std::vector<std::string>& args)
     return true;
     }
 
-  // add in a depend in the vtkVTKWrapTcl executable
-  m_Makefile->AddUtility("vtkWrapTcl");
-  
-  // what is the current source dir
-  std::string cdir = m_Makefile->GetCurrentDirectory();
-
   // keep the library name
   m_LibraryName = args[0];
-  m_SourceList = args[1];
-  
-  // get the list of classes for this library
-  cmMakefile::SourceMap &Classes = m_Makefile->GetSources();
-  for(std::vector<std::string>::iterator j = (args.begin() + 2);
+
+  // extract the sources and commands parameters
+  std::vector<std::string> sources;
+  bool doing_sources = true;
+
+  for(std::vector<std::string>::iterator j = (args.begin() + 1);
       j != args.end(); ++j)
     {   
-    cmMakefile::SourceMap::iterator l = Classes.find(*j);
-    for(std::vector<cmSourceFile>::iterator i = l->second.begin(); 
-        i != l->second.end(); i++)
+    if(*j == "SOURCES")
+      {
+      doing_sources = true;
+      }
+    else if (*j == "COMMANDS")
       {
-      cmSourceFile &curr = *i;
-      // if we should wrap the class
-      if (!curr.GetWrapExclude())
+      doing_sources = false;
+      }
+    else
+      { 
+      if(doing_sources)
+        {
+        sources.push_back(*j);
+        }
+      else
+        {
+        m_Commands.push_back(*j);
+        }
+      }
+    }
+
+  // get the list of classes for this library
+  if (sources.size())
+    {
+    // what is the current source dir
+    std::string cdir = m_Makefile->GetCurrentDirectory();
+
+    // add in a depend in the vtkVTKWrapTcl executable
+    m_Makefile->AddUtility("vtkWrapTcl");
+
+    // get the resulting source list name
+    m_SourceList = sources[0];
+
+    cmMakefile::SourceMap &Classes = m_Makefile->GetSources();
+    for(std::vector<std::string>::iterator j = (sources.begin() + 1);
+        j != sources.end(); ++j)
+      {   
+      cmMakefile::SourceMap::iterator l = Classes.find(*j);
+      for(std::vector<cmSourceFile>::iterator i = l->second.begin(); 
+          i != l->second.end(); i++)
         {
-        cmSourceFile file;
-        file.SetIsAnAbstractClass(curr.IsAnAbstractClass());
-        std::string newName = curr.GetSourceName() + "Tcl";
-        file.SetName(newName.c_str(), m_Makefile->GetCurrentOutputDirectory(),
-                     "cxx",false);
-        std::string hname = cdir + "/" + curr.GetSourceName() + ".h";
-        m_WrapHeaders.push_back(hname);
-        // add starting depends
-        file.GetDepends().push_back(hname);
-        m_WrapClasses.push_back(file);
+        cmSourceFile &curr = *i;
+        // if we should wrap the class
+        if (!curr.GetWrapExclude())
+          {
+          cmSourceFile file;
+          file.SetIsAnAbstractClass(curr.IsAnAbstractClass());
+          std::string newName = curr.GetSourceName() + "Tcl";
+          file.SetName(newName.c_str(), m_Makefile->GetCurrentOutputDirectory(),
+                       "cxx",false);
+          std::string hname = cdir + "/" + curr.GetSourceName() + ".h";
+          m_WrapHeaders.push_back(hname);
+          // add starting depends
+          file.GetDepends().push_back(hname);
+          m_WrapClasses.push_back(file);
+          }
         }
       }
     }
@@ -135,18 +168,8 @@ void cmVTKWrapTclCommand::FinalPass()
 
 bool cmVTKWrapTclCommand::CreateInitFile(std::string& res) 
 {
-  unsigned int i;
-  
   /* we have to make sure that the name is the correct case */
-  std::string kitName = m_LibraryName;
-  if (kitName[0] > 90) kitName[0] -= 32;
-  for (i = 1; i < kitName.size(); i++)
-    {
-    if ((kitName[i] > 64)&&(kitName[i] < 91))
-      {
-      kitName[i] += 32;
-      }
-    }
+  std::string kitName = cmSystemTools::Capitalized(m_LibraryName);
   
   std::vector<std::string> classes;
   int lastClass = m_WrapHeaders.size();
@@ -187,6 +210,13 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     {
     return false;
     }
+
+  // capitalized commands just once
+  std::vector<std::string> capcommands;
+  for (i = 0; i < m_Commands.size(); i++)
+    {
+    capcommands.push_back(cmSystemTools::Capitalized(m_Commands[i]));
+    }
   
   fprintf(fout,"#include \"vtkTclUtil.h\"\n");
   
@@ -211,14 +241,20 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     }
   fprintf(fout,"extern void vtkTclDeleteObjectFromHash(void *);\n");  
   fprintf(fout,"extern void vtkTclListInstances(Tcl_Interp *interp, ClientData arg);\n");
+
+  for (i = 0; i < m_Commands.size(); i++)
+    {
+    fprintf(fout,"\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n",
+            capcommands[i].c_str());
+    }
   
-  fprintf(fout,"\n\nextern \"C\" {int VTK_EXPORT %s_SafeInit(Tcl_Interp *interp);}\n\n",
+  fprintf(fout,"\n\nextern \"C\" {int VTK_EXPORT %s_SafeInit(Tcl_Interp *interp);}\n",
 	  kitName);
-  fprintf(fout,"\n\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n\n",
+  fprintf(fout,"\nextern \"C\" {int VTK_EXPORT %s_Init(Tcl_Interp *interp);}\n",
 	  kitName);
   
   /* create an extern ref to the generic delete function */
-  fprintf(fout,"\n\nextern void vtkTclGenericDeleteObject(ClientData cd);\n\n");
+  fprintf(fout,"\nextern void vtkTclGenericDeleteObject(ClientData cd);\n");
 
   /* the main declaration */
   fprintf(fout,"\n\nint VTK_EXPORT %s_SafeInit(Tcl_Interp *interp)\n{\n",kitName);
@@ -247,6 +283,12 @@ bool cmVTKWrapTclCommand::WriteInit(const char *kitName,
     fprintf(fout,"  Tcl_CreateCommand(interp,(char *) \"vtkCommand\",vtkCommand,\n		    (ClientData *)NULL, NULL);\n\n");
     }
   
+  for (i = 0; i < m_Commands.size(); i++)
+    {
+    fprintf(fout,"  %s_Init(interp);\n", capcommands[i].c_str());
+    }
+  fprintf(fout,"\n");
+
   for (i = 0; i < classes.size(); i++)
     {
     fprintf(fout,"  vtkTclCreateNew(interp,(char *) \"%s\", %sNewCommand,\n",