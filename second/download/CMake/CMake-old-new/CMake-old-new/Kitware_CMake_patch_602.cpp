@@ -9,8 +9,8 @@ Version:   $Revision$
 Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
 See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
-This software is distributed WITHOUT ANY WARRANTY; without even 
-the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+This software is distributed WITHOUT ANY WARRANTY; without even
+the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
@@ -36,21 +36,25 @@ PURPOSE.  See the above copyright notices for more information.
 typedef std::vector<char> cmCTestSubmitHandlerVectorOfChar;
 
 static size_t
-cmCTestSubmitHandlerWriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data)
+cmCTestSubmitHandlerWriteMemoryCallback(void *ptr, size_t size, size_t nmemb,
+  void *data)
 {
   register int realsize = size * nmemb;
 
-  cmCTestSubmitHandlerVectorOfChar *vec = static_cast<cmCTestSubmitHandlerVectorOfChar*>(data);
+  cmCTestSubmitHandlerVectorOfChar *vec
+    = static_cast<cmCTestSubmitHandlerVectorOfChar*>(data);
   const char* chPtr = static_cast<char*>(ptr);
   vec->insert(vec->end(), chPtr, chPtr + realsize);
 
   return realsize;
 }
 
 static size_t
-cmCTestSubmitHandlerCurlDebugCallback(CURL *, curl_infotype, char *chPtr, size_t size, void *data)
+cmCTestSubmitHandlerCurlDebugCallback(CURL *, curl_infotype, char *chPtr,
+  size_t size, void *data)
 {
-  cmCTestSubmitHandlerVectorOfChar *vec = static_cast<cmCTestSubmitHandlerVectorOfChar*>(data);
+  cmCTestSubmitHandlerVectorOfChar *vec
+    = static_cast<cmCTestSubmitHandlerVectorOfChar*>(data);
   vec->insert(vec->end(), chPtr, chPtr + size);
 
   return size;
@@ -80,9 +84,9 @@ void cmCTestSubmitHandler::Initialize()
 }
 
 //----------------------------------------------------------------------------
-bool cmCTestSubmitHandler::SubmitUsingFTP(const cmStdString& localprefix, 
+bool cmCTestSubmitHandler::SubmitUsingFTP(const cmStdString& localprefix,
   const std::set<cmStdString>& files,
-  const cmStdString& remoteprefix, 
+  const cmStdString& remoteprefix,
   const cmStdString& url)
 {
   CURL *curl;
@@ -98,12 +102,12 @@ bool cmCTestSubmitHandler::SubmitUsingFTP(const cmStdString& localprefix,
     {
     /* get a curl handle */
     curl = curl_easy_init();
-    if(curl) 
+    if(curl)
       {
       // Using proxy
       if ( m_FTPProxyType > 0 )
         {
-        curl_easy_setopt(curl, CURLOPT_PROXY, m_FTPProxy.c_str()); 
+        curl_easy_setopt(curl, CURLOPT_PROXY, m_FTPProxy.c_str());
         switch (m_FTPProxyType)
           {
         case 2:
@@ -113,7 +117,7 @@ bool cmCTestSubmitHandler::SubmitUsingFTP(const cmStdString& localprefix,
           curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
           break;
         default:
-          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);           
+          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
           }
         }
 
@@ -125,21 +129,24 @@ bool cmCTestSubmitHandler::SubmitUsingFTP(const cmStdString& localprefix,
         {
         local_file = localprefix + "/" + *file;
         }
-      cmStdString upload_as = url + "/" + remoteprefix + cmSystemTools::GetFilenameName(*file);
+      cmStdString upload_as
+        = url + "/" + remoteprefix + cmSystemTools::GetFilenameName(*file);
 
       struct stat st;
       if ( ::stat(local_file.c_str(), &st) )
         {
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Cannot find file: " << local_file.c_str() << std::endl);
+        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Cannot find file: "
+          << local_file.c_str() << std::endl);
         ::curl_easy_cleanup(curl);
-        ::curl_global_cleanup(); 
+        ::curl_global_cleanup();
         return false;
         }
 
       ftpfile = ::fopen(local_file.c_str(), "rb");
       *m_LogFile << "\tUpload file: " << local_file.c_str() << " to "
           << upload_as.c_str() << std::endl;
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   Upload file: " << local_file.c_str() << " to " 
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   Upload file: "
+        << local_file.c_str() << " to "
         << upload_as.c_str() << std::endl);
 
       ::curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
@@ -151,14 +158,17 @@ bool cmCTestSubmitHandler::SubmitUsingFTP(const cmStdString& localprefix,
       ::curl_easy_setopt(curl, CURLOPT_INFILE, ftpfile);
 
       // and give the size of the upload (optional)
-      ::curl_easy_setopt(curl, CURLOPT_INFILESIZE, static_cast<long>(st.st_size));
+      ::curl_easy_setopt(curl, CURLOPT_INFILESIZE,
+        static_cast<long>(st.st_size));
 
       // and give curl the buffer for errors
       ::curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &error_buffer);
 
       // specify handler for output
-      ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cmCTestSubmitHandlerWriteMemoryCallback);
-      ::curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, cmCTestSubmitHandlerCurlDebugCallback);
+      ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
+        cmCTestSubmitHandlerWriteMemoryCallback);
+      ::curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION,
+        cmCTestSubmitHandlerCurlDebugCallback);
 
       /* we pass our 'chunk' struct to the callback function */
       cmCTestSubmitHandlerVectorOfChar chunk;
