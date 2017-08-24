@@ -589,7 +589,7 @@ int cmCTestTestHandler::ProcessHandler()
         cmCTestTestResult *result = &this->TestResults[cc];
         totalTestTime += result->ExecutionTime;
         }
-      
+      this->PrintLabelSummary();
       char buf[1024];
       sprintf(buf, "%6.2f sec", totalTestTime); 
       cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time = " 
@@ -657,6 +657,53 @@ int cmCTestTestHandler::ProcessHandler()
 }
 
 //----------------------------------------------------------------------
+void cmCTestTestHandler::PrintLabelSummary()
+{
+  cmCTestTestHandler::ListOfTests::iterator it = this->TestList.begin();
+  cmCTestTestHandler::TestResultsVector::iterator ri =
+    this->TestResults.begin(); 
+  std::map<cmStdString, double> labelTimes;
+  std::set<cmStdString> labels;
+  // initialize maps
+  for(; it != this->TestList.end(); ++it)
+    {
+    cmCTestTestProperties& p = *it;
+    if(p.Labels.size() != 0)
+      { 
+      for(std::vector<std::string>::iterator l = p.Labels.begin();
+          l !=  p.Labels.end(); ++l)
+        {
+        labels.insert(*l);
+        labelTimes[*l] = 0;
+        }
+      }
+    }
+  it = this->TestList.begin();
+  ri = this->TestResults.begin(); 
+  // fill maps
+  for(; it != this->TestList.end(); ++it, ++ri)
+    {
+    cmCTestTestProperties& p = *it;
+    cmCTestTestResult &result = *ri;
+    if(p.Labels.size() != 0)
+      { 
+      for(std::vector<std::string>::iterator l = p.Labels.begin();
+          l !=  p.Labels.end(); ++l)
+        {
+        labelTimes[*l] += result.ExecutionTime;
+        }
+      }
+    }
+  // now print times
+  for(std::set<cmStdString>::const_iterator i = labels.begin();
+      i != labels.end(); ++i)
+    {
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTime in " 
+               << *i << " = " << labelTimes[*i] << " sec" );
+    }
+}
+
+//----------------------------------------------------------------------
 void cmCTestTestHandler::ProcessOneTest(cmCTestTestProperties *it,
                                         std::vector<cmStdString> &passed,
                                         std::vector<cmStdString> &failed,