@@ -2156,13 +2156,27 @@ void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed,
 
     if ( m_ShowOnly )
       {
-      fprintf(stderr,"%3d/%3d Testing %-30s\n", cnt, (int)tmsize, testname.c_str());
-      }
+      std::cerr.width(3);
+      std::cerr.setf(std::ios_base::right);
+      std::cerr << cnt << "/";
+      std::cerr.width(3);
+      std::cerr << tmsize << " Testing ";
+      std::string outname = testname;
+      outname.resize(30, ' ');
+      std::cerr << outname.c_str() << "\n";
+     }
     else
       {
-      fprintf(stderr,"%3d/%3d Testing %-30s ", cnt, (int)tmsize, testname.c_str());
-      fflush(stderr);
+      std::cerr.width(3);
+      std::cerr << cnt << "/";
+      std::cerr.width(3);
+      std::cerr << tmsize << " Testing ";
+      std::string outname = testname;
+      outname.resize(30, ' ');
+      std::cerr << outname.c_str();
+      std::cerr.flush();
       }
+    
     //std::cerr << "Testing " << args[0] << " ... ";
     // find the test executable
     std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());
@@ -2279,7 +2293,7 @@ void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed,
       {
       if (res == cmsysProcess_State_Exited && retVal == 0)
         {
-        fprintf(stderr,"   Passed\n");
+        std::cerr <<   "   Passed\n";
         passed.push_back(testname);
         cres.m_Status = cmCTest::COMPLETED;
         }
@@ -2288,44 +2302,44 @@ void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed,
         cres.m_Status = cmCTest::FAILED;
         if ( res == cmsysProcess_State_Expired )
           {
-          fprintf(stderr,"***Timeout\n");
+          std::cerr << "***Timeout\n";
           cres.m_Status = cmCTest::TIMEOUT;
           }
         else if ( res == cmsysProcess_State_Exception )
           {
-          fprintf(stderr,"***Exception: ");
+          std::cerr << "***Exception: ";
           switch ( retVal )
             {
           case cmsysProcess_Exception_Fault:
-            fprintf(stderr,"SegFault");
+            std::cerr << "SegFault";
             cres.m_Status = cmCTest::SEGFAULT;
             break;
           case cmsysProcess_Exception_Illegal:
-            fprintf(stderr,"Illegal");
+            std::cerr << "Illegal";
             cres.m_Status = cmCTest::ILLEGAL;
             break;
           case cmsysProcess_Exception_Interrupt:
-            fprintf(stderr,"Interrupt");
+            std::cerr << "Interrupt";
             cres.m_Status = cmCTest::INTERRUPT;
             break;
           case cmsysProcess_Exception_Numerical:
-            fprintf(stderr,"Numerical");
+            std::cerr << "Numerical";
             cres.m_Status = cmCTest::NUMERICAL;
             break;
           default:
-            fprintf(stderr,"Other");
+            std::cerr << "Other";
             cres.m_Status = cmCTest::OTHER_FAULT;
             }
-          fprintf(stderr,"\n");
+           std::cerr << "\n";
           }
         else if ( res == cmsysProcess_State_Error )
           {
-          fprintf(stderr,"***Bad command %d\n", res);
+          std::cerr << "***Bad command " << res << "\n";
           cres.m_Status = cmCTest::BAD_COMMAND;
           }
         else
           {
-          fprintf(stderr,"***Failed\n");
+          std::cerr << "***Failed\n";
           }
         failed.push_back(testname);
         }
@@ -4269,6 +4283,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       {
       i++;
       this->m_ConfigType = args[i];
+      cmSystemTools::ReplaceString(this->m_ConfigType, ".\\", "");
       }
 
     if( arg.find("-V",0) == 0 || arg.find("--verbose",0) == 0 )