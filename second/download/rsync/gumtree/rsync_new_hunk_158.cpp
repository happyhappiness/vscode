  fprintf(f,"the block size defaults to %d\n",BLOCK_SIZE);  
}

enum {OPT_VERSION,OPT_SUFFIX,OPT_SENDER,OPT_SERVER,OPT_EXCLUDE,
      OPT_EXCLUDE_FROM,OPT_DELETE,OPT_RSYNC_PATH,OPT_CSUM_LENGTH};

static char *short_options = "oblHpguDCtcahvrIxnSe:B:";

static struct option long_options[] = {
  {"version",     0,     0,    OPT_VERSION},
  {"server",      0,     0,    OPT_SERVER},
  {"sender",      0,     0,    OPT_SENDER},
  {"delete",      0,     0,    OPT_DELETE},
