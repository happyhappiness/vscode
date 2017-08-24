@@ -209,16 +209,17 @@ std::string cmCTest::MakeXMLSafe(const std::string& str)
 {
   cmOStringStream ost;
   char buffer[10];
-  int lcnt = 0;
+  // By uncommenting the lcnt code, it will put newline every 120 characters
+  //int lcnt = 0;
   for (std::string::size_type  pos = 0; pos < str.size(); pos ++ )
     {
     unsigned char ch = str[pos];
     if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 )
       {
-      sprintf(buffer, "&gt;%d&lt;", (int)ch);
+      sprintf(buffer, "&lt;%d&gt;", (int)ch);
       //sprintf(buffer, "&#x%0x;", (unsigned int)ch);
       ost << buffer;
-      lcnt += 4;
+      //lcnt += 4;
       }
     else
       {
@@ -227,10 +228,12 @@ std::string cmCTest::MakeXMLSafe(const std::string& str)
         case '&': ost << "&amp;"; break;
         case '<': ost << "&lt;"; break;
         case '>': ost << "&gt;"; break;
-        case '\n': ost << "\n"; lcnt = 0; break;
+        case '\n': ost << "\n"; 
+          //lcnt = 0; 
+          break;
         default: ost << ch;
         }
-      lcnt ++;
+      //lcnt ++;
       }
     //if ( lcnt > 120 )
     //  {
@@ -2982,7 +2985,7 @@ int cmCTest::RunConfigurationScript()
   std::string command;
   std::string output;
   int retVal = 0;
-  bool res = 0; 
+  bool res; 
   
   // do an initial cvs update on the src dir
   const char *cvsCmd = mf->GetDefinition("CTEST_CVS_COMMAND");