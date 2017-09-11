@@ -6,6 +6,7 @@
  * \author Tianqi Chen
  */
 #include <string>
+#include <cstdlib>
 #include <vector>
 #include <hdfs.h>
 #include <errno.h>
@@ -15,11 +16,15 @@
 /*! \brief io interface */
 namespace rabit {
 namespace io {
-class HDFSStream : public utils::ISeekStream {
+class HDFSStream : public ISeekStream {
  public:
-  HDFSStream(hdfsFS fs, const char *fname, const char *mode)
-      : fs_(fs), at_end_(false) {
-    int flag;
+  HDFSStream(hdfsFS fs,
+             const char *fname,
+             const char *mode,
+             bool disconnect_when_done)
+      : fs_(fs), at_end_(false),
+        disconnect_when_done_(disconnect_when_done) {
+    int flag = 0;
     if (!strcmp(mode, "r")) {
       flag = O_RDONLY;
     } else if (!strcmp(mode, "w"))  {
@@ -35,6 +40,9 @@ class HDFSStream : public utils::ISeekStream {
   }
   virtual ~HDFSStream(void) {
     this->Close();
+    if (disconnect_when_done_) {
+      utils::Check(hdfsDisconnect(fs_) == 0, "hdfsDisconnect error");
+    }
   }
   virtual size_t Read(void *ptr, size_t size) {
     tSize nread = hdfsRead(fs_, fp_, ptr, size);
@@ -86,52 +94,69 @@ class HDFSStream : public utils::ISeekStream {
     }
   }  
   
+  inline static std::string GetNameNode(void) {
+    const char *nn = getenv("rabit_hdfs_namenode");
+    if (nn == NULL) {
+      return std::string("default");
+    } else {
+      return std::string(nn);
+    }
+  }
  private:
   hdfsFS fs_;
   hdfsFile fp_;
   bool at_end_;
+  bool disconnect_when_done_;
 };
 
 /*! \brief line split from normal file system */
-class HDFSSplit : public LineSplitBase {
+class HDFSProvider : public LineSplitter::IFileProvider {
  public:
-  explicit HDFSSplit(const char *uri, unsigned rank, unsigned nsplit) {
-    fs_ = hdfsConnect("default", 0);
+  explicit HDFSProvider(const char *uri) {
+    fs_ = hdfsConnect(HDFSStream::GetNameNode().c_str(), 0);
+    utils::Check(fs_ != NULL, "error when connecting to default HDFS");
     std::vector<std::string> paths;
-    LineSplitBase::SplitNames(&paths, uri, "#");
+    LineSplitter::SplitNames(&paths, uri, "#");
     // get the files
-    std::vector<size_t> fsize;
     for (size_t  i = 0; i < paths.size(); ++i) {
       hdfsFileInfo *info = hdfsGetPathInfo(fs_, paths[i].c_str());
+      utils::Check(info != NULL, "path %s do not exist", paths[i].c_str());
       if (info->mKind == 'D') {
         int nentry;
         hdfsFileInfo *files = hdfsListDirectory(fs_, info->mName, &nentry);
+        utils::Check(files != NULL, "error when ListDirectory %s", info->mName);
         for (int i = 0; i < nentry; ++i) {
-          if (files[i].mKind == 'F') {
-            fsize.push_back(files[i].mSize);
+          if (files[i].mKind == 'F' && files[i].mSize != 0) {
+            fsize_.push_back(files[i].mSize);            
             fnames_.push_back(std::string(files[i].mName));
           }
         }
         hdfsFreeFileInfo(files, nentry);
       } else {
-        fsize.push_back(info->mSize);
-        fnames_.push_back(std::string(info->mName));
+        if (info->mSize != 0) {
+          fsize_.push_back(info->mSize);
+          fnames_.push_back(std::string(info->mName));
+        }
       }
       hdfsFreeFileInfo(info, 1);
     }
-    LineSplitBase::Init(fsize, rank, nsplit);
   }
-  virtual ~HDFSSplit(void) {}
-  
- protected:
-  virtual utils::ISeekStream *GetFile(size_t file_index) {
+  virtual ~HDFSProvider(void) {
+    utils::Check(hdfsDisconnect(fs_) == 0, "hdfsDisconnect error");
+  }  
+  virtual const std::vector<size_t> &FileSize(void) const {
+    return fsize_;
+  }
+  virtual ISeekStream *Open(size_t file_index) {
     utils::Assert(file_index < fnames_.size(), "file index exceed bound"); 
-    return new HDFSStream(fs_, fnames_[file_index].c_str(), "r");
+    return new HDFSStream(fs_, fnames_[file_index].c_str(), "r", false);
   }
-
+  
  private:
   // hdfs handle
   hdfsFS fs_;
+  // file sizes
+  std::vector<size_t> fsize_;
   // file names
   std::vector<std::string> fnames_;
 };