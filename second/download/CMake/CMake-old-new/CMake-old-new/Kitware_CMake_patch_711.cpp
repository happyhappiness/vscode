@@ -167,10 +167,11 @@ std::string cmCTest::MakeXMLSafe(const std::string& str)
   char buffer[10];
   for ( pos = 0; pos < str.size(); pos ++ )
     {
-    char ch = str[pos];
-    if ( ch > 126 )
+    unsigned char ch = str[pos];
+    if ( (ch > 126 || ch < 32) && ch != 9 )
       {
-      sprintf(buffer, "&%x", (int)ch);
+      sprintf(buffer, "&gt;&lt;");
+      //sprintf(buffer, "&#x%0x;", (unsigned int)ch);
       ost << buffer;
       }
     else
@@ -1151,7 +1152,7 @@ int cmCTest::CoverageDirectory()
     }
 
   std::ofstream log; 
-  if (!this->OpenOutputFile("Coverage", "Coverage.log", log))
+  if (!this->OpenOutputFile("Temporary", "Coverage.log", log))
     {
     std::cout << "Cannot open log file" << std::endl;
     return 1;
@@ -1163,14 +1164,16 @@ int cmCTest::CoverageDirectory()
     return 1;
     }
 
-  std::string opath = m_ToplevelPath + "/Testing/" + m_CurrentTag + "/Coverage";
+  std::string opath = m_ToplevelPath + "/Testing/Temporary/Coverage";
+  cmSystemTools::MakeDirectory(opath.c_str());
   
   for ( cc = 0; cc < files.size(); cc ++ )
     {
     std::string command = "gcov -l \"" + files[cc] + "\"";
     std::string output;
     int retVal = 0;
     //std::cout << "Run gcov on " << files[cc] << std::flush;
+    //std::cout << "   --- Run [" << command << "]" << std::endl;
     bool res = true;
     if ( !m_ShowOnly )
       {
@@ -1269,7 +1272,17 @@ int cmCTest::CoverageDirectory()
           {
           cov.m_FullPath = allbinaryfiles[it->first];
           }
-        //std::cerr << "Full path: " << cov.m_FullPath << std::endl;
+        std::string src_dir = m_DartConfiguration["SourceDirectory"];
+        std::string::size_type spos = cov.m_FullPath.find(src_dir);
+        if ( spos == 0 )
+          {
+          cov.m_FullPath = std::string(".") + cov.m_FullPath.substr(src_dir.size());
+          }
+        else
+          {
+          std::cerr << "Compare -- " << cov.m_FullPath << std::endl;
+          std::cerr << "        -- " << src_dir << std::endl;
+          }
         }
       for ( cc = 0; cc < lines.size(); cc ++ )
         {
@@ -1307,12 +1320,6 @@ int cmCTest::CoverageDirectory()
   std::ofstream cfileoutput; 
   int cfileoutputcount = 0;
   char cfileoutputname[100];
-  sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);
-  if (!this->OpenOutputFile(m_CurrentTag, cfileoutputname, cfileoutput))
-    {
-    std::cout << "Cannot open log file" << std::endl;
-    return 1;
-    }
   std::string local_start_time = ::CurrentTime();
   std::string local_end_time;
   for ( cit = coverageresults.begin(); cit != coverageresults.end(); cit ++ )
@@ -1321,28 +1328,29 @@ int cmCTest::CoverageDirectory()
       {
       local_end_time = ::CurrentTime();
       cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
-                  << "</CoverageLog>\n"
-                  << "</Site>" << std::endl;
+        << "</CoverageLog>\n"
+        << "</Site>" << std::endl;
       cfileoutput.close();
+      std::cout << "Close file: " << cfileoutputname << std::endl;
+      ccount = 0;
+      }
+    if ( ccount == 0 )
+      {
       sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);
+      std::cout << "Open file: " << cfileoutputname << std::endl;
       if (!this->OpenOutputFile(m_CurrentTag, cfileoutputname, cfileoutput))
         {
-        std::cout << "Cannot open log file" << std::endl;
+        std::cout << "Cannot open log file: " << cfileoutputname << std::endl;
         return 1;
         }
-      ccount = 0;
-      }
-
-    if ( ccount == 0 )
-      {
       local_start_time = ::CurrentTime();
       cfileoutput << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
-                  << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-                  << "\" BuildStamp=\"" << m_CurrentTag << "-"
-                  << this->GetTestModelString() << "\" Name=\""
-                  << m_DartConfiguration["Site"] << "\">\n"
-                  << "<CoverageLog>\n"
-                  << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
+        << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
+        << "\" BuildStamp=\"" << m_CurrentTag << "-"
+        << this->GetTestModelString() << "\" Site=\""
+        << m_DartConfiguration["Site"] << "\">\n"
+        << "<CoverageLog>\n"
+        << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
       }
 
     //std::cerr << "Final process of Source file: " << cit->first << std::endl;
