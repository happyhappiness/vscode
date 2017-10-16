           const char *reason = param2text(res);
           warnf(config, "%s:%d: warning: '%s' %s\n",
                 filename, lineno, option, reason);
         }
       }
 
-      if(alloced_param)
-      {
+      if(alloced_param) {
         free(param);
         param = NULL;
       }
 
       free(aline);
     }
