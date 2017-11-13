int main(int argc,char *argv[])
{
    int pid, status = 0, status2 = 0;
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

    signal(SIGUSR1, sigusr1_handler);

    starttime = time(NULL);
    am_root = (getuid() == 0);

    /* we set a 0 umask so that correct file permissions can be
       carried across */
    orig_umask = (int)umask(0);

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

	case 'I':
	  ignore_times = 1;
	  break;

	case 'x':
	  one_file_system=1;
	  break;

	case OPT_DELETE:
	  delete_mode = 1;
	  break;

	case OPT_FORCE:
	  force_delete = 1;
	  break;

	case OPT_NUMERIC_IDS:
	  numeric_ids = 1;
	  break;

	case OPT_EXCLUDE:
	  add_exclude(optarg);
	  break;

	case OPT_EXCLUDE_FROM:
	  add_exclude_file(optarg,1);
	  break;

	case 'h':
	  usage(FINFO);
	  exit_cleanup(0);

	case 'b':
	  make_backups=1;
	  break;

	case 'n':
	  dry_run=1;
	  break;

	case 'S':
	  sparse_files=1;
	  break;

	case 'C':
	  cvs_exclude=1;
	  break;

	case 'u':
	  update_only=1;
	  break;

	case 'l':
	  preserve_links=1;
	  break;

	case 'L':
	  copy_links=1;
	  break;

	case 'W':
	  whole_file=1;
	  break;

	case 'H':
#if SUPPORT_HARD_LINKS
	  preserve_hard_links=1;
#else 
	  fprintf(FERROR,"ERROR: hard links not supported on this platform\n");
	  exit_cleanup(1);
#endif
	  break;

	case 'p':
	  preserve_perms=1;
	  break;

	case 'o':
	  preserve_uid=1;
	  break;

	case 'g':
	  preserve_gid=1;
	  break;

	case 'D':
	  preserve_devices=1;
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
	  if (am_root) {
	    preserve_devices=1;
	    preserve_uid=1;
	  }
	  break;

	case OPT_SERVER:
	  am_server = 1;
	  break;

	case OPT_SENDER:
	  if (!am_server) {
	    usage(FERROR);
	    exit_cleanup(1);
	  }
	  sender = 1;
	  break;

	case 'r':
	  recurse = 1;
	  break;

	case 'R':
	  relative_paths = 1;
	  break;

	case 'e':
	  shell_cmd = optarg;
	  break;

	case 'B':
	  block_size = atoi(optarg);
	  break;

	case OPT_TIMEOUT:
	  io_timeout = atoi(optarg);
	  break;

	case 'T':
		tmpdir = optarg;
		break;

        case 'z':
	  do_compression = 1;
	  break;

	default:
	  /* fprintf(FERROR,"bad option -%c\n",opt); */
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

#ifndef SUPPORT_LINKS
    if (!am_server && preserve_links) {
	    fprintf(FERROR,"ERROR: symbolic links not supported\n");
	    exit_cleanup(1);
    }
#endif

    if (am_server) {
      setup_protocol(STDOUT_FILENO,STDIN_FILENO);
	
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
      usage(FERROR);
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
      fprintf(FINFO,"cmd=%s machine=%s user=%s path=%s\n",
	      shell_cmd?shell_cmd:"",
	      shell_machine?shell_machine:"",
	      shell_user?shell_user:"",
	      shell_path?shell_path:"");
    }
    
    if (!sender && argc != 1) {
      usage(FERROR);
      exit_cleanup(1);
    }

    pid = do_cmd(shell_cmd,shell_machine,shell_user,shell_path,&f_in,&f_out);

    setup_protocol(f_out,f_in);

#if HAVE_SETLINEBUF
    setlinebuf(FINFO);
    setlinebuf(FERROR);
#endif

    if (verbose > 3) 
      fprintf(FINFO,"parent=%d child=%d sender=%d recurse=%d\n",
	      (int)getpid(),pid,sender,recurse);

    if (sender) {
      if (cvs_exclude)
	add_cvs_excludes();
      if (delete_mode) 
	send_exclude_list(f_out);
      flist = send_file_list(f_out,argc,argv);
      if (verbose > 3) 
	fprintf(FINFO,"file list sent\n");
      send_files(flist,f_out,f_in);
      if (verbose > 3)
	fprintf(FINFO,"waiting on %d\n",pid);
      waitpid(pid, &status, 0);
      report(-1);
      exit_cleanup(status);
    }

    send_exclude_list(f_out);

    flist = recv_file_list(f_in);
    if (!flist || flist->count == 0) {
      fprintf(FINFO,"nothing to do\n");
      exit_cleanup(0);
    }

    local_name = get_local_name(flist,argv[0]);

    status2 = do_recv(f_in,f_out,flist,local_name);

    report(f_in);

    waitpid(pid, &status, 0);

    return status | status2;
}