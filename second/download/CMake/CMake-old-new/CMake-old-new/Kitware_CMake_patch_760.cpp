@@ -17,42 +17,20 @@
 #include "cmTryCompileCommand.h"
 #include "cmCacheManager.h"
 
-// cmExecutableCommand
-bool cmTryCompileCommand::InitialPass(std::vector<std::string> const& argv)
+int cmTryCompileCommand::CoreTryCompileCode(
+  cmMakefile *mf, std::vector<std::string> const& argv, bool clean)
 {
-  if(argv.size() < 3)
-    {
-    return false;
-    }
-
   // which signature were we called with ?
   bool srcFileSignature = true;
-  
-  // look for CMAKE_FLAGS and store them
-  std::vector<std::string> cmakeFlags;
   int i;
-  for (i = 3; i < argv.size(); ++i)
-    {
-    if (argv[i] == "CMAKE_FLAGS")
-      {
-      for (; i < argv.size(); ++i)
-        {
-        cmakeFlags.push_back(argv[i]);
-        }
-      }
-    else
-      {
-      srcFileSignature = false;
-      }
-    }
   
   // where will the binaries be stored
   const char* binaryDirectory = argv[1].c_str();
   const char* sourceDirectory = argv[2].c_str();
   const char* projectName = 0;
   const char* targetName = 0;
   std::string tmpString;
-
+  
   // compute the binary dir when TRY_COMPILE is called with a src file
   // signature
   if (srcFileSignature)
@@ -64,13 +42,54 @@ bool cmTryCompileCommand::InitialPass(std::vector<std::string> const& argv)
   cmSystemTools::MakeDirectory(binaryDirectory);
   
   // do not allow recursive try Compiles
-  if (!strcmp(binaryDirectory,m_Makefile->GetHomeOutputDirectory()))
+  if (!strcmp(binaryDirectory,mf->GetHomeOutputDirectory()))
     {
     cmSystemTools::Error("Attempt at a recursive or nested TRY_COMPILE", 
                          binaryDirectory);
-    return false;
+    return -1;
     }
-      
+  
+  // look for CMAKE_FLAGS and store them
+  std::vector<std::string> cmakeFlags;
+  for (i = 3; i < argv.size(); ++i)
+    {
+    if (argv[i] == "CMAKE_FLAGS")
+      {
+      for (; i < argv.size() && argv[i] != "COMPILE_DEFINITIONS"; 
+           ++i)
+        {
+        cmakeFlags.push_back(argv[i]);
+        }
+      break;
+      }
+    else
+      {
+      srcFileSignature = false;
+      }
+    }
+
+  // look for COMPILE_DEFINITIONS and store them
+  std::vector<std::string> compileFlags;
+  for (i = 0; i < argv.size(); ++i)
+    {
+    if (argv[i] == "COMPILE_DEFINITIONS")
+      {
+      // only valid for srcfile signatures
+      if (!srcFileSignature)
+        {
+        cmSystemTools::Error(
+          "COMPILE_FLAGS specified on a srcdir type TRY_COMPILE");
+        return -1;
+        }
+      for (i = i + 1; i < argv.size() && argv[i] != "CMAKE_FLAGS"; 
+           ++i)
+        {
+        compileFlags.push_back(argv[i]);
+        }
+      break;
+      }
+    }
+  
   // which signature are we using? If we are using var srcfile bindir
   if (srcFileSignature)
     {
@@ -89,13 +108,24 @@ bool cmTryCompileCommand::InitialPass(std::vector<std::string> const& argv)
       {
       cmSystemTools::Error("Failed to create CMakeList file for ", 
                            outFileName.c_str());
-      return false;
+      return -1;
       }
-    fprintf(fout,"PROJECT(CMAKE_TRY_COMPILE)\n");
+    fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE)\n");
     fprintf(fout, "IF (CMAKE_ANSI_CXXFLAGS)\n");
     fprintf(fout, "  SET(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} ${CMAKE_ANSI_CXXFLAGS}\")\n");
     fprintf(fout, "ENDIF (CMAKE_ANSI_CXXFLAGS)\n");
-    fprintf(fout,"ADD_EXECUTABLE(cmTryCompileExec \"%s\")\n",argv[2].c_str());
+    // handle any compile flags we need to pass on
+    if (compileFlags.size())
+      {
+      fprintf(fout, "ADD_DEFINITIONS( ");
+      for (i = 0; i < compileFlags.size(); ++i)
+        {
+        fprintf(fout,"%s ",compileFlags[i].c_str());
+        }
+      fprintf(fout, ")\n");
+      }
+    
+    fprintf(fout, "ADD_EXECUTABLE(cmTryCompileExec \"%s\")\n",argv[2].c_str());
     fclose(fout);
     projectName = "CMAKE_TRY_COMPILE";
     targetName = "cmTryCompileExec";
@@ -112,14 +142,14 @@ bool cmTryCompileCommand::InitialPass(std::vector<std::string> const& argv)
     }
   
   // actually do the try compile now that everything is setup
-  int res = m_Makefile->TryCompile(sourceDirectory, binaryDirectory,
-                                   projectName, targetName, &cmakeFlags);
+  int res = mf->TryCompile(sourceDirectory, binaryDirectory,
+                           projectName, targetName, &cmakeFlags);
   
   // set the result var to the return value to indicate success or failure
-  m_Makefile->AddDefinition(argv[0].c_str(), (res == 0 ? "TRUE" : "FALSE"));
-      
-  // if we created a directory etc, then cleanup after ourselves  
-  if (srcFileSignature)
+  mf->AddDefinition(argv[0].c_str(), (res == 0 ? "TRUE" : "FALSE"));
+  
+  // if They specified clean then we clean up what we can
+  if (srcFileSignature && clean)
     {
     cmDirectory dir;
     dir.Load(binaryDirectory);
@@ -137,6 +167,19 @@ bool cmTryCompileCommand::InitialPass(std::vector<std::string> const& argv)
       }
     }
   
+  return res;
+}
+
+// cmExecutableCommand
+bool cmTryCompileCommand::InitialPass(std::vector<std::string> const& argv)
+{
+  if(argv.size() < 3)
+    {
+    return false;
+    }
+
+  cmTryCompileCommand::CoreTryCompileCode(m_Makefile,argv,true);
+  
   return true;
 }
 