@@ -1750,7 +1750,7 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
 
         if ( !m_ShowOnly )
           {
-          if (res == cmsysProcess_State_Exited && retVal )
+          if (res == cmsysProcess_State_Exited && retVal == 0)
             {
             fprintf(stderr,"   Passed\n");
             passed.push_back(args[0].Value); 
@@ -1772,15 +1772,15 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
                 cres.m_Status = cmCTest::SEGFAULT;
                 break;
               case cmsysProcess_Exception_Illegal:
-                fprintf(stderr,"SegFault");
+                fprintf(stderr,"Illegal");
                 cres.m_Status = cmCTest::ILLEGAL;
                 break;
               case cmsysProcess_Exception_Interrupt:
-                fprintf(stderr,"SegFault");
+                fprintf(stderr,"Interrupt");
                 cres.m_Status = cmCTest::INTERRUPT;
                 break;
               case cmsysProcess_Exception_Numerical:
-                fprintf(stderr,"SegFault");
+                fprintf(stderr,"Numerical");
                 cres.m_Status = cmCTest::NUMERICAL;
                 break;
               default:
@@ -2324,21 +2324,25 @@ bool cmCTest::RunMakeCommand(const char* command, std::string* output,
     if ( output )
       {
       output->append(data, length);
-      while ( output->size() > (tick * tick_len) )
+      if ( !verbose )
         {
-        tick ++;
-        std::cout << "." << std::flush;
-        if ( tick % tick_line_len == 0 && tick > 0 )
+        while ( output->size() > (tick * tick_len) )
           {
-          std::cout << "  Size: ";
-          std::cout << int((output->size() / 1024.0) + 1) << "K" << std::endl;
-          std::cout << "    " << std::flush;
+          tick ++;
+          std::cout << "." << std::flush;
+          if ( tick % tick_line_len == 0 && tick > 0 )
+            {
+            std::cout << "  Size: ";
+            std::cout << int((output->size() / 1024.0) + 1) << "K" << std::endl;
+            std::cout << "    " << std::flush;
+            }
           }
         }
       }
     if(verbose)
       {
       std::cout.write(data, length);
+      std::cout.flush();
       }
     if ( ofs )
       {
@@ -2417,6 +2421,11 @@ int cmCTest::RunTest( const char* command, std::string* output, int *retVal)
       {
       output->append(data, length);
       }
+    if ( m_Verbose )
+      {
+      std::cout.write(data, length);
+      std::cout.flush();
+      }
     }
   
   cmsysProcess_WaitForExit(cp, 0);