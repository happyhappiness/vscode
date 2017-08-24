@@ -133,11 +133,43 @@ int cmTryCompileCommand::CoreTryCompileCode(
                            outFileName.c_str());
       return -1;
       }
-    fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE)\n");
-    fprintf(fout, "IF (CMAKE_ANSI_CXXFLAGS)\n");
-    fprintf(fout, "  SET(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} ${CMAKE_ANSI_CXXFLAGS}\")\n");
-    fprintf(fout, "  SET(CMAKE_C_FLAGS \"${CMAKE_C_FLAGS} ${CMAKE_ANSI_CFLAGS}\")\n");
-    fprintf(fout, "ENDIF (CMAKE_ANSI_CXXFLAGS)\n");
+    
+    std::string source = argv[2];
+    cmSystemTools::e_FileFormat format = 
+      cmSystemTools::GetFileFormat( 
+        cmSystemTools::GetFilenameExtension(source).c_str());
+    if ( format == cmSystemTools::C_FILE_FORMAT )
+      {
+      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE C)\n");      
+      }
+    else if ( format == cmSystemTools::CXX_FILE_FORMAT )
+      {
+      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE CXX)\n");      
+      }
+    else
+      {
+      cmSystemTools::Error("Unknown file format for file: ", source.c_str(), 
+                           "; TRY_COMPILE only works for C and CXX files");
+      return -1;
+      }
+
+    if ( format == cmSystemTools::CXX_FILE_FORMAT )
+      {
+      fprintf(fout, "IF (CMAKE_ANSI_CXXFLAGS)\n");
+      fprintf(fout, "  SET(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS}"
+              " ${CMAKE_ANSI_CXXFLAGS}\")\n");
+      fprintf(fout, "ENDIF (CMAKE_ANSI_CXXFLAGS)\n");
+      }
+
+    if ( format == cmSystemTools::C_FILE_FORMAT )
+      {
+      fprintf(fout, "IF (CMAKE_ANSI_CFLAGS)\n");
+      fprintf(fout, "  SET(CMAKE_C_FLAGS \"${CMAKE_C_FLAGS} ${CMAKE_ANSI_CFLAGS}\")\n");
+      fprintf(fout, "ENDIF (CMAKE_ANSI_CFLAGS)\n");
+      }
+    fprintf(fout, "ADD_DEFINITIONS(${COMPILE_DEFINITIONS})\n");
+    fprintf(fout, "INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})\n");
+    fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");
     // handle any compile flags we need to pass on
     if (compileFlags.size())
       {
@@ -149,7 +181,8 @@ int cmTryCompileCommand::CoreTryCompileCode(
       fprintf(fout, ")\n");
       }
     
-    fprintf(fout, "ADD_EXECUTABLE(cmTryCompileExec \"%s\")\n",argv[2].c_str());
+    fprintf(fout, "ADD_EXECUTABLE(cmTryCompileExec \"%s\")\n",source.c_str());
+    fprintf(fout, "TARGET_LINK_LIBRARIES(cmTryCompileExec ${LINK_LIBRARIES})\n");
     fclose(fout);
     projectName = "CMAKE_TRY_COMPILE";
     targetName = "cmTryCompileExec";