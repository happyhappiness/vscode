   fprintf(f,"\n");
   fprintf(f,"the backup suffix defaults to %s\n",BACKUP_SUFFIX);
   fprintf(f,"the block size defaults to %d\n",BLOCK_SIZE);  
 }
 
 enum {OPT_VERSION,OPT_SUFFIX,OPT_SENDER,OPT_SERVER,OPT_EXCLUDE,
-      OPT_EXCLUDE_FROM,OPT_DELETE,OPT_NUMERIC_IDS,OPT_RSYNC_PATH};
+      OPT_EXCLUDE_FROM,OPT_DELETE,OPT_NUMERIC_IDS,OPT_RSYNC_PATH,
+      OPT_FORCE,OPT_TIMEOUT};
 
 static char *short_options = "oblLWHpguDCtcahvrRIxnSe:B:T:z";
 
 static struct option long_options[] = {
   {"version",     0,     0,    OPT_VERSION},
   {"server",      0,     0,    OPT_SERVER},
   {"sender",      0,     0,    OPT_SENDER},
   {"delete",      0,     0,    OPT_DELETE},
+  {"force",       0,     0,    OPT_FORCE},
   {"numeric-ids", 0,     0,    OPT_NUMERIC_IDS},
   {"exclude",     1,     0,    OPT_EXCLUDE},
   {"exclude-from",1,     0,    OPT_EXCLUDE_FROM},
   {"rsync-path",  1,     0,    OPT_RSYNC_PATH},
   {"one-file-system",0,  0,    'x'},
   {"ignore-times",0,     0,    'I'},
