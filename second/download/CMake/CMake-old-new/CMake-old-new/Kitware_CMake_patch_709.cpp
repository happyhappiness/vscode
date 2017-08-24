@@ -26,6 +26,9 @@
 
 #include <stdio.h>
 #include <time.h>
+#include <math.h>
+
+#define FIXNUM(x) ((isnan(x))?((0)):((isinf(x))?(0):(x)))
 
 #ifdef HAVE_CURL
 static struct tm* GetNightlyTime(std::string str)
@@ -1319,8 +1322,10 @@ int cmCTest::CoverageDirectory()
           {
           //std::cerr << "Compare -- " << cov.m_FullPath << std::endl;
           //std::cerr << "        -- " << src_dir << std::endl;
+          cov.m_Show = false;
           continue;
           }
+        cov.m_Show = true;
         }
       for ( cc = 0; cc < lines.size(); cc ++ )
         {
@@ -1362,6 +1367,11 @@ int cmCTest::CoverageDirectory()
   std::string local_end_time;
   for ( cit = coverageresults.begin(); cit != coverageresults.end(); cit ++ )
     {
+    cmCTest::cmCTestCoverage &cov = cit->second;
+    if ( !cov.m_Show )
+      {
+      continue;
+      }
     if ( ccount == 100 )
       {
       local_end_time = ::CurrentTime();
@@ -1392,7 +1402,6 @@ int cmCTest::CoverageDirectory()
       }
 
     //std::cerr << "Final process of Source file: " << cit->first << std::endl;
-    cmCTest::cmCTestCoverage &cov = cit->second;
 
 
     std::ifstream ifile(cov.m_AbsolutePath.c_str());
@@ -1411,7 +1420,7 @@ int cmCTest::CoverageDirectory()
     cmSystemTools::Split(buffer, lines);
     delete [] buffer;
     cfileoutput << "\t<File Name=\"" << cit->first << "\" FullPath=\""
-      << cov.m_FullPath << std::endl << "\">\n"
+      << cov.m_FullPath << "\">\n"
       << "\t\t<Report>" << std::endl;
     for ( cc = 0; cc < lines.size(); cc ++ )
       {
@@ -1428,24 +1437,26 @@ int cmCTest::CoverageDirectory()
     total_untested += cov.m_UnTested;
     float cper = 0;
     float cmet = 0;
-    if ( total_tested + total_untested > 0 )
+    if ( total_tested + total_untested > 0 && (cov.m_Tested + cov.m_UnTested) > 0)
       {
       cper = (100 * static_cast<float>(cov.m_Tested)/
         static_cast<float>(cov.m_Tested + cov.m_UnTested));
       cmet = ( static_cast<float>(cov.m_Tested + 10) /
         static_cast<float>(cov.m_Tested + cov.m_UnTested + 10));
       }
-    char cmbuff[100];
-    char cpbuff[100];
-    sprintf(cmbuff, "%.2f", cmet);
-    sprintf(cpbuff, "%.2f", cper);
 
     log << "\t<File Name=\"" << cit->first << "\" FullPath=\"" << cov.m_FullPath
       << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"
       << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"
       << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"
-      << "\t\t<PercentCoverage>" << cpbuff << "</PercentCoverage>\n"
-      << "\t\t<CoverageMetric>" << cmbuff << "</CoverageMetric>\n"
+      << "\t\t<PercentCoverage>";
+    log.setf(std::ios::fixed, std::ios::floatfield);
+    log.precision(2);
+    log << FIXNUM(cper) << "</PercentCoverage>\n"
+      << "\t\t<CoverageMetric>";
+    log.setf(std::ios::fixed, std::ios::floatfield);
+    log.precision(2);
+    log << FIXNUM(cmet) << "</CoverageMetric>\n"
       << "\t</File>" << std::endl;
     ccount ++;
     }
@@ -1468,21 +1479,26 @@ int cmCTest::CoverageDirectory()
     }
 
   std::string end_time = ::CurrentTime();
-  char buffer[100];
-  sprintf(buffer, "%.2f", percent_coverage);
 
   log << "\t<LOCTested>" << total_tested << "</LOCTested>\n"
       << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"
       << "\t<LOC>" << total_lines << "</LOC>\n"
-      << "\t<PercentCoverage>" << buffer << "</PercentCoverage>\n"
+      << "\t<PercentCoverage>";
+  log.setf(std::ios::fixed, std::ios::floatfield);
+  log.precision(2);
+  log << FIXNUM(percent_coverage)<< "</PercentCoverage>\n"
       << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"
       << "</Coverage>\n"
       << "</Site>" << std::endl;
 
   std::cout << "\tCovered LOC:         " << total_tested << std::endl
             << "\tNot covered LOC:     " << total_untested << std::endl
             << "\tTotal LOC:           " << total_lines << std::endl
-            << "\tPercentage Coverage: " << percent_coverage << "%" << std::endl;
+            << "\tPercentage Coverage: ";
+
+  std::cout.setf(std::ios::fixed, std::ios::floatfield);
+  std::cout.precision(2);
+  std::cout << FIXNUM(percent_coverage) << "%" << std::endl;
 
 
   return 1;