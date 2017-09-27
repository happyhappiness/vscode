     }
 
     /*
      * We can access the files the right way, and we have a record
      * to add or update.  Let's do it..
      */
+    tn = get_tempname(pool);
     if (apr_file_mktemp(&ftemp, tn, 0, pool) != APR_SUCCESS) {
         apr_file_printf(errfile, "%s: unable to create temporary file %s\n", 
                         argv[0], tn);
         exit(ERR_FILEPERM);
     }
 
