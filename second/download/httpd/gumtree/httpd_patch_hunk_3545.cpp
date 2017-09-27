                 else {
                     write_request(c);
                 }
             }
         }
     } while (lasttime < stoptime && done < requests);
-    
+
     if (heartbeatres)
         fprintf(stderr, "Finished %d requests\n", done);
     else
         printf("..done\n");
 
     if (use_html)
