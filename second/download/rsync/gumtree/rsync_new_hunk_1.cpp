    fprintf(stderr,"receiver read %d\n",read_total());
  waitpid(pid, &status, 0);
  exit(status);
}


static void usage(FILE *f)
{
  fprintf(f,"rsync version %s Copyright Andrew Tridgell and Paul Mackerras\n\n",
	  VERSION);
  fprintf(f,"Usage:\t%s [options] src user@host:dest\nOR",RSYNC_NAME);
  fprintf(f,"\t%s [options] user@host:src dest\n\n",RSYNC_NAME);
  fprintf(f,"Options:\n");
  fprintf(f,"-v, --verbose            increase verbosity\n");
  fprintf(f,"-c, --checksum           always checksum\n");
  fprintf(f,"-a, --archive            archive mode (same as -rlptDog)\n");
  fprintf(f,"-r, --recursive          recurse into directories\n");
  fprintf(f,"-b, --backup             make backups (default ~ extension)\n");
  fprintf(f,"-u, --update             update only (don't overwrite newer files)\n");
  fprintf(f,"-l, --links              preserve soft links\n");
  fprintf(f,"-p, --perms              preserve permissions\n");
  fprintf(f,"-o, --owner              preserve owner (root only)\n");
  fprintf(f,"-g, --group              preserve group\n");
  fprintf(f,"-D, --devices            preserve devices (root only)\n");
  fprintf(f,"-t, --times              preserve times\n");  
  fprintf(f,"-B, --block-size SIZE    checksum blocking size\n");  
  fprintf(f,"-e, --rsh COMMAND        specify rsh replacement\n");
  fprintf(f,"-C, --cvs-exclude        auto ignore files in the same way CVS does\n");
  fprintf(f,"    --exclude FILE       exclude file FILE\n");
  fprintf(f,"    --exclude-from FILE  exclude files listed in FILE\n");
  fprintf(f,"    --suffix SUFFIX      override backup suffix\n");  
  fprintf(f,"    --version            print version number\n");  

  fprintf(f,"\n");
  fprintf(f,"the backup suffix defaults to %s\n",BACKUP_SUFFIX);
  fprintf(f,"the block size defaults to %d\n",BLOCK_SIZE);  
}

enum {OPT_VERSION,OPT_SUFFIX,OPT_SENDER,OPT_SERVER,OPT_EXCLUDE,OPT_EXCLUDE_FROM};

static char *short_options = "oblpguDCtcahvre:B:";

static struct option long_options[] = {
  {"version",     0,     0,    OPT_VERSION},
  {"server",      0,     0,    OPT_SERVER},
  {"sender",      0,     0,    OPT_SENDER},
  {"exclude",     1,     0,    OPT_EXCLUDE},
  {"exclude-from",1,     0,    OPT_EXCLUDE_FROM},
  {"help",        0,     0,    'h'},
  {"cvs-exclude", 0,     0,    'C'},
  {"archive",     0,     0,    'a'},
  {"checksum",    0,     0,    'c'},
  {"backup",      0,     0,    'b'},
  {"update",      0,     0,    'u'},
  {"verbose",     0,     0,    'v'},
  {"recursive",   0,     0,    'r'},
  {"devices",     0,     0,    'D'},
  {"perms",       0,     0,    'p'},
  {"links",       0,     0,    'l'},
  {"owner",       0,     0,    'o'},
  {"group",       0,     0,    'g'},
  {"times",       0,     0,    't'},
  {"rsh",         1,     0,    'e'},
  {"suffix",      1,     0,    OPT_SUFFIX},
  {"block-size",  1,     0,    'B'},
  {0,0,0,0}};

int main(int argc,char *argv[])
{
    int i, pid, status, pid2, status2;
    int opt;
    int option_index;
    char *shell_cmd = NULL;
    char *shell_machine = NULL;
    char *shell_path = NULL;
    char *shell_user = NULL;
    char *p;
    int f_in,f_out;
    struct file_list *flist;
    char *local_name = NULL;

    starttime = time(NULL);

    while ((opt = getopt_long(argc, argv, 
			      short_options, long_options, &option_index)) 
	   != -1)
      switch (opt) 
	{
	case OPT_VERSION:
	  printf("rsync version %s  protocol version %d\n",
		 VERSION,PROTOCOL_VERSION);
	  exit(0);

	case OPT_SUFFIX:
	  backup_suffix = optarg;
	  exit(0);

	case OPT_EXCLUDE:
	  add_exclude(optarg);
	  break;

	case OPT_EXCLUDE_FROM:
	  add_exclude_file(optarg);
	  break;

	case 'h':
	  usage(stdout);
	  exit(0);

	case 'b':
	  make_backups=1;
	  break;

	case 'C':
	  cvs_exclude=1;
	  break;

	case 'u':
	  update_only=1;
	  break;

#if SUPPORT_LINKS
	case 'l':
