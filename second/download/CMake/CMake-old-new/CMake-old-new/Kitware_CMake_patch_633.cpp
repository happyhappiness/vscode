@@ -112,138 +112,104 @@ bool cmMacroHelperCommand::InvokeInitialPass
   // declare varuiables for ARGV ARGN but do not compute until needed
   std::string argvDef;
   std::string argnDef;
-  bool argnDefInitialized = false;
   bool argvDefInitialized = false;
-  
-  // Invoke all the functions that were collected in the block.
-  cmListFileFunction newLFF;
-  // for each function
-  for(unsigned int c = 0; c < m_Functions.size(); ++c)
+
+  // save the current definitions of all vars that we will be setting
+  std::string oldARGC;
+  if (m_Makefile->GetDefinition("ARGC"))
     {
-    // Replace the formal arguments and then invoke the command.
-    newLFF.m_Arguments.clear();
-    newLFF.m_Arguments.reserve(m_Functions[c].m_Arguments.size());
-    newLFF.m_Name = m_Functions[c].m_Name;
-    newLFF.m_FilePath = m_Functions[c].m_FilePath;
-    newLFF.m_Line = m_Functions[c].m_Line;
-    const char* def =
-      m_Makefile->GetDefinition("CMAKE_MACRO_REPORT_DEFINITION_LOCATION"); 
-    bool macroReportLocation = false;
-    if(def && !cmSystemTools::IsOff(def))
-      {
-      macroReportLocation = true;
-      }
-    
-    // for each argument of the current function
-    for (std::vector<cmListFileArgument>::const_iterator k = 
-           m_Functions[c].m_Arguments.begin();
-         k != m_Functions[c].m_Arguments.end(); ++k)
+    oldARGC = m_Makefile->GetDefinition("ARGC");
+    }
+  m_Makefile->AddDefinition("ARGC",argcDef.c_str());
+
+  // store ARGN, ARGV
+  std::vector<std::string> oldARGVArgs;
+  std::vector<std::string>::const_iterator eit;
+  std::vector<std::string>::size_type cnt = 0;
+  char argvName[60];
+  for ( eit = expandedArgs.begin(); eit != expandedArgs.end(); ++eit )
+    {
+    if ( cnt >= m_Args.size()-1 )
       {
-      tmps = k->Value;
-      // replace formal arguments
-      for (unsigned int j = 1; j < m_Args.size(); ++j)
-        {
-        variable = "${";
-        variable += m_Args[j];
-        variable += "}"; 
-        cmSystemTools::ReplaceString(tmps, variable.c_str(),
-                                     expandedArgs[j-1].c_str());
-        }
-      // replace argc
-      cmSystemTools::ReplaceString(tmps, "${ARGC}",argcDef.c_str());
-      
-      // repleace ARGN
-      if (tmps.find("${ARGN}") != std::string::npos)
-        {
-        if (!argnDefInitialized)
-          {
-          std::vector<std::string>::const_iterator eit;
-          std::vector<std::string>::size_type cnt = 0;
-          for ( eit = expandedArgs.begin(); eit != expandedArgs.end(); ++eit )
-            {
-            if ( cnt >= m_Args.size()-1 )
-              {
-              if ( argnDef.size() > 0 )
-                {
-                argnDef += ";";
-                }
-              argnDef += *eit;
-              }
-            cnt ++;
-            }
-          argnDefInitialized = true;
-          }
-        cmSystemTools::ReplaceString(tmps, "${ARGN}", argnDef.c_str());
-        }
-      
-      // if the current argument of the current function has ${ARGV in it
-      // then try replacing ARGV values
-      if (tmps.find("${ARGV") != std::string::npos)
+      if ( argnDef.size() > 0 )
         {
-        char argvName[60];
-        
-        // repleace ARGV, compute it only once
-        if (!argvDefInitialized)
-          {
-          std::vector<std::string>::const_iterator eit;
-          for ( eit = expandedArgs.begin(); eit != expandedArgs.end(); ++eit )
-            {
-            if ( argvDef.size() > 0 )
-              {
-              argvDef += ";";
-              }
-            argvDef += *eit;
-            }
-          argvDefInitialized = true;
-          }
-        cmSystemTools::ReplaceString(tmps, "${ARGV}", argvDef.c_str());
-        
-        // also replace the ARGV1 ARGV2 ... etc
-        for (unsigned int t = 0; t < expandedArgs.size(); ++t)
-          {
-          sprintf(argvName,"${ARGV%i}",t);
-          cmSystemTools::ReplaceString(tmps, argvName,
-                                       expandedArgs[t].c_str());
-          }
+        argnDef += ";";
         }
-      
-      arg.Value = tmps;
-      arg.Quoted = k->Quoted;
-      if(macroReportLocation)
-        {
-        // Report the location of the argument where the macro was
-        // defined.
-        arg.FilePath = k->FilePath;
-        arg.Line = k->Line;
-        }
-      else
-        {
-        // Report the location of the argument where the macro was
-        // invoked.
-        if (args.size())
-          {
-          arg.FilePath = args[0].FilePath;
-          arg.Line = args[0].Line;
-          }
-        else
-          {
-          arg.FilePath = "Unknown";
-          arg.Line = 0;
-          }
-        }
-      newLFF.m_Arguments.push_back(arg);
+      argnDef += *eit;
+      }
+    if ( argvDef.size() > 0 )
+      {
+      argvDef += ";";
       }
-    if(!m_Makefile->ExecuteCommand(newLFF))
+    argvDef += *eit;
+    oldARGVArgs.push_back(std::string());
+    sprintf(argvName,"ARGV%i",cnt);
+    if (m_Makefile->GetDefinition(argvName))
+      {
+      oldARGVArgs[cnt] = m_Makefile->GetDefinition(argvName);
+      }
+    m_Makefile->AddDefinition(argvName,eit->c_str());
+    cnt++;
+    }
+  std::string oldARGN;
+  if (m_Makefile->GetDefinition("ARGN"))
+    {
+    oldARGN = m_Makefile->GetDefinition("ARGN");
+    }
+  m_Makefile->AddDefinition("ARGN",argnDef.c_str());
+  std::string oldARGV;
+  if (m_Makefile->GetDefinition("ARGV"))
+    {
+    oldARGV = m_Makefile->GetDefinition("ARGV");
+    }
+  m_Makefile->AddDefinition("ARGV",argvDef.c_str());
+
+  // store old defs for formal args
+  std::vector<std::string> oldFormalArgs;
+  for (unsigned int j = 1; j < m_Args.size(); ++j)
+    {
+    oldFormalArgs.push_back(std::string());
+    if (m_Makefile->GetDefinition(m_Args[j].c_str()))
+      {
+      oldFormalArgs[j-1] = m_Makefile->GetDefinition(m_Args[j].c_str());
+      }
+    m_Makefile->AddDefinition(m_Args[j].c_str(),expandedArgs[j-1].c_str());
+    }
+  
+  // Invoke all the functions that were collected in the block.
+  for(unsigned int c = 0; c < m_Functions.size(); ++c)
+    {
+    if(!m_Makefile->ExecuteCommand(m_Functions[c]))
       {
       cmOStringStream error;
       error << "Error in cmake code at\n"
-            << args[0].FilePath << ":" << args[0].Line << ":\n"
+            << args[0].FilePath << ":" << args[0].Line << "\n"
             << "A command failed during the invocation of macro \""
-            << this->m_Args[0].c_str() << "\".";
+            << this->m_Args[0].c_str() << "\".\nThe failing line "
+            << "in the macro definition was at\n" 
+            << m_Functions[c].m_FilePath << ":"
+            << m_Functions[c].m_Line << "\n";
       cmSystemTools::Error(error.str().c_str());
       return false;
       }
     }
