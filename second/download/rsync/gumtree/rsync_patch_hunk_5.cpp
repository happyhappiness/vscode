   fprintf(f,"the backup suffix defaults to %s\n",BACKUP_SUFFIX);
   fprintf(f,"the block size defaults to %d\n",BLOCK_SIZE);  
 }
 
 enum {OPT_VERSION,OPT_SUFFIX,OPT_SENDER,OPT_SERVER,OPT_EXCLUDE,OPT_EXCLUDE_FROM};
 
-static char *short_options = "oblpguDCtcahvre:B:";
+static char *short_options = "oblpguDCtcahvrne:B:";
 
 static struct option long_options[] = {
   {"version",     0,     0,    OPT_VERSION},
   {"server",      0,     0,    OPT_SERVER},
   {"sender",      0,     0,    OPT_SENDER},
   {"exclude",     1,     0,    OPT_EXCLUDE},
   {"exclude-from",1,     0,    OPT_EXCLUDE_FROM},
   {"help",        0,     0,    'h'},
+  {"dry-run",     0,     0,    'n'},
   {"cvs-exclude", 0,     0,    'C'},
   {"archive",     0,     0,    'a'},
   {"checksum",    0,     0,    'c'},
   {"backup",      0,     0,    'b'},
   {"update",      0,     0,    'u'},
   {"verbose",     0,     0,    'v'},
