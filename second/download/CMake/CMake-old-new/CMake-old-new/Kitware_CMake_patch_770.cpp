@@ -997,17 +997,16 @@ bool cmSystemTools::FilesDiffer(const char* source,
   if(statSource.st_size != finSource.gcount() ||
      statSource.st_size != finDestination.gcount())
     {
-    char msg[256];
-    sprintf(msg, "FilesDiffer failed to read files (allocated: %lu, source: %lu, dest: %lu)", statSource.st_size, finSource.gcount(), finDestination.gcount());
-    cmSystemTools::Error(msg);
+    std::strstream msg;
+    msg << "FilesDiffer failed to read files (allocated: " 
+        << statSource.st_size << ", read source: " <<  finSource.gcount() 
+        << ", read dest: " << finDestination.gcount() << std::ends;
+    cmSystemTools::Error(msg.str());
+    delete [] msg.str();
     delete [] source_buf;
     delete [] dest_buf;
     return false;
     }
-
-  finSource.close();
-  finDestination.close();
-
   int ret = memcmp((const void*)source_buf, 
                    (const void*)dest_buf, 
                    statSource.st_size);
@@ -1106,9 +1105,12 @@ void cmSystemTools::cmCopyFile(const char* source,
 
   if (statSource.st_size != statDestination.st_size)
     {
-    char msg[256];
-    sprintf(msg, "CopyFile failed to copy files (sizes differ, source: %lu, dest: %lu)", statSource.st_size, statDestination.st_size);
-    cmSystemTools::Error(msg);
+    std::strstream msg;
+    msg << "CopyFile failed to copy files (sizes differ, source: " 
+        << statSource.st_size << " , dest: " << statDestination.st_size 
+        << std::ends;
+    cmSystemTools::Error(msg.str());
+    delete [] msg.str();
     }
 }
 