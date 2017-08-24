@@ -209,6 +209,7 @@ std::string cmCTest::MakeXMLSafe(const std::string& str)
 {
   cmOStringStream ost;
   char buffer[10];
+  int lcnt = 0;
   for (std::string::size_type  pos = 0; pos < str.size(); pos ++ )
     {
     unsigned char ch = str[pos];
@@ -217,6 +218,7 @@ std::string cmCTest::MakeXMLSafe(const std::string& str)
       sprintf(buffer, "&gt;%d&lt;", (int)ch);
       //sprintf(buffer, "&#x%0x;", (unsigned int)ch);
       ost << buffer;
+      lcnt += 4;
       }
     else
       {
@@ -225,9 +227,16 @@ std::string cmCTest::MakeXMLSafe(const std::string& str)
         case '&': ost << "&amp;"; break;
         case '<': ost << "&lt;"; break;
         case '>': ost << "&gt;"; break;
+        case '\n': ost << "\n"; lcnt = 0; break;
         default: ost << ch;
         }
+      lcnt ++;
       }
+    //if ( lcnt > 120 )
+    //  {
+    //  ost << "\n";
+    //  lcnt = 0;
+    //  }
     }
   return ost.str();
 }
@@ -1006,6 +1015,36 @@ int cmCTest::BuildDirectory()
     ofs.close();
     }
 
+  int cc;
+  std::string srcdir = m_DartConfiguration["SourceDirectory"] + "/";
+  std::string bindir = m_DartConfiguration["BuildDirectory"] + "/";
+  std::string srcdirrep;
+  std::string bindirrep;
+  for ( cc = srcdir.size()-2; cc > 0; cc -- )
+    {
+    if ( srcdir[cc] == '/' )
+      {
+      srcdirrep = srcdir.c_str() + cc;
+      srcdirrep = "/..." + srcdirrep;
+      break;
+      }
+    }
+  for ( cc = bindir.size()-2; cc > 0; cc -- )
+    {
+    if ( bindir[cc] == '/' )
+      {
+      bindirrep = bindir.c_str() + cc;
+      bindirrep = "/..." + bindirrep;
+      break;
+      }
+    }
+
+  //std::cout << "Use " << srcdirrep.c_str() << std::endl;
+  //std::cout << "Use " << bindirrep.c_str() << std::endl;
+
+  cmSystemTools::ReplaceString(output, srcdir.c_str(), srcdirrep.c_str());
+  cmSystemTools::ReplaceString(output, bindir.c_str(), bindirrep.c_str());
+
   // Parsing of output for errors and warnings.
 
   std::vector<cmStdString> lines;
@@ -1018,7 +1057,6 @@ int cmCTest::BuildDirectory()
   // > 1 - warning
   std::vector<int> markedLines(lines.size(), 0);
   
-  int cc;
   // Errors
   for ( cc = 0; cmCTestErrorMatches[cc]; cc ++ )
     {