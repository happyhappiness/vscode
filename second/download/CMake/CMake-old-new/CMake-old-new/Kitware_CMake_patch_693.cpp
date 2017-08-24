@@ -1,17 +1,17 @@
 /*=========================================================================
 
-  Program:   CMake - Cross-Platform Makefile Generator
-  Module:    $RCSfile$
-  Language:  C++
-  Date:      $Date$
-  Version:   $Revision$
+Program:   CMake - Cross-Platform Makefile Generator
+Module:    $RCSfile$
+Language:  C++
+Date:      $Date$
+Version:   $Revision$
 
-  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
-  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
+Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
+See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
-     This software is distributed WITHOUT ANY WARRANTY; without even 
-     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
-     PURPOSE.  See the above copyright notices for more information.
+This software is distributed WITHOUT ANY WARRANTY; without even 
+the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
 
@@ -24,7 +24,6 @@
 cmCTestSubmit::cmCTestSubmit() : m_HTTPProxy(), m_FTPProxy()
 {
   m_Verbose = false;
-  std::cout << "Setup proxy" << std::endl;
   m_HTTPProxy = "";
   m_HTTPProxyType = 0;
   if ( getenv("HTTP_PROXY") )
@@ -83,14 +82,20 @@ cmCTestSubmit::cmCTestSubmit() : m_HTTPProxy(), m_FTPProxy()
         }
       }
     }
-  std::cout << this << " HTTP Proxy: " << m_HTTPProxy << std::endl;
-
+  if ( m_HTTPProxy.size() > 0 )
+    {
+    std::cout << "  Use HTTP Proxy: " << m_HTTPProxy << std::endl;
+    }
+  if ( m_FTPProxy.size() > 0 )
+    {
+    std::cout << "  Use FTP Proxy: " << m_FTPProxy << std::endl;
+    }
 }
 
 bool cmCTestSubmit::SubmitUsingFTP(const std::string& localprefix, 
-                                   const std::vector<std::string>& files,
-                                   const std::string& remoteprefix, 
-                                   const std::string& url)
+  const std::vector<std::string>& files,
+  const std::string& remoteprefix, 
+  const std::string& url)
 {
   CURL *curl;
   CURLcode res;
@@ -112,23 +117,23 @@ bool cmCTestSubmit::SubmitUsingFTP(const std::string& localprefix,
         curl_easy_setopt(curl, CURLOPT_PROXY, m_FTPProxy.c_str()); 
         switch (m_FTPProxyType)
           {
-          case 2:
-            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
-            break;
-          case 3:
-            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
-            break;
-          default:
-            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);           
+        case 2:
+          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
+          break;
+        case 3:
+          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
+          break;
+        default:
+          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);           
           }
         }
-      
+
       // enable uploading
       ::curl_easy_setopt(curl, CURLOPT_UPLOAD, TRUE) ;
-      
+
       std::string local_file = localprefix + "/" + files[cc];
       std::string upload_as = url + "/" + remoteprefix + files[cc];
-      
+
       struct stat st;
       if ( ::stat(local_file.c_str(), &st) )
         {
@@ -138,19 +143,17 @@ bool cmCTestSubmit::SubmitUsingFTP(const std::string& localprefix,
       ftpfile = ::fopen(local_file.c_str(), "rb");
       if ( m_Verbose )
         {
-        std::cout << "upload file: " << local_file.c_str() << " to " 
-                  << upload_as.c_str() << std::endl;
+        std::cout << "  Upload file: " << local_file.c_str() << " to " 
+          << upload_as.c_str() << std::endl;
         }
 
-      //std::cout << "File is opened: " << ftpfile << std::endl;
-
       if ( m_Verbose )
         {
         ::curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
         }
       // specify target
       ::curl_easy_setopt(curl,CURLOPT_URL, upload_as.c_str());
-      
+
       // now specify which file to upload
       ::curl_easy_setopt(curl, CURLOPT_INFILE, ftpfile);
 
@@ -162,14 +165,14 @@ bool cmCTestSubmit::SubmitUsingFTP(const std::string& localprefix,
       fclose(ftpfile);
       if ( res )
         {
-        std::cout << "Error when uploading" << std::endl;
+        std::cout << "  Error when uploading file: " << local_file.c_str() << std::endl;
         ::curl_easy_cleanup(curl);
         ::curl_global_cleanup(); 
         return false;
         }
       // always cleanup
       ::curl_easy_cleanup(curl);
-      std::cout << "Uploaded: " + local_file << std::endl;
+      std::cout << "  Uploaded: " + local_file << std::endl;
       }
     }
   ::curl_global_cleanup(); 
@@ -178,11 +181,10 @@ bool cmCTestSubmit::SubmitUsingFTP(const std::string& localprefix,
 
 // Uploading files is simpler
 bool cmCTestSubmit::SubmitUsingHTTP(const std::string& localprefix, 
-                                   const std::vector<std::string>& files,
-                                   const std::string& remoteprefix, 
-                                   const std::string& url)
+  const std::vector<std::string>& files,
+  const std::string& remoteprefix, 
+  const std::string& url)
 {
-  std::cout << this << " Using proxy: " << m_HTTPProxy << std::endl;
   CURL *curl;
   CURLcode res;
   FILE* ftpfile;
@@ -204,14 +206,14 @@ bool cmCTestSubmit::SubmitUsingHTTP(const std::string& localprefix,
         curl_easy_setopt(curl, CURLOPT_PROXY, m_HTTPProxy.c_str()); 
         switch (m_HTTPProxyType)
           {
-          case 2:
-            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
-            break;
-          case 3:
-            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
-            break;
-          default:
-            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);           
+        case 2:
+          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
+          break;
+        case 3:
+          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
+          break;
+        default:
+          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);           
           }
         }
 
@@ -235,19 +237,19 @@ bool cmCTestSubmit::SubmitUsingHTTP(const std::string& localprefix,
         hex[0] = c;
         switch ( c )
           {
-          case '+':
-          case '?':
-          case '/':
-          case '\\':
-          case '&':
-          case ' ':
-          case '=':
-          case '%':
-            sprintf(hex, "%%%02X", (int)c);
-            ofile.append(hex);
-            break;
-          default: 
-            ofile.append(hex);
+        case '+':
+        case '?':
+        case '/':
+        case '\\':
+        case '&':
+        case ' ':
+        case '=':
+        case '%':
+          sprintf(hex, "%%%02X", (int)c);
+          ofile.append(hex);
+          break;
+        default: 
+          ofile.append(hex);
           }
         }
       std::string upload_as = url + "?FileName=" + ofile;
@@ -261,11 +263,11 @@ bool cmCTestSubmit::SubmitUsingHTTP(const std::string& localprefix,
       ftpfile = ::fopen(local_file.c_str(), "rb");
       if ( m_Verbose )
         {
-        std::cout << "upload file: " << local_file.c_str() << " to " 
+        std::cout << "  Upload file: " << local_file.c_str() << " to " 
           << upload_as.c_str() << " Size: " << st.st_size << std::endl;
         }
 
-                
+
       // specify target
       ::curl_easy_setopt(curl,CURLOPT_URL, upload_as.c_str());
 
@@ -281,28 +283,29 @@ bool cmCTestSubmit::SubmitUsingHTTP(const std::string& localprefix,
       fclose(ftpfile);
       if ( res )
         {
-        std::cout << "Error when uploading" << std::endl;
+        std::cout << "  Error when uploading file: " << local_file.c_str() << std::endl;
         ::curl_easy_cleanup(curl);
         ::curl_global_cleanup(); 
         return false;
         }
       // always cleanup
       ::curl_easy_cleanup(curl);
+      std::cout << "  Uploaded: " + local_file << std::endl;
       }
     }
   ::curl_global_cleanup(); 
   return true;
 }
 
 bool cmCTestSubmit::TriggerUsingHTTP(const std::vector<std::string>& files,
-                                     const std::string& remoteprefix, 
-                                     const std::string& url)
+  const std::string& remoteprefix, 
+  const std::string& url)
 {
   CURL *curl;
 
   /* In windows, this will init the winsock stuff */
   ::curl_global_init(CURL_GLOBAL_ALL);
