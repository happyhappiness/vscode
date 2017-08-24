@@ -589,25 +589,15 @@ int cmCTestTestHandler::ProcessHandler()
                << static_cast<int>(percent + .5) << "% tests passed, "
                << failed.size() << " tests failed out of " 
                << total << std::endl); 
-    double totalTestTime = 0;
-
-    for(cmCTestTestHandler::TestResultsVector::size_type cc = 0;
-        cc < this->TestResults.size(); cc ++ )
+    if(this->CTest->GetLabelSummary())
       {
-      cmCTestTestResult *result = &this->TestResults[cc];
-      totalTestTime += result->ExecutionTime;
+      this->PrintLabelSummary();
       }
-    
     char realBuf[1024];
     sprintf(realBuf, "%6.2f sec", (double)(clock_finish - clock_start));
     cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (real) = "
                << realBuf << "\n" );
 
-    char totalBuf[1024];
-    sprintf(totalBuf, "%6.2f sec", totalTestTime); 
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (parallel) = "
-               <<  totalBuf << "\n" );
-
     if (failed.size())
       {
       cmGeneratedFileStream ofs;
@@ -672,6 +662,7 @@ void cmCTestTestHandler::PrintLabelSummary()
   std::map<cmStdString, double> labelTimes;
   std::set<cmStdString> labels;
   // initialize maps
+  std::string::size_type maxlen = 0;
   for(; it != this->TestList.end(); ++it)
     {
     cmCTestTestProperties& p = *it;
@@ -680,6 +671,10 @@ void cmCTestTestHandler::PrintLabelSummary()
       for(std::vector<std::string>::iterator l = p.Labels.begin();
           l !=  p.Labels.end(); ++l)
         {
+        if((*l).size() > maxlen)
+          {
+          maxlen = (*l).size();
+          }
         labels.insert(*l);
         labelTimes[*l] = 0;
         }
@@ -696,23 +691,40 @@ void cmCTestTestHandler::PrintLabelSummary()
       {
       for(std::vector<std::string>::iterator l = p.Labels.begin();
           l !=  p.Labels.end(); ++l)
-        {
+        {  
         labelTimes[*l] += result.ExecutionTime;
         }
       }
     }
-  // now print times
+  // now print times  
+  if(labels.size())
+    {
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nLabel Time Summary:");
+    }
   for(std::set<cmStdString>::const_iterator i = labels.begin();
       i != labels.end(); ++i)
     {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTime in "
-               << *i << " = " << labelTimes[*i] << " sec" );
+    std::string label = *i;
+    label.resize(maxlen +3, ' ');
+    char buf[1024];
+    sprintf(buf, "%6.2f sec", labelTimes[*i]);
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\n"
+               << label << " = " << buf );
     if ( this->LogFile )
-        {
-        *this->LogFile << "\nTime in " << *i << " = "
-                       << labelTimes[*i] << " sec"  << std::endl;
-        }
+      {
+      *this->LogFile << "\n" << *i << " = "
+                     << buf << "\n";
+      }
+    }
+  if(labels.size())
+    { 
+    if(this->LogFile)
+      {
+      *this->LogFile << "\n";
+      }
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\n");
     }
+
 }
 
 //----------------------------------------------------------------------