@@ -30,16 +30,16 @@ inline InputSplit *CreateInputSplit(const char *uri,
     return new SingleFileSplit(uri);
   }
   if (!strncmp(uri, "file://", 7)) {
-    return new FileSplit(uri, part, nsplit);
+    return new LineSplitter(new FileProvider(uri), part, nsplit);
   }
   if (!strncmp(uri, "hdfs://", 7)) {
 #if RABIT_USE_HDFS
-    return new HDFSSplit(uri, part, nsplit);
+    return new LineSplitter(new HDFSProvider(uri), part, nsplit);
 #else
     utils::Error("Please compile with RABIT_USE_HDFS=1");
 #endif
   }
-  return new FileSplit(uri, part, nsplit);  
+  return new LineSplitter(new FileProvider(uri), part, nsplit);
 }
 /*!
  * \brief create an stream, the stream must be able to close
@@ -55,7 +55,8 @@ inline IStream *CreateStream(const char *uri, const char *mode) {
   }
   if (!strncmp(uri, "hdfs://", 7)) {
 #if RABIT_USE_HDFS
-    return new HDFSStream(hdfsConnect("default", 0), uri, mode);
+    return new HDFSStream(hdfsConnect(HDFSStream::GetNameNode().c_str(), 0),
+                          uri, mode, true);
 #else
     utils::Error("Please compile with RABIT_USE_HDFS=1");
 #endif