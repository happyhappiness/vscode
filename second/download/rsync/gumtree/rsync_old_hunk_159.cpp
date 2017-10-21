
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
