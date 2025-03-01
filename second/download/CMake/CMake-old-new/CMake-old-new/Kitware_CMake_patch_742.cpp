@@ -153,8 +153,8 @@ int cmTryCompileCommand::CoreTryCompileCode(
       return -1;
       }
 
-    fprintf(fout, "SET(CMAKE_C_FLAGS ${CMAKE_C_FLAGS} ${COMPILE_DEFINITIONS})\n");
-    fprintf(fout, "SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${COMPILE_DEFINITIONS})\n");
+    fprintf(fout, "SET(CMAKE_C_FLAGS \"${CMAKE_C_FLAGS} ${COMPILE_DEFINITIONS}\"\")\n");
+    fprintf(fout, "SET(CMAKE_CXX_FLAGS \"${CMAKE_CXX_FLAGS} ${COMPILE_DEFINITIONS}\")\n");
     fprintf(fout, "INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})\n");
     fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");
     // handle any compile flags we need to pass on
@@ -232,6 +232,7 @@ static void cmTryCompileCommandNotUsed(bool){}
 
 void cmTryCompileCommand::CleanupFiles(const char* binDir)
 {
+  return;
   if ( !binDir )
     {
     return;