@@ -172,42 +182,50 @@ bool cmCTestSubmitHandler::SubmitUsingFTP(const cmStdString& localprefix,
       if ( chunk.size() > 0 )
         {
         cmCTestLog(m_CTest, DEBUG, "CURL output: ["
-          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]" << std::endl);
+          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]"
+          << std::endl);
         }
       if ( chunkDebug.size() > 0 )
         {
         cmCTestLog(m_CTest, DEBUG, "CURL debug output: ["
-          << cmCTestLogWrite(&*chunkDebug.begin(), chunkDebug.size()) << "]" << std::endl);
+          << cmCTestLogWrite(&*chunkDebug.begin(), chunkDebug.size()) << "]"
+          << std::endl);
         }
 
       fclose(ftpfile);
       if ( res )
         {
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error when uploading file: " << local_file.c_str() << std::endl);
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error message was: " << error_buffer << std::endl);
-        *m_LogFile << "   Error when uploading file: " << local_file.c_str() << std::endl
+        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error when uploading file: "
+          << local_file.c_str() << std::endl);
+        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error message was: "
+          << error_buffer << std::endl);
+        *m_LogFile << "   Error when uploading file: " << local_file.c_str()
+          << std::endl
           << "   Error message was: " << error_buffer << std::endl
-          << "   Curl output was: " << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << std::endl;
+          << "   Curl output was: "
+          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << std::endl;
         cmCTestLog(m_CTest, ERROR_MESSAGE, "CURL output: ["
-          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]" << std::endl);
+          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]"
+          << std::endl);
         ::curl_easy_cleanup(curl);
-        ::curl_global_cleanup(); 
+        ::curl_global_cleanup();
         return false;
         }
       // always cleanup
       ::curl_easy_cleanup(curl);
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Uploaded: " + local_file << std::endl);
+      cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Uploaded: " + local_file
+        << std::endl);
       }
     }
-  ::curl_global_cleanup(); 
+  ::curl_global_cleanup();
   return true;
 }
 
 //----------------------------------------------------------------------------
 // Uploading files is simpler
