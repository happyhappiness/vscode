 
         if (conn != NULL) {
             const int fd = conn->clientConnection->fd;
             storeAppendPrintf(s, "\tFD %d, read %" PRId64 ", wrote %" PRId64 "\n", fd,
                               fd_table[fd].bytes_read, fd_table[fd].bytes_written);
             storeAppendPrintf(s, "\tFD desc: %s\n", fd_table[fd].desc);
-            storeAppendPrintf(s, "\tin: buf %p, offset %ld, size %ld\n",
-                              conn->in.buf, (long int) conn->in.notYetUsed, (long int) conn->in.allocatedSize);
+            storeAppendPrintf(s, "\tin: buf %p, used %ld, free %ld\n",
+                              conn->in.buf.c_str(), (long int) conn->in.buf.length(), (long int) conn->in.buf.spaceSize());
             storeAppendPrintf(s, "\tremote: %s\n",
                               conn->clientConnection->remote.toUrl(buf,MAX_IPSTRLEN));
             storeAppendPrintf(s, "\tlocal: %s\n",
                               conn->clientConnection->local.toUrl(buf,MAX_IPSTRLEN));
             storeAppendPrintf(s, "\tnrequests: %d\n",
                               conn->nrequests);
