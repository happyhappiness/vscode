    * line (in that order, with later options overwriting previous ones in
    * general).
    * Also, this will automatically load modules.
    */
   if (cf_read(configfile)) {
     fprintf(stderr, "Error: Reading the config file failed!\n"
-                    "Read the logs for details.\n");
+                    "Read the syslog for details.\n");
     return (1);
   }
 
   /*
    * Change directory. We do this _after_ reading the config and loading
    * modules to relative paths work as expected.
