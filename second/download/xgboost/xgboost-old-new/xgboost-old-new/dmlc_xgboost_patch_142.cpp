@@ -15,7 +15,7 @@
 namespace rabit {
 namespace io {
 /*! \brief implementation of file i/o stream */
-class FileStream : public utils::ISeekStream {
+class FileStream : public utils::SeekStream {
  public:
   explicit FileStream(const char *fname, const char *mode)
       : use_stdio(false) {
@@ -84,7 +84,7 @@ class FileProvider : public LineSplitter::IFileProvider {
   }
   // destrucor
   virtual ~FileProvider(void) {}  
-  virtual utils::ISeekStream *Open(size_t file_index) {
+  virtual utils::SeekStream *Open(size_t file_index) {
     utils::Assert(file_index < fnames_.size(), "file index exceed bound"); 
     return new FileStream(fnames_[file_index].c_str(), "rb");
   }