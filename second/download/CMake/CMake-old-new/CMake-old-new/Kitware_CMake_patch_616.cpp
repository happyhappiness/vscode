@@ -156,10 +156,14 @@ int cmTryCompileCommand::CoreTryCompileCode(
       {
       fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE CXX)\n");      
       }
+    else if ( format == cmSystemTools::FORTRAN_FILE_FORMAT )
+      {
+      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE FORTRAN)\n");      
+      }
     else
       {
       cmSystemTools::Error("Unknown file format for file: ", source.c_str(), 
-                           "; TRY_COMPILE only works for C and CXX files");
+                           "; TRY_COMPILE only works for C, CXX, and FORTRAN files");
       return -1;
       }
     const char* cflags = mf->GetDefinition("CMAKE_C_FLAGS"); 
@@ -181,6 +185,16 @@ int cmTryCompileCommand::CoreTryCompileCode(
         }
       fprintf(fout, " ${COMPILE_DEFINITIONS}\")\n");
       }
+    if(format == cmSystemTools::FORTRAN_FILE_FORMAT )
+      {
+      const char* fflags = mf->GetDefinition("CMAKE_FORTRAN_FLAGS");
+      fprintf(fout, "SET(CMAKE_FORTRAN_FLAGS \"${CMAKE_FORTRAN_FLAGS} ");
+      if(fflags)
+        {
+        fprintf(fout, " %s ", fflags);
+        }
+      fprintf(fout, " ${COMPILE_DEFINITIONS}\")\n");
+      }
     fprintf(fout, "INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES})\n");
     fprintf(fout, "LINK_DIRECTORIES(${LINK_DIRECTORIES})\n");
     // handle any compile flags we need to pass on