         quit_urls:
 
         /* Set file extended attributes */
         if(!result && config->xattr && outs.fopened && outs.stream) {
           int rc = fwrite_xattr(curl, fileno(outs.stream));
           if(rc)
-            warnf(config, "Error setting extended attributes: %s\n",
+            warnf(config->global, "Error setting extended attributes: %s\n",
                   strerror(errno));
         }
 
         /* Close the file */
         if(outs.fopened && outs.stream) {
           int rc = fclose(outs.stream);
