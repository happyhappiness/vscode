               /* set type pointer */
               type = &ptr[5];
 
               /* verify that this is a fine type specifier */
               if(2 != sscanf(type, "%127[^/]/%127[^;,\n]",
                              major, minor)) {
-                fprintf(stderr, "Illegally formatted content-type field!\n");
+                warnf(config, "Illegally formatted content-type field!\n");
                 free(contents);
                 FreeMultiInfo (multi_start);
                 return 2; /* illegal content-type syntax! */
               }
               /* now point beyond the content-type specifier */
               sep = (char *)type + strlen(major)+strlen(minor)+1;