-bool cmCTestSubmitHandler::SubmitUsingHTTP(const cmStdString& localprefix, 
+bool cmCTestSubmitHandler::SubmitUsingHTTP(const cmStdString& localprefix,
   const std::set<cmStdString>& files,
-  const cmStdString& remoteprefix, 
+  const cmStdString& remoteprefix,
   const cmStdString& url)
 {
   CURL *curl;
@@ -224,13 +242,13 @@ bool cmCTestSubmitHandler::SubmitUsingHTTP(const cmStdString& localprefix,
     {
     /* get a curl handle */
     curl = curl_easy_init();
-    if(curl) 
+    if(curl)
       {
 
       // Using proxy
       if ( m_HTTPProxyType > 0 )
         {
-        curl_easy_setopt(curl, CURLOPT_PROXY, m_HTTPProxy.c_str()); 
+        curl_easy_setopt(curl, CURLOPT_PROXY, m_HTTPProxy.c_str());
         switch (m_HTTPProxyType)
           {
         case 2:
@@ -261,7 +279,8 @@ bool cmCTestSubmitHandler::SubmitUsingHTTP(const cmStdString& localprefix,
         {
         local_file = localprefix + "/" + *file;
         }
-      cmStdString remote_file = remoteprefix + cmSystemTools::GetFilenameName(*file);
+      cmStdString remote_file
+        = remoteprefix + cmSystemTools::GetFilenameName(*file);
 
       *m_LogFile << "\tUpload file: " << local_file.c_str() << " to "
           << remote_file.c_str() << std::endl;
@@ -285,25 +304,27 @@ bool cmCTestSubmitHandler::SubmitUsingHTTP(const cmStdString& localprefix,
           sprintf(hexCh, "%%%02X", (int)c);
           ofile.append(hexCh);
           break;
-        default: 
+        default:
           ofile.append(hexCh);
           }
         }
-      cmStdString upload_as 
-        = url + ((url.find("?",0) == cmStdString::npos) ? "?" : "&") 
+      cmStdString upload_as
+        = url + ((url.find("?",0) == cmStdString::npos) ? "?" : "&")
         + "FileName=" + ofile;
 
       struct stat st;
       if ( ::stat(local_file.c_str(), &st) )
         {
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Cannot find file: " << local_file.c_str() << std::endl);
+        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Cannot find file: "
+          << local_file.c_str() << std::endl);
         ::curl_easy_cleanup(curl);
-        ::curl_global_cleanup(); 
+        ::curl_global_cleanup();
         return false;
         }
 
       ftpfile = ::fopen(local_file.c_str(), "rb");
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   Upload file: " << local_file.c_str() << " to " 
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   Upload file: "
+        << local_file.c_str() << " to "
         << upload_as.c_str() << " Size: " << st.st_size << std::endl);
 
 
@@ -314,14 +335,17 @@ bool cmCTestSubmitHandler::SubmitUsingHTTP(const cmStdString& localprefix,
       ::curl_easy_setopt(curl, CURLOPT_INFILE, ftpfile);
 
       // and give the size of the upload (optional)
-      ::curl_easy_setopt(curl, CURLOPT_INFILESIZE, static_cast<long>(st.st_size));
+      ::curl_easy_setopt(curl, CURLOPT_INFILESIZE,
+        static_cast<long>(st.st_size));
 
       // and give curl the buffer for errors
       ::curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &error_buffer);
 
       // specify handler for output
-      ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cmCTestSubmitHandlerWriteMemoryCallback);
-      ::curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, cmCTestSubmitHandlerCurlDebugCallback);
+      ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
+        cmCTestSubmitHandlerWriteMemoryCallback);
+      ::curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION,
+        cmCTestSubmitHandlerCurlDebugCallback);
 
       /* we pass our 'chunk' struct to the callback function */
       cmCTestSubmitHandlerVectorOfChar chunk;
@@ -335,40 +359,49 @@ bool cmCTestSubmitHandler::SubmitUsingHTTP(const cmStdString& localprefix,
       if ( chunk.size() > 0 )
         {
         cmCTestLog(m_CTest, DEBUG, "CURL output: ["
-          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]" << std::endl);
+          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]"
+          << std::endl);
         }
       if ( chunkDebug.size() > 0 )
         {
         cmCTestLog(m_CTest, DEBUG, "CURL debug output: ["
-          << cmCTestLogWrite(&*chunkDebug.begin(), chunkDebug.size()) << "]" << std::endl);
+          << cmCTestLogWrite(&*chunkDebug.begin(), chunkDebug.size()) << "]"
+          << std::endl);
         }
 
       fclose(ftpfile);
       if ( res )
         {
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error when uploading file: " << local_file.c_str() << std::endl);
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error message was: " << error_buffer << std::endl);
-        *m_LogFile << "   Error when uploading file: " << local_file.c_str() << std::endl
+        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error when uploading file: "
+          << local_file.c_str() << std::endl);
+        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error message was: "
+          << error_buffer << std::endl);
+        *m_LogFile << "   Error when uploading file: " << local_file.c_str()
+          << std::endl
           << "   Error message was: " << error_buffer << std::endl
-          << "   Curl output was: " << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << std::endl;
+          << "   Curl output was: "
+          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << std::endl;
         cmCTestLog(m_CTest, ERROR_MESSAGE, "CURL output: ["
-          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]" << std::endl);
+          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]"
+          << std::endl);
         ::curl_easy_cleanup(curl);
-        ::curl_global_cleanup(); 
+        ::curl_global_cleanup();
         return false;
         }
       // always cleanup
       ::curl_easy_cleanup(curl);
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Uploaded: " + local_file << std::endl);
+      cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Uploaded: " + local_file
+        << std::endl);
       }
     }
-  ::curl_global_cleanup(); 
+  ::curl_global_cleanup();
   return true;
 }
 
 //----------------------------------------------------------------------------