@@ -1361,17 +1369,17 @@ int cmCTest::CoverageDirectory()
     cmSystemTools::Split(buffer, lines);
     delete [] buffer;
     cfileoutput << "\t<File Name=\"" << cit->first << "\" FullPath=\""
-                << cov.m_FullPath << std::endl << "\">\n"
-                << "\t\t<Report>" << std::endl;
+      << cov.m_FullPath << std::endl << "\">\n"
+      << "\t\t<Report>" << std::endl;
     for ( cc = 0; cc < lines.size(); cc ++ )
       {
       cfileoutput << "\t\t<Line Number=\"" 
-                  << static_cast<int>(cc) << "\" Count=\""
-                  << cov.m_Lines[cc] << "\">"
-                  << lines[cc] << "</Line>" << std::endl;
+        << static_cast<int>(cc) << "\" Count=\""
+        << cov.m_Lines[cc] << "\">"
+        << cmCTest::MakeXMLSafe(lines[cc]) << "</Line>" << std::endl;
       }
     cfileoutput << "\t\t</Report>\n"
-                << "\t</File>" << std::endl;
+      << "\t</File>" << std::endl;
 
 
     total_tested += cov.m_Tested;
@@ -1381,17 +1389,18 @@ int cmCTest::CoverageDirectory()
     if ( total_tested + total_untested > 0 )
       {
       cper = (100 * static_cast<float>(cov.m_Tested)/
-              static_cast<float>(cov.m_Tested + cov.m_UnTested));
+        static_cast<float>(cov.m_Tested + cov.m_UnTested));
       cmet = ( static_cast<float>(cov.m_Tested + 10) /
-               static_cast<float>(cov.m_Tested + cov.m_UnTested + 10));
+        static_cast<float>(cov.m_Tested + cov.m_UnTested + 10));
       }
     log << "\t<File Name=\"" << cit->first << "\" FullPath=\"" << cov.m_FullPath
-        << "\" Covered=\"" << cov.m_Covered << "\">\n"
-        << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"
-        << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"
-        << "\t\t<PercentCoverage>" << cper << "</PercentCoverage>\n"
-        << "\t\t<CoverageMetric>" << cmet << "</CoverageMetric>\n"
-        << "\t</File>" << std::endl;
+      << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"
+      << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"
+      << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"
+      << "\t\t<PercentCoverage>" << cper << "</PercentCoverage>\n"
+      << "\t\t<CoverageMetric>" << cmet << "</CoverageMetric>\n"
+      << "\t</File>" << std::endl;
+    ccount ++;
     }
   
   if ( ccount > 0 )
@@ -1427,7 +1436,6 @@ int cmCTest::CoverageDirectory()
             << "\tPercentage Coverage: " << percent_coverage << "%" << std::endl;
 
 
-  std::cerr << "Coverage test is not yet implemented" << std::endl;
   return 1;
 }
 
@@ -1462,6 +1470,7 @@ bool cmCTest::OpenOutputFile(const std::string& path,
   stream.open(filename.c_str());
   if( !stream )
     {
+    std::cout << "Problem opening file: " << filename << std::endl;
     return false;
     }
   return true;
@@ -1791,12 +1800,32 @@ int cmCTest::SubmitResults()
   if ( this->CTestFileExists("Coverage.xml") )
     {
     files.push_back("Coverage.xml");
+    std::vector<std::string> gfiles;
+    std::string gpath = m_ToplevelPath + "/Testing/" + m_CurrentTag;
+    std::string::size_type glen = gpath.size() + 1;
+    gpath = gpath + "/CoverageLog*";
+    //std::cout << "Globbing for: " << gpath.c_str() << std::endl;
+    if ( cmSystemTools::SimpleGlob(gpath, gfiles, 1) )
+      {
+      size_t cc;
+      for ( cc = 0; cc < gfiles.size(); cc ++ )
+        {
+        gfiles[cc] = gfiles[cc].substr(glen);
+        //std::cout << "Glob file: " << gfiles[cc].c_str() << std::endl;
+        files.push_back(gfiles[cc]);
+        }
+      }
+    else
+      {
+      std::cout << "Problem globbing" << std::endl;
+      }
     }
   if ( this->CTestFileExists("Purify.xml") )
     {
     files.push_back("Purify.xml");
     }
   cmCTestSubmit submit;
+  submit.SetVerbose(m_Verbose);
   if ( m_DartConfiguration["DropMethod"] == "" ||
        m_DartConfiguration["DropMethod"] ==  "ftp" )
     {
@@ -1806,7 +1835,8 @@ int cmCTest::SubmitResults()
       m_DartConfiguration["DropSitePassword"] + "@" + 
       m_DartConfiguration["DropSite"] + 
       m_DartConfiguration["DropLocation"];
-    if ( !submit.SubmitUsingFTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, files, prefix, url) )
+    if ( !submit.SubmitUsingFTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, 
+        files, prefix, url) )
       {
       return 0;
       }
@@ -1838,6 +1868,7 @@ int cmCTest::SubmitResults()
       {
       return 0;
       }
+    std::cout << "Submission successfull" << std::endl;
     return 1;
     }
   else