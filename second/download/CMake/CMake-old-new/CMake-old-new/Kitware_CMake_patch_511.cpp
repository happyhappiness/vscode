@@ -977,6 +977,7 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
     // Command to start progress for a build
     else if (args[1] == "cmake_progress_start" && args.size() == 4)
       {
+#if defined(CMAKE_BUILD_WITH_CMAKE)
       // bascially remove the directory
       std::string dirName = args[2];
       dirName += "/Progress";
@@ -992,12 +993,14 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
         fprintf(progFile,"%i\n",count);
         fclose(progFile);
         }
+#endif
       return 0;
       }
 
     // Command to report progress for a build
     else if (args[1] == "cmake_progress_report" && args.size() >= 4)
       {
+#if defined(CMAKE_BUILD_WITH_CMAKE)
       std::string dirName = args[2];
       dirName += "/Progress";
       std::string fName;
@@ -1033,6 +1036,7 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
           }
         fclose(progFile);
         }
+#endif
       return 0;
       }
     