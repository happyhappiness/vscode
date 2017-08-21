@@ -1,29 +1,20 @@
-/*============================================================================
-  KWSys - Kitware System Library
-  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium
-
-  Distributed under the OSI-approved BSD License (the "License");
-  see accompanying file Copyright.txt for details.
-
-  This software is distributed WITHOUT ANY WARRANTY; without even the
-  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
-  See the License for more information.
-============================================================================*/
+/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
+   file Copyright.txt or https://cmake.org/licensing#kwsys for details.  */
 #include "kwsysPrivate.h"
 #include KWSYS_HEADER(MD5.h)
 
 /* Work-around CMake dependency scanning limitation.  This must
    duplicate the above list of headers.  */
 #if 0
-# include "MD5.h.in"
+#include "MD5.h.in"
 #endif
 
 #include <stdio.h>
 #include <string.h>
 
 static const unsigned char testMD5input1[] =
-"  A quick brown fox jumps over the lazy dog.\n"
-"  This is sample text for MD5 sum input.\n";
+  "  A quick brown fox jumps over the lazy dog.\n"
+  "  This is sample text for MD5 sum input.\n";
 static const char testMD5output1[] = "8f146af46ed4f267921bb937d4d3500c";
 
 static const int testMD5input2len = 28;
@@ -40,7 +31,7 @@ static int testMD5_1(kwsysMD5* md5)
   printf("md5sum 1: expected [%s]\n"
          "               got [%s]\n",
          testMD5output1, md5out);
-  return (strcmp(md5out, testMD5output1) != 0)? 1:0;
+  return (strcmp(md5out, testMD5output1) != 0) ? 1 : 0;
 }
 
 static int testMD5_2(kwsysMD5* md5)
@@ -55,7 +46,7 @@ static int testMD5_2(kwsysMD5* md5)
   printf("md5sum 2: expected [%s]\n"
          "               got [%s]\n",
          testMD5output2, md5out);
-  return (strcmp(md5out, testMD5output2) != 0)? 1:0;
+  return (strcmp(md5out, testMD5output2) != 0) ? 1 : 0;
 }
 
 int testEncode(int argc, char* argv[])
@@ -66,10 +57,10 @@ int testEncode(int argc, char* argv[])
 
   /* Test MD5 digest.  */
   {
-  kwsysMD5* md5 = kwsysMD5_New();
-  result |= testMD5_1(md5);
-  result |= testMD5_2(md5);
-  kwsysMD5_Delete(md5);
+    kwsysMD5* md5 = kwsysMD5_New();
+    result |= testMD5_1(md5);
+    result |= testMD5_2(md5);
+    kwsysMD5_Delete(md5);
   }
 
   return result;