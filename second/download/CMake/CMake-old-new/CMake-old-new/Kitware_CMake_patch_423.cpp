@@ -13,8 +13,11 @@
 #include "cmake.h"
 #include "cmCacheManager.h"
 #include "cmGlobalGenerator.h"
+#include "cmExportTryCompileFileGenerator.h"
 #include <cmsys/Directory.hxx>
 
+#include <assert.h>
+
 int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
 {
   this->BinaryDirectory = argv[1].c_str();
@@ -39,7 +42,8 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
      // is not used, so it matches regular command line parsing which has
      // the program name as arg 0
       for (; i < argv.size() && argv[i] != "COMPILE_DEFINITIONS" &&
-             argv[i] != "OUTPUT_VARIABLE";
+             argv[i] != "OUTPUT_VARIABLE" &&
+             argv[i] != "LINK_LIBRARIES";
            ++i)
         {
         extraArgs++;
@@ -75,7 +79,8 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       {
       extraArgs++;
       for (i = i + 1; i < argv.size() && argv[i] != "CMAKE_FLAGS" &&
-             argv[i] != "OUTPUT_VARIABLE";
+             argv[i] != "OUTPUT_VARIABLE" &&
+             argv[i] != "LINK_LIBRARIES";
            ++i)
         {
         extraArgs++;
@@ -85,6 +90,61 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       }
     }
 
+  std::vector<cmTarget*> targets;
+  std::string libsToLink = " ";
+  bool useOldLinkLibs = true;
+  for (i = 3; i < argv.size(); ++i)
+    {
+    if (argv[i] == "LINK_LIBRARIES")
+      {
+      if ( argv.size() <= (i+1) )
+        {
+        this->Makefile->IssueMessage(cmake::FATAL_ERROR,
+          "LINK_LIBRARIES specified but there is no content");
+        return -1;
+        }
+      extraArgs++;
+      ++i;
+      useOldLinkLibs = false;
+      for ( ; i < argv.size() && argv[i] != "CMAKE_FLAGS"
+          && argv[i] != "COMPILE_DEFINITIONS" && argv[i] != "OUTPUT_VARIABLE";
+          ++i)
+        {
+        extraArgs++;
+        libsToLink += argv[i] + " ";
+        cmTarget *tgt = this->Makefile->FindTargetToUse(argv[i].c_str());
+        if (!tgt)
+          {
+          continue;
+          }
+        switch(tgt->GetType())
+        {
+        case cmTarget::SHARED_LIBRARY:
+        case cmTarget::STATIC_LIBRARY:
+        case cmTarget::UNKNOWN_LIBRARY:
+          break;
+        case cmTarget::EXECUTABLE:
+          if (tgt->IsExecutableWithExports())
+            {
+            break;
+            }
+        default:
+          this->Makefile->IssueMessage(cmake::FATAL_ERROR,
+            "Only libraries may be used as try_compile IMPORTED "
+            "LINK_LIBRARIES.  Got " + std::string(tgt->GetName()) + " of "
+            "type " + tgt->GetTargetTypeName(tgt->GetType()) + ".");
+          return -1;
+        }
+        if (!tgt->IsImported())
+          {
+          continue;
+          }
+        targets.push_back(tgt);
+        }
+      break;
+      }
+    }
+
   // look for COPY_FILE
   std::string copyFile;
   for (i = 3; i < argv.size(); ++i)
@@ -247,6 +307,32 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       fprintf(fout, ")\n");
       }
 
+    /* Use a random file name to avoid rapid creation and deletion
+       of the same executable name (some filesystems fail on that).  */
+    sprintf(targetNameBuf, "cmTryCompileExec%u",
+            cmSystemTools::RandomSeed());
+    targetName = targetNameBuf;
+
+    if (!targets.empty())
+      {
+      std::string fname = "/" + std::string(targetName) + "Targets.cmake";
+      cmExportTryCompileFileGenerator tcfg;
+      tcfg.SetExportFile((this->BinaryDirectory + fname).c_str());
+      tcfg.SetExports(targets);
+      tcfg.SetConfig(this->Makefile->GetDefinition(
+                                          "CMAKE_TRY_COMPILE_CONFIGURATION"));
+
+      if(!tcfg.GenerateImportFile())
+        {
+        this->Makefile->IssueMessage(cmake::FATAL_ERROR,
+                                     "could not write export file.");
+        return -1;
+        }
+      fprintf(fout,
+              "\ninclude(\"${CMAKE_CURRENT_LIST_DIR}/%s\")\n\n",
+              fname.c_str());
+      }
+
     /* for the TRY_COMPILEs we want to be able to specify the architecture.
       So the user can set CMAKE_OSX_ARCHITECTURE to i386;ppc and then set
       CMAKE_TRY_COMPILE_OSX_ARCHITECTURE first to i386 and then to ppc to
@@ -286,18 +372,22 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       fprintf(fout, "SET(CMAKE_POSITION_INDEPENDENT_CODE \"ON\")\n");
       }
 
-    /* Use a random file name to avoid rapid creation and deletion
-       of the same executable name (some filesystems fail on that).  */
-    sprintf(targetNameBuf, "cmTryCompileExec%u",
-            cmSystemTools::RandomSeed());
-    targetName = targetNameBuf;
-
     /* Put the executable at a known location (for COPY_FILE).  */
     fprintf(fout, "SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
             this->BinaryDirectory.c_str());
     /* Create the actual executable.  */
     fprintf(fout, "ADD_EXECUTABLE(%s \"%s\")\n", targetName, source.c_str());
-    fprintf(fout, "TARGET_LINK_LIBRARIES(%s ${LINK_LIBRARIES})\n",targetName);
+    if (useOldLinkLibs)
+      {
+      fprintf(fout,
+              "TARGET_LINK_LIBRARIES(%s ${LINK_LIBRARIES})\n",targetName);
+      }
+    else
+      {
+      fprintf(fout, "TARGET_LINK_LIBRARIES(%s %s)\n",
+              targetName,
+              libsToLink.c_str());
+      }
     fclose(fout);
     projectName = "CMAKE_TRY_COMPILE";
     // if the source is not in CMakeTmp