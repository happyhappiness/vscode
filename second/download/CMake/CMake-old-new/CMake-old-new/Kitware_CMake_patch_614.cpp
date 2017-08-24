@@ -158,7 +158,7 @@ int cmTryCompileCommand::CoreTryCompileCode(
       }
     else if ( format == cmSystemTools::FORTRAN_FILE_FORMAT )
       {
-      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE FORTRAN)\n");      
+      fprintf(fout, "PROJECT(CMAKE_TRY_COMPILE Fortran)\n");      
       }
     else
       {
@@ -187,8 +187,8 @@ int cmTryCompileCommand::CoreTryCompileCode(
       }
     if(format == cmSystemTools::FORTRAN_FILE_FORMAT )
       {
-      const char* fflags = mf->GetDefinition("CMAKE_FORTRAN_FLAGS");
-      fprintf(fout, "SET(CMAKE_FORTRAN_FLAGS \"${CMAKE_FORTRAN_FLAGS} ");
+      const char* fflags = mf->GetDefinition("CMAKE_Fortran_FLAGS");
+      fprintf(fout, "SET(CMAKE_Fortran_FLAGS \"${CMAKE_Fortran_FLAGS} ");
       if(fflags)
         {
         fprintf(fout, " %s ", fflags);