     // Clean up logging, this is just plain ugly...
     //    write(m_logFd, "\n---\n", sizeof("\n---\n"));
     result = write(m_parent->log_fd(), m_buffer, m_bufferSize);
     result = write(m_parent->log_fd(), "\n---\n", sizeof("\n---\n"));
   }
 
-  lt_log_print_dump(torrent::LOG_RPC_DEBUG, m_body, m_bufferSize - std::distance(m_buffer, m_body), "scgi", "RPC read.", 0);
+  lt_log_print_dump(torrent::LOG_RPC_DUMP, m_body, m_bufferSize - std::distance(m_buffer, m_body), "scgi", "RPC read.", 0);
 
   // Close if the call failed, else stay open to write back data.
   if (!m_parent->receive_call(this, m_body, m_bufferSize - std::distance(m_buffer, m_body)))
     close();
 
   return;
