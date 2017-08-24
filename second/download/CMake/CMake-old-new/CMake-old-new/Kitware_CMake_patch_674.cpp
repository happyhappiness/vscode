@@ -71,10 +71,9 @@ IsFunctionBlocked(const cmListFileFunction& lff, cmMakefile &mf)
       cmSystemTools::Error(error.str().c_str());
       return true;
       }
-    
-    // now set the new argcDef
-    char argcDef[64];
-    sprintf(argcDef,"%i",expandedArguments.size());    
+    cmOStringStream argcDefStream;
+    argcDefStream << expandedArguments.size();
+    std::string argcDef = argcDefStream.str();
     
     // Invoke all the functions that were collected in the block.
     cmListFileFunction newLFF;
@@ -104,7 +103,7 @@ IsFunctionBlocked(const cmListFileFunction& lff, cmMakefile &mf)
         for (unsigned int j = 1; j < m_Args.size(); ++j)
           {
           variable = "${ARGC}";
-          cmSystemTools::ReplaceString(tmps, variable.c_str(),argcDef);
+          cmSystemTools::ReplaceString(tmps, variable.c_str(),argcDef.c_str());
           }
         for (unsigned int j = 1; j < m_Args.size(); ++j)
           {