@@ -463,7 +463,10 @@ bool cmOrderLinkDirectories::DetermineLibraryPathOrder()
 #ifdef CM_ORDER_LINK_DIRECTORIES_DEBUG
     fprintf(stderr, "Raw link item [%s]\n", this->RawLinkItems[i].c_str());
 #endif
-    if(cmSystemTools::FileIsFullPath(this->RawLinkItems[i].c_str()))
+    // check to see if the file is a full path or just contains 
+    // a / in it and is a path to something
+    if(cmSystemTools::FileIsFullPath(this->RawLinkItems[i].c_str())
+      || this->RawLinkItems[i].find("/") != cmStdString.npos)
       {
       if(cmSystemTools::FileIsDirectory(this->RawLinkItems[i].c_str()))
         {
@@ -486,6 +489,8 @@ bool cmOrderLinkDirectories::DetermineLibraryPathOrder()
           }
         else
           {
+          // A full path to a directory was found as a link item
+          // warn user 
           std::string message = 
             "Warning: Ignoring path found in link libraries for target: ";
           message += this->TargetName;
@@ -496,7 +501,7 @@ bool cmOrderLinkDirectories::DetermineLibraryPathOrder()
           cmSystemTools::Message(message.c_str());
           continue;
           }
-        }
+        } // is it a directory
       if(!framework)
         {
         dir = cmSystemTools::GetFilenamePath(this->RawLinkItems[i]);