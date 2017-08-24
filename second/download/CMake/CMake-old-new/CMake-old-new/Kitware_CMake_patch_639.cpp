@@ -1632,10 +1632,12 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
 
   int firstTest = 1;
   long line = 0;
+
+#define SPACE_REGEX "[ \t\r\n]"
   
   cmsys::RegularExpression ireg(this->m_IncludeRegExp.c_str());
   cmsys::RegularExpression ereg(this->m_ExcludeRegExp.c_str());
-  cmsys::RegularExpression dartStuff("([\t\n ]*<DartMeasurement.*/DartMeasurement[a-zA-Z]*>[\t ]*[\n]*)");
+  cmsys::RegularExpression dartStuff("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");
 
   bool parseError;
   while ( fin )
@@ -1756,8 +1758,9 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
               {
               if (dartStuff.find(output.c_str()))
                 {
-                cmSystemTools::ReplaceString(output,
-                                             dartStuff.match(1).c_str(),"");
+                std::string res = dartStuff.match(1);
+                cmSystemTools::ReplaceString(output, res.c_str(),"");
+                cres.m_RegressionImages = this->GenerateRegressionImages(res);
                 }
               if (output != "" && m_Verbose)
                 {
@@ -1771,10 +1774,12 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
             fprintf(stderr,"   Passed\n");
             if (output != "")
               {
+              std::cout << "Before dart check" << std::endl;
               if (dartStuff.find(output.c_str()))
                 {
-                cmSystemTools::ReplaceString(output,
-                                             dartStuff.match(1).c_str(),"");
+                std::string res = dartStuff.match(1);
+                cmSystemTools::ReplaceString(output, res.c_str(),"");
+                cres.m_RegressionImages = this->GenerateRegressionImages(res);
                 }
               if (output != "" && m_Verbose)
                 {
@@ -1855,7 +1860,7 @@ int cmCTest::TestDirectory()
       std::cerr << "Cannot create testing XML file" << std::endl;
       return 1;
       }
-    this->GenerateDartOutput(ofs);
+    this->GenerateDartTestOutput(ofs);
     }
 
   return int(failed.size());
@@ -1983,7 +1988,7 @@ std::string cmCTest::GetSubmitResultsPrefix()
   return name;
 }
 
-void cmCTest::GenerateDartOutput(std::ostream& os)
+void cmCTest::GenerateDartTestOutput(std::ostream& os)
 {
   if ( !m_DartMode )
     {
@@ -2026,6 +2031,7 @@ void cmCTest::GenerateDartOutput(std::ostream& os)
          << "CHILDSTATUS" << "</Value></NamedMeasurement>\n"
          << "\t\t\t<NamedMeasurement type=\"text/string\" name=\"Exit Value\"><Value>"
          << result->m_ReturnValue << "</Value></NamedMeasurement>" << std::endl;
+      os << result->m_RegressionImages;
       }
     os << "\t\t\t<NamedMeasurement type=\"numeric/double\" "
        << "name=\"Execution Time\"><Value>"
@@ -2116,6 +2122,135 @@ std::string cmCTest::GetTestModelString()
   return "Experimental";
 }
 
+std::string cmCTest::GenerateRegressionImages(const std::string& xml)
+{
+  cmsys::RegularExpression twoattributes(
+    "<DartMeasurement" 
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    SPACE_REGEX "*>([^<]*)</DartMeasurement>");
+  cmsys::RegularExpression threeattributes(
+    "<DartMeasurement" 
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    SPACE_REGEX "*>([^<]*)</DartMeasurement>");
+  cmsys::RegularExpression fourattributes(
+    "<DartMeasurement" 
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    SPACE_REGEX "*>([^<]*)</DartMeasurement>");
+  cmsys::RegularExpression measurementfile(
+    "<DartMeasurementFile" 
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    SPACE_REGEX "*>([^<]*)</DartMeasurementFile>");
+
+  cmOStringStream ostr;
+  bool done = false;
+  std::string cxml = xml;
+  while ( ! done )
+    {
+    if ( twoattributes.find(cxml) )
+      {
+      ostr
+        << "\t\t\t<NamedMeasurement" 
+        << " " << twoattributes.match(1) << "=\"" << twoattributes.match(2) << "\""
+        << " " << twoattributes.match(3) << "=\"" << twoattributes.match(4) << "\""
+        << "><Value>" << twoattributes.match(5) 
+        << "</Value></NamedMeasurement>" 
+        << std::endl;
+      cxml.erase(twoattributes.start(), twoattributes.end() - twoattributes.start());
+      }
+    else if ( threeattributes.find(cxml) )
+      {
+      ostr
+        << "\t\t\t<NamedMeasurement" 
+        << " " << threeattributes.match(1) << "=\"" << threeattributes.match(2) << "\""
+        << " " << threeattributes.match(3) << "=\"" << threeattributes.match(4) << "\""
+        << " " << threeattributes.match(5) << "=\"" << threeattributes.match(6) << "\""
+        << "><Value>" << threeattributes.match(7) 
+        << "</Value></NamedMeasurement>" 
+        << std::endl;
+      cxml.erase(threeattributes.start(), threeattributes.end() - threeattributes.start());
+      }
+    else if ( fourattributes.find(cxml) )
+      {
+      ostr
+        << "\t\t\t<NamedMeasurement" 
+        << " " << fourattributes.match(1) << "=\"" << fourattributes.match(2) << "\""
+        << " " << fourattributes.match(3) << "=\"" << fourattributes.match(4) << "\""
+        << " " << fourattributes.match(5) << "=\"" << fourattributes.match(6) << "\""
+        << " " << fourattributes.match(7) << "=\"" << fourattributes.match(8) << "\""
+        << "><Value>" << fourattributes.match(9) 
+        << "</Value></NamedMeasurement>" 
+        << std::endl;
+      cxml.erase(fourattributes.start(), fourattributes.end() - fourattributes.start());
+      }
+    else if ( measurementfile.find(cxml) )
+      {
+      const std::string& filename = measurementfile.match(5);
+      if ( cmSystemTools::FileExists(filename.c_str()) )
+        {
+        long len = cmSystemTools::FileLength(filename.c_str());
+        std::ifstream ifs(filename.c_str(), std::ios::in 
+#ifdef _WIN32
+          | std::ios::binary
+#endif
+          );
+        unsigned char *file_buffer = new unsigned char [ len + 1 ];
+        ifs.read(reinterpret_cast<char*>(file_buffer), len);
+        unsigned char *encoded_buffer = new unsigned char [ static_cast<int>(len * 1.5 + 1) ];
+
+        unsigned long rlen = cmsysBase64_Encode(file_buffer, len, encoded_buffer, 1);
+        unsigned long cc;
+
+        ostr
+          << "\t\t\t<NamedMeasurement" 
+          << " " << measurementfile.match(1) << "=\"" << measurementfile.match(2) << "\""
+          << " " << measurementfile.match(3) << "=\"" << measurementfile.match(4) << "\""
+          << " encoding=\"base64\""
+          << ">" << std::endl << "\t\t\t\t<Value>";
+        for ( cc = 0; cc < rlen; cc ++ )
+          {
+          ostr << encoded_buffer[cc];
+          if ( cc % 60 == 0 && cc )
+            {
+            ostr << std::endl;
+            }
+          }
+        ostr
+          << "</Value>" << std::endl << "\t\t\t</NamedMeasurement>" 
+          << std::endl;
+        delete [] file_buffer;
+        delete [] encoded_buffer;
+        }
+      else
+        {
+        int idx = 4;
+        if ( measurementfile.match(1) == "name" )
+          {
+          idx = 2;
+          }
+        ostr
+          << "\t\t\t<NamedMeasurement" 
+          << " name=\"" << measurementfile.match(idx) << "\""
+          << " text=\"text/string\""
+          << "><Value>File " << filename << " not found</Value></NamedMeasurement>" 
+          << std::endl;
+        }
+      cxml.erase(measurementfile.start(), measurementfile.end() - measurementfile.start());
+      }
+    else
+      {
+      done = true;
+      }
+    }
+  return ostr.str();
+}
+
 bool cmCTest::RunMakeCommand(const char* command, std::string* output,
     int* retVal, const char* dir, bool verbose, int timeout, std::ofstream& ofs)
 {