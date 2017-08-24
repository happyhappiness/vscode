@@ -594,7 +594,10 @@ int cmCTestTestHandler::ProcessHandler()
       sprintf(buf, "%6.2f sec", totalTestTime); 
       cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time = " 
                  <<  buf << "\n" );
-      
+      if ( this->LogFile )
+        {
+        *this->LogFile << "\nTotal Test time = " << buf << std::endl;
+        }
       }
 
     if (failed.size())
@@ -699,7 +702,12 @@ void cmCTestTestHandler::PrintLabelSummary()
       i != labels.end(); ++i)
     {
     cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTime in " 
-               << *i << " = " << labelTimes[*i] << " sec" );
+               << *i << " = " << labelTimes[*i] << " sec" ); 
+    if ( this->LogFile )
+        {
+        *this->LogFile << "\nTime in " << *i << " = "
+                       << labelTimes[*i] << " sec"  << std::endl;
+        }
     }
 }
 
@@ -942,6 +950,10 @@ void cmCTestTestHandler::ProcessOneTest(cmCTestTestProperties *it,
     char buf[1024];
     sprintf(buf, "%6.2f sec", cres.ExecutionTime);
     cmCTestLog(this->CTest, HANDLER_OUTPUT, buf << "\n" );
+    if ( this->LogFile )
+      {
+      *this->LogFile << "\nTest time = " << buf << std::endl;
+      }
     if (!output.empty() && output.find("<DartMeasurement") != output.npos)
       {
       if (this->DartStuff.find(output.c_str()))