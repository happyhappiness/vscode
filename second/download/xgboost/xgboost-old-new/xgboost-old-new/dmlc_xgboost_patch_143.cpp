@@ -16,7 +16,7 @@
 /*! \brief io interface */
 namespace rabit {
 namespace io {
-class HDFSStream : public ISeekStream {
+class HDFSStream : public SeekStream {
  public:
   HDFSStream(hdfsFS fs,
              const char *fname,
@@ -147,7 +147,7 @@ class HDFSProvider : public LineSplitter::IFileProvider {
   virtual const std::vector<size_t> &FileSize(void) const {
     return fsize_;
   }
-  virtual ISeekStream *Open(size_t file_index) {
+  virtual SeekStream *Open(size_t file_index) {
     utils::Assert(file_index < fnames_.size(), "file index exceed bound"); 
     return new HDFSStream(fs_, fnames_[file_index].c_str(), "r", false);
   }