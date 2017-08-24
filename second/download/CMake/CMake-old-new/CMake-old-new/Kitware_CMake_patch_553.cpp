@@ -4091,12 +4091,14 @@ namespace KWSYS_NAMESPACE
 
 static int SystemToolsDebugReport(int, char* message, int*)
 {
-  fprintf(stderr, message);
-  exit(1);
+  fprintf(stderr, "%s", message);
+  fflush(stderr);
+  return 1; // no further reporting required
 }
+
 void SystemTools::EnableMSVCDebugHook()
 {
-  if(getenv("DART_TEST_FROM_DART"))
+  if (getenv("DART_TEST_FROM_DART"))
     {
     _CrtSetReportHook(SystemToolsDebugReport);
     }
@@ -4109,5 +4111,3 @@ namespace KWSYS_NAMESPACE
 void SystemTools::EnableMSVCDebugHook() {}
 } // namespace KWSYS_NAMESPACE
 #endif
-
-