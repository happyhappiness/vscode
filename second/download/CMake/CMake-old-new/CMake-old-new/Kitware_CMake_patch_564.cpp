@@ -83,7 +83,7 @@ void MFCMessageCallback(const char* m, const char* title, bool& nomore, void*)
 // CMakeSetupDialog dialog
 void updateProgress(const char *msg, float prog, void *cd)
 {
-  char tmp[1024];
+  char* tmp = new char[strlen(msg) + 40];
   if (prog >= 0)
     {
     sprintf(tmp,"%s %i%%",msg,(int)(100*prog));
@@ -120,6 +120,7 @@ void updateProgress(const char *msg, float prog, void *cd)
       break;
       }
     }
+  delete [] tmp;
 }
 
 // Convert to Win32 path (slashes). This calls the system tools one and then