-  
+
   std::string::size_type cc, kk;
   for ( cc = 0; cc < files.size(); cc ++ )
     {
@@ -316,14 +319,14 @@ bool cmCTestSubmit::TriggerUsingHTTP(const std::vector<std::string>& files,
         curl_easy_setopt(curl, CURLOPT_PROXY, m_HTTPProxy.c_str()); 
         switch (m_HTTPProxyType)
           {
-          case 2:
-            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
-            break;
-          case 3:
-            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
-            break;
-          default:
-            curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);           
+        case 2:
+          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS4);
+          break;
+        case 3:
+          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
+          break;
+        default:
+          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_HTTP);           
           }
         }
 
@@ -341,30 +344,30 @@ bool cmCTestSubmit::TriggerUsingHTTP(const std::vector<std::string>& files,
         hex[0] = c;
         switch ( c )
           {
-          case '+':
-          case '?':
-          case '/':
-          case '\\':
-          case '&':
-          case ' ':
-          case '=':
-          case '%':
-            sprintf(hex, "%%%02X", (int)c);
-            ofile.append(hex);
-            break;
-          default: 
-            ofile.append(hex);
+        case '+':
+        case '?':
+        case '/':
+        case '\\':
+        case '&':
+        case ' ':
+        case '=':
+        case '%':
+          sprintf(hex, "%%%02X", (int)c);
+          ofile.append(hex);
+          break;
+        default: 
+          ofile.append(hex);
           }
         }
       std::string turl = url + "?xmlfile=" + ofile;
       if ( m_Verbose )
         {
-        std::cout << "Trigger url: " << turl.c_str() << std::endl;
+        std::cout << "  Trigger url: " << turl.c_str() << std::endl;
         }
       curl_easy_setopt(curl, CURLOPT_URL, turl.c_str());
       if ( curl_easy_perform(curl) )
         {
-        std::cout << "Error when uploading" << std::endl;
+        std::cout << "  Error when triggering: " << turl.c_str() << std::endl;
         ::curl_easy_cleanup(curl);
         ::curl_global_cleanup(); 
         return false;
@@ -375,14 +378,14 @@ bool cmCTestSubmit::TriggerUsingHTTP(const std::vector<std::string>& files,
       }
     }
   ::curl_global_cleanup(); 
-  std::cout << "Dart server triggered..." << std::endl;
+  std::cout << "  Dart server triggered..." << std::endl;
   return true;
 }
 
 bool cmCTestSubmit::SubmitUsingSCP(const std::string&, 
-                                   const std::vector<std::string>&,
-                                   const std::string&, 
-                                   const std::string&)
+  const std::vector<std::string>&,
+  const std::string&, 
+  const std::string&)
 {
   std::cout << "SubmitUsingSCP is not yet implemented" << std::endl;
   return false;