-bool cmCTestSubmitHandler::TriggerUsingHTTP(const std::set<cmStdString>& files,
-  const cmStdString& remoteprefix, 
+bool cmCTestSubmitHandler::TriggerUsingHTTP(
+  const std::set<cmStdString>& files,
+  const cmStdString& remoteprefix,
   const cmStdString& url)
 {
   CURL *curl;
@@ -382,12 +415,12 @@ bool cmCTestSubmitHandler::TriggerUsingHTTP(const std::set<cmStdString>& files,
     {
     /* get a curl handle */
     curl = curl_easy_init();
-    if(curl) 
+    if(curl)
       {
       // Using proxy
       if ( m_HTTPProxyType > 0 )
         {
-        curl_easy_setopt(curl, CURLOPT_PROXY, m_HTTPProxy.c_str()); 
+        curl_easy_setopt(curl, CURLOPT_PROXY, m_HTTPProxy.c_str());
         switch (m_HTTPProxyType)
           {
         case 2:
@@ -397,7 +430,7 @@ bool cmCTestSubmitHandler::TriggerUsingHTTP(const std::set<cmStdString>& files,
           curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
           break;
         default:
-          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);           
+          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);
           if (m_HTTPProxyAuth.size() > 0)
             {
             curl_easy_setopt(curl, CURLOPT_PROXYUSERPWD,
@@ -412,16 +445,19 @@ bool cmCTestSubmitHandler::TriggerUsingHTTP(const std::set<cmStdString>& files,
       ::curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, &error_buffer);
 
       // specify handler for output
-      ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cmCTestSubmitHandlerWriteMemoryCallback);
-      ::curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, cmCTestSubmitHandlerCurlDebugCallback);
+      ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,
+        cmCTestSubmitHandlerWriteMemoryCallback);
+      ::curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION,
+        cmCTestSubmitHandlerCurlDebugCallback);
 
       /* we pass our 'chunk' struct to the callback function */
       cmCTestSubmitHandlerVectorOfChar chunk;
       cmCTestSubmitHandlerVectorOfChar chunkDebug;
       ::curl_easy_setopt(curl, CURLOPT_FILE, (void *)&chunk);
       ::curl_easy_setopt(curl, CURLOPT_DEBUGDATA, (void *)&chunkDebug);
 
-      cmStdString rfile = remoteprefix + cmSystemTools::GetFilenameName(*file);
+      cmStdString rfile
+        = remoteprefix + cmSystemTools::GetFilenameName(*file);
       cmStdString ofile = "";
       cmStdString::iterator kk;
       for ( kk = rfile.begin(); kk < rfile.end(); ++ kk)
@@ -442,57 +478,66 @@ bool cmCTestSubmitHandler::TriggerUsingHTTP(const std::set<cmStdString>& files,
           sprintf(hexCh, "%%%02X", (int)c);
           ofile.append(hexCh);
           break;
-        default: 
+        default:
           ofile.append(hexCh);
           }
         }
-      cmStdString turl 
-        = url + ((url.find("?",0) == cmStdString::npos) ? "?" : "&") 
+      cmStdString turl
+        = url + ((url.find("?",0) == cmStdString::npos) ? "?" : "&")
         + "xmlfile=" + ofile;
       *m_LogFile << "Trigger url: " << turl.c_str() << std::endl;
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   Trigger url: " << turl.c_str() << std::endl);
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   Trigger url: "
+        << turl.c_str() << std::endl);
       curl_easy_setopt(curl, CURLOPT_URL, turl.c_str());
       if ( curl_easy_perform(curl) )
         {
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error when triggering: " << turl.c_str() << std::endl);
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error message was: " << error_buffer << std::endl);
-        *m_LogFile << "\tTrigerring failed with error: " << error_buffer << std::endl
+        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error when triggering: "
+          << turl.c_str() << std::endl);
+        cmCTestLog(m_CTest, ERROR_MESSAGE, "   Error message was: "
+          << error_buffer << std::endl);
+        *m_LogFile << "\tTrigerring failed with error: " << error_buffer
+          << std::endl
           << "   Error message was: " << error_buffer << std::endl
-          << "   Curl output was: " << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << std::endl;
+          << "   Curl output was: "
+          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << std::endl;
         cmCTestLog(m_CTest, ERROR_MESSAGE, "CURL output: ["
-          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]" << std::endl);
+          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]"
+          << std::endl);
         ::curl_easy_cleanup(curl);
-        ::curl_global_cleanup(); 
+        ::curl_global_cleanup();
         return false;
         }
 
       if ( chunk.size() > 0 )
         {
         cmCTestLog(m_CTest, DEBUG, "CURL output: ["
-          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]" << std::endl);
+          << cmCTestLogWrite(&*chunk.begin(), chunk.size()) << "]"
+          << std::endl);
         }
       if ( chunkDebug.size() > 0 )
         {
         cmCTestLog(m_CTest, DEBUG, "CURL debug output: ["
-          << cmCTestLogWrite(&*chunkDebug.begin(), chunkDebug.size()) << "]" << std::endl);
+          << cmCTestLogWrite(&*chunkDebug.begin(), chunkDebug.size())
+          << "]" << std::endl);
         }
 
       // always cleanup
       ::curl_easy_cleanup(curl);
       cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl);
       }
     }
