@@ -105,6 +105,7 @@ void ctest::ProcessDirectory(int &passed, int &failed)
   std::string name;
   std::vector<std::string> args;
   cmRegularExpression var(this->m_RegExp.c_str());
+  cmRegularExpression dartStuff("([\t\n ]*<DartMeasurement.*/DartMeasurement[a-zA-Z]*>[\t ]*[\n]*)");
 
   while ( fin )
     {
@@ -153,14 +154,22 @@ void ctest::ProcessDirectory(int &passed, int &failed)
          */
         std::string output;
         int retVal;
-        
+
         if (!cmSystemTools::RunCommand(testCommand.c_str(), output, 
                                        retVal, false) || retVal != 0)
           {
           fprintf(stderr,"***Failed\n");
           if (output != "")
             {
-            std::cerr << output.c_str() << "\n";
+            if (dartStuff.find(output.c_str()))
+              {
+              cmSystemTools::ReplaceString(output,
+                                           dartStuff.match(1).c_str(),"");
+              }
+            if (output != "")
+              {
+              std::cerr << output.c_str() << "\n";
+              }
             }
           failed++;
           }
@@ -169,7 +178,15 @@ void ctest::ProcessDirectory(int &passed, int &failed)
           fprintf(stderr,"   Passed\n");
           if (output != "")
             {
-            std::cerr << output.c_str() << "\n";
+            if (dartStuff.find(output.c_str()))
+              {
+              cmSystemTools::ReplaceString(output,
+                                           dartStuff.match(1).c_str(),"");
+              }
+            if (output != "")
+              {
+              std::cerr << output.c_str() << "\n";
+              }
             }
           passed++;
           }