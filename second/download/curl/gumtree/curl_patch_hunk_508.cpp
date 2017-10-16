               fprintf(config->errors, "%s%s",
                       CURL_CA_CERT_ERRORMSG1,
                       CURL_CA_CERT_ERRORMSG2 );
             }
           }
         }
-
         if(outfile && !curlx_strequal(outfile, "-") && outs.stream) {
-          int rc = fclose(outs.stream);
+          int rc;
+
+          if(config->xattr) {
+            rc = fwrite_xattr(curl, fileno(outs.stream) );
+            if(rc)
+              warnf(config, "Error setting extended attributes: %s\n",
+                    strerror(errno) );
+          }
+
+          rc = fclose(outs.stream);
           if(!res && rc) {
             /* something went wrong in the writing process */
             res = CURLE_WRITE_ERROR;
             fprintf(config->errors, "(%d) Failed writing body\n", res);
           }
         }
