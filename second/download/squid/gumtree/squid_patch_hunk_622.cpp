                 if (x <= 0)
                     break;
             }
 
             if (x != 0)
                 fprintf(stderr, "client: ERROR: Cannot send file.\n");
+            else
+                fprintf(stderr, "done.\n");
         }
         /* Read the data */
 
 #if _SQUID_WINDOWS_
         setmode(1, O_BINARY);
 #endif