-  ::curl_global_cleanup(); 
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Dart server triggered..." << std::endl);
+  ::curl_global_cleanup();
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Dart server triggered..."
+    << std::endl);
   return true;
 }
 
 //----------------------------------------------------------------------------
 bool cmCTestSubmitHandler::SubmitUsingSCP(
-  const cmStdString& scp_command, 
-  const cmStdString& localprefix, 
+  const cmStdString& scp_command,
+  const cmStdString& localprefix,
   const std::set<cmStdString>& files,
-  const cmStdString& remoteprefix, 
+  const cmStdString& remoteprefix,
   const cmStdString& url)
 {
   if ( !scp_command.size() || !localprefix.size() ||
@@ -524,9 +569,10 @@ bool cmCTestSubmitHandler::SubmitUsingSCP(
     argv[1] = lfname.c_str();
     std::string rfname = url + "/" + remoteprefix + *file;
     argv[2] = rfname.c_str();
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Execute \"" << argv[0] << "\" \"" << argv[1] << "\" \"" 
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Execute \"" << argv[0]
+      << "\" \"" << argv[1] << "\" \""
       << argv[2] << "\"" << std::endl);
-    *m_LogFile << "Execute \"" << argv[0] << "\" \"" << argv[1] << "\" \"" 
+    *m_LogFile << "Execute \"" << argv[0] << "\" \"" << argv[1] << "\" \""
       << argv[2] << "\"" << std::endl;
 
     cmsysProcess_SetCommand(cp, &*argv.begin());
@@ -536,7 +582,8 @@ bool cmCTestSubmitHandler::SubmitUsingSCP(
 
     while(cmsysProcess_WaitForData(cp, &data, &length, 0))
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, cmCTestLogWrite(data, length));
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+        cmCTestLogWrite(data, length));
       }
 
     cmsysProcess_WaitForExit(cp, 0);
@@ -548,24 +595,27 @@ bool cmCTestSubmitHandler::SubmitUsingSCP(
       retVal = cmsysProcess_GetExitValue(cp);
       if ( retVal != 0 )
         {
-        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "\tSCP returned: " << retVal << std::endl);
+        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "\tSCP returned: "
+          << retVal << std::endl);
         *m_LogFile << "\tSCP returned: " << retVal << std::endl;
         problems ++;
         }
       }
     else if(result == cmsysProcess_State_Exception)
       {
       retVal = cmsysProcess_GetExitException(cp);
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "\tThere was an exception: " << retVal << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "\tThere was an exception: "
+        << retVal << std::endl);
       *m_LogFile << "\tThere was an exception: " << retVal << std::endl;
       problems ++;
       }
     else if(result == cmsysProcess_State_Expired)
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "\tThere was a timeout" << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "\tThere was a timeout"
+        << std::endl);
       *m_LogFile << "\tThere was a timeout" << std::endl;
       problems ++;
