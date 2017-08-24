@@ -23,150 +23,130 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
   this->BinaryDirectory = argv[1].c_str();
   this->OutputFile = "";
   // which signature were we called with ?
-  this->SrcFileSignature = false;
-  unsigned int i;
+  this->SrcFileSignature = true;
 
   const char* sourceDirectory = argv[2].c_str();
   const char* projectName = 0;
   const char* targetName = 0;
-  char targetNameBuf[64];
-  int extraArgs = 0;
-
-  // look for CMAKE_FLAGS and store them
   std::vector<std::string> cmakeFlags;
-  for (i = 3; i < argv.size(); ++i)
-    {
-    if (argv[i] == "CMAKE_FLAGS")
-      {
-     // CMAKE_FLAGS is the first argument because we need an argv[0] that
-     // is not used, so it matches regular command line parsing which has
-     // the program name as arg 0
-      for (; i < argv.size() && argv[i] != "COMPILE_DEFINITIONS" &&
-             argv[i] != "OUTPUT_VARIABLE" &&
-             argv[i] != "LINK_LIBRARIES";
-           ++i)
-        {
-        extraArgs++;
-        cmakeFlags.push_back(argv[i]);
-        }
-      break;
-      }
-    }
-
-  // look for OUTPUT_VARIABLE and store them
+  std::vector<std::string> compileDefs;
   std::string outputVariable;
-  for (i = 3; i < argv.size(); ++i)
+  std::string copyFile;
+  std::vector<cmTarget*> targets;
+  std::string libsToLink = " ";
+  bool useOldLinkLibs = true;
+  char targetNameBuf[64];
+  bool didOutputVariable = false;
+  bool didCopyFile = false;
+
+  enum Doing { DoingNone, DoingCMakeFlags, DoingCompileDefinitions,
+               DoingLinkLibraries, DoingOutputVariable, DoingCopyFile };
+  Doing doing = DoingNone;
+  for(size_t i=3; i < argv.size(); ++i)
     {
-    if (argv[i] == "OUTPUT_VARIABLE")
+    if(argv[i] == "CMAKE_FLAGS")
       {
-      if ( argv.size() <= (i+1) )
-        {
-        this->Makefile->IssueMessage(cmake::FATAL_ERROR,
-          "OUTPUT_VARIABLE specified but there is no variable");
-        return -1;
-        }
-      extraArgs += 2;
-      outputVariable = argv[i+1];
-      break;
+      doing = DoingCMakeFlags;
+      // CMAKE_FLAGS is the first argument because we need an argv[0] that
+      // is not used, so it matches regular command line parsing which has
+      // the program name as arg 0
+      cmakeFlags.push_back(argv[i]);
       }
-    }
-
-  // look for COMPILE_DEFINITIONS and store them
-  std::vector<std::string> compileFlags;
-  for (i = 3; i < argv.size(); ++i)
-    {
-    if (argv[i] == "COMPILE_DEFINITIONS")
+    else if(argv[i] == "COMPILE_DEFINITIONS")
       {
-      extraArgs++;
-      for (i = i + 1; i < argv.size() && argv[i] != "CMAKE_FLAGS" &&
-             argv[i] != "OUTPUT_VARIABLE" &&
-             argv[i] != "LINK_LIBRARIES";
-           ++i)
-        {
-        extraArgs++;
-        compileFlags.push_back(argv[i]);
-        }
-      break;
+      doing = DoingCompileDefinitions;
       }
-    }
-
-  std::vector<cmTarget*> targets;
-  std::string libsToLink = " ";
-  bool useOldLinkLibs = true;
-  for (i = 3; i < argv.size(); ++i)
-    {
-    if (argv[i] == "LINK_LIBRARIES")
+    else if(argv[i] == "LINK_LIBRARIES")
       {
-      if ( argv.size() <= (i+1) )
-        {
-        this->Makefile->IssueMessage(cmake::FATAL_ERROR,
-          "LINK_LIBRARIES specified but there is no content");
-        return -1;
-        }
-      extraArgs++;
-      ++i;
+      doing = DoingLinkLibraries;
       useOldLinkLibs = false;
-      for ( ; i < argv.size() && argv[i] != "CMAKE_FLAGS"
-          && argv[i] != "COMPILE_DEFINITIONS" && argv[i] != "OUTPUT_VARIABLE";
-          ++i)
+      }
+    else if(argv[i] == "OUTPUT_VARIABLE")
+      {
+      doing = DoingOutputVariable;
+      didOutputVariable = true;
+      }
+    else if(argv[i] == "COPY_FILE")
+      {
+      doing = DoingCopyFile;
+      didCopyFile = true;
+      }
+    else if(doing == DoingCMakeFlags)
+      {
+      cmakeFlags.push_back(argv[i]);
+      }
+    else if(doing == DoingCompileDefinitions)
+      {
+      compileDefs.push_back(argv[i]);
+      }
+    else if(doing == DoingLinkLibraries)
+      {
+      libsToLink += "\"" + cmSystemTools::TrimWhitespace(argv[i]) + "\" ";
+      if(cmTarget *tgt = this->Makefile->FindTargetToUse(argv[i].c_str()))
         {
-        extraArgs++;
-        libsToLink += "\"" + cmSystemTools::TrimWhitespace(argv[i]) + "\" ";
-        cmTarget *tgt = this->Makefile->FindTargetToUse(argv[i].c_str());
-        if (!tgt)
-          {
-          continue;
-          }
         switch(tgt->GetType())
-        {
-        case cmTarget::SHARED_LIBRARY:
-        case cmTarget::STATIC_LIBRARY:
-        case cmTarget::UNKNOWN_LIBRARY:
-          break;
-        case cmTarget::EXECUTABLE:
-          if (tgt->IsExecutableWithExports())
-            {
+          {
+          case cmTarget::SHARED_LIBRARY:
+          case cmTarget::STATIC_LIBRARY:
+          case cmTarget::UNKNOWN_LIBRARY:
             break;
-            }
-        default:
-          this->Makefile->IssueMessage(cmake::FATAL_ERROR,
-            "Only libraries may be used as try_compile IMPORTED "
-            "LINK_LIBRARIES.  Got " + std::string(tgt->GetName()) + " of "
-            "type " + tgt->GetTargetTypeName(tgt->GetType()) + ".");
-          return -1;
-        }
-        if (!tgt->IsImported())
+          case cmTarget::EXECUTABLE:
+            if (tgt->IsExecutableWithExports())
+              {
+              break;
+              }
+          default:
+            this->Makefile->IssueMessage(cmake::FATAL_ERROR,
+              "Only libraries may be used as try_compile IMPORTED "
+              "LINK_LIBRARIES.  Got " + std::string(tgt->GetName()) + " of "
+              "type " + tgt->GetTargetTypeName(tgt->GetType()) + ".");
+            return -1;
+          }
+        if (tgt->IsImported())
           {
-          continue;
+          targets.push_back(tgt);
           }
-        targets.push_back(tgt);
         }
-      break;
+      }
+    else if(doing == DoingOutputVariable)
+      {
+      outputVariable = argv[i].c_str();
+      doing = DoingNone;
+      }
+    else if(doing == DoingCopyFile)
+      {
+      copyFile = argv[i].c_str();
+      doing = DoingNone;
+      }
+    else if(i == 3)
+      {
+      this->SrcFileSignature = false;
+      projectName = argv[i].c_str();
+      }
+    else if(i == 4 && !this->SrcFileSignature)
+      {
+      targetName = argv[i].c_str();
+      }
+    else
+      {
+      cmOStringStream m;
+      m << "try_compile given unknown argument \"" << argv[i] << "\".";
+      this->Makefile->IssueMessage(cmake::AUTHOR_WARNING, m.str());
       }
     }
 
