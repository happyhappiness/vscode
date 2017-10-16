           if(config->xattr) {
             rc = fwrite_xattr(curl, fileno(outs.stream) );
             if(rc)
               warnf(config, "Error setting extended attributes: %s\n",
                     strerror(errno) );
           }
+          if(outs.alloc_filename)
+            free(outs.filename);
 
           rc = fclose(outs.stream);
           if(!res && rc) {
             /* something went wrong in the writing process */
             res = CURLE_WRITE_ERROR;
             fprintf(config->errors, "(%d) Failed writing body\n", res);
