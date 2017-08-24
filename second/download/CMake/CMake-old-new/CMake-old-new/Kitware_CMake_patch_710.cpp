@@ -168,9 +168,9 @@ std::string cmCTest::MakeXMLSafe(const std::string& str)
   for ( pos = 0; pos < str.size(); pos ++ )
     {
     unsigned char ch = str[pos];
-    if ( (ch > 126 || ch < 32) && ch != 9 )
+    if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 )
       {
-      sprintf(buffer, "&gt;&lt;");
+      sprintf(buffer, "&gt;%d&lt;", (int)ch);
       //sprintf(buffer, "&#x%0x;", (unsigned int)ch);
       ost << buffer;
       }
@@ -1276,6 +1276,11 @@ int cmCTest::CoverageDirectory()
       {
       //std::cout << "\t" << gfiles[cc] << std::endl;
       std::ifstream ifile(gfiles[cc].c_str());
+      if ( !ifile )
+        {
+        std::cout << "Cannot open file: " << gfiles[cc].c_str() << std::endl;
+        }
+
       ifile.seekg (0, std::ios::end);
       int length = ifile.tellg();
       ifile.seekg (0, std::ios::beg);
@@ -1299,16 +1304,22 @@ int cmCTest::CoverageDirectory()
           {
           cov.m_FullPath = allbinaryfiles[it->first];
           }
+        cov.m_AbsolutePath = cov.m_FullPath;
         std::string src_dir = m_DartConfiguration["SourceDirectory"];
+        if ( src_dir[src_dir.size()-1] != '/' )
+          {
+          src_dir.push_back('/');
+          }
         std::string::size_type spos = cov.m_FullPath.find(src_dir);
         if ( spos == 0 )
           {
-          cov.m_FullPath = std::string(".") + cov.m_FullPath.substr(src_dir.size());
+          cov.m_FullPath = std::string("./") + cov.m_FullPath.substr(src_dir.size());
           }
         else
           {
-          std::cerr << "Compare -- " << cov.m_FullPath << std::endl;
-          std::cerr << "        -- " << src_dir << std::endl;
+          //std::cerr << "Compare -- " << cov.m_FullPath << std::endl;
+          //std::cerr << "        -- " << src_dir << std::endl;
+          continue;
           }
         }
       for ( cc = 0; cc < lines.size(); cc ++ )
@@ -1384,7 +1395,11 @@ int cmCTest::CoverageDirectory()
     cmCTest::cmCTestCoverage &cov = cit->second;
 
 
-    std::ifstream ifile(cov.m_FullPath.c_str());
+    std::ifstream ifile(cov.m_AbsolutePath.c_str());
+    if ( !ifile )
+      {
+      std::cerr << "Cannot open file: " << cov.m_FullPath.c_str() << std::endl;
+      }
     ifile.seekg (0, std::ios::end);
     int length = ifile.tellg();
     ifile.seekg (0, std::ios::beg);
@@ -1420,12 +1435,17 @@ int cmCTest::CoverageDirectory()
       cmet = ( static_cast<float>(cov.m_Tested + 10) /
         static_cast<float>(cov.m_Tested + cov.m_UnTested + 10));
       }
+    char cmbuff[100];
+    char cpbuff[100];
+    sprintf(cmbuff, "%.2f", cmet);
+    sprintf(cpbuff, "%.2f", cper);
+
     log << "\t<File Name=\"" << cit->first << "\" FullPath=\"" << cov.m_FullPath
       << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"
       << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"
       << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"
-      << "\t\t<PercentCoverage>" << cper << "</PercentCoverage>\n"
-      << "\t\t<CoverageMetric>" << cmet << "</CoverageMetric>\n"
+      << "\t\t<PercentCoverage>" << cpbuff << "</PercentCoverage>\n"
+      << "\t\t<CoverageMetric>" << cmbuff << "</CoverageMetric>\n"
       << "\t</File>" << std::endl;
     ccount ++;
     }
@@ -1448,11 +1468,13 @@ int cmCTest::CoverageDirectory()
     }
 
   std::string end_time = ::CurrentTime();
+  char buffer[100];
+  sprintf(buffer, "%.2f", percent_coverage);
 
   log << "\t<LOCTested>" << total_tested << "</LOCTested>\n"
       << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"
       << "\t<LOC>" << total_lines << "</LOC>\n"
-      << "\t<PercentCoverage>" << percent_coverage << "</PercentCoverage>\n"
+      << "\t<PercentCoverage>" << buffer << "</PercentCoverage>\n"
       << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"
       << "</Coverage>\n"
       << "</Site>" << std::endl;