-  // look for COPY_FILE
-  std::string copyFile;
-  for (i = 3; i < argv.size(); ++i)
+  if(didCopyFile && copyFile.empty())
     {
-    if (argv[i] == "COPY_FILE")
-      {
-      if ( argv.size() <= (i+1) )
-        {
-        this->Makefile->IssueMessage(cmake::FATAL_ERROR,
-          "COPY_FILE specified but there is no variable");
-        return -1;
-        }
-      extraArgs += 2;
-      copyFile = argv[i+1];
-      break;
-      }
+    this->Makefile->IssueMessage(cmake::FATAL_ERROR,
+      "COPY_FILE must be followed by a file path");
+    return -1;
     }
 
-  // do we have a srcfile signature
-  if (argv.size() - extraArgs == 3)
+  if(didOutputVariable && outputVariable.empty())
     {
-    this->SrcFileSignature = true;
+    this->Makefile->IssueMessage(cmake::FATAL_ERROR,
+      "OUTPUT_VARIABLE must be followed by a variable name");
+    return -1;
     }
 
   // compute the binary dir when TRY_COMPILE is called with a src file
@@ -179,10 +159,10 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
   else
     {
     // only valid for srcfile signatures
-    if (compileFlags.size())
+    if (compileDefs.size())
       {
       this->Makefile->IssueMessage(cmake::FATAL_ERROR,
-        "COMPILE_FLAGS specified on a srcdir type TRY_COMPILE");
+        "COMPILE_DEFINITIONS specified on a srcdir type TRY_COMPILE");
       return -1;
       }
     if (copyFile.size())
@@ -297,12 +277,12 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     fprintf(fout, "SET(CMAKE_SUPPRESS_REGENERATION 1)\n");
     fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");
     // handle any compile flags we need to pass on
-    if (compileFlags.size())
+    if (compileDefs.size())
       {
       fprintf(fout, "ADD_DEFINITIONS( ");
-      for (i = 0; i < compileFlags.size(); ++i)
+      for (size_t i = 0; i < compileDefs.size(); ++i)
         {
-        fprintf(fout,"%s ",compileFlags[i].c_str());
+        fprintf(fout,"%s ",compileDefs[i].c_str());
         }
       fprintf(fout, ")\n");
       }
@@ -398,16 +378,6 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       }
 
     }
-  // else the srcdir bindir project target signature
-  else
-    {
-    projectName = argv[3].c_str();
-
-    if (argv.size() - extraArgs == 5)
-      {
-      targetName = argv[4].c_str();
-      }
-    }
 
   bool erroroc = cmSystemTools::GetErrorOccuredFlag();
   cmSystemTools::ResetErrorOccuredFlag();