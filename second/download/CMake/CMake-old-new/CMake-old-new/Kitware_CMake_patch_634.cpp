@@ -1713,7 +1713,6 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
           {
           std::cerr << "Unable to find executable: " << 
             args[1].Value.c_str() << "\n";
-          cres.m_Status = cmCTest::NOT_RUN;
           m_TestResults.push_back( cres );
           continue;
           }
@@ -1760,6 +1759,7 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
             }
           else
             {
+            cres.m_Status = cmCTest::FAILED;
             if ( res == cmsysProcess_State_Expired )
               {
               fprintf(stderr,"***Timeout\n");
@@ -2482,6 +2482,7 @@ const char* cmCTest::GetTestStatus(int status)
     "INTERRUPT",
     "NUMERICAL",
     "OTHER_FAULT",
+    "Failed",
     "BAD_COMMAND",
     "Completed"
   };