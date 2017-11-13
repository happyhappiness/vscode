int main(int argc,char *argv[])
{
    int pid, status, pid2, status2;
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

    checksum_init();

    while ((opt = getopt_long(argc, argv, 
			      short_options, long_options, &option_index)) 
	   != -1) {
      switch (opt) 
	{
	case OPT_VERSION:
	  printf("rsync version %s  protocol version %d\n",
		 VERSION,PROTOCOL_VERSION);
	  exit_cleanup(0);

	case OPT_SUFFIX:
	  backup_suffix = optarg;
	  break;

	case OPT_RSYNC_PATH:
	  rsync_path = optarg;
	  break;

	case OPT_CSUM_LENGTH:
	  csum_length = atoi(optarg);
	  csum_length = MIN(csum_length,SUM_LENGTH);
	  break;

	case 'I':
	  ignore_times = 1;
	  break;

	case 'x':
	  one_file_system=1;
	  break;

	case OPT_DELETE:
	  delete_mode = 1;
	  break;

	case OPT_EXCLUDE:
	  add_exclude(optarg);
	  break;

	case OPT_EXCLUDE_FROM:
	  add_exclude_file(optarg,1);
	  break;

	case 'h':
	  usage(stdout);
	  exit_cleanup(0);

	case 'b':
	  make_backups=1;
	  break;

	case 'n':
	  dry_run=1;
	  break;

	case 'C':
	  cvs_exclude=1;
	  break;

	case 'u':
	  update_only=1;
	  break;

#if SUPPORT_LINKS
	case 'l':
	  preserve_links=1;
	  break;
#endif

	case 'p':
	  preserve_perms=1;
	  break;

	case 'o':
	  if (getuid() == 0) {
	    preserve_uid=1;
	  } else {
	    fprintf(stderr,"-o only allowed for root\n");
	    exit_cleanup(1);
	  }
	  break;

	case 'g':
	  preserve_gid=1;
	  break;

	case 'D':
	  if (getuid() == 0) {
	    preserve_devices=1;
	  } else {
	    fprintf(stderr,"-D only allowed for root\n");
	    exit_cleanup(1);
	  }
	  break;

	case 't':
	  preserve_times=1;
	  break;

	case 'c':
	  always_checksum=1;
	  break;

	case 'v':
	  verbose++;
	  break;

	case 'a':
	  recurse=1;
#if SUPPORT_LINKS
	  preserve_links=1;
#endif
	  preserve_perms=1;
	  preserve_times=1;
	  preserve_gid=1;
	  if (getuid() == 0) {
	    preserve_devices=1;
	    preserve_uid=1;
	  }	    
	  break;

	case OPT_SERVER:
	  am_server = 1;
	  break;

	case OPT_SENDER:
	  if (!am_server) {
	    usage(stderr);
	    exit_cleanup(1);
	  }
	  sender = 1;
	  break;

	case 'r':
	  recurse = 1;
	  break;

	case 'e':
	  shell_cmd = optarg;
	  break;

	case 'B':
	  block_size = atoi(optarg);
	  break;

	default:
	  fprintf(stderr,"bad option -%c\n",opt);
	  exit_cleanup(1);
	}
    }

    while (optind--) {
      argc--;
      argv++;
    }

    signal(SIGCHLD,SIG_IGN);
    signal(SIGINT,SIGNAL_CAST sig_int);
    signal(SIGPIPE,SIGNAL_CAST sig_int);
    signal(SIGHUP,SIGNAL_CAST sig_int);

    if (dry_run)
      verbose = MAX(verbose,1);

    if (am_server) {
      remote_version = read_int(STDIN_FILENO);
      if (remote_version < MIN_PROTOCOL_VERSION ||
	  remote_version > MAX_PROTOCOL_VERSION) {
	fprintf(stderr,"protocol version mismatch - is your shell clean?\n");
	exit_cleanup(1);
      }
      write_int(STDOUT_FILENO,PROTOCOL_VERSION);
      write_flush(STDOUT_FILENO);

      setup_protocol();
	
      if (sender) {
	recv_exclude_list(STDIN_FILENO);
	if (cvs_exclude)
	  add_cvs_excludes();
	do_server_sender(argc,argv);
      } else {
	do_server_recv(argc,argv);
      }
      exit_cleanup(0);
    }

    if (argc < 2) {
      usage(stderr);
      exit_cleanup(1);
    }

    p = strchr(argv[0],':');

    if (p) {
      sender = 0;
      *p = 0;
      shell_machine = argv[0];
      shell_path = p+1;
      argc--;
      argv++;
    } else {
      sender = 1;

      p = strchr(argv[argc-1],':');
      if (!p) {
	local_server = 1;
      }

      if (local_server) {
	shell_machine = NULL;
	shell_path = argv[argc-1];
      } else {
	*p = 0;
	shell_machine = argv[argc-1];
	shell_path = p+1;
      }
      argc--;
    }

    if (shell_machine) {
      p = strchr(shell_machine,'@');
      if (p) {
	*p = 0;
	shell_user = shell_machine;
	shell_machine = p+1;
      }
    }

    if (verbose > 3) {
      fprintf(stderr,"cmd=%s machine=%s user=%s path=%s\n",
	      shell_cmd?shell_cmd:"",
	      shell_machine?shell_machine:"",
	      shell_user?shell_user:"",
	      shell_path?shell_path:"");
    }
    
    if (!sender && argc != 1) {
      usage(stderr);
      exit_cleanup(1);
    }

    pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,&f_in,&f_out);

    write_int(f_out,PROTOCOL_VERSION);
    write_flush(f_out);
    {
      remote_version = read_int(f_in);
      if (remote_version < MIN_PROTOCOL_VERSION ||
	  remote_version > MAX_PROTOCOL_VERSION) {
	fprintf(stderr,"protocol version mismatch - is your shell clean?\n");
	exit_cleanup(1);
      }	
    }

    setup_protocol();

    if (verbose > 3) 
      fprintf(stderr,"parent=%d child=%d sender=%d recurse=%d\n",
	      (int)getpid(),pid,sender,recurse);

    if (sender) {
      if (cvs_exclude)
	add_cvs_excludes();
      if (delete_mode) 
	send_exclude_list(f_out);
      flist = send_file_list(f_out,recurse,argc,argv);
      if (verbose > 3) 
	fprintf(stderr,"file list sent\n");
      send_files(flist,f_out,f_in);
      if (verbose > 3)
	fprintf(stderr,"waiting on %d\n",pid);
      waitpid(pid, &status, 0);
      report(-1);
      exit_cleanup(status);
    }

    send_exclude_list(f_out);

    flist = recv_file_list(f_in);
    if (!flist || flist->count == 0) {
      fprintf(stderr,"nothing to do\n");
      exit_cleanup(0);
    }

    local_name = get_local_name(flist,argv[0]);

    if ((pid2=fork()) == 0) {
      recv_files(f_in,flist,local_name);
      if (verbose > 1)
	fprintf(stderr,"receiver read %d\n",read_total());
      exit_cleanup(0);
    }

    generate_files(f_out,flist,local_name);

    waitpid(pid2, &status2, 0);

    report(f_in);

    waitpid(pid, &status, 0);

    return status | status2;
}