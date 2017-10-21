   fprintf(f,"-C, --cvs-exclude        auto ignore files in the same way CVS does\n");
   fprintf(f,"    --delete             delete files that don't exist on the sending side\n");
   fprintf(f,"-I, --ignore-times       don't exclude files that match length and time\n");
   fprintf(f,"    --exclude FILE       exclude file FILE\n");
   fprintf(f,"    --exclude-from FILE  exclude files listed in FILE\n");
   fprintf(f,"    --suffix SUFFIX      override backup suffix\n");  
+  fprintf(f,"    --csum-length LENGTH set the checksum length\n");  
   fprintf(f,"    --version            print version number\n");  
 
   fprintf(f,"\n");
   fprintf(f,"the backup suffix defaults to %s\n",BACKUP_SUFFIX);
   fprintf(f,"the block size defaults to %d\n",BLOCK_SIZE);  
 }
 
 enum {OPT_VERSION,OPT_SUFFIX,OPT_SENDER,OPT_SERVER,OPT_EXCLUDE,
-      OPT_EXCLUDE_FROM,OPT_DELETE,OPT_RSYNC_PATH};
+      OPT_EXCLUDE_FROM,OPT_DELETE,OPT_RSYNC_PATH,OPT_CSUM_LENGTH};
 
 static char *short_options = "oblpguDCtcahvrIxne:B:";
 
 static struct option long_options[] = {
   {"version",     0,     0,    OPT_VERSION},
   {"server",      0,     0,    OPT_SERVER},
   {"sender",      0,     0,    OPT_SENDER},
   {"delete",      0,     0,    OPT_DELETE},
   {"exclude",     1,     0,    OPT_EXCLUDE},
   {"exclude-from",1,     0,    OPT_EXCLUDE_FROM},
   {"rsync-path",  1,     0,    OPT_RSYNC_PATH},
+  {"csum-length", 1,     0,    OPT_CSUM_LENGTH},
   {"one-file-system",0,  0,    'x'},
   {"ignore-times",0,     0,    'I'},
   {"help",        0,     0,    'h'},
   {"dry-run",     0,     0,    'n'},
   {"cvs-exclude", 0,     0,    'C'},
   {"archive",     0,     0,    'a'},
