@@ -256,8 +256,8 @@ bool cmCTestSubmitHandler::SubmitUsingHTTP(const cmStdString& localprefix,
       for ( kk = 0; kk < remote_file.size(); kk ++ )
         {
         char c = remote_file[kk];
-        char hex[4] = { 0, 0, 0, 0 };
-        hex[0] = c;
+        char hexCh[4] = { 0, 0, 0, 0 };
+        hexCh[0] = c;
         switch ( c )
           {
         case '+':
@@ -268,11 +268,11 @@ bool cmCTestSubmitHandler::SubmitUsingHTTP(const cmStdString& localprefix,
         case ' ':
         case '=':
         case '%':
-          sprintf(hex, "%%%02X", (int)c);
-          ofile.append(hex);
+          sprintf(hexCh, "%%%02X", (int)c);
+          ofile.append(hexCh);
           break;
         default: 
-          ofile.append(hex);
+          ofile.append(hexCh);
           }
         }
       cmStdString upload_as 
@@ -407,8 +407,8 @@ bool cmCTestSubmitHandler::TriggerUsingHTTP(const std::set<cmStdString>& files,
       for ( kk = rfile.begin(); kk < rfile.end(); ++ kk)
         {
         char c = *kk;
-        char hex[4] = { 0, 0, 0, 0 };
-        hex[0] = c;
+        char hexCh[4] = { 0, 0, 0, 0 };
+        hexCh[0] = c;
         switch ( c )
           {
         case '+':
@@ -419,11 +419,11 @@ bool cmCTestSubmitHandler::TriggerUsingHTTP(const std::set<cmStdString>& files,
         case ' ':
         case '=':
         case '%':
-          sprintf(hex, "%%%02X", (int)c);
-          ofile.append(hex);
+          sprintf(hexCh, "%%%02X", (int)c);
+          ofile.append(hexCh);
           break;
         default: 
-          ofile.append(hex);
+          ofile.append(hexCh);
           }
         }
       cmStdString turl 
@@ -760,7 +760,6 @@ int cmCTestSubmitHandler::ProcessHandler()
     {
     ofs << "Upload files:" << std::endl;
     int cnt = 0;
-    cmCTest::tm_SetOfStrings::iterator it;
     for ( it = files.begin(); it != files.end(); ++ it )
       {
       ofs << cnt << "\t" << it->c_str() << std::endl;