-      } 
+      }
     else if(result == cmsysProcess_State_Error)
       {
       cmCTestLog(m_CTest, ERROR_MESSAGE, "\tError executing SCP: "
@@ -584,9 +634,9 @@ bool cmCTestSubmitHandler::SubmitUsingSCP(
 }
 
 //----------------------------------------------------------------------------
-bool cmCTestSubmitHandler::SubmitUsingXMLRPC(const cmStdString& localprefix, 
+bool cmCTestSubmitHandler::SubmitUsingXMLRPC(const cmStdString& localprefix,
   const std::set<cmStdString>& files,
-  const cmStdString& remoteprefix, 
+  const cmStdString& remoteprefix,
   const cmStdString& url)
 {
   xmlrpc_env env;
@@ -601,7 +651,8 @@ bool cmCTestSubmitHandler::SubmitUsingXMLRPC(const cmStdString& localprefix,
   xmlrpc_env_init(&env);
 
   /* Call the famous server at UserLand. */
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submitting to: " << realURL.c_str() << " (" << remoteprefix.c_str() << ")" << std::endl);
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submitting to: "
+    << realURL.c_str() << " (" << remoteprefix.c_str() << ")" << std::endl);
   cmCTest::tm_SetOfStrings::const_iterator file;
   for ( file = files.begin(); file != files.end(); ++file )
     {
@@ -612,19 +663,22 @@ bool cmCTestSubmitHandler::SubmitUsingXMLRPC(const cmStdString& localprefix,
       {
       local_file = localprefix + "/" + *file;
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submit file: " << local_file.c_str() << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submit file: "
+      << local_file.c_str() << std::endl);
     struct stat st;
     if ( ::stat(local_file.c_str(), &st) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "  Cannot find file: " << local_file.c_str() << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "  Cannot find file: "
+        << local_file.c_str() << std::endl);
       return false;
       }
 
     size_t fileSize = st.st_size;
     FILE* fp = fopen(local_file.c_str(), "rb");
     if ( !fp )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "  Cannot open file: " << local_file.c_str() << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "  Cannot open file: "
+        << local_file.c_str() << std::endl);
       return false;
       }
 
@@ -633,7 +687,8 @@ bool cmCTestSubmitHandler::SubmitUsingXMLRPC(const cmStdString& localprefix,
       {
       delete [] fileBuffer;
       fclose(fp);
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "  Cannot read file: " << local_file.c_str() << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "  Cannot read file: "
+        << local_file.c_str() << std::endl);
       return false;
       }
     fclose(fp);
@@ -647,7 +702,8 @@ bool cmCTestSubmitHandler::SubmitUsingXMLRPC(const cmStdString& localprefix,
 
     if ( env.fault_occurred )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, " Submission problem: " << env.fault_string << " (" << env.fault_code << ")" << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, " Submission problem: "
+        << env.fault_string << " (" << env.fault_code << ")" << std::endl);
       xmlrpc_env_clean(&env);
       xmlrpc_client_cleanup();
       return false;
@@ -668,10 +724,13 @@ bool cmCTestSubmitHandler::SubmitUsingXMLRPC(const cmStdString& localprefix,
 //----------------------------------------------------------------------------
 int cmCTestSubmitHandler::ProcessHandler()
 {
-  const std::string &buildDirectory = m_CTest->GetCTestConfiguration("BuildDirectory");
+  const std::string &buildDirectory
+    = m_CTest->GetCTestConfiguration("BuildDirectory");
   if ( buildDirectory.size() == 0 )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot find BuildDirectory  key in the DartConfiguration.tcl" << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE,
+      "Cannot find BuildDirectory  key in the DartConfiguration.tcl"
+      << std::endl);
     return -1;
     }
 
@@ -742,11 +801,13 @@ int cmCTestSubmitHandler::ProcessHandler()
 
   if ( m_HTTPProxy.size() > 0 )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Use HTTP Proxy: " << m_HTTPProxy << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Use HTTP Proxy: " << m_HTTPProxy
+      << std::endl);
     }
   if ( m_FTPProxy.size() > 0 )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Use FTP Proxy: " << m_FTPProxy << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Use FTP Proxy: " << m_FTPProxy
+      << std::endl);
     }
   cmGeneratedFileStream ofs;
   this->StartLogFile("Submit", ofs);
@@ -762,17 +823,20 @@ int cmCTestSubmitHandler::ProcessHandler()
   if ( m_CTest->AddIfExists(files, "Coverage.xml") )
     {
     cmCTest::tm_VectorOfStrings gfiles;
-    std::string gpath = buildDirectory + "/Testing/" + m_CTest->GetCurrentTag();
+    std::string gpath
+      = buildDirectory + "/Testing/" + m_CTest->GetCurrentTag();
     std::string::size_type glen = gpath.size() + 1;
     gpath = gpath + "/CoverageLog*";
-    cmCTestLog(m_CTest, DEBUG, "Globbing for: " << gpath.c_str() << std::endl);
+    cmCTestLog(m_CTest, DEBUG, "Globbing for: " << gpath.c_str()
+      << std::endl);
     if ( cmSystemTools::SimpleGlob(gpath, gfiles, 1) )
       {
       size_t cc;
       for ( cc = 0; cc < gfiles.size(); cc ++ )
         {
         gfiles[cc] = gfiles[cc].substr(glen);
-        cmCTestLog(m_CTest, DEBUG, "Glob file: " << gfiles[cc].c_str() << std::endl);
+        cmCTestLog(m_CTest, DEBUG, "Glob file: " << gfiles[cc].c_str()
+          << std::endl);
         files.insert(gfiles[cc]);
         }
       }
@@ -803,60 +867,75 @@ int cmCTestSubmitHandler::ProcessHandler()
       cnt ++;
       }
     }
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "Submit files (using " << m_CTest->GetCTestConfiguration("DropMethod") << ")"
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, "Submit files (using "
+    << m_CTest->GetCTestConfiguration("DropMethod") << ")"
     << std::endl);
   this->SetLogFile(&ofs);
   if ( m_CTest->GetCTestConfiguration("DropMethod") == "" ||
     m_CTest->GetCTestConfiguration("DropMethod") ==  "ftp" )
     {
     ofs << "Using drop method: FTP" << std::endl;
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Using FTP submit method" << std::endl
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Using FTP submit method"
+      << std::endl
       << "   Drop site: ftp://");
     std::string url = "ftp://";
