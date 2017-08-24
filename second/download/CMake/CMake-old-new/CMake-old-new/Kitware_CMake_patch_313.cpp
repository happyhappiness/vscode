@@ -534,48 +534,9 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
     // Command to report progress for a build
     else if (args[1] == "cmake_progress_report" && args.size() >= 3)
       {
-      std::string dirName = args[2];
-      dirName += "/Progress";
-      std::string fName;
-      FILE *progFile;
-
-      // read the count
-      fName = dirName;
-      fName += "/count.txt";
-      progFile = cmsys::SystemTools::Fopen(fName,"r");
-      int count = 0;
-      if (!progFile)
-        {
-        return 0;
-        }
-      else
-        {
-        if (1!=fscanf(progFile,"%i",&count))
-          {
-          cmSystemTools::Message("Could not read from progress file.");
-          }
-        fclose(progFile);
-        }
-      unsigned int i;
-      for (i = 3; i < args.size(); ++i)
-        {
-        fName = dirName;
-        fName += "/";
-        fName += args[i];
-        progFile = cmsys::SystemTools::Fopen(fName,"w");
-        if (progFile)
-          {
-          fprintf(progFile,"empty");
-          fclose(progFile);
-          }
-        }
-      int fileNum = static_cast<int>
-        (cmsys::Directory::GetNumberOfFilesInDirectory(dirName));
-      if (count > 0)
-        {
-        // print the progress
-        fprintf(stdout,"[%3i%%] ",((fileNum-3)*100)/count);
-        }
+      // This has been superseded by cmake_echo_color --progress-*
+      // options.  We leave it here to avoid errors if somehow this
+      // is invoked by an existing makefile without regenerating.
       return 0;
       }
 
@@ -987,6 +948,65 @@ bool cmcmd::SymlinkInternal(std::string const& file, std::string const& link)
 }
 
 //----------------------------------------------------------------------------
+static void cmcmdProgressReport(std::string const& dir,
+                                std::string const& num)
+{
+  std::string dirName = dir;
+  dirName += "/Progress";
+  std::string fName;
+  FILE *progFile;
+
+  // read the count
+  fName = dirName;
+  fName += "/count.txt";
+  progFile = cmsys::SystemTools::Fopen(fName,"r");
+  int count = 0;
+  if (!progFile)
+    {
+    return;
+    }
+  else
+    {
+    if (1!=fscanf(progFile,"%i",&count))
+      {
+      cmSystemTools::Message("Could not read from progress file.");
+      }
+    fclose(progFile);
+    }
+  const char* last = num.c_str();
+  for(const char* c = last;; ++c)
+    {
+    if (*c == ',' || *c == '\0')
+      {
+      if (c != last)
+        {
+        fName = dirName;
+        fName += "/";
+        fName.append(last, c-last);
+        progFile = cmsys::SystemTools::Fopen(fName,"w");
+        if (progFile)
+          {
+          fprintf(progFile,"empty");
+          fclose(progFile);
+          }
+        }
+      if(*c == '\0')
+        {
+        break;
+        }
+      last = c + 1;
+      }
+    }
+  int fileNum = static_cast<int>
+    (cmsys::Directory::GetNumberOfFilesInDirectory(dirName));
+  if (count > 0)
+    {
+    // print the progress
+    fprintf(stdout,"[%3i%%] ",((fileNum-3)*100)/count);
+    }
+}
+
+//----------------------------------------------------------------------------
 int cmcmd::ExecuteEchoColor(std::vector<std::string>& args)
 {
   // The arguments are
@@ -996,6 +1016,7 @@ int cmcmd::ExecuteEchoColor(std::vector<std::string>& args)
   bool enabled = true;
   int color = cmsysTerminal_Color_Normal;
   bool newline = true;
+  std::string progressDir;
   for(unsigned int i=2; i < args.size(); ++i)
     {
     if(args[i].find("--switch=") == 0)
@@ -1014,6 +1035,18 @@ int cmcmd::ExecuteEchoColor(std::vector<std::string>& args)
           }
         }
       }
+    else if(cmHasLiteralPrefix(args[i], "--progress-dir="))
+      {
+      progressDir = args[i].substr(15);
+      }
+    else if(cmHasLiteralPrefix(args[i], "--progress-num="))
+      {
+      if (!progressDir.empty())
+        {
+        std::string const& progressNum = args[i].substr(15);
+        cmcmdProgressReport(progressDir, progressNum);
+        }
+      }
     else if(args[i] == "--normal")
       {
       color = cmsysTerminal_Color_Normal;