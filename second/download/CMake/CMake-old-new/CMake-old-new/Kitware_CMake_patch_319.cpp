@@ -128,7 +128,7 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
     // Copy directory content
     if (args[1] == "copy_directory" && args.size() == 4)
       {
-      if(!cmSystemTools::CopyADirectory(args[2].c_str(), args[3].c_str()))
+      if(!cmSystemTools::CopyADirectory(args[2], args[3]))
         {
         std::cerr << "Error copying directory from \""
                   << args[2] << "\" to \"" << args[3]
@@ -155,7 +155,7 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
     // Compare files
     if (args[1] == "compare_files" && args.size() == 4)
       {
-      if(cmSystemTools::FilesDiffer(args[2].c_str(), args[3].c_str()))
+      if(cmSystemTools::FilesDiffer(args[2], args[3]))
         {
         std::cerr << "Files \""
                   << args[2] << "\" to \"" << args[3]
@@ -269,8 +269,8 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
 
     else if (args[1] == "remove_directory" && args.size() == 3)
       {
-      if(cmSystemTools::FileIsDirectory(args[2].c_str()) &&
-         !cmSystemTools::RemoveADirectory(args[2].c_str()))
+      if(cmSystemTools::FileIsDirectory(args[2]) &&
+         !cmSystemTools::RemoveADirectory(args[2]))
         {
         std::cerr << "Error removing directory \"" << args[2]
                   << "\".\n";
@@ -293,7 +293,7 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
           {
           // Complain if the file could not be removed, still exists,
           // and the -f option was not given.
-          if(!cmSystemTools::RemoveFile(args[cc].c_str()) && !force &&
+          if(!cmSystemTools::RemoveFile(args[cc]) && !force &&
              cmSystemTools::FileExists(args[cc].c_str()))
             {
             return 1;
@@ -309,7 +309,7 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
         {
         // Complain if the file could not be removed, still exists,
         // and the -f option was not given.
-        if(!cmSystemTools::Touch(args[cc].c_str(), true))
+        if(!cmSystemTools::Touch(args[cc], true))
           {
           return 1;
           }
@@ -323,7 +323,7 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
         {
         // Complain if the file could not be removed, still exists,
         // and the -f option was not given.
-        if(!cmSystemTools::Touch(args[cc].c_str(), false))
+        if(!cmSystemTools::Touch(args[cc], false))
           {
           return 1;
           }
@@ -453,10 +453,10 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
       // basically remove the directory
       std::string dirName = args[2];
       dirName += "/Progress";
-      cmSystemTools::RemoveADirectory(dirName.c_str());
+      cmSystemTools::RemoveADirectory(dirName);
 
       // is the last argument a filename that exists?
-      FILE *countFile = cmsys::SystemTools::Fopen(args[3].c_str(),"r");
+      FILE *countFile = cmsys::SystemTools::Fopen(args[3],"r");
       int count;
       if (countFile)
         {
@@ -476,7 +476,7 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
         // write the count into the directory
         std::string fName = dirName;
         fName += "/count.txt";
-        FILE *progFile = cmsys::SystemTools::Fopen(fName.c_str(),"w");
+        FILE *progFile = cmsys::SystemTools::Fopen(fName,"w");
         if (progFile)
           {
           fprintf(progFile,"%i\n",count);
@@ -497,7 +497,7 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
       // read the count
       fName = dirName;
       fName += "/count.txt";
-      progFile = cmsys::SystemTools::Fopen(fName.c_str(),"r");
+      progFile = cmsys::SystemTools::Fopen(fName,"r");
       int count = 0;
       if (!progFile)
         {
@@ -517,15 +517,15 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
         fName = dirName;
         fName += "/";
         fName += args[i];
-        progFile = cmsys::SystemTools::Fopen(fName.c_str(),"w");
+        progFile = cmsys::SystemTools::Fopen(fName,"w");
         if (progFile)
           {
           fprintf(progFile,"empty");
           fclose(progFile);
           }
         }
       int fileNum = static_cast<int>
-        (cmsys::Directory::GetNumberOfFilesInDirectory(dirName.c_str()));
+        (cmsys::Directory::GetNumberOfFilesInDirectory(dirName));
       if (count > 0)
         {
         // print the progress
@@ -660,10 +660,10 @@ int cmcmd::ExecuteCMakeCommand(std::vector<std::string>& args)
 
       // Create a local generator configured for the directory in
       // which dependencies will be scanned.
-      homeDir = cmSystemTools::CollapseFullPath(homeDir.c_str());
-      startDir = cmSystemTools::CollapseFullPath(startDir.c_str());
-      homeOutDir = cmSystemTools::CollapseFullPath(homeOutDir.c_str());
-      startOutDir = cmSystemTools::CollapseFullPath(startOutDir.c_str());
+      homeDir = cmSystemTools::CollapseFullPath(homeDir);
+      startDir = cmSystemTools::CollapseFullPath(startDir);
+      homeOutDir = cmSystemTools::CollapseFullPath(homeOutDir);
+      startOutDir = cmSystemTools::CollapseFullPath(startOutDir);
       cm.SetHomeDirectory(homeDir);
       cm.SetStartDirectory(startDir);
       cm.SetHomeOutputDirectory(homeOutDir);
@@ -885,9 +885,9 @@ int cmcmd::SymlinkExecutable(std::vector<std::string>& args)
 bool cmcmd::SymlinkInternal(std::string const& file, std::string const& link)
 {
   if(cmSystemTools::FileExists(link.c_str()) ||
-     cmSystemTools::FileIsSymlink(link.c_str()))
+     cmSystemTools::FileIsSymlink(link))
     {
-    cmSystemTools::RemoveFile(link.c_str());
+    cmSystemTools::RemoveFile(link);
     }
 #if defined(_WIN32) && !defined(__CYGWIN__)
   return cmSystemTools::CopyFileAlways(file.c_str(), link.c_str());
@@ -1318,7 +1318,7 @@ int cmcmd::VisualStudioLinkIncremental(std::vector<std::string>& args,
     }
   std::string manifestFile = targetName;
   manifestFile += ".embed.manifest";
-  std::string fullPath= cmSystemTools::CollapseFullPath(manifestFile.c_str());
+  std::string fullPath= cmSystemTools::CollapseFullPath(manifestFile);
   fout << type << " /* CREATEPROCESS_MANIFEST_RESOURCE_ID "
     "*/ 24 /* RT_MANIFEST */ " << "\"" << fullPath << "\"";
   fout.close();