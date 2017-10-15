 SCgiTask::event_error() {
   close();
 }
 
 bool
 SCgiTask::receive_write(const char* buffer, uint32_t length) {
+  if (buffer == NULL || length > (100 << 20))
+    throw torrent::internal_error("SCgiTask::receive_write(...) received bad input.");
+
   // Need to cast due to a bug in MacOSX gcc-4.0.1.
   if (length + 256 > std::max(m_bufferSize, (unsigned int)default_buffer_size))
     realloc_buffer(length + 256, NULL, 0);
 
   // Who ever bothers to check the return value?
   int headerSize = sprintf(m_buffer, "Status: 200 OK\r\nContent-Type: text/xml\r\nContent-Length: %i\r\n\r\n", length);
 
   m_position = m_buffer;
   m_bufferSize = length + headerSize;
   
   std::memcpy(m_buffer + headerSize, buffer, length);
-  event_write();
 
+  if (m_parent->log_fd() >= 0) {
+    // Clean up logging, this is just plain ugly...
+    //    write(m_logFd, "\n---\n", sizeof("\n---\n"));
+    write(m_parent->log_fd(), m_buffer, m_bufferSize);
+    write(m_parent->log_fd(), "\n---\n", sizeof("\n---\n"));
+  }
+
+  event_write();
   return true;
 }
 
 }
