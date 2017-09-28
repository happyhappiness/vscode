         argv2[j+3-got_comma] = sdsnew(argv[j]);
         if (!got_comma) keys++;
     }
     argv2[2] = sdscatprintf(sdsempty(),"%d",keys);
 
     /* Call it */
-    return cliSendCommand(argc+3-got_comma, argv2, config.repeat);
+    return issueCommand(argc+3-got_comma, argv2);
 }
 
 /*------------------------------------------------------------------------------
  * Latency and latency history modes
  *--------------------------------------------------------------------------- */
 
