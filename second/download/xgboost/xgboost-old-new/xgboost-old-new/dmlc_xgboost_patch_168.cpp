@@ -1,7 +1,7 @@
 #ifndef RABIT_LEARN_IO_LINE_SPLIT_INL_H_
 #define RABIT_LEARN_IO_LINE_SPLIT_INL_H_
 /*!
- * \file line_split-inl.h
+ * \std::FILE line_split-inl.h
  * \brief base implementation of line-spliter
  * \author Tianqi Chen
  */
@@ -30,7 +30,7 @@ class LineSplitBase : public InputSplit {
         if (out_data->length() != 0) return true;
         file_ptr_ += 1;
         if (offset_curr_ != file_offset_[file_ptr_]) {
-          utils::Error("warning:file size not calculated correctly\n");
+          utils::Error("warning:std::FILE size not calculated correctly\n");
           offset_curr_ = file_offset_[file_ptr_];
         }
         if (offset_curr_ >= offset_end_) return false;
@@ -59,7 +59,7 @@ class LineSplitBase : public InputSplit {
   }
   /*!
    * \brief initialize the line spliter,
-   * \param file_size, size of each files
+   * \param file_size, size of each std::FILEs
    * \param rank the current rank of the data
    * \param nsplit number of split we will divide the data into
    */
@@ -96,51 +96,51 @@ class LineSplitBase : public InputSplit {
   }
   /*!
    * \brief get the seek stream of given file_index
-   * \return the corresponding seek stream at head of file
+   * \return the corresponding seek stream at head of std::FILE
    */
   virtual utils::ISeekStream *GetFile(size_t file_index) = 0;
   /*!
    * \brief split names given 
-   * \param out_fname output file names
-   * \param uri_ the iput uri file
+   * \param out_fname output std::FILE names
+   * \param uri_ the iput uri std::FILE
    * \param dlm deliminetr
    */
   inline static void SplitNames(std::vector<std::string> *out_fname,
                                 const char *uri_,
                                 const char *dlm) {
     std::string uri = uri_;
-    char *p = strtok(BeginPtr(uri), dlm);
+    char *p = std::strtok(BeginPtr(uri), dlm);
     while (p != NULL) {
       out_fname->push_back(std::string(p));
-      p = strtok(NULL, dlm);
+      p = std::strtok(NULL, dlm);
     }
   }
  private:
   /*! \brief current input stream */
   utils::ISeekStream *fs_;
-  /*! \brief file pointer of which file to read on */
+  /*! \brief std::FILE pointer of which std::FILE to read on */
   size_t file_ptr_;
-  /*! \brief file pointer where the end of file lies */
+  /*! \brief std::FILE pointer where the end of std::FILE lies */
   size_t file_ptr_end_;
   /*! \brief get the current offset */
   size_t offset_curr_;
   /*! \brief beginning of offset */
   size_t offset_begin_;
   /*! \brief end of the offset */
   size_t offset_end_;
-  /*! \brief byte-offset of each file */
+  /*! \brief byte-offset of each std::FILE */
   std::vector<size_t> file_offset_;
   /*! \brief buffer reader */
   StreamBufferReader reader_;
   /*! \brief buffer size */
   const static size_t kBufferSize = 256;  
 };
 
-/*! \brief line split from single file */
+/*! \brief line split from single std::FILE */
 class SingleFileSplit : public InputSplit {
  public:
   explicit SingleFileSplit(const char *fname) {
-    if (!strcmp(fname, "stdin")) {
+    if (!std::strcmp(fname, "stdin")) {
 #ifndef RABIT_STRICT_CXX98_
       use_stdin_ = true; fp_ = stdin;
 #endif
@@ -151,13 +151,13 @@ class SingleFileSplit : public InputSplit {
     end_of_file_ = false;
   }
   virtual ~SingleFileSplit(void) {
-    if (!use_stdin_) fclose(fp_);
+    if (!use_stdin_) std::fclose(fp_);
   }
   virtual bool NextLine(std::string *out_data) {
     if (end_of_file_) return false;
     out_data->clear();
     while (true) {
-      char c = fgetc(fp_);
+      char c = std::fgetc(fp_);
       if (c == EOF) {
         end_of_file_ = true;
       }
@@ -172,7 +172,7 @@ class SingleFileSplit : public InputSplit {
   }  
     
  private:
-  FILE *fp_;
+  std::FILE *fp_;
   bool use_stdin_;
   bool end_of_file_;
 };