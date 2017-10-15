     // Clean up logging, this is just plain ugly...
     //    write(m_logFd, "\n---\n", sizeof("\n---\n"));
     result = write(m_parent->log_fd(), m_buffer, m_bufferSize);
     result = write(m_parent->log_fd(), "\n---\n", sizeof("\n---\n"));
   }
 
-  lt_log_print(torrent::LOG_RPC_DEBUG, "---\n%*s\n---", m_bufferSize, m_buffer);
+  lt_log_print_dump(torrent::LOG_RPC_DEBUG, m_buffer, m_bufferSize, "scgi", "RPC write.", 0);
 
   event_write();
   return true;
 }
 
 }
