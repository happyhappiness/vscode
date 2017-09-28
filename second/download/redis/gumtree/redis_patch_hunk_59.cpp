                         obuf_pos = 0;
                     }
                 }
                 if (obuf_len == 0 && eof) break;
             }
         }
+
+        /* Handle timeout, that is, we reached EOF, and we are not getting
+         * replies from the server for a few seconds, nor the final ECHO is
+         * received. */
+        if (eof && config.pipe_timeout > 0 &&
+            time(NULL)-last_read_time > config.pipe_timeout)
+        {
+            fprintf(stderr,"No replies for %d seconds: exiting.\n",
+                config.pipe_timeout);
+            errors++;
+            break;
+        }
     }
     redisReaderFree(reader);
     printf("errors: %lld, replies: %lld\n", errors, replies);
     if (errors)
         exit(1);
     else
