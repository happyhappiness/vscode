void parse_arguments(int argc, char *argv[])
{
    int opt;
    int option_index;

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
	  rprintf(FERROR,"ERROR: hard links not supported on this platform\n");
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
	  am_sender = 1;
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

	case OPT_DAEMON:
		am_daemon = 1;
		break;

	case OPT_CONFIG:
		config_file = optarg;
		break;

	case OPT_PORT:
		rsync_port = atoi(optarg);
		break;

	default:
	  /* rprintf(FERROR,"bad option -%c\n",opt); */
	  exit_cleanup(1);
	}
    }
}