             storeAppendPrintf(s, "\tFD %d, read %" PRId64 ", wrote %" PRId64 "\n", fd,
                               fd_table[fd].bytes_read, fd_table[fd].bytes_written);
             storeAppendPrintf(s, "\tFD desc: %s\n", fd_table[fd].desc);
             storeAppendPrintf(s, "\tin: buf %p, offset %ld, size %ld\n",
                               conn->in.buf, (long int) conn->in.notYetUsed, (long int) conn->in.allocatedSize);
             storeAppendPrintf(s, "\tremote: %s\n",
-                              conn->clientConnection->remote.ToURL(buf,MAX_IPSTRLEN));
+                              conn->clientConnection->remote.toUrl(buf,MAX_IPSTRLEN));
             storeAppendPrintf(s, "\tlocal: %s\n",
-                              conn->clientConnection->local.ToURL(buf,MAX_IPSTRLEN));
+                              conn->clientConnection->local.toUrl(buf,MAX_IPSTRLEN));
             storeAppendPrintf(s, "\tnrequests: %d\n",
                               conn->nrequests);
         }
 
         storeAppendPrintf(s, "uri %s\n", http->uri);
-        storeAppendPrintf(s, "logType %s\n", Format::log_tags[http->logType]);
+        storeAppendPrintf(s, "logType %s\n", LogTags_str[http->logType]);
         storeAppendPrintf(s, "out.offset %ld, out.size %lu\n",
                           (long int) http->out.offset, (unsigned long int) http->out.size);
         storeAppendPrintf(s, "req_sz %ld\n", (long int) http->req_sz);
         e = http->storeEntry();
         storeAppendPrintf(s, "entry %p/%s\n", e, e ? e->getMD5Text() : "N/A");
-#if 0
-        /* Not a member anymore */
-        e = http->old_entry;
-        storeAppendPrintf(s, "old_entry %p/%s\n", e, e ? e->getMD5Text() : "N/A");
-#endif
-
         storeAppendPrintf(s, "start %ld.%06d (%f seconds ago)\n",
                           (long int) http->start_time.tv_sec,
                           (int) http->start_time.tv_usec,
                           tvSubDsec(http->start_time, current_time));
 #if USE_AUTH
         if (http->request->auth_user_request != NULL)