+  
+  // restore all args
+  m_Makefile->AddDefinition("ARGC",oldARGC.c_str());
+  m_Makefile->AddDefinition("ARGN",oldARGN.c_str());
+  m_Makefile->AddDefinition("ARGV",oldARGV.c_str());
+  // restore old defs for formal args
+  for (unsigned int j = 1; j < m_Args.size(); ++j)
+    {
+    m_Makefile->AddDefinition(m_Args[j].c_str(),oldFormalArgs[j-1].c_str());
+    }
+  // restore old defs for formal args
+  for (unsigned int j = 0; j < oldARGVArgs.size(); ++j)
+    {
+    sprintf(argvName,"ARGV%i",j);
+    m_Makefile->AddDefinition(argvName,oldARGVArgs[j].c_str());
+    }
+  
   return true;
 }
 
@@ -252,7 +218,7 @@ IsFunctionBlocked(const cmListFileFunction& lff, cmMakefile &mf)
 {
   // record commands until we hit the ENDMACRO
   // at the ENDMACRO call we shift gears and start looking for invocations
-  if(lff.m_Name == "ENDMACRO")
+  if(cmSystemTools::LowerCase(lff.m_Name) == "endmacro")
     {
     std::vector<std::string> expandedArguments;
     mf.ExpandArguments(lff.m_Arguments, expandedArguments);
@@ -292,7 +258,7 @@ IsFunctionBlocked(const cmListFileFunction& lff, cmMakefile &mf)
 bool cmMacroFunctionBlocker::
 ShouldRemove(const cmListFileFunction& lff, cmMakefile &mf) 
 {
-  if(lff.m_Name == "ENDMACRO")
+  if(cmSystemTools::LowerCase(lff.m_Name) == "endmacro")
     {
     std::vector<std::string> expandedArguments;
     mf.ExpandArguments(lff.m_Arguments, expandedArguments);