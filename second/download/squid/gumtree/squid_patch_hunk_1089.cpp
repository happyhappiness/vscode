 
         if (t)
             ++t;        /* skip the ? */
         else
             t = "";
 
-        mb.Printf("query %s\r\nquit", t);
+        mb.appendf("query %s\r\nquit", t);
     } else {
         if (gopherState->type_id == GOPHER_INDEX) {
             if (char *t = strchr(gopherState->request, '?'))
                 *t = '\t';
         }
         mb.append(gopherState->request, strlen(gopherState->request));
