         length = read(pipeFd[0], buffer, sizeof(buffer));
 
         if (length > 0)
           m_capture += std::string(buffer, length);
       } while (length > 0);
 
+      ::close(pipeFd[0]);
+
       if (m_logFd != -1) {
         write(m_logFd, "Captured output:\n", sizeof("Captured output:\n"));
         write(m_logFd, m_capture.data(), m_capture.length());
       }
     }
 
