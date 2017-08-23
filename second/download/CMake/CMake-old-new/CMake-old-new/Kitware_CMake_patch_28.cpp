@@ -7,6 +7,7 @@
 #include <sstream>
 #include <stdio.h>
 
+#include "cmAlgorithms.h"
 #include "cmMakefile.h"
 #include "cmProcessOutput.h"
 #include "cmSystemTools.h"
@@ -46,6 +47,7 @@ bool cmExecuteProcessCommand::InitialPass(std::vector<std::string> const& args,
   std::string output_variable;
   std::string error_variable;
   std::string result_variable;
+  std::string results_variable;
   std::string working_directory;
   cmProcessOutput::Encoding encoding = cmProcessOutput::None;
   for (size_t i = 0; i < args.size(); ++i) {
@@ -77,6 +79,14 @@ bool cmExecuteProcessCommand::InitialPass(std::vector<std::string> const& args,
         this->SetError(" called with no value for RESULT_VARIABLE.");
         return false;
       }
+    } else if (args[i] == "RESULTS_VARIABLE") {
+      doing_command = false;
+      if (++i < args.size()) {
+        results_variable = args[i];
+      } else {
+        this->SetError(" called with no value for RESULTS_VARIABLE.");
+        return false;
+      }
     } else if (args[i] == "WORKING_DIRECTORY") {
       doing_command = false;
       if (++i < args.size()) {
@@ -287,7 +297,7 @@ bool cmExecuteProcessCommand::InitialPass(std::vector<std::string> const& args,
     switch (cmsysProcess_GetState(cp)) {
       case cmsysProcess_State_Exited: {
         int v = cmsysProcess_GetExitValue(cp);
-        char buf[100];
+        char buf[16];
         sprintf(buf, "%d", v);
         this->Makefile->AddDefinition(result_variable, buf);
       } break;
@@ -305,6 +315,47 @@ bool cmExecuteProcessCommand::InitialPass(std::vector<std::string> const& args,
         break;
     }
   }
+  // Store the result of running the processes.
+  if (!results_variable.empty()) {
+    switch (cmsysProcess_GetState(cp)) {
+      case cmsysProcess_State_Exited: {
+        std::vector<std::string> res;
+        for (size_t i = 0; i < cmds.size(); ++i) {
+          switch (cmsysProcess_GetStateByIndex(cp, static_cast<int>(i))) {
+            case kwsysProcess_StateByIndex_Exited: {
+              int exitCode =
+                cmsysProcess_GetExitValueByIndex(cp, static_cast<int>(i));
+              char buf[16];
+              sprintf(buf, "%d", exitCode);
+              res.push_back(buf);
+            } break;
+            case kwsysProcess_StateByIndex_Exception:
+              res.push_back(cmsysProcess_GetExceptionStringByIndex(
+                cp, static_cast<int>(i)));
+              break;
+            case kwsysProcess_StateByIndex_Error:
+            default:
+              res.push_back("Error getting the child return code");
+              break;
+          }
+        }
+        this->Makefile->AddDefinition(results_variable,
+                                      cmJoin(res, ";").c_str());
+      } break;
+      case cmsysProcess_State_Exception:
+        this->Makefile->AddDefinition(results_variable,
+                                      cmsysProcess_GetExceptionString(cp));
+        break;
+      case cmsysProcess_State_Error:
+        this->Makefile->AddDefinition(results_variable,
+                                      cmsysProcess_GetErrorString(cp));
+        break;
+      case cmsysProcess_State_Expired:
+        this->Makefile->AddDefinition(results_variable,
+                                      "Process terminated due to timeout");
+        break;
+    }
+  }
 
   // Delete the process instance.
   cmsysProcess_Delete(cp);