-    url += cmCTest::MakeURLSafe(m_CTest->GetCTestConfiguration("DropSiteUser")) + ":" + 
-      cmCTest::MakeURLSafe(m_CTest->GetCTestConfiguration("DropSitePassword")) + "@" + 
-      m_CTest->GetCTestConfiguration("DropSite") + 
+    url += cmCTest::MakeURLSafe(
+      m_CTest->GetCTestConfiguration("DropSiteUser")) + ":" +
+      cmCTest::MakeURLSafe(m_CTest->GetCTestConfiguration(
+          "DropSitePassword")) + "@" +
+      m_CTest->GetCTestConfiguration("DropSite") +
       cmCTest::MakeURLSafe(m_CTest->GetCTestConfiguration("DropLocation"));
     if ( m_CTest->GetCTestConfiguration("DropSiteUser").size() > 0 )
       {
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, m_CTest->GetCTestConfiguration("DropSiteUser").c_str());
+      cmCTestLog(m_CTest, HANDLER_OUTPUT, m_CTest->GetCTestConfiguration(
+          "DropSiteUser").c_str());
       if ( m_CTest->GetCTestConfiguration("DropSitePassword").size() > 0 )
         {
         cmCTestLog(m_CTest, HANDLER_OUTPUT, ":******");
         }
       cmCTestLog(m_CTest, HANDLER_OUTPUT, "@");
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, m_CTest->GetCTestConfiguration("DropSite")
+    cmCTestLog(m_CTest, HANDLER_OUTPUT,
+      m_CTest->GetCTestConfiguration("DropSite")
       << m_CTest->GetCTestConfiguration("DropLocation") << std::endl);
-    if ( !this->SubmitUsingFTP(buildDirectory+"/Testing/"+m_CTest->GetCurrentTag(), 
+    if ( !this->SubmitUsingFTP(buildDirectory + "/Testing/"
+        + m_CTest->GetCurrentTag(),
         files, prefix, url) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "   Problems when submitting via FTP" << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "   Problems when submitting via FTP"
+        << std::endl);
       ofs << "   Problems when submitting via FTP" << std::endl;
       return -1;
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Using HTTP trigger method" << std::endl
-      << "   Trigger site: " << m_CTest->GetCTestConfiguration("TriggerSite") << std::endl);
-    if ( !this->TriggerUsingHTTP(files, prefix, m_CTest->GetCTestConfiguration("TriggerSite")) )
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Using HTTP trigger method"
+      << std::endl
+      << "   Trigger site: " << m_CTest->GetCTestConfiguration("TriggerSite")
+      << std::endl);
+    if ( !this->TriggerUsingHTTP(files, prefix,
+        m_CTest->GetCTestConfiguration("TriggerSite")) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "   Problems when triggering via HTTP" << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE,
+        "   Problems when triggering via HTTP" << std::endl);
       ofs << "   Problems when triggering via HTTP" << std::endl;
       return -1;
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submission successful" << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submission successful"
+      << std::endl);
     ofs << "   Submission successful" << std::endl;
     return 0;
     }
   else if ( m_CTest->GetCTestConfiguration("DropMethod") == "http" )
     {
     ofs << "Using drop method: HTTP" << std::endl;
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Using HTTP submit method" << std::endl
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Using HTTP submit method"
+      << std::endl
       << "   Drop site: http://");
     std::string url = "http://";
     if ( m_CTest->GetCTestConfiguration("DropSiteUser").size() > 0 )
       {
       url += m_CTest->GetCTestConfiguration("DropSiteUser");
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, m_CTest->GetCTestConfiguration("DropSiteUser").c_str());
+      cmCTestLog(m_CTest, HANDLER_OUTPUT,
+        m_CTest->GetCTestConfiguration("DropSiteUser").c_str());
       if ( m_CTest->GetCTestConfiguration("DropSitePassword").size() > 0 )
         {
         url += ":" + m_CTest->GetCTestConfiguration("DropSitePassword");
@@ -865,40 +944,53 @@ int cmCTestSubmitHandler::ProcessHandler()
       url += "@";
       cmCTestLog(m_CTest, HANDLER_OUTPUT, "@");
       }
