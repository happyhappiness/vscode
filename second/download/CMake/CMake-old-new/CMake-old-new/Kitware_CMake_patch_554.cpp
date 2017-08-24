@@ -996,16 +996,19 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
       std::string dirName = args[2];
       dirName += "/Progress";
       cmSystemTools::RemoveADirectory(dirName.c_str());
-      cmSystemTools::MakeDirectory(dirName.c_str());
-      // write the count into the directory
-      std::string fName = dirName;
-      fName += "/count.txt";
-      FILE *progFile = fopen(fName.c_str(),"w");
-      if (progFile)
+      int count = atoi(args[3].c_str());
+      if (count)
         {
-        int count = atoi(args[3].c_str());
-        fprintf(progFile,"%i\n",count);
-        fclose(progFile);
+        cmSystemTools::MakeDirectory(dirName.c_str());
+        // write the count into the directory
+        std::string fName = dirName;
+        fName += "/count.txt";
+        FILE *progFile = fopen(fName.c_str(),"w");
+        if (progFile)
+          {
+          fprintf(progFile,"%i\n",count);
+          fclose(progFile);
+          }
         }
       return 0;
       }
@@ -1017,6 +1020,21 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
       dirName += "/Progress";
       std::string fName;
       FILE *progFile;
+
+      // read the count
+      fName = dirName;
+      fName += "/count.txt";
+      progFile = fopen(fName.c_str(),"r");
+      int count = 0;
+      if (!progFile)
+        {
+        return 0;
+        }
+      else
+        {
+        fscanf(progFile,"%i",&count);
+        fclose(progFile);
+        }
       unsigned int i;
       for (i = 3; i < args.size(); ++i)
         {
@@ -1032,20 +1050,10 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
         }
       int fileNum = static_cast<int>
         (cmsys::Directory::GetNumberOfFilesInDirectory(dirName.c_str()));
-      // read the count
-      fName = dirName;
-      fName += "/count.txt";
-      progFile = fopen(fName.c_str(),"r");
-      if (progFile)
+      if (count > 0)
         {
-        int count = 0;
-        fscanf(progFile,"%i",&count);
-        if (count > 0)
-          {
-          // print the progress
-          fprintf(stdout,"[%3i%%] ",((fileNum-3)*100)/count);
-          }
-        fclose(progFile);
+        // print the progress
+        fprintf(stdout,"[%3i%%] ",((fileNum-3)*100)/count);
         }
       return 0;
       }