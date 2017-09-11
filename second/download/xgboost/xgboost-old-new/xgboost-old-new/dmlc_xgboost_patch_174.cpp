@@ -38,15 +38,15 @@ struct MemoryFixSizeBuffer : public ISeekStream {
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
@@ -77,7 +77,7 @@ struct MemoryBufferStream : public ISeekStream {
     utils::Assert(curr_ptr_ <= p_buffer_->length(),
                   "read can not have position excceed buffer length");
     size_t nread = std::min(p_buffer_->length() - curr_ptr_, size);
-    if (nread != 0) memcpy(ptr, &(*p_buffer_)[0] + curr_ptr_, nread);
+    if (nread != 0) std::memcpy(ptr, &(*p_buffer_)[0] + curr_ptr_, nread);
     curr_ptr_ += nread;
     return nread;
   }
@@ -86,7 +86,7 @@ struct MemoryBufferStream : public ISeekStream {
     if (curr_ptr_ + size > p_buffer_->length()) {
       p_buffer_->resize(curr_ptr_+size);
     }
-    memcpy(&(*p_buffer_)[0] + curr_ptr_, ptr, size);
+    std::memcpy(&(*p_buffer_)[0] + curr_ptr_, ptr, size);
     curr_ptr_ += size;
   }
   virtual void Seek(size_t pos) {