-    url += m_CTest->GetCTestConfiguration("DropSite") + m_CTest->GetCTestConfiguration("DropLocation");
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, m_CTest->GetCTestConfiguration("DropSite")
+    url += m_CTest->GetCTestConfiguration("DropSite") +
+      m_CTest->GetCTestConfiguration("DropLocation");
+    cmCTestLog(m_CTest, HANDLER_OUTPUT,
+      m_CTest->GetCTestConfiguration("DropSite")
       << m_CTest->GetCTestConfiguration("DropLocation") << std::endl);
-    if ( !this->SubmitUsingHTTP(buildDirectory +"/Testing/"+m_CTest->GetCurrentTag(), files, prefix, url) )
+    if ( !this->SubmitUsingHTTP(buildDirectory + "/Testing/" +
+        m_CTest->GetCurrentTag(), files, prefix, url) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "   Problems when submitting via HTTP" << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE,
+        "   Problems when submitting via HTTP" << std::endl);
       ofs << "   Problems when submitting via HTTP" << std::endl;
       return -1;
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Using HTTP trigger method" << std::endl
-      << "   Trigger site: " << m_CTest->GetCTestConfiguration("TriggerSite") << std::endl);
-    if ( !this->TriggerUsingHTTP(files, prefix, m_CTest->GetCTestConfiguration("TriggerSite")) )
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Using HTTP trigger method"
+      << std::endl
+      << "   Trigger site: " << m_CTest->GetCTestConfiguration("TriggerSite")
+      << std::endl);
+    if ( !this->TriggerUsingHTTP(files, prefix,
+        m_CTest->GetCTestConfiguration("TriggerSite")) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "   Problems when triggering via HTTP" << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE,
+        "   Problems when triggering via HTTP" << std::endl);
       ofs << "   Problems when triggering via HTTP" << std::endl;
       return -1;
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submission successful" << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submission successful"
+      << std::endl);
     ofs << "   Submission successful" << std::endl;
     return 0;
     }
   else if ( m_CTest->GetCTestConfiguration("DropMethod") == "xmlrpc" )
     {
     ofs << "Using drop method: XML-RPC" << std::endl;
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Using XML-RPC submit method" << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Using XML-RPC submit method"
+      << std::endl);
     std::string url = m_CTest->GetCTestConfiguration("DropSite");
     prefix = m_CTest->GetCTestConfiguration("DropLocation");
-    if ( !this->SubmitUsingXMLRPC(buildDirectory+"/Testing/"+m_CTest->GetCurrentTag(), files, prefix, url) )
+    if ( !this->SubmitUsingXMLRPC(buildDirectory + "/Testing/" +
+        m_CTest->GetCurrentTag(), files, prefix, url) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "   Problems when submitting via XML-RPC" << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE,
+        "   Problems when submitting via XML-RPC" << std::endl);
       ofs << "   Problems when submitting via XML-RPC" << std::endl;
       return -1;
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submission successful" << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submission successful"
+      << std::endl);
     ofs << "   Submission successful" << std::endl;
     return 0;
     }
@@ -910,7 +1002,8 @@ int cmCTestSubmitHandler::ProcessHandler()
       {
       url += m_CTest->GetCTestConfiguration("DropSiteUser") + "@";
       }
-    url += m_CTest->GetCTestConfiguration("DropSite") + ":" + m_CTest->GetCTestConfiguration("DropLocation");
+    url += m_CTest->GetCTestConfiguration("DropSite") + ":" +
+      m_CTest->GetCTestConfiguration("DropLocation");
 
     // change to the build directory so that we can uses a relative path
     // on windows since scp dosn't support "c:" a drive in the path
@@ -921,17 +1014,20 @@ int cmCTestSubmitHandler::ProcessHandler()
         "Testing/"+m_CTest->GetCurrentTag(), files, prefix, url) )
       {
       cmSystemTools::ChangeDirectory(oldWorkingDirectory.c_str());
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "   Problems when submitting via SCP" << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "   Problems when submitting via SCP"
+        << std::endl);
       ofs << "   Problems when submitting via SCP" << std::endl;
       return -1;
       }
     cmSystemTools::ChangeDirectory(oldWorkingDirectory.c_str());
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submission successful" << std::endl);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Submission successful"
+      << std::endl);
     ofs << "   Submission successful" << std::endl;
     return 0;
     }
 
-  cmCTestLog(m_CTest, ERROR_MESSAGE, "   Unknown submission method: \"" << m_CTest->GetCTestConfiguration("DropMethod") << "\"" << std::endl);
+  cmCTestLog(m_CTest, ERROR_MESSAGE, "   Unknown submission method: \""
+    << m_CTest->GetCTestConfiguration("DropMethod") << "\"" << std::endl);
   return -1;
 }
 