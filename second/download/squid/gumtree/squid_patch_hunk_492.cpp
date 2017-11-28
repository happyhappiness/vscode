                 }
             } else
                 msg_ctx = 0;
             gss_release_buffer(&min_stat, &status_string);
         } while (msg_ctx);
         debug((char *) "%s| %s: ERROR: %s failed: %s\n", LogTime(), PROGRAM, function, buf);
-        fprintf(stdout, "BH %s failed: %s\n", function, buf);
+        if (sout)
+            fprintf(stdout, "BH %s failed: %s\n", function, buf);
         if (log)
             fprintf(stderr, "%s| %s: INFO: User not authenticated\n", LogTime(),
                     PROGRAM);
         return (1);
     }
     return (0);
