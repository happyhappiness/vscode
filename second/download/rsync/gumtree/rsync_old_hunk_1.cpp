    fprintf(stderr,"receiver read %d\n",read_total());
  waitpid(pid, &status, 0);
  exit(status);
}


void usage(void)
{
  fprintf(stderr,"rsync version %s Copyright Andrew Tridgell and Paul Mackerras\n\n",VERSION);
  fprintf(stderr,"Usage:\t%s [options] src user@host:dest\nOR",RSYNC_NAME);
  fprintf(stderr,"\t%s [options] user@host:src dest\n\n",RSYNC_NAME);
  fprintf(stderr,"Options:\n");
  fprintf(stderr,"-v       : increase verbosity\n");
  fprintf(stderr,"-c       : always checksum\n");
  fprintf(stderr,"-a       : archive mode (same as -rlptDog)\n");
  fprintf(stderr,"-r       : recurse into directories\n");
  fprintf(stderr,"-b       : make backups (default ~ extension)\n");
  fprintf(stderr,"-u       : update only (don't overwrite newer files)\n");
  fprintf(stderr,"-l       : preserve soft links\n");
  fprintf(stderr,"-p       : preserve permissions\n");
  fprintf(stderr,"-o       : preserve owner (root only)\n");
  fprintf(stderr,"-g       : preserve group\n");
  fprintf(stderr,"-D       : preserve devices (root only)\n");
  fprintf(stderr,"-t       : preserve times\n");  
  fprintf(stderr,"-e cmd   : specify rsh replacement\n");
}


int main(int argc,char *argv[])
{
    int i, pid, status, pid2, status2;
    int opt;
    extern char *optarg;
    extern int optind;
    char *shell_cmd = NULL;
    char *shell_machine = NULL;
    char *shell_path = NULL;
    char *shell_user = NULL;
    char *p;
    int f_in,f_out;
    struct file_list *flist;
    char *local_name = NULL;

    starttime = time(NULL);

    while ((opt=getopt(argc, argv, "oblpguDtcahvSsre:B:")) != EOF)
      switch (opt) 
	{
	case 'h':
	  usage();
	  exit(0);

	case 'b':
	  make_backups=1;
	  break;

	case 'u':
	  update_only=1;
	  break;

#if SUPPORT_LINKS
	case 'l':
