@@ -15,11 +15,42 @@
 
 namespace rabit {
 namespace io {
-class LineSplitBase : public InputSplit {
+
+/*! \brief class that split the files by line */
+class LineSplitter : public InputSplit {
  public:
-  virtual ~LineSplitBase() {
-    if (fs_ != NULL) delete fs_;
+  class IFileProvider {
+   public:
+    /*!
+     * \brief get the seek stream of given file_index
+     * \return the corresponding seek stream at head of the stream
+     *  the seek stream's resource can be freed by calling delete 
+     */
+    virtual ISeekStream *Open(size_t file_index) = 0;
+    /*!
+     * \return const reference to size of each files
+     */
+    virtual const std::vector<size_t> &FileSize(void) const = 0;
+    // virtual destructor
+    virtual ~IFileProvider() {}
+  };
+  // constructor
+  explicit LineSplitter(IFileProvider *provider,
+                         unsigned rank,
+                         unsigned nsplit)
+      : provider_(provider), fs_(NULL),
+        reader_(kBufferSize) {
+    this->Init(provider_->FileSize(), rank, nsplit);
+  }
+  // destructor
+  virtual ~LineSplitter() {
+    if (fs_ != NULL) {
+      delete fs_; fs_ = NULL;
+    }
+    // delete provider after destructing the streams
+    delete provider_;
   }
+  // get next line
   virtual bool NextLine(std::string *out_data) {
     if (file_ptr_ >= file_ptr_end_ &&
         offset_curr_ >= offset_end_) return false;
@@ -29,15 +60,15 @@ class LineSplitBase : public InputSplit {
       if (reader_.AtEnd()) {
         if (out_data->length() != 0) return true;
         file_ptr_ += 1;
+        if (offset_curr_ >= offset_end_) return false;
         if (offset_curr_ != file_offset_[file_ptr_]) {
-          utils::Error("warning:std::FILE size not calculated correctly\n");
+          utils::Error("warning: FILE size not calculated correctly\n");
           offset_curr_ = file_offset_[file_ptr_];
         }
-        if (offset_curr_ >= offset_end_) return false;
         utils::Assert(file_ptr_ + 1 < file_offset_.size(),
                       "boundary check");
         delete fs_;
-        fs_ = this->GetFile(file_ptr_);
+        fs_ = provider_->Open(file_ptr_);
         reader_.set_stream(fs_);
       } else {
         ++offset_curr_;
@@ -51,15 +82,27 @@ class LineSplitBase : public InputSplit {
       }
     }
   }
-
- protected:
-  // constructor
-  LineSplitBase(void)
-      : fs_(NULL), reader_(kBufferSize) {
+  /*!
+   * \brief split names given 
+   * \param out_fname output std::FILE names
+   * \param uri_ the iput uri std::FILE
+   * \param dlm deliminetr
+   */
+  inline static void SplitNames(std::vector<std::string> *out_fname,
+                                const char *uri_,
+                                const char *dlm) {
+    std::string uri = uri_;
+    char *p = std::strtok(BeginPtr(uri), dlm);
+    while (p != NULL) {
+      out_fname->push_back(std::string(p));
+      p = std::strtok(NULL, dlm);
+    }
   }
+  
+ private:
   /*!
    * \brief initialize the line spliter,
-   * \param file_size, size of each std::FILEs
+   * \param file_size, size of each files
    * \param rank the current rank of the data
    * \param nsplit number of split we will divide the data into
    */
@@ -82,7 +125,7 @@ class LineSplitBase : public InputSplit {
     file_ptr_end_ = std::upper_bound(file_offset_.begin(),
                                      file_offset_.end(),
                                      offset_end_) - file_offset_.begin() - 1;
-    fs_ = GetFile(file_ptr_);
+    fs_ = provider_->Open(file_ptr_);
     reader_.set_stream(fs_);
     // try to set the starting position correctly
     if (file_offset_[file_ptr_] != offset_begin_) {
@@ -94,41 +137,23 @@ class LineSplitBase : public InputSplit {
       }
     }
   }
-  /*!
-   * \brief get the seek stream of given file_index
-   * \return the corresponding seek stream at head of std::FILE
-   */
-  virtual utils::ISeekStream *GetFile(size_t file_index) = 0;
-  /*!
-   * \brief split names given 
-   * \param out_fname output std::FILE names
-   * \param uri_ the iput uri std::FILE
-   * \param dlm deliminetr
-   */
-  inline static void SplitNames(std::vector<std::string> *out_fname,
-                                const char *uri_,
-                                const char *dlm) {
-    std::string uri = uri_;
-    char *p = std::strtok(BeginPtr(uri), dlm);
-    while (p != NULL) {
-      out_fname->push_back(std::string(p));
-      p = std::strtok(NULL, dlm);
-    }
-  }
+
  private:
+  /*! \brief FileProvider */
+  IFileProvider *provider_;
   /*! \brief current input stream */
   utils::ISeekStream *fs_;
-  /*! \brief std::FILE pointer of which std::FILE to read on */
+  /*! \brief file pointer of which file to read on */
   size_t file_ptr_;
-  /*! \brief std::FILE pointer where the end of std::FILE lies */
+  /*! \brief file pointer where the end of file lies */
   size_t file_ptr_end_;
   /*! \brief get the current offset */
   size_t offset_curr_;
   /*! \brief beginning of offset */
   size_t offset_begin_;
   /*! \brief end of the offset */
   size_t offset_end_;
-  /*! \brief byte-offset of each std::FILE */
+  /*! \brief byte-offset of each file */
   std::vector<size_t> file_offset_;
   /*! \brief buffer reader */
   StreamBufferReader reader_;