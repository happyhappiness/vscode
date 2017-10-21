
  fprintf(f,"\n");
  fprintf(f,"the backup suffix defaults to %s\n",BACKUP_SUFFIX);
  fprintf(f,"the block size defaults to %d\n",BLOCK_SIZE);  
}

enum {OPT_VERSION,OPT_SUFFIX,OPT_SENDER,OPT_SERVER,OPT_EXCLUDE,
      OPT_EXCLUDE_FROM};

static char *short_options = "oblpguDCtcahvrne:B:";

static struct option long_options[] = {
  {"version",     0,     0,    OPT_VERSION},
  {"server",      0,     0,    OPT_SERVER},
