@@ -29,9 +29,10 @@
 # include "cmVariableWatch.h"
 # include "cmVersion.h"
 # include <cmsys/Terminal.h>
-# include <cmsys/Directory.hxx>
 #endif
 
+# include <cmsys/Directory.hxx>
+
 // only build kdevelop generator on non-windows platforms
 // when not bootstrapping cmake
 #if !defined(_WIN32)
@@ -977,7 +978,6 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
     // Command to start progress for a build
     else if (args[1] == "cmake_progress_start" && args.size() == 4)
       {
-#if defined(CMAKE_BUILD_WITH_CMAKE)
       // bascially remove the directory
       std::string dirName = args[2];
       dirName += "/Progress";
@@ -993,14 +993,12 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
         fprintf(progFile,"%i\n",count);
         fclose(progFile);
         }
-#endif
       return 0;
       }
 
     // Command to report progress for a build
     else if (args[1] == "cmake_progress_report" && args.size() >= 4)
       {
-#if defined(CMAKE_BUILD_WITH_CMAKE)
       std::string dirName = args[2];
       dirName += "/Progress";
       std::string fName;
@@ -1036,7 +1034,6 @@ int cmake::ExecuteCMakeCommand(std::vector<std::string>& args)
           }
         fclose(progFile);
         }
-#endif
       return 0;
       }
     