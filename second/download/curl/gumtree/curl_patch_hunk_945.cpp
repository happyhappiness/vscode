             /* fill '#1' ... '#9' terms from URL pattern */
             char *storefile = outfile;
             result = glob_match_url(&outfile, storefile, urls);
             Curl_safefree(storefile);
             if(result) {
               /* bad globbing */
-              warnf(config, "bad output glob!\n");
+              warnf(config->global, "bad output glob!\n");
               goto quit_urls;
             }
           }
 
           /* Create the directory hierarchy, if not pre-existent to a multiple
              file output call */
