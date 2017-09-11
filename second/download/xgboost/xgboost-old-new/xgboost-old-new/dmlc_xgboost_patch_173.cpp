@@ -110,15 +110,15 @@ struct MemoryFixSizeBuffer : public ISeekStream {
     utils::Assert(curr_ptr_ + size <= buffer_size_,
                   "read can not have position excceed buffer length");
     size_t nread = std::min(buffer_size_ - curr_ptr_, size);
-    if (nread != 0) memcpy(ptr, p_buffer_ + curr_ptr_, nread);
+    if (nread != 0) std::memcpy(ptr, p_buffer_ + curr_ptr_, nread);
     curr_ptr_ += nread;
     return nread;
   }
   virtual void Write(const void *ptr, size_t size) {
     if (size == 0) return;
     utils::Assert(curr_ptr_ + size <=  buffer_size_, 
                   "write position exceed fixed buffer size");
-    memcpy(p_buffer_ + curr_ptr_, ptr, size);
+    std::memcpy(p_buffer_ + curr_ptr_, ptr, size);
     curr_ptr_ += size;
   }
   virtual void Seek(size_t pos) {
@@ -149,7 +149,7 @@ struct MemoryBufferStream : public ISeekStream {
     utils::Assert(curr_ptr_ <= p_buffer_->length(),
                   "read can not have position excceed buffer length");
     size_t nread = std::min(p_buffer_->length() - curr_ptr_, size);
-    if (nread != 0) memcpy(ptr, &(*p_buffer_)[0] + curr_ptr_, nread);
+    if (nread != 0) std::memcpy(ptr, &(*p_buffer_)[0] + curr_ptr_, nread);
     curr_ptr_ += nread;
     return nread;
   }
@@ -158,7 +158,7 @@ struct MemoryBufferStream : public ISeekStream {
     if (curr_ptr_ + size > p_buffer_->length()) {
       p_buffer_->resize(curr_ptr_+size);
     }
-    memcpy(&(*p_buffer_)[0] + curr_ptr_, ptr, size); 
+    std::memcpy(&(*p_buffer_)[0] + curr_ptr_, ptr, size); 
     curr_ptr_ += size;
   }
   virtual void Seek(size_t pos) {
@@ -178,7 +178,7 @@ struct MemoryBufferStream : public ISeekStream {
 /*! \brief implementation of file i/o stream */
 class FileStream : public ISeekStream {
  public:
-  explicit FileStream(FILE *fp) : fp(fp) {}
+  explicit FileStream(std::FILE *fp) : fp(fp) {}
   explicit FileStream(void) {
     this->fp = NULL;
   }
@@ -201,7 +201,7 @@ class FileStream : public ISeekStream {
   }
 
  private:
-  FILE *fp;
+  std::FILE *fp;
 };
 }  // namespace utils
 }  // namespace xgboost