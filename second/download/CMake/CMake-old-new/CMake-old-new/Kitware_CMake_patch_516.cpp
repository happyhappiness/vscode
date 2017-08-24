@@ -3125,9 +3125,9 @@ void SystemTools::SplitPath(const char* p,
     if(root.size() == 1)
       {
 #if defined(_WIN32) && !defined(__CYGWIN__)
-      if(const char* p = getenv("USERPROFILE"))
+      if(const char* userp = getenv("USERPROFILE"))
         {
-        homedir = p;
+        homedir = userp;
         }
       else
 #endif
@@ -4279,10 +4279,10 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
           }
 
         res += " ";
-        sprintf(buffer, "%d", osvi.dwMajorVersion);
+        sprintf(buffer, "%ld", osvi.dwMajorVersion);
         res += buffer;
         res += ".";
-        sprintf(buffer, "%d", osvi.dwMinorVersion);
+        sprintf(buffer, "%ld", osvi.dwMinorVersion);
         res += buffer;
         }
 
@@ -4304,7 +4304,7 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
         if (lRet == ERROR_SUCCESS)
           {
           res += " Service Pack 6a (Build ";
-          sprintf(buffer, "%d", osvi.dwBuildNumber & 0xFFFF);
+          sprintf(buffer, "%ld", osvi.dwBuildNumber & 0xFFFF);
           res += buffer;
           res += ")";
           }
@@ -4313,7 +4313,7 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
           res += " ";
           res += osvi.szCSDVersion;
           res += " (Build ";
-          sprintf(buffer, "%d", osvi.dwBuildNumber & 0xFFFF);
+          sprintf(buffer, "%ld", osvi.dwBuildNumber & 0xFFFF);
           res += buffer;
           res += ")";
           }
@@ -4325,7 +4325,7 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
         res += " ";
         res += osvi.szCSDVersion;
         res += " (Build ";
-        sprintf(buffer, "%d", osvi.dwBuildNumber & 0xFFFF);
+        sprintf(buffer, "%ld", osvi.dwBuildNumber & 0xFFFF);
         res += buffer;
         res += ")";
         }