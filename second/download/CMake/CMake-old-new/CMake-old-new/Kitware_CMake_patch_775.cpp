@@ -292,15 +292,15 @@ int main (int argc, char *argv[])
 
   // call process directory
   inst.ProcessDirectory(passed, failed);
-  total = passed + failed.size();
+  total = passed + int(failed.size());
 
   if (total == 0)
     {
     std::cerr << "No tests were found!!!\n";
     }
   else
     {
-    float percent = passed * 100.0 / total;
+    float percent = passed * 100.0f / total;
     fprintf(stderr,"%.0f%% tests passed, %i tests failed out of %i\n",
             percent, failed.size(), total);
     if (failed.size()) 
@@ -314,5 +314,5 @@ int main (int argc, char *argv[])
       }
     }
   
-  return failed.size();
+  return int(failed.size());
 }