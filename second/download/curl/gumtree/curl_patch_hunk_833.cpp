             }
 #endif /* MSDOS || WIN32 */
           }
           else if(urls) {
             /* fill '#1' ... '#9' terms from URL pattern */
             char *storefile = outfile;
-            res = glob_match_url(&outfile, storefile, urls);
+            res = (CURLcode) glob_match_url(&outfile, storefile, urls);
             Curl_safefree(storefile);
             if(res) {
               /* bad globbing */
               warnf(config, "bad output glob!\n");
               goto quit_urls;
             }
