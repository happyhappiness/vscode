@@ -139,45 +139,47 @@ std::string cmCTest::CurrentTime()
 //----------------------------------------------------------------------
 std::string cmCTest::MakeXMLSafe(const std::string& str)
 {
-  cmOStringStream ost;
-  // By uncommenting the lcnt code, it will put newline every 120 characters
-  //int lcnt = 0;
-  for (std::string::size_type  pos = 0; pos < str.size(); pos ++ )
+  std::vector<char> result;
+  result.reserve(500);
+  const char* pos = str.c_str();
+  for ( ;*pos; ++pos)
     {
-    unsigned char ch = str[pos];
-    if ( ch == '\r' )
-      {
-      // Ignore extra CR characters.
-      }
-    else if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 )
+    char ch = *pos;
+    if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 && ch != '\r' )
       {
       char buffer[33];
       sprintf(buffer, "&lt;%d&gt;", (int)ch);
       //sprintf(buffer, "&#x%0x;", (unsigned int)ch);
-      ost << buffer;
-      //lcnt += 4;
+      result.insert(result.end(), buffer, buffer+strlen(buffer));
       }
     else
       {
+      const char* const encodedChars[] = {
+        "&amp;",
+        "&lt;",
+        "&gt;"
+      };
       switch ( ch )
         {
-        case '&': ost << "&amp;"; break;
-        case '<': ost << "&lt;"; break;
-        case '>': ost << "&gt;"; break;
-        case '\n': ost << "\n"; 
-          //lcnt = 0; 
+        case '&':
+          result.insert(result.end(), encodedChars[0], encodedChars[0]+5);
+          break;
+        case '<':
+          result.insert(result.end(), encodedChars[1], encodedChars[1]+4);
+          break;
+        case '>':
+          result.insert(result.end(), encodedChars[2], encodedChars[2]+4);
+          break;
+        case '\n':
+          result.push_back('\n');
           break;
-        default: ost << ch;
+        case '\r': break; // Ignore \r
+        default:
+          result.push_back(ch);
         }
-      //lcnt ++;
       }
-    //if ( lcnt > 120 )
-    //  {
-    //  ost << "\n";
-    //  lcnt = 0;
-    //  }
     }
-  return ost.str();
+  return std::string(&*result.begin(), result.size());
 }
 
 //----------------------------------------------------------------------
@@ -473,49 +475,56 @@ bool cmCTest::UpdateCTestConfiguration()
     }
   if ( !cmSystemTools::FileExists(fileName.c_str()) )
     {
-    cmCTestLog(this, ERROR_MESSAGE, "Cannot find file: " << fileName.c_str() << std::endl);
-    return false;
-    }
-  // parse the dart test file
-  std::ifstream fin(fileName.c_str());
-  if(!fin)
-    {
-    return false;
+    // No need to exit if we are not producing XML
+    if ( m_ProduceXML )
+      {
+      cmCTestLog(this, ERROR_MESSAGE, "Cannot find file: " << fileName.c_str() << std::endl);
+      return false;
+      }
     }
-
-  char buffer[1024];
-  while ( fin )
+  else
     {
-    buffer[0] = 0;
-    fin.getline(buffer, 1023);
-    buffer[1023] = 0;
-    std::string line = cmCTest::CleanString(buffer);
-    if(line.size() == 0)
+    // parse the dart test file
+    std::ifstream fin(fileName.c_str());
+    if(!fin)
       {
-      continue;
+      return false;
       }
-    while ( fin && (line[line.size()-1] == '\\') )
+
+    char buffer[1024];
+    while ( fin )
       {
-      line = line.substr(0, line.size()-1);
       buffer[0] = 0;
       fin.getline(buffer, 1023);
       buffer[1023] = 0;
-      line += cmCTest::CleanString(buffer);
-      }
-    if ( line[0] == '#' )
-      {
-      continue;
-      }
-    std::string::size_type cpos = line.find_first_of(":");
-    if ( cpos == line.npos )
-      {
-      continue;
+      std::string line = cmCTest::CleanString(buffer);
+      if(line.size() == 0)
+        {
+        continue;
+        }
+      while ( fin && (line[line.size()-1] == '\\') )
+        {
+        line = line.substr(0, line.size()-1);
+        buffer[0] = 0;
+        fin.getline(buffer, 1023);
+        buffer[1023] = 0;
+        line += cmCTest::CleanString(buffer);
+        }
+      if ( line[0] == '#' )
+        {
+        continue;
+        }
+      std::string::size_type cpos = line.find_first_of(":");
+      if ( cpos == line.npos )
+        {
+        continue;
+        }
+      std::string key = line.substr(0, cpos);
+      std::string value = cmCTest::CleanString(line.substr(cpos+1, line.npos));
+      m_CTestConfiguration[key] = value;
       }
-    std::string key = line.substr(0, cpos);
-    std::string value = cmCTest::CleanString(line.substr(cpos+1, line.npos));
-    m_CTestConfiguration[key] = value;
+    fin.close();
     }
-  fin.close();
   if ( m_ProduceXML )
     {
     m_TimeOut = atoi(m_CTestConfiguration["TimeOut"].c_str());
@@ -1699,28 +1708,29 @@ int cmCTest::ReadCustomConfigurationFileTree(const char* dir)
 {
   tm_VectorOfStrings dirs;
   tm_VectorOfStrings ndirs;
-  dirs.push_back(dir);
   cmake cm;
   cmGlobalGenerator gg;
   gg.SetCMakeInstance(&cm);
   std::auto_ptr<cmLocalGenerator> lg(gg.CreateLocalGenerator());
   lg->SetGlobalGenerator(&gg);
   cmMakefile *mf = lg->GetMakefile();
 
-  while ( dirs.size() > 0 )
+  std::string rexpr = dir;
+  rexpr += "/*/CTestCustom.ctest";
+  cmGlob gl;
+  gl.RecurseOn();
+  gl.FindFiles(rexpr);
+  std::vector<std::string>& files = gl.GetFiles();
+  std::vector<std::string>::iterator fileIt;
+  for ( fileIt = files.begin(); fileIt != files.end();
+    ++ fileIt )
     {
-    tm_VectorOfStrings::iterator cdir = dirs.end()-1;
-    std::string rexpr = *cdir + "/*";
-    std::string fname = *cdir + "/CTestCustom.ctest";
-    if ( cmSystemTools::FileExists(fname.c_str()) && 
-      (!lg->GetMakefile()->ReadListFile(0, fname.c_str()) ||
-       cmSystemTools::GetErrorOccuredFlag() ) )
+    cmCTestLog(this, DEBUG, "* Read custom CTest configuration file: " << fileIt->c_str() << std::endl);
+    if ( !lg->GetMakefile()->ReadListFile(0, fileIt->c_str()) ||
+      cmSystemTools::GetErrorOccuredFlag() )
       {
-      cmCTestLog(this, ERROR_MESSAGE, "Problem reading custom configuration" << std::endl);
+      cmCTestLog(this, ERROR_MESSAGE, "Problem reading custom configuration: " << fileIt->c_str() << std::endl);
       }
-    dirs.erase(dirs.end()-1, dirs.end());
-    cmSystemTools::SimpleGlob(rexpr, ndirs, -1);
-    dirs.insert(dirs.end(), ndirs.begin(), ndirs.end());
     }
 
   cmCTest::t_TestingHandlers::iterator it;