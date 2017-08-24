@@ -25,6 +25,7 @@
 #include <cmsys/SystemInformation.hxx>
 #include "cmDynamicLoader.h"
 #include "cmGeneratedFileStream.h"
+#include "cmXMLSafe.h"
 #include "cmCTestCommand.h"
 
 #include "cmCTestBuildHandler.h"
@@ -149,59 +150,7 @@ std::string cmCTest::CurrentTime()
     strftime(current_time, 1000, "%a %b %d %H:%M:%S %Z %Y", t);
     }
   cmCTestLog(this, DEBUG, "   Current_Time: " << current_time << std::endl);
-  return cmCTest::MakeXMLSafe(cmCTest::CleanString(current_time));
-}
-
-
-//----------------------------------------------------------------------
-std::string cmCTest::MakeXMLSafe(const std::string& str)
-{
-  std::vector<char> result;
-  result.reserve(500);
-  const char* pos = str.c_str();
-  for ( ;*pos; ++pos)
-    {
-    char ch = *pos;
-    if ( (ch > 126 || ch < 32) && ch != 9  &&
-      ch != 10 && ch != 13 && ch != '\r' )
-      {
-      char buffer[33];
-      sprintf(buffer, "&lt;%d&gt;", (int)ch);
-      //sprintf(buffer, "&#x%0x;", (unsigned int)ch);
-      result.insert(result.end(), buffer, buffer+strlen(buffer));
-      }
-    else
-      {
-      const char* const encodedChars[] = {
-        "&amp;",
-        "&lt;",
-        "&gt;"
-      };
-      switch ( ch )
-        {
-        case '&':
-          result.insert(result.end(), encodedChars[0], encodedChars[0]+5);
-          break;
-        case '<':
-          result.insert(result.end(), encodedChars[1], encodedChars[1]+4);
-          break;
-        case '>':
-          result.insert(result.end(), encodedChars[2], encodedChars[2]+4);
-          break;
-        case '\n':
-          result.push_back('\n');
-          break;
-        case '\r': break; // Ignore \r
-        default:
-          result.push_back(ch);
-        }
-      }
-    }
-  if ( result.size() == 0 )
-    {
-    return "";
-    }
-  return std::string(&*result.begin(), result.size());
+  return cmXMLSafe(cmCTest::CleanString(current_time)).str();
 }
 
 //----------------------------------------------------------------------
@@ -1386,7 +1335,7 @@ int cmCTest::GenerateCTestNotesOutput(std::ostream& os,
     {
     cmCTestLog(this, OUTPUT, "\tAdd file: " << it->c_str() << std::endl);
     std::string note_time = this->CurrentTime();
-    os << "<Note Name=\"" << this->MakeXMLSafe(it->c_str()) << "\">\n"
+    os << "<Note Name=\"" << cmXMLSafe(*it) << "\">\n"
       << "<Time>" << cmSystemTools::GetTime() << "</Time>\n"
       << "<DateTime>" << note_time << "</DateTime>\n"
       << "<Text>" << std::endl;
@@ -1396,7 +1345,7 @@ int cmCTest::GenerateCTestNotesOutput(std::ostream& os,
       std::string line;
       while ( cmSystemTools::GetLineFromStream(ifs, line) )
         {
-        os << this->MakeXMLSafe(line) << std::endl;
+        os << cmXMLSafe(line) << std::endl;
         }
       ifs.close();
       }